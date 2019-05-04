#define _CRT_SECURE_NO_WARNINGS
// Kursovaya.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <cstdlib>
#include "pch.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stddef.h>
#include <algorithm>




#define admins_pr "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\admins_profile.txt"
#define users_pr "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\users_profile.txt.txt"
//#define product_in_stock "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\product_in_stock.txt"
//#define product_in_order "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\product_in_order.txt"
#define shops "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\shops.txt"

#define scanf scanf_s
#define printf printf_s
#define pause system("pause");       //для упрощения написания,вместо system("pause"),пишем pause;
#define cls system("cls");  // для упрощения написания,вместо system("cls"),пишем cls;
const int N = 50; //максимальное количество записей

bool IS_AUTHORIZATION = false; //перед релизом поменять на true!!!11!!!11!!!!!!

using namespace std;


FILE *F1;
FILE *F2;

struct Date //структура для хранения даты
{
	int day;  // день
	int month;// месяц
	int year; //год
	char date_format[30]; //формат даты XX.XX.XXXX

};
struct User //cтруктура пользователь
{
	char login[8]; // логин
	char password[8]; // пароль
	char first_name[20]; // имя
	char last_name[20]; // фамилия
	char middle_name[20]; // отчество
	int tel_nomber; // номер телефона
};
struct ProductsInStock //структура продукта, который есть в магазине
{
	int ID;//ID продукта
	int cost;// стоимость
	int quantity; //количество продуктов
	char brand[20]; //марка продукта
	char name[20]; // название продукта
	char description[20]; //характеристика продукта(молоко-козье,хлеб-чёрный)
	char quan_descr[20]; // количественная характеристика продуктов(вес,объём)
	Date expiration_date; // срок годности
	Date delivery_date; //дата доставки(при наличии его в магазине)
	

};


struct ProductsInOrder // продукт , который будет заказан
{
	int ID;//ID продукта
	char name[20]; //название продукта
	char brand[20]; // марка продуктов
	int quantity; //количество продутов
	Date order_date; //дата доставки

};


struct Shop //структура хранения данных о магазине
{
	int ID; //ID
	char name[20]; //название магазина
	char adress[20]; //адрес магазина
	int contact_tel_nomber;// контактный телефон
	ProductsInStock products_in_stock[N]; // Продукт ,который есть в магазине
	ProductsInOrder products_in_order[N]; // Продукт, который будет заказан
};

//ProductsInStock mas_in_stock[N]; // массив для записей
Shop mas_shop[N]; 

void selection_menu();//меню авторизации
void welcome_menu(void);//текст меню авторизации
int autorisation_admin();//авторизация админа
int autorisation_user();//авторизация юзера
void view_admin_menu();//текст меню выбора для администратора
void view_user_menu();//текст меню выбора для пользователя
void admin_menu();//меню администратора
void user_menu();//меню пользователя
//void add_user(); //добавление информации о пользователях - регистрация пользователяя лишняя
void add_product_in_stock(ProductsInStock* mas_in_stock);
void add_product_in_order(ProductsInOrder* mas_in_order);
void view_menu_delete();//удаление записи
void delete_all_shops(); //удаление всех магазинов
void delete_all_p_stock();//удаление всех продуктов, которые есть в магазине
void delete_all_p_order();//удаление всех продуктов, которые будут заказаны
void edit_menu();//изменение записи
void show_elements();//просмотр
void menu_search_product();//поиск продукта
void sort_menu_view();// меню сортировки
void sort_menu();//сортировка
void control_users();//управление пользователями
int int_checker();//проверка на значение
int check_date(char* str); //проверка на дату
void add_shop(); // добавление магазина
void view_print_menu(); // меню добавления магазина
void print_all_shops(); //печать всех магазинов
void print_all_products_in_stock(); //печать всех продуктов, которые есть в магазине
void print_all_products_in_order(); //печать всех продуктов, которые будут заказаны
void load_db(); //база данных
void main_task();//основная задача 
void work_with_file();//работа с файлом
void show_all_users();// показать всех существующих пользователей
void delete_user(); // удаление пользователя
void delete_one_record(); //удаление одной записи
void del_one_shop();//удаление одного магазина
void del_one_p_stock();//удаление одного продукта,который есть в магазине
void del_one_p_order();//удаление одного продукта,который будет заказан
int index_by_id(Shop* mas_shop_index, int ID);
void print_products_in_stock(Shop );
int index_by_id(ProductsInStock* mas_product_in_stock_index, int ID);
void del_from_shop(Shop* mas_shop, int t);
void del_from_product_in_stock(ProductsInStock* mas_in_stock, int t);
void del_from_product_in_order(ProductsInOrder* mas_in_order, int t);
int index_by_id(ProductsInOrder* mas_product_in_order_index, int ID);
void print_products_in_order(Shop mas_shop);
void sort_by_shop_name(Shop* tmp, int srt);
void save_all_p_in_stock_in_vector(Shop* shop_mass, vector<ProductsInStock>& products_vector);
void sort_by_products_name(vector<ProductsInStock>& products_vector);
void print_sort_products(vector<ProductsInStock>& products_vector);
int main()
{
	setlocale(LC_ALL, "Rus"); 
	load_db();
	selection_menu();
}

void load_db() {
	int j;
	FILE* fadd;
	F1 = fopen(shops, "a+");
	fclose(F1);
	fadd = fopen(shops, "r+");
	for (j = 0; (fread(&mas_shop[j], sizeof(struct Shop), 1, F1)) != 0; j++);
	fclose(fadd);
}

void welcome_menu(void) {
	printf("Здравствуйте!\n");
	printf("1. Вход под администратором. \n");
	printf("2. Вход под пользователем. \n");
	//printf("3. Регистрация");
	printf("0. Выход. \n");
	printf("Выберите один из вышеперечисленных пунктов: \n");
}

void selection_menu() {
	bool flag = false;
	do {
		cls;
		welcome_menu();

		switch (_getch())
		{
		case '0': {
			cls
				printf("До свидания!");
			flag = true;
			break;
		}
		case '1': {
			if (IS_AUTHORIZATION) {
				autorisation_admin();
			}
			else {
				admin_menu();
			}
			
			break;
		}
		case '2': {
			if (IS_AUTHORIZATION) {
				autorisation_user();
			}
			else {
				user_menu();
			}
			
			break;
		}
		default:
			cls;
			break;
		}

	} while (!flag);
}

int autorisation_admin() {
	int counter = 0;
	puts("Вход под администратором.\n");
	char password[20], file_password[20];
	int i = 0;
	puts("Для ввода пароля у Вас есть 3 попытки.");
	
	FILE *F1 = fopen(admins_pr, "r");
	printf("Введите пароль: ");
	fscanf(F1, "%s", file_password);
	counter = 0;
	do {
		fflush(stdin);
		for (i = 0; (password[i] = _getch()) != '\r' && i < 19;) {
			fflush(stdin);
			if (password[i] == '\b' && i != 0) {
				printf("%s", "\b \b");
				i--;
			}
			else if (password[i] != '\b' && password[i] != '\0') {
				printf("%c", '*');
				i++;
			}
		}
		//когда исчерпает попытки -> завершать работу
		password[i] = '\0';
		if (strcmp(password, file_password)) {
			counter++;
			if (counter == 3) {
				puts("\nВы исчерпали свои попытки.");
				_getch();
				return 1;
			}
			printf("\nПароль введен неверно. Оставшееся количество попыток для ввода пароля: %d.\nПовторите пароль для входа в систему: ", 3 - counter);
		}
		else break;
	} while (1);
	fclose(F1);
	cls;
	admin_menu();
	return 0;
	cls;
}

int autorisation_user() {
		system("cls");
		int counter = 0;
		char login[20], file_login[20];
		char password[20], file_password[20];
		int sch = 0;
		int i = 0;

		FILE *F2 = fopen(users_pr, "r+");
		fscanf(F2, "%s", file_login);
		if (feof(F2)) {
			puts("Ни один пользователь не создан.");
			system("pause");
			fclose(F2);
			return 0;
		}

		puts("---Вход под пользователем---");

		puts("Для ввода логина и пароля у Вас есть 3 попытки.");
		do {
			printf("Введите логин: ");
			fflush(stdin);
			scanf_s("%s", login, 20);
			
			printf("Введите пароль: ");
			for (i = 0; (password[i] = _getch()) != '\r' && i < 19;) {
				fflush(stdin);
				if (password[i] == '\b' && i != 0) {
					printf("%s", "\b \b");
					i--;
				}
				else if (password[i] != '\b' && password[i] != '\0') {
					printf("%c", '*');
					i++;
				}
			}
			password[i] = '\0';
			sch = 0;
			rewind(F2);
			do {
				fscanf(F2, "%s%s", file_login, file_password);
				if (feof(F2)) {
					break;
				}
				if (!strcmp(login, file_login)) {                   
					//Найден такой же логин, как тот что ввел пользователь
					sch = 1;
					break;
				}
			} while (1);
			if (sch == 0) {
				counter++;
				if (counter == 3) {
					puts("\nВы исчерпали свои попытки.");
					_getch();
					return 0;
				}
				printf("\nЛогина \"%s\" нет. Оставшееся количество попыток для ввода логина: %d.\nПовторите ввод.\n", login, 3 - counter);
			}
			else break;
		} while (1);
		fclose(F2);
		counter = 0;

		do {
			if (strcmp(password, file_password)) {                            
				//Если пароль введенный пользователем не совпадает с нужным паролем                          
				counter++;
				if (counter == 3) {
					puts("\nВы исчерпали свои попытки.");
					_getch();
					return 0;
				}
				printf("\nНеверный пароль. Оставшееся количество попыток для ввода пароля: %d.\nПовторите пароль: ", 3 - counter);
			}
			else {
				break;
			}
			fflush(stdin);
			for (i = 0; (password[i] = _getch()) != '\r' && i < 19;) {
				fflush(stdin);
				if (password[i] == '\b' && i != 0 && password[i] != '\0') {
					printf("%s", "\b \b");
					i--;
				}
				else if (password[i] != '\b' && password[i] != '\0') {
					printf("%c", '*');
					i++;
				}
			}
			password[i] = '\0';
		} while (1);
		//cls;
		view_user_menu();
		return 1;

	}

void view_admin_menu()
{
	cls;
	printf("Меню администратора. Выполняемая операция:\n");
	printf("1.Добавить запись о магазине \n");
	printf("2.Удаление записи \n");
	printf("3.Изменение записи \n");
	printf("4.Просмотр в табличной форме \n");
	printf("5.Поиск продукта \n");
	printf("6.Сортировка \n");
	printf("7.Управление пользователями \n");
	printf("8.Работа с файлом \n");
	printf("9.Задача \n");
	printf("0.Выйти в главное меню \n");
}

void view_user_menu()
{
	cout << "Меню пользователя. Выполняемая операция: " << endl;
	cout << "1.Просмотр в табличной форме" << endl;
	cout << "2.Поиск продукта" << endl;
	cout << "3.Сортировка продуктов " << endl;
	cout << "4.Задача " << endl;
	cout << "0.Выйти в главное меню" << endl;
}

void admin_menu()
{

	bool flag = false;
	do
	{
		cls;
		view_admin_menu();
		cin.clear();
		char ans;
		cin >> ans;
		switch (ans)
		{
		case '0': {cls;
			printf("До свидания!\n");
			flag = true;
			break; }
		case '1': {cls;		add_shop();		break;  	}
		case '2': {cls; 	view_menu_delete();		break;   }
		case '3': {cls; 	edit_menu();  	break;	}
		case '4': {cls; 	view_print_menu();		break;	}
		case '5': {cls; 	menu_search_product();		break;	}
		case '6': {cls; 	sort_menu();		break;	}
		case '7': {cls;      control_users(); break; }
		case'8': {cls;      work_with_file(); break; }
		case '9': {cls;     main_task(); break; }
		default:  cls;
			printf("Такого пункта меню нет!\n");
			pause;
			break;
		}

	} while (!flag);
}

void user_menu()
{
	bool flag = false;
	do
	{
		cls;
		view_user_menu();
		cin.clear();
		char ans;
		cin >> ans;
		switch (ans)
		{
		case '0': {cls;
			printf("До свидания!\n");
			flag = true;
			break; }
		case '1': {cls;		view_print_menu();		break;  	}
		case '2': {cls; 	menu_search_product();		break;   }
		case '3': {cls; 	sort_menu();  	break;	}
		case '4': {cls; 	main_task();		break;	}
		
		default:  cls;
			printf("Такого пункта меню нет!\n");
			pause;
			break;
		}

	} while (!flag);
}

void edit_menu() {}


void menu_search_product() {}

//добавление магазина и продуктов в нём
void add_shop() {
	FILE* fadd;
	char o[1] = { '\0' };
	int i = 0, j = 0, g = 0;
	char ch;
	do {
		ch = '0';
		F1 = fopen(shops, "a+");
		fclose(F1);
		fadd = fopen(shops, "r+");
		for (j = 0; (fread(&mas_shop[j], sizeof(struct Shop), 1, F1)) != 0; j++);
		fclose(fadd);
		i = j;
		int id;
		bool flag1 = true, flag2;
		do
		{
			flag2 = true;
			std::cout << "Введите ID магазина (Должен быть уникальным):" << endl;
			fflush(stdin);
			//cin >> id; // проверку на ввод вставить
			id = int_checker();
			for (int t = 0; t < j; t++)
			{
				if (id == mas_shop[t].ID) {
					flag2 = false;
					break;
				}
			}
			if (flag2 == false) {
				cout << "Такой ID уже существует! Введите другой!" << endl;
				flag1 = true;
			}
			else
			{
				mas_shop[i].ID = id;
				flag1 = false;
			}

		} while (flag1 != false);

		while (g == 0) {
			fflush(stdin);
			cout << "Введите название магазина, который вы хотите добавить:" << endl;
			gets_s(mas_shop[i].name, 20);
			if (strcmp(mas_shop[i].name, o) != 0)
				g = 1;
		}
		g = 0;
		while (g == 0) {
			fflush(stdin);
			cout << "Введите адрес магазина: " << endl;
			gets_s(mas_shop[i].adress, 20);
			if (strcmp(mas_shop[i].adress, o) != 0)
				g = 1;
		}
		fflush(stdin);
		cout << "Введите контактный телефон магазина: " << endl;
		mas_shop[i].contact_tel_nomber = int_checker();

	cout << "Введите информацию о продуктах в магазине:" << endl;
	add_product_in_stock(mas_shop[i].products_in_stock);

	cout << "Введите информацию о заказных продуктах:" << endl;
	add_product_in_order(mas_shop[i].products_in_order);


	fadd = fopen(shops, "a+");
	fwrite(&mas_shop[i], sizeof(struct Shop), 1, fadd);
	fclose(fadd);
	cout << "Если Вы хотите добавить ещё одну запись,то нажмите 1." << endl;
	cout << "Если нет,то нажмите любую клавишу." << endl;
	ch = _getwch();
	if (ch == '1') {
		i++;
	}
	} while (ch == '1');
}

//добавление продуктов ,которые есть в магазине
void add_product_in_stock(ProductsInStock* mas_in_stock)
{
	char o[1] = { '\0' };
	int i = 0, j = 0, g = 0;
	char ch;
	do {
		ch = '0';
		for (j = 0; mas_in_stock[j].ID != 0; j++);
		i = j;
		int id;
		bool flag1 = true, flag2;
		do
		{
			flag2 = true;
			cout << "Введите ID продукта (Должен быть уникальным):" << endl;
			fflush(stdin);
			//cin >> id; // проверку на ввод вставить
			id = int_checker();
			for (int t = 0; t < j - 1; t++)
			{
				if (id == mas_in_stock[t].ID) {
					flag2 = false;
					break;
				}
			}
			if (flag2 == false) {
				cout << "Такой ID уже существует! Введите другой!" << endl;
				flag1 = true;
			}
			else
			{
				mas_in_stock[i].ID = id;
				flag1 = false;
			}

		} while (flag1 != false);

		while (g == 0) {
			fflush(stdin);
			cout << "Введите название продукта, который вы хотите добавить:" << endl;
			gets_s(mas_in_stock[i].name, 20);
			if (strcmp(mas_in_stock[i].name, o) != 0)
				g = 1;
		}
		g = 0;
		fflush(stdin);
		cout << "Введите стоимость продукта (в белорусских рублях):" << endl;
		mas_in_stock[i].cost = int_checker();

		fflush(stdin);
		cout << "Введите количество продуктов (единиц):" << endl;
		mas_in_stock[i].quantity = int_checker();
	
		
			fflush(stdin);
			while (g == 0) {
				fflush(stdin);
				cout << "Введите название марки продукта: " << endl;
				gets_s(mas_in_stock[i].brand, 20);
				if (strcmp(mas_in_stock[i].brand, o) != 0)
					g = 1;
			}
			g = 0;
			fflush(stdin);

			while (g == 0) {
				fflush(stdin);
				cout << "Введите характеристику продукта:" << endl;
				gets_s(mas_in_stock[i].description, 20);
				if (strcmp(mas_in_stock[i].description, o) != 0)
					g = 1;
			}
			g = 0;
			fflush(stdin);

			while (g == 0) {
				fflush(stdin);
				cout << "Введите весовую характеристику продукта(объём, количество(грамм)):" << endl;
				gets_s(mas_in_stock[i].quan_descr, 20);
				if (strcmp(mas_in_stock[i].quan_descr, o) != 0)
					g = 1;
			}
			g = 0;
			fflush(stdin);

			bool flag3 = true;
			while (flag3)
			{
				cout << "Введите дату срока годности продукта(Формат ввода : XX.XX.XXXX)  :" << endl;
				char check[30];
				fflush(stdin);
				cin >> check;
				if (check_date(check)) {
					flag3 = false;
					strcpy(mas_in_stock[i].expiration_date.date_format, check);
					int d = 0;
					char dd[3], mm[3], yyyy[5];
					for (; d < 2; d++)
						dd[d] = check[d];
					dd[2] = '\0';
					mas_in_stock[i].expiration_date.day = atoi(dd);

					for (int j = 0, d = 3; d < 5; d++, j++) {
						mm[j] = check[d];
					}
					mm[2] = '\0';
					mas_in_stock[i].expiration_date.month = atoi(mm);
					for (int j = 0, d = 6; d < (int)strlen(check) + 1; d++, j++) {
						yyyy[j] = check[d];
					}
					yyyy[4] = '\0';
					mas_in_stock[i].expiration_date.year = atoi(yyyy);

				}
			}

			flag3 = true;
			while (flag3)
			{
				cout << "Введите дату доставки продукта(Формат ввода : XX.XX.XXXX)  :" << endl;
				char check[30];
				fflush(stdin);
				cin >> check;
				int ans = check_date(check);
				if (ans) {
					flag3 = false;
					strcpy(mas_in_stock[i].delivery_date.date_format, check);
					int d = 0;
					char dd[3], mm[3], yyyy[5];
					for (; d < 2; d++)
						dd[d] = check[d];
					dd[2] = '\0';
					mas_in_stock[i].delivery_date.day = atoi(dd);

					for (int j = 0, d = 3; d < 5; d++, j++) {
						mm[j] = check[d];
					}
					mm[2] = '\0';
					mas_in_stock[i].delivery_date.month = atoi(mm);
					for (int j = 0, d = 6; d < (int)strlen(check) + 1; d++, j++) {
						yyyy[j] = check[d];
					}
					yyyy[4] = '\0';
					mas_in_stock[i].delivery_date.year = atoi(yyyy);

				}
			}


			/*fadd1 = fopen(product_in_stock, "a+");
			fwrite(&mas_in_stock[i], sizeof(struct ProductsInStock), 1, fadd1);
			fclose(fadd1);*/
			cout << "Если Вы хотите добавить ещё одну запись,то нажмите 1." << endl;
			cout << "Если нет,то нажмите любую клавишу." << endl;
			cin.clear();
			cin >> ch;
			if (ch == '1') {
				i++;
			}
		} while (ch == '1');
}

//добавление продуктов ,которые будут заказаны
void add_product_in_order(ProductsInOrder* mas_in_order) {
	char o[1] = { '\0' };
	int i = 0, j = 0, g = 0;
	char ch;
	do {
		ch = '0';
		for (j = 0; mas_in_order[j].ID != 0; j++);
		i = j;
		int id;
		bool flag1 = true, flag2;
		do
		{
			flag2 = true;
			cout << "Введите ID продукта (Должен быть уникальным):" << endl;
			fflush(stdin);
			//cin >> id; // проверку на ввод вставить
			id = int_checker();
			for (int t = 0; t < j - 1; t++)
			{
				if (id == mas_in_order[t].ID) {
					flag2 = false;
					break;
				}
			}
			if (flag2 == false) {
				cout << "Такой ID уже существует! Введите другой!" << endl;
				flag1 = true;
			}
			else
			{
				mas_in_order[i].ID = id;
				flag1 = false;
			}

		} while (flag1 != false);

		while (g == 0) {
			fflush(stdin);
			cout << "Введите название продукта, который вы хотите добавить:" << endl;
			gets_s(mas_in_order[i].name, 20);
			if (strcmp(mas_in_order[i].name, o) != 0)
				g = 1;
		}
		g = 0;

		fflush(stdin);
		while (g == 0) {
			fflush(stdin);
			cout << "Введите название марки продукта поставки: " << endl;
			gets_s(mas_in_order[i].brand, 20);
			if (strcmp(mas_in_order[i].brand, o) != 0)
				g = 1;
		}
		g = 0;
		fflush(stdin);
		

		fflush(stdin);
		cout << "Введите количество продуктов для поставки (единиц):" << endl;
		mas_in_order[i].quantity = int_checker();


		bool flag3 = true;
		while (flag3)
		{
			cout << "Введите дату доставки продукта(Формат ввода : XX.XX.XXXX)  :" << endl;
			char check[30];
			fflush(stdin);
			cin >> check;
			int ans = check_date(check);
			if (ans) {
				flag3 = false;
				strcpy(mas_in_order[i].order_date.date_format, check);
				int d = 0;
				char dd[3], mm[3], yyyy[5];
				for (; d < 2; d++)
					dd[d] = check[d];
				dd[2] = '\0';
				mas_in_order[i].order_date.day = atoi(dd);

				for (int j = 0, d = 3; d < 5; d++, j++) {
					mm[j] = check[d];
				}
				mm[2] = '\0';
				mas_in_order[i].order_date.month = atoi(mm);
				for (int j = 0, d = 6; d < (int)strlen(check) + 1; d++, j++) {
					yyyy[j] = check[d];
				}
				yyyy[4] = '\0';
				mas_in_order[i].order_date.year = atoi(yyyy);

			}
		}
		/*
		fadd2 = fopen(product_in_order, "a+");
		fwrite(&mas_in_order[i], sizeof(struct ProductsInOrder), 1, fadd2);
		fclose(fadd2);*/
		cout << "Если Вы хотите добавить ещё одну запись,то нажмите 1." << endl;
		cout << "Если нет,то нажмите любую клавишу." << endl;
		cin.clear();
		cin >> ch;
		if (ch == '1') {
			i++;
		}
	} while (ch == '1');
		
}

int int_checker()
{
	char mas[9];
	int count = 0, i = 0, j;
	while (1) {
		//cls;
		cin.clear();
		fflush(stdin);
		char ch = getchar();
		if (ch != '\n'){
			mas[0] = ch;
			j = 1;
		}
		else {
			j = 0;
		}
		for (i = j; (mas[i] = getchar()) != '\n' && i < 8; i++);
		mas[i] = '\0';
		fflush(stdin);

		for (count = 0, i = 0; mas[i] != '\0'; i++)
			if (!(mas[i] >= '0' && mas[i] <= '9')) {
				count++;
				break;
			}
		if (mas[0] == '\0')
			count++;
		if (mas[i] == '\t')
			count++;
		if (count == 0)
			break;
		else
			printf("\nНеверный формат ввода! Попробуйте ещё раз!\n");
	}
	return atoi(mas);
}

int check_date(char* str)
{
	if (strlen(str) != 10) {
		cout << "Неверный формат ввода" << endl;
		return 0;
	}
	else {
		int i = 0;
		char day[3];
		char month[3];
		char year[5];
		for (; i < 2; i++) {
			day[i] = str[i];
		}
		day[2] = '\0';
		if (atoi(day) < 0 || atoi(day) > 31) {
			cout << "Некоректная дата" << endl;
			return 0;
		}
		else {
			for (int j = 0, i = 3; i < 5; i++, j++) {
				month[j] = str[i];
			}
			month[2] = '\0';
			if (atoi(month) < 0 || atoi(month) > 12) {
				cout << "Некоректная дата" << endl;
				return 0;
			}
			else {
				for (int j = 0, i = 6; i < (int)strlen(str) + 1; i++, j++) {
					year[j] = str[i];
				}
				year[4] = '\0';
				if (atoi(year) < 2000 || atoi(year) > 2100) {

					cout << "Неверный диапазон года (2000 - 2100)" << endl;
				}
				else
					return 1;
			}
		}
	}

}

//удаление
void view_menu_delete()
{
	bool flag = true;
	if ((F1 = fopen(shops, "r+")) == NULL) {
		cls;
		cout << "Файл пустой! Необходимо добавить магазин!" << endl;
		pause;
	}
	else
	{
		do
		{
			cls;
			
			cout << "1.Удалить одну запись" << endl;
			cout << "2.Удалить все записи о магазинах" << endl;
			cout << "3.Удалить все записи о продуктах,которые есть в магазинах" << endl;
			cout << "4.Удалить все записи о продуктах,которые будут заказаны" << endl << endl;
			cout << "0.Выход" << endl;
			char ch;
			cin.clear();
			cin >> ch;
			switch (ch)
			{
			
			case'1': {cls; delete_one_record(); pause; break; }
			case'2': {cls; delete_all_shops(); pause; break; }
			case'3': {cls; delete_all_p_stock(); pause; break; }
			case'4': {cls; delete_all_p_order(); pause; break; }
			case'0': { cls; flag = false; pause; break; }
			default: {cls; cout << "Такой операции не существует!" << endl;
				pause; break; }
			}

		} while (flag);
	}
}

int index_by_id(Shop* mas_shop_index, int ID) {
	int ans = -1;
		for (int i = 0; mas_shop_index[i].ID != NULL; i++) {
			if (mas_shop_index[i].ID == ID) {
				ans = i;
			}
	}
	return ans;
}

int index_by_id(ProductsInStock* mas_product_in_stock_index, int ID) {
	int ans = -1;
	for (int i = 0; mas_product_in_stock_index[i].ID != NULL; i++) {
		if (mas_product_in_stock_index[i].ID == ID) {
			ans = i;
		}
	}
	return ans;
}

int index_by_id(ProductsInOrder* mas_product_in_order_index, int ID) {
	int ans = -1;
	for (int i = 0; mas_product_in_order_index[i].ID != NULL; i++) {
		if (mas_product_in_order_index[i].ID == ID) {
			ans = i;
		}
	}
	return ans;
}

void delete_one_record() {
	bool flag = true;
	do
	{
		cls;

		cout << "1 .Удалить одну запись о магазине" << endl;
		cout << "2. Удалить одну запись о продукте,который есть в магазине" << endl;
		//cout << "3. Удалить одну запись о продукте,который будет заказан" << endl << endl;
		cout << "0.Выход" << endl;
		char ch;
		cin.clear();
		cin >> ch;
		switch (ch)
		{

		case'1': {cls; del_one_shop(); pause; break; }
		case'2': {cls; del_one_p_stock(); pause; break; }
		case'4': {cls; del_one_p_order(); pause; break; }
		case'0': { cls; flag = false; pause; break; }
		default: {cls; cout << "Такой операции не существует!" << endl;
			pause; break; }

		}
	} while (flag);
}

void del_one_shop()
{
	int i = 0, num, flag = -1;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[i], sizeof(struct Shop), 1, F1);
		flag = i;
		i++;
	}
	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		print_all_shops();
		cout << "Введите ID записи,которую вы хотите удалить :" << endl;
		cin >> num; // проверка на ввод
		t = index_by_id(mas_shop, num);
		
		fflush(stdin);
		if (flag < t || t < 0) {
			cls;
			cout << "Записи #" << num << " не существует!" << endl;
		}
		else
		{
			cls;
			cout << "Запись #" << t << " успешно удалена!" << endl;
			//header();
			del_from_shop(mas_shop, t);
			print_all_shops();
			F1 = fopen(shops, "w+");
			i = 0;
			while (i < t) {
				fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
				i++;
			}
			i++;
			for (; i < flag; i++)
				fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
			fclose(F1);
			
		}
	}
	pause; 
}

void del_from_shop(Shop * mas_shop, int t) {
	int n = 0;
	for (n; (mas_shop[n].ID != NULL); n++);
	Shop *temp = new Shop();
	if (n == 1) {

		mas_shop[0] = *temp;
	}
	else {
		for (int i = t; i < n; i++) {
			mas_shop[i] = mas_shop[i + 1];
		}
		mas_shop[n] = *temp;
	}
	F1 = fopen(shops, "w+");
	for (int i = 0; mas_shop[i].ID != NULL; i++) {
		fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
	}
	fclose(F1);

}
	
void del_one_p_stock() {
	int i = 0, num, flag_shop = -1, flag = 0;
	int id_in_shop;
	int t_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[i], sizeof(struct Shop), 1, F1);
		flag_shop = i;
		i++;
	}
	fclose(F1);
	if (flag_shop == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{

		print_all_shops();
		cout << "Введите ID магазина, из которого вы хотите удалить продукт:" << endl;
		cin >> num; // проверка на ввод
		t_shop = index_by_id(mas_shop, num);

		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|                                                                Информация о продуктах,которые находятся в магазинах                                                            |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название продукта   |     Марка продукта     |  Стоимость(руб)  |    Вид   | Количество(един) | Вес, объём | Дата доставки |  Срок годности  |  Местоположение  |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		print_products_in_stock(mas_shop[t_shop]);
		cout << "Введите ID продукта, который вы хотите удалить:" << endl;
		cin >> num; // проверка на ввод
		t = index_by_id(mas_shop[t_shop].products_in_stock, num);

		for (flag; mas_shop[flag].ID != 0; flag++);

		fflush(stdin);
		 if (flag < t || t < 0) {
			cls;
			cout << "Записи #" << num << " не существует!" << endl;
		}
		else
		{
			cls;
			cout << "Запись #" << t << " успешно удалена!" << endl;
			del_from_product_in_stock(mas_shop[t].products_in_stock, t);
			print_products_in_stock(mas_shop[t]);
			
		}
	}
	pause;
}

void del_from_product_in_stock(ProductsInStock* mas_in_stock, int t) {
	int n = 0;
	for (n; (mas_in_stock[n].ID != NULL); n++);
	ProductsInStock *temp = new ProductsInStock();
	if (n == 1) {
		
		mas_in_stock[0] = *temp;
	}
	else {
		for (int i = t; i < n; i++) {
			mas_in_stock[i] = mas_in_stock[i+1];
		}
		mas_in_stock[n] = *temp;
	}
	F1 = fopen(shops, "w+");
	for (int i = 0; mas_shop[i].ID != NULL; i++) {
		fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
	}
	fclose(F1);
	
}

void del_one_p_order() {
	int i = 0, num, flag_shop = -1, flag = 0;
	int id_in_shop;
	int t_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[i], sizeof(struct Shop), 1, F1);
		flag_shop = i;
		i++;
	}
	fclose(F1);
	if (flag_shop == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{

		print_all_shops();
		cout << "Введите ID магазина, из которого вы хотите удалить продукт:" << endl;
		cin >> num; // проверка на ввод
		t_shop = index_by_id(mas_shop, num);

		printf("+--------------------------------------------------------------------------------------+\n");
		printf("                      Информация о продуктах,которые будут доставлены                  |\n");
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
		printf("+--------------------------------------------------------------------------------------+\n");

		print_products_in_order(mas_shop[t_shop]);
		cout << "Введите ID продукта, который вы хотите удалить:" << endl;
		cin >> num; // проверка на ввод
		t = index_by_id(mas_shop[t_shop].products_in_order, num);

		for (flag; mas_shop[flag].ID != 0; flag++);

		fflush(stdin);
		if (flag < t || t < 0) {
			cls;
			cout << "Записи #" << num << " не существует!" << endl;
		}
		else
		{
			cls;
			cout << "Запись #" << t << " успешно удалена!" << endl;
			//header();
			del_from_product_in_order(mas_shop[t].products_in_order, t);
			print_products_in_order(mas_shop[t]);
			F1 = fopen(shops, "w+");
			for (int i = 0; mas_shop[i].ID != NULL; i++) {
				fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
			}
			fclose(F1);
		}
	}
	pause;
}

void del_from_product_in_order(ProductsInOrder* mas_in_order, int t) {
	int n = 0;
	for (n; (mas_in_order[n].ID != NULL); n++);
	ProductsInOrder *temp = new ProductsInOrder();
	if (n == 1) {

		mas_in_order[0] = *temp;
	}
	else {
		for (int i = t; i < n; i++) {
			mas_in_order[i] = mas_in_order[i + 1];
		}
		mas_in_order[n] = *temp;
	}
	F1 = fopen(shops, "w+");
	for (int i = 0; mas_shop[i].ID != NULL; i++) {
		fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
	}
	fclose(F1);

}

void delete_all_shops() {
	F1 = fopen(shops, "w+");
	remove(shops); //как удалить элемент массива в с++
	fclose(F1);
	while (mas_shop[0].ID != NULL) {
		del_from_shop(mas_shop, 0);
	}
}

void delete_all_p_stock() { //который есть
	F1 = fopen(shops, "r+");
	int i = 0;
	while (!feof(F1))
	{
		fread(&mas_shop[i], sizeof(struct Shop), 1, F1);
		i++;
	}
	fclose(F1);
	int num;
	int t_shop;
	print_all_shops();
	cout << "Введите ID магазина, из которого вы хотите удалить все продукты:" << endl;
	cin >> num; // проверка на ввод
	t_shop = index_by_id(mas_shop, num);

	while (mas_shop[t_shop].products_in_stock[0].ID != NULL) {
		del_from_product_in_stock(mas_shop[t_shop].products_in_stock, 0);
	}
	cls;
	print_all_shops();
	F1 = fopen(shops, "w+");
	for (int i = 0; mas_shop[i].ID != NULL; i++) {
		fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
	}
	fclose(F1);
}

void delete_all_p_order() { //который будет заказан
	F1 = fopen(shops, "r+");
	int i = 0;
	while (!feof(F1))
	{
		fread(&mas_shop[i], sizeof(struct Shop), 1, F1);
		i++;
	}
	fclose(F1);
	int num;
	int t_shop;
	print_all_shops();
	cout << "Введите ID магазина, из которого вы хотите удалить все продукты:" << endl;
	cin >> num; // проверка на ввод
	t_shop = index_by_id(mas_shop, num);

	while (mas_shop[t_shop].products_in_order[0].ID != NULL) {
		del_from_product_in_order(mas_shop[t_shop].products_in_order, 0);
	}
	cls;
	print_all_shops();
	F1 = fopen(shops, "w+");
	for (int i = 0; mas_shop[i].ID != NULL; i++) {
		fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
	}
	fclose(F1);
}

void view_print_menu() {
	bool flag = true;
	do
	{
		cls;
		cout << "Меню просмотра данных в табличной форме.  " << endl;
		cout << "1.Информация о магазинах" << endl;
		cout << "2.Информация о существующих продуктах" << endl;
		cout << "3.Информация о заказных продуктах " << endl;
		cout << "0 Выход" << endl;
		fflush(stdin);
		char ans;
		cin >> ans;
	    switch (ans)
	{
		case '1': {cls; print_all_shops(); pause; break; }
		case '2': {cls; print_all_products_in_stock(); pause; break; }
		case '3': {cls; print_all_products_in_order(); pause; break; }
		case '0': {cls;
			printf("До свидания!\n");
			flag = true;
			break; }
		default:  cls;
			printf("Такого пункта меню нет!\n");
			pause;
			break;
		}

	} while (!flag);

}

void print_all_shops() {
	int i = 0;
	for (i; mas_shop[i].ID != NULL; i++) {
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("                      Информация о магазине  %21s                                            \n", mas_shop[i].name);//почему????
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название магазина  |    Адрес магазина    | Контакт. тел. |   Продукты             \n");
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("| %3d | %21s | %20s |  %12d | %5s  %5s |\n", mas_shop[i].ID, mas_shop[i].name, mas_shop[i].adress, mas_shop[i].contact_tel_nomber, mas_shop[i].products_in_stock[0].name, mas_shop[i].products_in_stock[0].brand );
		
		for (int j = 1; mas_shop[i].products_in_stock[j].ID != 0; j++) {
			printf(" %76s  %14s    |\n", mas_shop[i].products_in_stock[j].name, mas_shop[i].products_in_stock[j].brand);
		}
		
	}
}


void print_all_products_in_stock() {
	F1 = fopen(shops, "r+");
	int i = 0;
	while (!feof(F1))
	{
		fread(&mas_shop[i], sizeof(struct Shop), 1, F1);
		i++;
	}
	fclose(F1);
	printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("|                                                                Информация о продуктах,которые находятся в магазинах                                                      |\n");
	printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("|  ID  | Название продукта |     Марка продукта     | Цена(руб) |      Вид      | Кол-во(един.) | Вес, объём | Дата доставки |  Срок годности  |       Местоположение      |\n");
	printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	if (mas_shop[0].ID != NULL) {
		for (int j = 0; mas_shop[j].ID != NULL; j++) {
			print_products_in_stock(mas_shop[j]);
		}
	}

	else {
		printf("|            Нет информации о продуктах            |\n");
	}
	}

void print_products_in_stock(Shop mas_shop) {
	for (int i = 0; mas_shop.products_in_stock[i].ID != NULL; i++)
	{
		printf("| %4d | %17s | %22s | %9d | %13s | %13d | %10s | %13s | %15s | %5s %5s |\n", mas_shop.products_in_stock[i].ID, mas_shop.products_in_stock[i].name,
			mas_shop.products_in_stock[i].brand, mas_shop.products_in_stock[i].cost, mas_shop.products_in_stock[i].description,
			mas_shop.products_in_stock[i].quantity, mas_shop.products_in_stock[i].quan_descr, mas_shop.products_in_stock[i].delivery_date.date_format, mas_shop.products_in_stock[i].expiration_date.date_format,
			mas_shop.name, mas_shop.adress
		);
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	}
}

void print_products_in_order(Shop mas_shop) {
	for (int i = 0; mas_shop.products_in_order[i].ID != NULL; i++)
	{
		printf("| %3d | %21s | %21s |  %15d | %15s |\n", mas_shop.products_in_order[i].ID, mas_shop.products_in_order[i].name,
			mas_shop.products_in_order[i].brand, mas_shop.products_in_order[i].quantity, mas_shop.products_in_order[i].order_date.date_format);
		printf("+-----+-----------------------+-----------------------+-------------+\n");
	}
}

//переделать меню просмотра
void print_all_products_in_order() {
	F1 = fopen(shops, "r+");
	int i = 0;
	while (!feof(F1))
	{
		fread(&mas_shop[i], sizeof(struct Shop), 1, F1);
		i++;
	}
	fclose(F1);
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("                      Информация о продуктах,которые будут доставлены                  |\n");
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
	printf("+--------------------------------------------------------------------------------------+\n");

	if (mas_shop[0].ID != NULL) {
		for (int j = 0; mas_shop[j].ID != NULL; j++) {

			print_products_in_order(mas_shop[j]);

		}
	}

	else {
		printf("|            Нет информации о предметах и преподавателях            |\n");
	}
}

void work_with_file() {
	int r = 0;
	int flag = 1;
	FILE *f;
	do {
		puts("\n1.Создать файл\n2.Очистить файл\n3. Удалить файл\n0. Выход в меню администратора");
		fflush(stdin);
		char ans;
		cin >> ans;
		switch (ans) {

		case '1': {	system("cls");
			if (flag == 0) {
				f = fopen(shops, "w+"); 
				fclose(f);
				puts("Файл успешно создан");
				flag = 1;
			}
			if (flag == 1)
				puts("Файл уже создан");
			break; }
		case '2': {	system("cls");
			if (flag == 0)
				puts("Файл не создан");
			else {
				f = fopen(shops, "w");
				fclose(f);
				puts("Файл успешно очищен");
				flag = 1;
			}
			break; }
		case '3': {	system("cls");
			if (flag == 1) {
				remove(shops);
				puts("Файл успешно удалён");
				flag = 0;
			}
			else
				puts("Ошибка удаления файла");
			break; }
		case '0': {	system("cls"); r = 1;
			break; }
		default: system("cls");
		}
	} while (r == 0);
}
	
void control_users() {
	bool flag = true;
	do
	{
		cls;
		cout << "Меню управления пользователями.  " << endl;
		cout << "1.Показать всех пользователей" << endl;
		cout << "2.Удаление пользователя" << endl;
		cout << "0 Выход" << endl;
		fflush(stdin);
		char ans;
		cin >> ans;
		switch (ans)
		{
		case '1': {cls; show_all_users(); pause; break; } //почему функция принимает 0 аргументов ?
		case '2': {cls; delete_user(); pause; break; } //почему функция принимает 0 аргументов?
		case '0': {cls;
			printf("До свидания!\n");
			flag = true;
			break; }
		default:  cls;
			printf("Такого пункта меню нет!\n");
			pause;
			break;
		}

	} while (!flag);
}

void show_all_users() {
	char file_login[20];
	char file_password[20];
	FILE *f2;
	f2 = fopen(users_pr, "r+");
	if (users_pr != 0)
	{
		fscanf(f2, "%s", file_login);
		if (feof(f2)) {
			puts("Ни один пользователь не создан.");
			_getch();
			fclose(f2);
			return;
		}
		rewind(f2);
		puts("Все зарегестрированные пользователи:");
		puts("--->");
		do {
			fscanf(f2, "%s%s", file_login, file_password);
			if (feof(f2))//читает не весь файл
				break;
			printf("    %s\n", file_login);
		} while (1);
		puts("--->");
		fclose(f2);
	}
	else {
		puts("Ни один пользователь не создан.");
		fclose(f2);
	}
	pause;
	cls;

}

void delete_user() {
	{
		system("cls");
		FILE *F2;
		int sch = 0;
		int i = 0;
		char login[20], file_login[20];
		char file_password[20];
		FILE *temp = NULL;
		F2 = fopen(users_pr, "r+");
		fscanf(F2, "%s", file_login);
		if (feof(F2)) {
			puts("Ни один пользователь не создан.");
			_getch();
			fclose(F2);
			return;
		}
		rewind(F2);
		puts("---Удаление пользователя---");
		show_all_users();
		printf("Введите логин пользователя, которого хотите удалить: ");
		do {
			rewind(F2);
			scanf("%19s", login);
			fflush(stdin);
			sch = 0;
			do {
				fscanf(F2, "%s%s", file_login, file_password);
				if (feof(F2)) {
					break;
				}
				if (!strcmp(login, file_login)) {                    //Найден такой же логин, как тот что ввел пользователь
					sch = 1;
					break;
				}
			} while (1);

			if (sch == 0)
				printf("Логина \"%s\" в списке нет. Повторите ввод: ", login);
			else
				break;
		} while (1);

		rewind(F2);
		temp = fopen("TEMP.txt", "w+t");
		do {
			fscanf(F2, "%s%s", file_login, file_password);
			if (feof(F2)) {
				break;
			}
			if (strcmp(login, file_login)) {           //Если логины не совпадают
				fprintf(temp, "%s %s\n", file_login, file_password);
			}
		} while (1);

		fclose(F2);
		F2 = fopen(users_pr, "w+t");
		rewind(temp);

		do {
			fscanf(temp, "%s%s", file_login, file_password);
			if (feof(temp)) {
				break;
			}
			fprintf(F2, "%s %s\n", file_login, file_password);
		} while (1);

		fclose(temp);
		remove("TEMP.txt");
		rewind(F2);

		system("cls");
		printf("Пользователь \"%s\" удален.\n", login);
		puts("Оставишиеся логины пользователей:");
		puts("--->");
		do {
			fscanf(F2, "%s%s", file_login, file_password);
			if (feof(F2)) {
				break;
			}
			printf("    %s\n", file_login);
		} while (1);
		puts("--->");
		fclose(F2);

		puts("Нажмите любую клавишу, чтобы вернуться назад.");
		_getch();
	}


}

void sort_menu_view() {
	
	cout << "1.Сортировка по названию магазина" << endl;
	cout << "2.Сортировка по названию продукта в магазинах" << endl;
	cout << "3.Сортировка по названию заказанных продуктов в магазинах" << endl;
	cout << "4.Сортировка по ID продукта" << endl;
	cout << "5.Сортировка по ID магазина" << endl;
	cout << "6.Сортировка по количеству ввозимого товара(задача)" << endl; //востребованный товар по количеству или по повторяемости?(1-больше товара чем больше заказ., тем более он популярен)
	cout << "7.Сортировка по дате срока годности товара" << endl;
	cout << "0.Выход" << endl;
}

void sort_menu() {
	struct Shop tmp[N], temp;
	int  srt, flag = 1, i = 0, j = 0;
	if (!fopen(shops, "r+")) {
		cls;
		cout << "Добавьте магазин!" << endl;
		pause;
	}
	else {
		F1 = fopen(shops, "r+");
		int i = 0;
		while ((fread(&tmp[i], sizeof(struct Shop), 1, F1))) {
			i++;
		}
		fclose(F1);
		srt = i;

		while (flag) {
			cls;
			print_all_shops();
			sort_menu_view();

			switch (_getch())
			{
			case '1': {
				cls;
				sort_by_shop_name(tmp, srt);
				
				//print_sorted(srt, tmp); (сделать меню отсортированных магазинов)
				cout << "Hello";
				break;
			}
			case '2': {
				cls;

				vector<ProductsInStock> all_p_in_stock;
				for (int j = 0; j < srt; j++) {
					for (int i = 0; tmp[j].products_in_stock[i].ID != NULL; i++) {
						all_p_in_stock.push_back(tmp[j].products_in_stock[i]);
					}
				}

				sort_by_products_name(all_p_in_stock);
				/*for (i = 0; i < srt - 1; i++) {
					for (j = i + 1; j < srt; j++) {
						if (strcmp(tmp[i].products_in_stock.name, tmp[j].products_in_stock.name) > 0) {
							temp = tmp[i];
							tmp[i] = tmp[j];
							tmp[j] = temp;
						}
					}
				}*/
				//print_sorted(srt, tmp); (сделать меню отсортированных продуктов)
				print_sort_products(all_p_in_stock);
				cout << "Hello";
				break;
			}
			/*case '3': {
				cls;
				for (i = 0; i < srt - 1; i++) {
					for (j = i + 1; j < srt; j++) {
						if (tmp[i].price > tmp[j].price) {
							temp = tmp[i];
							tmp[i] = tmp[j];
							tmp[j] = temp;
						}
					}
				}
				print_sorted(srt, tmp);
				break;
			}*/
					  /* case '4': {
						  cls;
						  for (i = 0; i < srt - 1; i++) {
							  for (j = i + 1; j < srt; j++) {
								  if (tmp[i].rating < tmp[j].rating) {
									  temp = tmp[i];
									  tmp[i] = tmp[j];
									  tmp[j] = temp;
								  }
							  }
						  }
						  print_sorted(srt, tmp);
						  break;
					  }*/
					  /*case '5': {
						  int fl = 0;
						  cls;
						  for (i = 0; i < srt - 1; i++) {
							  for (j = i + 1; j < srt; j++) {
								  if (tmp[i].date.year == tmp[j].date.year) {
									  if (tmp[i].date.month == tmp[j].date.month) {
										  if (tmp[i].date.day > tmp[j].date.day) {
											  temp = tmp[i];
											  tmp[i] = tmp[j];
											  tmp[j] = temp;
										  }
									  }
									  else {
										  if (tmp[i].date.month > tmp[j].date.month) {
											  temp = tmp[i];
											  tmp[i] = tmp[j];
											  tmp[j] = temp;
										  }
									  }
								  }
								  else {
									  if (tmp[i].date.year > tmp[j].date.year) {
										  temp = tmp[i];
										  tmp[i] = tmp[j];
										  tmp[j] = temp;

									  }
								  }
							  }
						  }
						  //print_sorted(srt, tmp); (сделать меню отсортированных продуктов по сроку годности)
						  break;
					  }
					  case '0': {
						  cls;
						  flag = 0;
						  break;
					  }
					  default: {
						  cls;
						  cout << "Такой операции нет!" << endl;
						  pause;
						  break;
					  }
					  }
				  }
			  }*/
			}
		}
	}
}


void main_task() {

}

void sort_by_shop_name(Shop shop_mass[], int shop_mass_size) {
	Shop temp;
	for (int i = 0; i < shop_mass_size - 1; i++) {
		for (int j = i + 1; j < shop_mass_size; j++) {
			if (strcmp(shop_mass[i].name, shop_mass[j].name) > 0) {
				temp = shop_mass[i];
				shop_mass[i] = shop_mass[j];
				shop_mass[j] = temp;
			}
		}
	}
}


/*bool is_bigger(ProductsInStock first_product, ProductsInStock second_product) {
	if (strcmp(first_product.name, second_product.name)<0) {
		return true;
	}
	else {
		return false;
	}
}*/

void sort_by_products_name(vector<ProductsInStock>& products_vector) {
	//sort(products_vector.begin(), products_vector.end(), is_bigger);
	bool swapp = true;
	while (swapp) {
		swapp = false;
		for (int i = 0; i < products_vector.size() - 1; i++) {
			if (strcmp(products_vector[i].name, products_vector[i + 1].name) > 0) {
				swap(products_vector[i], products_vector[i + 1]);
				swapp = true;
			}
		}
	}
}
void print_sort_products(vector<ProductsInStock>& products_vector) {
	printf("+----------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("|                                                                Информация о продуктах,которые находятся в магазинах                          |\n");
	printf("+----------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("|  ID  | Название продукта |     Марка продукта     | Цена(руб) |      Вид      | Кол-во(един.) | Вес, объём | Дата доставки |  Срок годности  |\n");
	printf("+----------------------------------------------------------------------------------------------------------------------------------------------+\n");
	for (int i = 0; i< products_vector.size(); i++)
	{
		printf("| %4d | %17s | %22s | %9d | %13s | %13d | %10s | %13s | %15s |\n", products_vector[i].ID, products_vector[i].name,
			products_vector[i].brand, products_vector[i].cost, products_vector[i].description,
			products_vector[i].quantity, products_vector[i].quan_descr, products_vector[i].delivery_date.date_format, products_vector[i].expiration_date.date_format
		);
		printf("+----------------------------------------------------------------------------------------------------------------------------------------------+\n");
	}

	system("pause");
}