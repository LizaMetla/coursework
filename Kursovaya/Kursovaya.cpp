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




#define admins_pr "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\admins_profile.txt"
#define users_pr "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\users_profile.txt.txt"
#define product_in_stock "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\product_in_stock.txt"
#define product_in_order "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\product_in_order.txt"
#define shops "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\shops.txt"

#define scanf scanf_s
#define printf printf_s
#define pause system("pause");       //для упрощения написания,вместо system("pause"),пишем pause;
#define cls system("cls");  // для упрощения написания,вместо system("cls"),пишем cls;
const int N = 50; //максимальное количество записей

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
void sort_menu();//сортировка
void control_users();//управление пользователями
int int_checker();//проверка на значение
int check_date(char* str); //проверка на дату
void add_shop();
void view_print_menu();
void print_all_shops();
void print_all_products_in_stock();
void print_all_products_in_order();
void load_db();
void main_task();//основная задача 
void work_with_file();//работа с файлом


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
			autorisation_admin();
			break;
		}
		case '2': {
			autorisation_user();
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
	printf("6.Сортировка продуктов по алфавиту \n");
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
		fflush(stdin);
		char ans = getchar();
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
		//case'8': {cls;      work_with_file(F1); break; }
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
}

void edit_menu() {}
void control_users() {}
void sort_menu() {}
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
			for (int t = 0; t < j - 1; t++)
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
	if ((F1 = fopen("shops", "r+")) == NULL) {
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
			switch (_getch())
			{
			
			//case'1': {cls; del_product(); pause; break; }
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

void del_product()
{
	int i = 0, num, flag = -1, t;
	F1 = fopen("shops", "r+");
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
		/*print_course();
		cout << "Выберите номер записи,который хотите удалить :" << endl;
		cin >> num; // проверка на ввод
		flush;
		t = num - 1;
		if (flag == 0 && num == 1) {
			cls;
			delete_all();
			cout << "Запись #" << num << " удалена!" << endl;
		}
		else if (flag < num || num <= 0) {
			cls;
			cout << "Записи #" << num << " не существует!" << endl;
		}
		else
		{
			cls;
			cout << "Запись #" << t << " успешно удалена!" << endl;
			header();
			print_one(t);
			f1 = fopen("course.txt", "w+");
			i = 0;
			while (i < num - 1) {
				fwrite(&mas[i], sizeof(struct Course), 1, f1);
				i++;
			}
			i++;
			for (; i < flag; i++)
				fwrite(&mas[i], sizeof(struct Course), 1, f1);
			fclose(f1);
		}
	}
	pause; */
}
	
}

void delete_all_shops() {
	F1 = fopen("shops", "w+");
	remove("shops.txt");
	fclose(F1);
}

void delete_all_p_stock() { //который есть
	F1 = fopen("product_in_stock", "w+");
	remove("product_in_stock");
	fclose(F1);
}

void delete_all_p_order() { //который будет заказан
	F1 = fopen("product_in_order", "w+");
	remove("product_in_order");
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
		printf("+--------------------------------------------------------------------------------------------+\n");
		printf("                      Информация о магазине  %21s                                            \n", mas_shop[i].name);//почему????
		printf("+--------------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название магазина  |   Адрес магазина   | Контактный тел. |   Продукты             \n");
		printf("+--------------------------------------------------------------------------------------------+\n");
		printf("| %3d | %21s | %20s |  %10d | %10s  %3s |\n", mas_shop[i].ID, mas_shop[i].name, mas_shop[i].adress, mas_shop[i].contact_tel_nomber, mas_shop[i].products_in_stock[0].name, mas_shop[i].products_in_stock[0].brand );
		
		for (int j = 1; mas_shop[i].products_in_stock[j].ID != 0; j++) {
			printf(" %74s %13s |\n", mas_shop[i].products_in_stock[j].name, mas_shop[i].products_in_stock[j].brand);
		}
		
	}
}
/*int ID; //ID
char name[20]; //название магазина
char adress[20]; //адрес магазина
int contact_tel_nomber;// контактный телефон
ProductsInStock products_in_stock[N]; // Продукт ,который есть в магазине
ProductsInOrder products_in_order[N]; // Продукт, который будет заказан*/

//переделать меню просмотра
void print_all_products_in_stock() {
	printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("|                                                                Информация о продуктах,которые находятся в магазинах                                                            |\n");
	printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("|  ID  |   Название продукта   |     Марка продукта     |  Стоимость(руб)  |    Вид   | Количество(един) | Вес, объём | Дата доставки |  Срок годности  |  Местоположение  |\n");
	printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	if (mas_shop[0].products_in_stock[0].ID != NULL) {
		for (int j = 0; mas_shop[j].ID != NULL; j++) {

			for (int i = 0; mas_shop[j].products_in_stock[i].ID != NULL; i++)
			{
				printf("| %3d | %22s | %21s |  %10d | %10s | %10d | %11s | %11s | %11s | %5s %5s |\n", mas_shop[j].products_in_stock[i].ID, mas_shop[j].products_in_stock[i].name, 
					mas_shop[j].products_in_stock[i].brand, mas_shop[j].products_in_stock[i].cost, mas_shop[j].products_in_stock[i].description,
					mas_shop[j].products_in_stock[i].quantity, mas_shop[j].products_in_stock[i].quan_descr, mas_shop[j].products_in_stock[i].delivery_date.date_format, mas_shop[j].products_in_stock[i].expiration_date.date_format,
					mas_shop[j].name, mas_shop[j].adress
				);
				printf("+-----+-----------------------+-----------------------+------------------------------------------------------------------------------+\n");
			}


		}
	}

	else {
		printf("|            Нет информации о предметах и преподавателях            |\n");
	}
	}

//int ID;//ID продукта
//int cost;// стоимость
//int quantity; //количество продуктов
//char brand[20]; //марка продукта
//char name[20]; // название продукта
//char description[20]; //характеристика продукта(молоко-козье,хлеб-чёрный)
//char quan_descr[20]; // количественная характеристика продуктов(вес,объём)
//Date expiration_date; // срок годности
//Date delivery_date;

//переделать меню просмотра
void print_all_products_in_order() {
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("                      Информация о продуктах,которые будут доставлены                  |\n");
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
	printf("+--------------------------------------------------------------------------------------+\n");

	if (mas_shop[0].products_in_order[0].ID != NULL) {
		for (int j = 0; mas_shop[j].ID != NULL; j++) {

			for (int i = 0; mas_shop[j].products_in_order[i].ID != NULL; i++)
			{
				printf("| %3d | %21s | %21s |  %15d | %15s |\n", mas_shop[i].products_in_order[i].ID, mas_shop[i].products_in_order[i].name, 
					mas_shop[i].products_in_order[i].brand, mas_shop[i].products_in_order[i].quantity, mas_shop[i].products_in_order[i].order_date.date_format);
				printf("+-----+-----------------------+-----------------------+-------------+\n");
			}


		}
	}

	else {
		printf("|            Нет информации о предметах и преподавателях            |\n");
	}
}

//int ID;//ID продукта
//char name[20]; //название продукта
//char brand[20]; // марка продуктов
//int quantity; //количество продутов
//Date order_date; //дата доставки

void work_with_file() {

}

//переделать меню просмотра
void main_task() {

}
