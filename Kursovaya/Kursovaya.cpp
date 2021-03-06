
#define _CRT_SECURE_NO_WARNINGS
// Kursovaya.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <cstdlib>
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stddef.h>
#include <algorithm>
#include <Windows.h>
#include <regex>
#include <cstdlib>
#include <limits>


#define admins_pr "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\admins_profile.txt"
#define users_pr "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\users_profile.txt.txt"
#define shops "C:\\Users\\elizavetametla\\source\\repos\\Kursovaya\\shops.txt"
#define scanf scanf_s
#define printf printf_s
#define pause system("pause");       //для упрощения написания,вместо system("pause"),пишем pause;
#define cls system("cls");  // для упрощения написания,вместо system("cls"),пишем cls;
const int N = 50; //максимальное количество записей
const int NUMBER_OF_POPULAR_PRODUCTS = 3;//количество выводимых популярных продуктов

bool IS_AUTHORIZATION = true; //перед релизом поменять на true!!!11!!!11!!!!!!

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
	int counter_search = 0; //счётчик поиска продуктов
	

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

struct PopularProductsInStock //структура для поиска популярного продукта
{
	char name[20];//название популярного продукта
	int all_search_counter;//счётчик вызовов в поиске
};

Shop mas_shop[N]; 

void selection_menu();//меню авторизации
int welcome_menu(void);//текст меню авторизации
int autorisation_admin();//авторизация админа
int autorisation_user();//авторизация юзера
int view_admin_menu();//текст меню выбора для администратора
int view_user_menu();//текст меню выбора для пользователя
void admin_menu();//меню администратора
void user_menu();//меню пользователя
int view_add_elements();//текст меню добавления
void add_elements();//меню добавления
void add_product_in_stock(ProductsInStock* mas_in_stock);//функция добавления продукта в магазин
void add_product_in_order(ProductsInOrder* mas_in_order);//функция добавление продукта в заказе
void add_one_product_in_stock();//добавления одного продукта в магазин
void add_one_product_in_order();//добавления одного продукта в заказе
int view_menu_delete();//меню удаления записи
void menu_delete();//удаление записи
void delete_all_shops(); //удаление всех магазинов
void delete_all_p_stock();//удаление всех продуктов, которые есть в магазине
void delete_all_p_order();//удаление всех продуктов, которые будут заказаны
void edit_menu();//изменение записи
int sort_menu_view();// меню сортировки
void sort_menu();//сортировка
int view_control_users();//текст меню управление пользователями
void control_users();//управление пользователями
int int_checker();//проверка на значение
int check_date(char* str); //проверка на дату
void add_shop(); // добавление магазина
int v_view_print_menu();//текст меню просмотра 
void view_print_menu(); // меню просмотра 
void print_all_shops(); //печать всех магазинов
void print_all_products_in_stock(); //печать всех продуктов, которые есть в магазине
void print_all_products_in_order(); //печать всех продуктов, которые будут заказаны
void load_db(); //база данных
void main_task();//основная задача 
int view_work_with_file();//текст меню работа с файлом
void work_with_file();//работа с файлом
void show_all_users();// показать всех существующих пользователей
void delete_user(); // удаление пользователя
int view_delete_one_record();//текст меню удаления одной записи
void delete_one_record(); //удаление одной записи
void del_one_shop();//удаление одного магазина
void del_one_p_stock();//удаление одного продукта,который есть в магазине
void del_one_p_order();//удаление одного продукта,который будет заказан
int index_by_id(Shop* mas_shop_index, int ID);//индекс магазина
void print_products_in_stock(Shop );//печать продуктов, которые есть в магазине
int index_by_id(ProductsInStock* mas_product_in_stock_index, int ID);//индекс продукта, который есть в магазине
void del_from_shop(Shop* mas_shop, int t);//удаление из магазина
void del_from_product_in_stock(ProductsInStock* mas_in_stock, int t);//удаление продукта,который есть в магазине
void del_from_product_in_order(ProductsInOrder* mas_in_order, int t);//удаление продукта,который есть в заказе
int index_by_id(ProductsInOrder* mas_product_in_order_index, int ID);//индекс продукта в заказе
void print_products_in_order(Shop mas_shop);//печать всех продуктов,которые в заказе
void sort_by_shop_name(Shop* tmp, int srt);//сортировка магазинов по названию
void save_all_p_in_stock_in_vector(Shop* shop_mass, vector<ProductsInStock>& products_vector);
void sort_p_in_stock_by_name(vector<ProductsInStock>& products_vector); //сортировка продукта, который есть в магазине, по названию
bool is_bigger_id(ProductsInStock first_product, ProductsInStock second_product);
void sort_p_in_order_by_name(vector<ProductsInOrder>& products_vector, int first, int last);//функция сортировки продукта,который в заказе, по названию
void sort_p_in_stock_by_id(vector<ProductsInStock>& products_vector);//функция сортировки продукта,который есть в магазине, по ID
void sort_p_in_order_by_qantity(vector<ProductsInOrder>& products_vector, int first, int last);//сортировка продуктов в заказе по количеству
void print_sort_products(vector<ProductsInStock>& products_vector);//печать отсортированных продуктов,которые есть в магазине
void print_sort_products_order(vector<ProductsInOrder>& products_vector);//печать отсортированных продуктов,которые в заказе
void print_sort_shops(Shop shop_mass[], int shop_mass_size);//печать отсортированных магазинов
int view_search_menu_view();//текст меню поиска элемента администратором
void search_menu_view();//меню поиска элемента администратором
int view_search_menu_user();//текст меню поиска элемента пользователем
void search_menu_user(); //меню поиска элемента пользователем
void sort_shop_by_id(Shop shop_mass[], int first, int last);//сортировка по ID магазина
void sort_p_in_stock_by_date(vector<ProductsInStock>& products_vector);//сортировка продуктов,которые есть в магазине, по сроку годности
void search_shop_by_name();//поиск по названию магазина
void search_shop_by_id();//поиск по ID магазина
void search_p_in_stock_by_name();//поиск по названию марки продукта,который есть в магазине
void search_p_in_stock_by_brand();//поиск по названию продукта,который есть в магазине
void search_p_in_stock_by_id();//поиск по ID продукта,который есть в магазине
void search_p_in_order_by_name();//поиск по названию продукта,который в заказе
void search_p_in_order_by_brand();//поиск по названию марки продукта,который в заказе
void search_p_in_order_by_id();//поиск по ID продукта,который в заказе
void edit_shop();//меню редактирования
void edit_p_in_stock();//редактирование продукта ,который находится в магазине
void edit_p_in_order();//редактирование продукта в заказе
void save_shops_to_file(Shop mass_shop[]);//сохранение магазинов в файл
PopularProductsInStock count_all_products(ProductsInStock product, Shop mass_shop[]);//функция поиска популярного продукта
void print_popular_products(vector<PopularProductsInStock> popular_products);//функция печати популярного продукта
int input_cost_by_pattern(string pattern);//функция проверки ввода цены
int input_by_pattern(string pattern);//проверка на ввод
string input_by_pattern_str(string pattern);//проверка на ввод
void reset_color();//функция для смены цвета

#if defined(max)
#undef max
#endif

int main()
{

	setlocale(LC_ALL, "Rus"); 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color 0B");
	load_db();
	selection_menu();
}


void reset_color() {
	printf("\x1b[0m");
}
void set_color(string color) {
	printf(color.c_str());
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

int welcome_menu(void) {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 2)//
				choice = 0;
			if (choice < 0)
				choice = 2;
			if (ch == 13)//enter
				return choice;
			printf(".______________________________________________.\n");
			printf("|_________________Здравствуйте!________________|\n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf("|          %c Вход под администратором.         |\n", pointer);
				reset_color();
			}
			else 
				printf("|            Вход под администратором.         |\n");
				
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf("|          %c Вход под пользователем.           |\n", pointer);
				reset_color();
			}
				
			else 
				printf("|            Вход под пользователем.           |\n");
			
			if (choice == 2) {
					set_color("\x1b[38;5;15m");
					printf("|          %c Выход.                            |\n", pointer);
					reset_color();
			 }
			
			else 
					printf("|            Выход.                            |\n");
		}
		printf(".______________________________________________. \n");
	
	ch = _getch();
	}
	
}

void selection_menu() {
	bool flag = false;
	do {
		cls;
		

		switch (welcome_menu())
		{
		case 2 : {
			cls
				printf("До свидания!");
			flag = true;
			break;
		}
		case 0 : {
			cls;
			if (IS_AUTHORIZATION) {
				autorisation_admin();
			}
			else {
				admin_menu();
			}
			
			break;
		}
		case 1 : {
			cls;
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
	puts("---Вход под администратором---\n");
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
				fscanf(F2, "%s %s", file_login, file_password);
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
		cls;
		user_menu();
		return 1;

	}

int view_admin_menu()
{
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 8)
				choice = 0;
			if (choice < 0)
				choice = 8;
			if (ch == 13)//enter
				return choice;
			printf(" .______________________________________________.\n");
			printf(" |______________Меню администратора_____________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Добавление записи.                |\n", pointer);
				reset_color();
			}	
			else
				printf(" |            Добавление записи.                |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Удаление записи.                  |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Удаление записи.                  |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Изменение записи.                 |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Изменение записи.                 |\n");
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Просмотр в табличной форме.       |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Просмотр в табличной форме.       |\n");
			if (choice == 4) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Поиск.                            |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Поиск.                            |\n");
			if (choice == 5) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Сортировка.                       |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Сортировка.                       |\n");
			if (choice == 6) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Управление пользователями.        |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Управление пользователями.        |\n");
			if (choice == 7) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Работа с файлом.                  |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Работа с файлом.                  |\n");
			if (choice == 8) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Выйти в главное меню.             |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Выйти в главное меню.             |\n");

		}
		printf(" |______________________________________________|\n");
		printf(" .______________________________________________.\n");

		ch = _getch();
	}
}

int view_user_menu()
{
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 4)//
				choice = 0;
			if (choice < 0)
				choice = 4;
			if (ch == 13)//enter
				return choice;
			printf(" .______________________________________________.\n");
			printf(" |_______________Меню пользователя______________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Просмотр в табличной форме.       |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Просмотр в табличной форме.       |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Поиск.                            |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Поиск.                            |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Сортировка.                       |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Сортировка.                       |\n");
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Задача.                           |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Задача.                           |\n");
			if (choice == 4) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Выйти в главное меню.             |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Выйти в главное меню.             |\n");

		}
		printf(" |______________________________________________|\n");
		printf(" .______________________________________________.\n");

		ch = _getch();
	}
	
}

void admin_menu()
{

	bool flag = false;
	do
	{
		cls;
		
		switch (view_admin_menu())
		{
		case 8: {cls;
			printf("До свидания!\n");
			flag = true;
			break; }
		case 0: {cls;		add_elements();		break;  	}
		case 1: {cls; 	menu_delete();		break;   }
		case 2: {cls; 	edit_menu();  	break;	}
		case 3: {cls; 	view_print_menu();		break;	}
		case 4: {cls; 	search_menu_view();		break;	}
		case 5: {cls; 	sort_menu();		break;	}
		case 6: {cls;     control_users(); break; }
		case 7: {cls;     work_with_file(); break; }
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
		
		switch (view_user_menu())
		{
		case 4: {cls;
			printf("До свидания!\n");
			flag = true;
			break; }
		case 0: {cls;		view_print_menu();		break;  	}
		case 1: {cls; 	search_menu_user();		break;   }
		case 2: {cls; 	sort_menu();  	break;	}
		case 3: {cls; 	main_task();		break;	}

		default:  cls;
			printf("Такого пункта меню нет!\n");
			pause;
			break;
		}

	} while (!flag);
}



int view_add_elements() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 3)//
				choice = 0;
			if (choice < 0)
				choice = 3;
			if (ch == 13)//enter
				return choice;
			printf(" .______________________________________________________.\n");
			printf(" |______________________Добавление______________________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Магазина.                                 |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Магазина.                                 |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Продукта в конкретном магазине.           |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Продукта в конкретном магазине.           |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Продукта в заказе в конкретном магазине.  |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Продукта в заказе в конкретном магазине.  |\n");
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Выход в основное меню администратора.     |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |            Выход в основное меню администратора.     |\n");
			

		}
		printf(" |______________________________________________________|\n");
		printf(" .______________________________________________________.\n");

		ch = _getch();
	}
		
}

void add_elements() {
	bool flag = false;
	do
	{
		cls;

		switch (view_add_elements())
		{
		case 0: {cls; add_shop(); pause; break; }
		case 1: {cls; add_one_product_in_stock(); pause; break; }
		case 2: {cls; add_one_product_in_order(); pause; break; }


		case 3: {cls;
			flag = true;
			break; }
		default:  cls;
			printf("Такого пункта меню нет!\n");
			pause;
			break;
		}

	} while (!flag);
}

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
			//id = input_by_pattern("[0-9]+");
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

		fflush(stdin);
		while (g == 0) {
			fflush(stdin);
			
			cout << "Введите название магазина, который вы хотите добавить:" << endl;
			string name = input_by_pattern_str("^[a-zA-ZА-Яа-яЁё0-9\\s]+$");
			strcpy_s(mas_shop[i].name, 20, name.c_str());
			if (strcmp(mas_shop[i].name, o) != 0)
				g = 1;
			
		}
		
		g = 0;
		fflush(stdin);

		
		while (g == 0) {
			cout << "Введите адрес магазина: " << endl;
			string adress = input_by_pattern_str("^[а-яА-ЯёЁa-zA-Z0-9\\s\.\,]+$");
			strcpy_s(mas_shop[i].adress, 20, adress.c_str());
			if (strcmp(mas_shop[i].adress, o) != 0)
				g = 1;
		}
		cout << "Введите контактный телефон магазина: " << endl;
		//mas_shop[i].contact_tel_nomber = input_by_pattern("[0-9]+");
		mas_shop[i].contact_tel_nomber = int_checker();

	cout << "Введите информацию о продуктах в магазине:" << endl;
	add_product_in_stock(mas_shop[i].products_in_stock);

	cout << "Введите информацию о заказных продуктах:" << endl;
	add_product_in_order(mas_shop[i].products_in_order);


	fadd = fopen(shops, "a+");
	fwrite(&mas_shop[i], sizeof(struct Shop), 1, fadd);
	fclose(fadd);
	cout << "Если Вы хотите добавить ещё одну запись о магазине, то нажмите 1." << endl;
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
			id = int_checker();
			for (int t = 0; t < j; t++)
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
			string name = input_by_pattern_str("[a-zA-ZА-Яа-я]+");
			strcpy_s(mas_in_stock[i].name, 20, name.c_str());
			if (strcmp(mas_in_stock[i].name, o) != 0)
				g = 1;
		}
		g = 0;
		cout << "Введите стоимость продукта (в белорусских рублях):" << endl;
		mas_in_stock[i].cost = int_checker();
		//mas_in_stock[i].cost = input_by_pattern("[0-9]+");
		//[0-9]+.?[0-9]+ чтобы можно было вводить с точкой (не работает)

		cout << "Введите количество продуктов (единиц):" << endl;
		//mas_in_stock[i].quantity = input_by_pattern("[0-9]+");
		mas_in_stock[i].quantity = int_checker();
	
		
			fflush(stdin);
			while (g == 0) {
				fflush(stdin);
				cout << "Введите название марки продукта: " << endl;
				
				string brand = input_by_pattern_str("^[a-zA-ZА-Яа-яЁё0-9\\s]+$");
				strcpy_s(mas_in_stock[i].brand, 20, brand.c_str());
				if (strcmp(mas_in_stock[i].brand, o) != 0)
					g = 1;
			}
			g = 0;
			fflush(stdin);

			while (g == 0) {
				fflush(stdin);
				cout << "Введите характеристику продукта:" << endl;
				
				string description = input_by_pattern_str("^[a-zA-ZА-Яа-яЁё\\s]+$");
				strcpy_s(mas_in_stock[i].description, 20, description.c_str());
				if (strcmp(mas_in_stock[i].description, o) != 0)
					g = 1;
			}
			g = 0;
			fflush(stdin);

			while (g == 0) {
				fflush(stdin);
				cout << "Введите весовую характеристику продукта(объём, количество(грамм)):" << endl;
				
				string quan_descr = input_by_pattern_str("^[а-яА-ЯёЁa-zA-Z0-9\\s\.]+$");
				strcpy_s(mas_in_stock[i].quan_descr, 20, quan_descr.c_str());
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
			cout << "Если Вы хотите добавить ещё одну запись о продукте, то нажмите 1." << endl;
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
			id = int_checker();
			for (int t = 0; t < j; t++)
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
			
			string name = input_by_pattern_str("^[a-zA-ZА-Яа-яЁё\\s]+$");
			strcpy_s(mas_in_order[i].name, 20, name.c_str());
			if (strcmp(mas_in_order[i].name, o) != 0)
				g = 1;
		}
		g = 0;

		fflush(stdin);
		while (g == 0) {
			fflush(stdin);
			cout << "Введите название марки продукта поставки: " << endl;
			string brand = input_by_pattern_str("^[a-zA-ZА-Яа-яЁё0-9\\s]+$");
			strcpy_s(mas_in_order[i].brand, 20, brand.c_str());
			if (strcmp(mas_in_order[i].brand, o) != 0)
				g = 1;
		}
		g = 0;
		fflush(stdin);
		

		fflush(stdin);
		cout << "Введите количество продуктов для поставки (единиц):" << endl;
		//mas_in_order[i].quantity = input_by_pattern("[0-9]+");
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
		
		cout << "Если Вы хотите добавить ещё одну запись о продукте в заказе, то нажмите 1." << endl;
		cout << "Если нет,то нажмите любую клавишу." << endl;
		cin.clear();
		cin >> ch;
		if (ch == '1') {
			i++;
		}
	} while (ch == '1');
		
}

void add_one_product_in_stock() {

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
		cout << "Пустой файл! Необходимо добавить магазин!" << endl;
	else
	{
		print_all_shops();
		cout << "Введите ID магазина, в который вы хотите добавить продукт: " << endl;
		cin >> num; // проверка на ввод
		t_shop = index_by_id(mas_shop, num);
		add_product_in_stock(mas_shop[t_shop].products_in_stock);

		cls;
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|                                                                Информация о продуктах,которые находятся в магазинах                                                      |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  | Название продукта |     Марка продукта     | Цена(руб) |      Вид      | Кол-во(един.) | Вес, объём | Дата доставки |  Срок годности  |       Местоположение      |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");


		print_products_in_stock(mas_shop[t_shop]);
		FILE* F1 = fopen(shops, "w+");
		for (int i = 0; mas_shop[i].ID != NULL; i++) {
			fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
		}
		fclose(F1);
	}

}

void add_one_product_in_order() {
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
		cout << "Пустой файл! Необходимо добавить магазин!" << endl;
	else
	{
		print_all_shops();
		cout << "Введите ID магазина, в который вы хотите добавить продукт: " << endl;
		cin >> num; // проверка на ввод
		t_shop = index_by_id(mas_shop, num);
		add_product_in_order(mas_shop[t_shop].products_in_order);

		cls;
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("                      Информация о продуктах,которые будут доставлены                  |\n");
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
		printf("+--------------------------------------------------------------------------------------+\n");

		print_products_in_order(mas_shop[t_shop]);
		FILE* F1 = fopen(shops, "w+");
		for (int i = 0; mas_shop[i].ID != NULL; i++) {
			fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
		}
		fclose(F1);
	}
}


int input_by_pattern(string pattern) //функция проверки  элементов массива
{
	string str;
	regex regex_pattern(pattern); // задание шаблона регулярного выражения
	//cin.ignore();
	//fflush;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, str);
	
	while (!regex_match(str, regex_pattern))
	{
		cout << "Неверный формат ввода!Попробуйте ещё раз! ";
		Sleep(1500);
		printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);

		getline(cin, str);
	};
	
	return stoi(str);
}

int input_cost_by_pattern(string pattern)// функция проверки для ввода цены
{
	string str;
	regex regex_pattern(pattern); // задание шаблона регулярного выражения

	cin.ignore();
	getline(cin, str);

	while (!regex_match(str, regex_pattern))
	{
		cout << "Неверный формат ввода!Попробуйте ещё раз! ";
		Sleep(1500);
		printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);

		getline(cin, str);
	};

	return stof(string(str));
}

// функция ввода строки через регулярные выражения
string input_by_pattern_str(string pattern) //функция проверки  элементов массива
{
	string str;
	regex regex_pattern(pattern); // задание шаблона регулярного выражения

	getline(cin, str);

	while (!regex_match(str, regex_pattern))
	{
		cout << "Неверный формат ввода!Попробуйте ещё раз! ";
		Sleep(1500);
		printf("%c[2K\r%c[A%c[2K\r\33[2K", 27, 27, 27);
		getline(cin, str);
	};

	return str;
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
		else {
			printf("Неверный формат ввода! Попробуйте ещё раз!");
			Sleep(1500);
			printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
		}
			
	}
	return atoi(mas);
}


int check_date(char* str)
{
	if (strlen(str) != 10) {
		cout << "Неверный формат ввода" << endl;
		Sleep(1500);
		printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
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
			Sleep(1500);
			printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
			return 0;
		}
		else {
			for (int j = 0, i = 3; i < 5; i++, j++) {
				month[j] = str[i];
			}
			month[2] = '\0';
			if (atoi(month) < 0 || atoi(month) > 12) {
				cout << "Некоректная дата" << endl;
				Sleep(1500);
				printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
				return 0;
			}
			else {
				for (int j = 0, i = 6; i < (int)strlen(str) + 1; i++, j++) {
					year[j] = str[i];
				}
				year[4] = '\0';
				if (atoi(year) < 2018 || atoi(year) > 2028) {

					cout << "Неверный диапазон года (2018 - 2028)" << endl;
					Sleep(1500);
					printf("%c[2K\r%c[A%c[2K\r", 27, 27, 27);
					return 0;
				}
				else
					return 1;
			}
		}
	}

}

int view_menu_delete() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 4)//
				choice = 0;
			if (choice < 0)
				choice = 4;
			if (ch == 13)//enter
				return choice;
			printf(" ._________________________________________________________________.\n");
			printf(" |____________________________Удаление_____________________________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Удалить одну запись.                                      |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Удалить одну запись.                                      |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Удалить все записи о магазинах.                           |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Удалить все записи о магазинах.                           |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Удалить все записи о продуктах,которые есть в магазинах.  |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Удалить все записи о продуктах,которые есть в магазинах.  |\n");
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Удалить все записи о продуктах,которые будут заказаны.    |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Удалить все записи о продуктах,которые будут заказаны.    |\n");
			if (choice == 4) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Выход в основное меню администратора.                     |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Выход в основное меню администратора.                     |\n");
			

		}
		printf(" |_________________________________________________________________|\n");
		printf(" ._________________________________________________________________.\n");

		ch = _getch();
	}
}

//удаление
void  menu_delete()
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
			
			switch (view_menu_delete())
			{
			
			case 0: {cls; delete_one_record(); break; }
			case 1: {cls; delete_all_shops();  break; }
			case 2: {cls; delete_all_p_stock(); break; }
			case 3: {cls; delete_all_p_order(); break; }
			case 4: { cls; flag = false; break; }
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

int view_delete_one_record() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 3)//
				choice = 0;
			if (choice < 0)
				choice = 3;
			if (ch == 13)//enter
				return choice;
			printf(" ._________________________________________________________________.\n");
			printf(" |_____________________Удаление одной записи_______________________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Удалить одну запись о магазине.                           |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Удалить одну запись о магазине.                           |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Удалить одну запись о продукте,который есть в магазине.   |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Удалить одну запись о продукте,который есть в магазине.   |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Удалить одну запись о продукте,который будет заказан.     |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Удалить одну запись о продукте,который будет заказан.     |\n");
			
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Выход в основное меню удаления.                           |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Выход в основное меню удаления.                           |\n");


		}
		printf(" |_________________________________________________________________|\n");
		printf(" ._________________________________________________________________.\n");

		ch = _getch();
	}
}

/*
set_color("\x1b[38;5;15m");

reset_color();
*/

void delete_one_record() {
	bool flag = true;
	do
	{
		cls;

		switch (view_delete_one_record())
		{

		case 0: {cls; del_one_shop(); break; }
		case 1: {cls; del_one_p_stock();  break; }
		case 2: {cls; del_one_p_order(); break; }
		case 3: { cls; flag = false; break; }
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
			del_from_product_in_order(mas_shop[t_shop].products_in_order, t);
			print_products_in_order(mas_shop[t_shop]);
			save_shops_to_file(mas_shop);
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

int v_view_print_menu() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 3)//
				choice = 0;
			if (choice < 0)
				choice = 3;
			if (ch == 13)//enter
				return choice;
			printf(" ._______________________________________________________________.\n");
			printf(" |____________Меню просмотра данных в табличной форме____________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Информация о магазинах.                                 |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Информация о магазинах.                                 |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Информация о существующих продуктах.                    |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Информация о существующих продуктах.                    |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Информация о заказных продуктах.                        |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Информация о заказных продуктах.                        |\n");

			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Выход в основное меню.                                  |\n", pointer);
				reset_color();
			}
				
			else
				printf(" |       Выход в основное меню.                                  |\n");


		}
		printf(" |_______________________________________________________________|\n");
		printf(" ._______________________________________________________________.\n");

		ch = _getch();
	}
	
}

void view_print_menu() {
	bool flag = true;
	do
	{
		cls;
		
	    switch (v_view_print_menu())
	{
		case 0: {cls; print_all_shops(); pause; break; }
		case 1: {cls; print_all_products_in_stock(); pause; break; }
		case 2: {cls; print_all_products_in_order(); pause; break; }
		case 3: {cls;
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
		printf("| %3d | %21s | %20s |  %12d |   %-12s %-11s |\n", mas_shop[i].ID, mas_shop[i].name, mas_shop[i].adress, mas_shop[i].contact_tel_nomber, mas_shop[i].products_in_stock[0].name, mas_shop[i].products_in_stock[0].brand );
		
		for (int j = 1; mas_shop[i].products_in_stock[j].ID != 0; j++) {
			printf(" %80s  %14s |\n", mas_shop[i].products_in_stock[j].name, mas_shop[i].products_in_stock[j].brand);
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
	{//заменила 9d на 9f
		printf("| %4d | %17s | %22s | %9d | %13s | %13d | %10s | %13s | %15s | %-10s %-14s |\n", mas_shop.products_in_stock[i].ID, mas_shop.products_in_stock[i].name,
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
		printf("| %4d | %21s | %19s |  %14d | %13s |\n", mas_shop.products_in_order[i].ID, mas_shop.products_in_order[i].name,
			mas_shop.products_in_order[i].brand, mas_shop.products_in_order[i].quantity, mas_shop.products_in_order[i].order_date.date_format);
		printf("+--------------------------------------------------------------------------------------+\n");
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
		printf("|                  Нет информации о предметах и заказанных продуктах                   |\n");
	}
}

int view_work_with_file() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 3)//
				choice = 0;
			if (choice < 0)
				choice = 3;
			if (ch == 13)//enter
				return choice;
			printf(" .______________________________________________________.\n");
			printf(" |____________________Работа с файлом___________________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Создать файл.                             |\n", pointer);
				reset_color();
			}

			else
				printf(" |            Создать файл.                             |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Очистить файл.                            |\n", pointer);
				reset_color();
			}

			else
				printf(" |            Очистить файл.                            |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Удалить файл.                             |\n", pointer);
				reset_color();
			}

			else
				printf(" |            Удалить файл.                             |\n");
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |          %c Выход в основное меню администратора.     |\n", pointer);
				reset_color();
			}

			else
				printf(" |            Выход в основное меню администратора.     |\n");


		}
		printf(" |______________________________________________________|\n");
		printf(" .______________________________________________________.\n");

		ch = _getch();
	}


}

void work_with_file() {
	int r = 0;
	int flag = 1;
	FILE *f;
	do {
		
		switch (view_work_with_file()) {

		case 0: {	system("cls");
			if (flag == 0) {
				f = fopen(shops, "w+"); 
				fclose(f);
				puts("Файл успешно создан");
				flag = 1;
			}
			if (flag == 1)
				puts("Файл уже создан");
			break; }
		case 1: {	system("cls");
			if (flag == 0)
				puts("Файл не создан");
			else {
				f = fopen(shops, "w");
				fclose(f);
				puts("Файл успешно очищен");
				flag = 1;
			}
			break; }
		case 2: {	system("cls");
			if (flag == 1) {
				remove(shops);
				puts("Файл успешно удалён");
				flag = 0;
			}
			else
				puts("Ошибка удаления файла");
			break; }
		case 3: {	system("cls"); r = 1;
			break; }
		default: system("cls");
		}
	} while (r == 0);
}
	
int view_control_users(){
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 2)//
				choice = 0;
			if (choice < 0)
				choice = 2;
			if (ch == 13)//enter
				return choice;
			printf(".____________________________________________________.\n");
			printf("|___________Меню управления пользователями___________|\n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf("|          %c Показать всех пользователей.            |\n", pointer);
				reset_color();
			}
			else
				printf("|            Показать всех пользователей.            |\n");

			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf("|          %c Удаление пользователя.                  |\n", pointer);
				reset_color();
			}

			else
				printf("|            Удаление пользователя.                  |\n");

			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf("|          %c Выход в основное меню администратора    |\n", pointer);
				reset_color();
			}

			else
				printf("|            Выход в основное меню администратора    |\n");
		}
		printf(".____________________________________________________. \n");

		ch = _getch();
	}

}

void control_users() {
	bool flag = true;
	do
	{
		cls;
		
		switch (view_control_users())
		{
		case 0: {cls; show_all_users(); pause; break; } //почему функция принимает 0 аргументов ?
		case 1: {cls; delete_user(); pause; break; } //почему функция принимает 0 аргументов?
		case 2: {cls;
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

}

void delete_user() {
	{
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
			fflush(stdin);
			cin.ignore();
			gets_s(login, 20);
			//scanf("%19s", login);
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

int sort_menu_view() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 7)//
				choice = 0;
			if (choice < 0)
				choice = 7;
			if (ch == 13)//enter
				return choice;
			print_all_shops();
			printf(" ._________________________________________________________________.\n");
			printf(" |___________________________Сортировка____________________________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Сортировка по названию магазина.                          |\n", pointer);
				reset_color();
			}

			else
				printf(" |       Сортировка по названию магазина.                          |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Сортировка по названию продукта в магазинах.              |\n", pointer);
				reset_color();
			}

			else
				printf(" |       Сортировка по названию продукта в магазинах.              |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Сортировка по названию заказанных продуктов в магазинах.  |\n", pointer);
				reset_color();
			}

			else
				printf(" |       Сортировка по названию заказанных продуктов в магазинах.  |\n");
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Сортировка по ID продукта,который есть в магазине.        |\n", pointer);
				reset_color();
			}

			else
				printf(" |       Сортировка по ID продукта,который есть в магазине.        |\n");
			if (choice == 4) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Сортировка по ID магазина.                                |\n", pointer);
				reset_color();
			}

			else
				printf(" |       Сортировка по ID магазина.                                |\n");

			if (choice == 5) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Сортировка по количеству ввозимого товара.                |\n", pointer);
				reset_color();
			}
			else
				printf(" |       Сортировка по количеству ввозимого товара.                |\n");


			if (choice == 6) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Сортировка по дате срока годности продукта.               |\n", pointer);
				reset_color();
			}

			else
				printf(" |       Сортировка по дате срока годности продукта.               |\n");
			if (choice == 7) {
				set_color("\x1b[38;5;15m");
				printf(" |     %c Выход в основное меню.                                    |\n", pointer);
				reset_color();
			}

			else
				printf(" |       Выход в основное меню.                                    |\n");


		}
		printf(" |_________________________________________________________________|\n");
		printf(" ._________________________________________________________________.\n");

		ch = _getch();
	}
	
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

		vector<ProductsInStock> all_p_in_stock;
		for (int j = 0; j < srt; j++) {
			for (int i = 0; tmp[j].products_in_stock[i].ID != NULL; i++) {
				all_p_in_stock.push_back(tmp[j].products_in_stock[i]);
			}
		}

		vector<ProductsInOrder> all_p_in_order;
		for (int j = 0; j < srt; j++) {
			for (int i = 0; tmp[j].products_in_order[i].ID != NULL; i++) {
				all_p_in_order.push_back(tmp[j].products_in_order[i]);
			}
		}

		while (flag) {
			cls;
			
			switch (sort_menu_view())
			{
			case 0: {
				cls;

				sort_by_shop_name(tmp, srt);
				print_sort_shops(tmp, srt);
				break;
			}
			case 1: {
				cls;

				sort_p_in_stock_by_name(all_p_in_stock);
				print_sort_products(all_p_in_stock);
				
				break;
			}
			case 2: {
				cls;

				sort_p_in_order_by_name(all_p_in_order, 0, all_p_in_order.size()-1);
				print_sort_products_order(all_p_in_order);
				break;
			}
			case 3: {
			    cls;
						  
				sort_p_in_stock_by_id(all_p_in_stock);
				print_sort_products(all_p_in_stock);
				 break;
			}
				
			case 4: {
				cls;

				sort_shop_by_id(tmp, 0, srt - 1);
				print_sort_shops(tmp, srt);
				break;

			}
					  
		    case 5: {
			    cls;

				sort_p_in_order_by_qantity(all_p_in_order, 0, all_p_in_order.size() - 1);
				print_sort_products_order(all_p_in_order);
			    
			    break;
					  }
		    case 6: {
				cls;
						  
				sort_p_in_stock_by_date(all_p_in_stock);
				print_sort_products(all_p_in_stock);

				break;
					  }
			case 7: {
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
		 }
	}
		

//Шейкерная сортировка
void sort_by_shop_name(Shop shop_mass[], int shop_mass_size) {
	Shop temp;
	int left = 1;
	int right = shop_mass_size - 1;
	while (left <= right)

	{
		for (int i = right; i >= left; i--) {
			if (strcmp(shop_mass[i - 1].name, shop_mass[i].name) > 0)
			{
				temp = shop_mass[i];
				shop_mass[i] = shop_mass[i - 1];
				shop_mass[i - 1] = temp;
			}
			
		}
		left++;

		for (int i = left; i <= right; i++) {
			if (strcmp(shop_mass[i - 1].name, shop_mass[i].name) > 0)

			{
				temp = shop_mass[i];
				shop_mass[i] = shop_mass[i - 1];
				shop_mass[i - 1] = temp;
			}
			
		}
		right--;


	}
	

	}

bool is_bigger(ProductsInStock first_product, ProductsInStock second_product) {
	if (_strcmpi(first_product.name, second_product.name) < 0) {
		return true;
	}
	else {
		return false;
	}
}

void sort_p_in_stock_by_name(vector<ProductsInStock>& products_vector) {
	sort(products_vector.begin(), products_vector.end(), is_bigger);
}

//QSort
void sort_p_in_order_by_name(vector<ProductsInOrder>& products_vector, int first, int last) {

	int i = first, j = last;
	ProductsInOrder x = products_vector[(first + last) / 2];

		do {
			while (_strcmpi(products_vector[i].name, x.name) < 0) i++;
			while (_strcmpi(products_vector[j].name, x.name) > 0) j--;

			if (i <= j) {
				if (_strcmpi(products_vector[i].name , products_vector[j].name) > 0) swap(products_vector[i], products_vector[j]);
				i++;
				j--;
			}
		} while (i <= j);

		if (i < last)
			sort_p_in_order_by_name(products_vector, i, last);
		if (first < j)
			sort_p_in_order_by_name(products_vector, first, j);
	}

bool is_bigger_id(ProductsInStock first_product, ProductsInStock second_product) {
	if (first_product.ID < second_product.ID ) {
		return true;
	}
	else {
		return false;
	}
}

void sort_p_in_stock_by_id(vector<ProductsInStock>& products_vector) {
	sort(products_vector.begin(), products_vector.end(), is_bigger_id);
}

//QSort
void sort_shop_by_id(Shop shop_mass[], int first, int last) {

	int i = first, j = last;
	Shop x = shop_mass[(first + last) / 2];

		do {
			while (shop_mass[i].ID < x.ID) i++;
			while (shop_mass[j].ID > x.ID) j--;

			if (i <= j) {
				if (shop_mass[i].ID > shop_mass[j].ID) 
					swap(shop_mass[i], shop_mass[j]);
				i++;
				j--;
			}
		} while (i <= j);

		if (i < last)
			sort_shop_by_id(shop_mass, i, last);
		if (first < j)
			sort_shop_by_id(shop_mass, first, j);

}

void sort_p_in_order_by_qantity(vector<ProductsInOrder>& products_vector, int first, int last) {
	int i = first, j = last;
	ProductsInOrder x = products_vector[(first + last) / 2];

	do {
		while (products_vector[i].quantity < x.quantity) i++;
		while (products_vector[j].quantity > x.quantity) j--;

		if (i <= j) {
			if (products_vector[i].quantity > products_vector[j].quantity) swap(products_vector[i], products_vector[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last)
		sort_p_in_order_by_qantity(products_vector, i, last);
	if (first < j)
		sort_p_in_order_by_qantity(products_vector, first, j);
}

void sort_p_in_stock_by_date(vector<ProductsInStock>& products_vector) {
	
	ProductsInStock temp;
	
	cls;
	for (int i = 0; i < products_vector.size() - 1; i++) {
		for (int j = i + 1; j < products_vector.size(); j++) {
			if (products_vector[i].expiration_date.year == products_vector[j].expiration_date.year) {
				if (products_vector[i].expiration_date.month == products_vector[j].expiration_date.month) {
					if (products_vector[i].expiration_date.day > products_vector[j].expiration_date.day) {
						temp = products_vector[i];
						products_vector[i] = products_vector[j];
						products_vector[j] = temp;
					}
				}
				else {
					if (products_vector[i].expiration_date.month > products_vector[j].expiration_date.month) {
						temp = products_vector[i];
						products_vector[i] = products_vector[j];
						products_vector[j] = temp;
					}
				}
			}
			else {
				if (products_vector[i].expiration_date.year > products_vector[j].expiration_date.year) {
					temp = products_vector[i];
					products_vector[i] = products_vector[j];
					products_vector[j] = temp;

				}
			}
		}
	}
}

void print_sort_shops(Shop shop_mass[], int shop_mass_size) {
	int i = 0;
	for (i; i<shop_mass_size; i++) {
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("                      Информация о магазине  %21s                                            \n", shop_mass[i].name);
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название магазина  |    Адрес магазина    | Контакт. тел. |   Продукты             \n");
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("| %3d | %21s | %20s |  %12d |   %-12s %-11s |\n", shop_mass[i].ID, shop_mass[i].name, shop_mass[i].adress, shop_mass[i].contact_tel_nomber, shop_mass[i].products_in_stock[0].name, shop_mass[i].products_in_stock[0].brand);

		for (int j = 0; shop_mass[i].products_in_stock[j].ID != NULL; j++) {
			printf(" %80s  %14s |\n", shop_mass[i].products_in_stock[j].name, shop_mass[i].products_in_stock[j].brand);
		}
	}
	system("pause");
}

void print_sort_products(vector<ProductsInStock>& products_vector) {
	printf("+----------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("|                                                                Информация о продуктах,которые находятся в магазинах                          |\n");
	printf("+----------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("|  ID  | Название продукта |     Марка продукта     | Цена(руб) |      Вид      | Кол-во(един.) | Вес, объём | Дата доставки |  Срок годности  |\n");
	printf("+----------------------------------------------------------------------------------------------------------------------------------------------+\n");
	for (int i = 0; i < products_vector.size(); i++)
	{
		printf("| %4d | %17s | %22s | %9d | %13s | %13d | %10s | %13s | %15s |\n", products_vector[i].ID, products_vector[i].name,
			products_vector[i].brand, products_vector[i].cost, products_vector[i].description,
			products_vector[i].quantity, products_vector[i].quan_descr, products_vector[i].delivery_date.date_format, products_vector[i].expiration_date.date_format
		);
		printf("+----------------------------------------------------------------------------------------------------------------------------------------------+\n");
	}

	system("pause");
}

void print_sort_products_order(vector<ProductsInOrder>& products_vector) {
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("                      Информация о продуктах,которые будут доставлены                  |\n");
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
	printf("+--------------------------------------------------------------------------------------+\n");
	for (int i = 0; i < products_vector.size(); i++)
	{

		printf("| %4d | %21s | %19s |  %14d | %13s |\n", products_vector[i].ID, products_vector[i].name,
			products_vector[i].brand, products_vector[i].quantity, products_vector[i].order_date.date_format);
		printf("+--------------------------------------------------------------------------------------+\n");

	}
	system("pause");
}


int view_search_menu_view() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 8)//
				choice = 0;
			if (choice < 0)
				choice = 8;
			if (ch == 13)//enter
				return choice;
			printf(" ._______________________________________________________________________.\n");
			printf(" |____________________________________Поиск______________________________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Магазина по названию.                                             |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Магазина по названию.                                             |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Магазина по ID.                                                   |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Магазина по ID.                                                   |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта, который есть в магазине, по названию.                   |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта, который есть в магазине, по названию.                   |\n");
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта, который есть в магазине, по названию марки продукта.    |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта, который есть в магазине, по названию марки продукта.    |\n");
			if (choice == 4) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта, который есть в магазине, по ID.                         |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта, который есть в магазине, по ID.                         |\n");
			if (choice == 5) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта ,который в заказе, по названию.                          |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта ,который в заказе, по названию.                          |\n");
			if (choice == 6) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта ,который в заказе, по названию марки продукта.           |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта ,который в заказе, по названию марки продукта.           |\n");
			if (choice == 7) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта ,который в заказе, по ID.                                |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта ,который в заказе, по ID.                                |\n");
			if (choice == 8) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Выход в основное меню администратора.                             |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Выход в основное меню администратора.                             |\n");


		}
		printf(" |_______________________________________________________________________|\n");
		printf(" ._______________________________________________________________________.\n");

		ch = _getch();
	}
}

void search_menu_view() {
	bool flag = true;
	do
	{
		cls;
		
		switch (view_search_menu_view())
		{
		case 0: {cls; search_shop_by_name(); pause; break; }
		case 1: {cls; search_shop_by_id(); pause; break; }
		case 2: {cls; search_p_in_stock_by_name(); pause; break; }
		case 3: {cls; search_p_in_stock_by_brand(); pause; break; }
		case 4: {cls; search_p_in_stock_by_id(); pause; break; }
		case 5: {cls; search_p_in_order_by_name(); pause; break; }
		case 6: {cls; search_p_in_order_by_brand(); pause; break; }
		case 7: {cls; search_p_in_order_by_id(); pause; break; }
		
		case 8: {cls;
			flag = true;
			break; }
		default:  cls;
			printf("Такого пункта поиска меню нет!\n");
			pause;
			break;
		}

	} while (!flag);

}

int view_search_menu_user() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 5)//
				choice = 0;
			if (choice < 0)
				choice = 5;
			if (ch == 13)//enter
				return choice;
			printf(" ._______________________________________________________________________.\n");
			printf(" |____________________________________Поиск______________________________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Магазина по названию.                                             |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Магазина по названию.                                             |\n");
			
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта, который есть в магазине, по названию.                   |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта, который есть в магазине, по названию.                   |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта, который есть в магазине, по названию марки продукта.    |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта, который есть в магазине, по названию марки продукта.    |\n");
			
			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта ,который в заказе, по названию.                          |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта ,который в заказе, по названию.                          |\n");
			if (choice == 4) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Продукта ,который в заказе, по названию марки продукта.           |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Продукта ,который в заказе, по названию марки продукта.           |\n");
			
			if (choice == 5) {
				set_color("\x1b[38;5;15m");
				printf(" |   %c Выход в основное меню пользователя.                               |\n", pointer);
				reset_color();
			}

			else
				printf(" |     Выход в основное меню пользователя.                               |\n");


		}
		printf(" |_______________________________________________________________________|\n");
		printf(" ._______________________________________________________________________.\n");

		ch = _getch();
	}

	
}

void search_menu_user() {
	bool flag = true;
	do
	{
		cls;
		
		
		switch (view_search_menu_user())
		{
		case 0: {cls; search_shop_by_name(); pause; break; }
		
		case 1: {cls; search_p_in_stock_by_name(); pause; break; }
		case 2: {cls; search_p_in_stock_by_brand(); pause; break; }

		case 3: {cls; search_p_in_order_by_name(); pause; break; }
		case 4: {cls; search_p_in_order_by_brand(); pause; break; }
		

		case 5: {cls;
			flag = true;
			break; }
		default:  cls;
			printf("Такого пункта меню поиска не существует!\n");
			pause;
			break;
		}

	} while (!flag);
}

void search_shop_by_name() {
	print_all_shops();
	char answer[225];

	int j = 0, num, flag = -1;
	bool flag1 = false;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}
	
	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		cout << endl << "Введите название магазина для поиска: ";
		fflush;
		gets_s(answer, 225);
		while (string(answer) == "")
		{
			fflush;
			//cout << "Неверый ввод!!!" << endl;
			//cout << endl << "Введите название магазина для поиска: ";
			gets_s(answer, 225);
		}
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("                            Информация о магазине                                                  \n");
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название магазина  |    Адрес магазина    | Контакт. тел. |   Продукты             \n");
		printf("+-------------------------------------------------------------------------------------------------+\n");
		if(mas_shop[0].name != NULL)
		for (int i = 0; mas_shop[i].ID != NULL; i++) {
			
			if (_strnicmp(mas_shop[i].name,  answer, string(answer).size()) == 0) {
				printf("| %3d | %21s | %20s |  %12d |   %-12s %-11s |\n", mas_shop[i].ID, mas_shop[i].name, mas_shop[i].adress, mas_shop[i].contact_tel_nomber, mas_shop[i].products_in_stock[0].name, mas_shop[i].products_in_stock[0].brand);
				flag1 = true;;
				for (int j = 1; mas_shop[i].products_in_stock[j].ID != 0; j++) {
					printf(" %80s  %14s |\n", mas_shop[i].products_in_stock[j].name, mas_shop[i].products_in_stock[j].brand);
				}
			}
		}
	}
	if (!flag1)
		printf("|            Нет информации о магазинах                         |\n");


}

void search_shop_by_id() {
	print_all_shops();
	int answer;

	int j = 0, num, flag = -1;
	bool flag1 = false;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}

	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		cout << endl << "Введите ID магазина для поиска: ";
		answer = int_checker();

		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("                            Информация о магазине                                                  \n");
		printf("+-------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название магазина  |    Адрес магазина    | Контакт. тел. |   Продукты             \n");
		printf("+-------------------------------------------------------------------------------------------------+\n");
		if (mas_shop[0].ID != NULL)
			for (int i = 0; mas_shop[i].ID != NULL; i++) {

				if ( mas_shop[i].ID  == answer ) {
					printf("| %3d | %21s | %20s |  %12d |   %-12s %-11s |\n", mas_shop[i].ID, mas_shop[i].name, mas_shop[i].adress, mas_shop[i].contact_tel_nomber, mas_shop[i].products_in_stock[0].name, mas_shop[i].products_in_stock[0].brand);
					flag1 = true;;
					for (int j = 1; mas_shop[i].products_in_stock[j].ID != 0; j++) {
						printf(" %76s  %14s    |\n", mas_shop[i].products_in_stock[j].name, mas_shop[i].products_in_stock[j].brand);
					}
				}
			}
	}
	if (!flag1)
		printf("|            Нет информации о магазинах                         |\n");

}

void search_p_in_stock_by_name() {
	print_all_products_in_stock();
	char answer[255];

	int j = 0, num, flag = -1;
	bool flag1 = false;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}

	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		cout << endl << "Введите название продукта в магазине для поиска: ";
		fflush;
		gets_s(answer, 225);
		while (string(answer) == "")
		{
			gets_s(answer, 225);
		}
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|                                                      Информация о найденных продуктах,которые находятся в магазинах                                                      |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  | Название продукта |     Марка продукта     | Цена(руб) |      Вид      | Кол-во(един.) | Вес, объём | Дата доставки |  Срок годности  |       Местоположение      |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

		if (mas_shop[0].name != NULL)
			for (int j = 0; mas_shop[j].ID != NULL; j++) {
				for (int i = 0; mas_shop[j].products_in_stock[i].ID != NULL; i++)
				{
					if (_strnicmp(mas_shop[j].products_in_stock[i].name, answer, string(answer).size()) == 0) {
						flag1 = true;
						printf("| %4d | %17s | %22s | %9d | %13s | %13d | %10s | %13s | %15s | %-10s %-14s |\n", mas_shop[j].products_in_stock[i].ID, mas_shop[j].products_in_stock[i].name,
							mas_shop[j].products_in_stock[i].brand, mas_shop[j].products_in_stock[i].cost, mas_shop[j].products_in_stock[i].description,
							mas_shop[j].products_in_stock[i].quantity, mas_shop[j].products_in_stock[i].quan_descr, mas_shop[j].products_in_stock[i].delivery_date.date_format, mas_shop[j].products_in_stock[i].expiration_date.date_format,
							mas_shop[j].name, mas_shop[j].adress
						);
						printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
						mas_shop[j].products_in_stock[i].counter_search++;
						
					}
					
				}
				
			}
	}
	if (!flag1) {
		printf("|            Нет информации о продуктах                         |\n");
	}
	else {
		save_shops_to_file(mas_shop);
	}
}

void search_p_in_stock_by_brand() {
	print_all_products_in_stock();
	char answer[255];

	int j = 0, num, flag = -1;
	bool flag1 = false;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}

	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		cout << endl << "Введите название марки продукта в магазине для поиска: ";
		fflush;
		gets_s(answer, 225);
		while (string(answer) == "")
		{
			gets_s(answer, 225);
		}
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|                                                            Информация о найденных продуктах, которые находятся в магазинах                                               |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  | Название продукта |     Марка продукта     | Цена(руб) |      Вид      | Кол-во(един.) | Вес, объём | Дата доставки |  Срок годности  |       Местоположение      |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

		if (mas_shop[0].name != NULL)
			for (int j = 0; mas_shop[j].ID != NULL; j++) {
				for (int i = 0; mas_shop[j].products_in_stock[i].ID != NULL; i++)
				{
					if (_strnicmp(mas_shop[j].products_in_stock[i].brand, answer, string(answer).size()) == 0) {
						flag1 = true;
						printf("| %4d | %17s | %22s | %9d | %13s | %13d | %10s | %13s | %15s | %-10s %-14s |\n", mas_shop[j].products_in_stock[i].ID, mas_shop[j].products_in_stock[i].name,
							mas_shop[j].products_in_stock[i].brand, mas_shop[j].products_in_stock[i].cost, mas_shop[j].products_in_stock[i].description,
							mas_shop[j].products_in_stock[i].quantity, mas_shop[j].products_in_stock[i].quan_descr, mas_shop[j].products_in_stock[i].delivery_date.date_format, mas_shop[j].products_in_stock[i].expiration_date.date_format,
							mas_shop[j].name, mas_shop[j].adress
						);
						printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
						mas_shop[j].products_in_stock[i].counter_search++;
					}

				}

			}
	}
	if (!flag1)
		printf("|            Нет информации о продуктах                         |\n");
	else {
		save_shops_to_file(mas_shop);
	}
}

void search_p_in_stock_by_id() {
	print_all_products_in_stock();
	int answer;

	int j = 0, num, flag = -1;
	bool flag1 = false;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}

	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		cout << endl << "Введите ID продукта в магазине для поиска: ";
		answer = int_checker();
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|                                                            Информация о найденных продуктах, которые находятся в магазинах                                               |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  | Название продукта |     Марка продукта     | Цена(руб) |      Вид      | Кол-во(един.) | Вес, объём | Дата доставки |  Срок годности  |       Местоположение      |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

		if (mas_shop[0].name != NULL)
			for (int j = 0; mas_shop[j].ID != NULL; j++) {
				for (int i = 0; mas_shop[j].products_in_stock[i].ID != NULL; i++)
				{
					if (mas_shop[j].products_in_stock[i].ID == answer) {
						flag1 = true;
						printf("| %4d | %17s | %22s | %9d | %13s | %13d | %10s | %13s | %15s | %-10s %-14s |\n", mas_shop[j].products_in_stock[i].ID, mas_shop[j].products_in_stock[i].name,
							mas_shop[j].products_in_stock[i].brand, mas_shop[j].products_in_stock[i].cost, mas_shop[j].products_in_stock[i].description,
							mas_shop[j].products_in_stock[i].quantity, mas_shop[j].products_in_stock[i].quan_descr, mas_shop[j].products_in_stock[i].delivery_date.date_format, mas_shop[j].products_in_stock[i].expiration_date.date_format,
							mas_shop[j].name, mas_shop[j].adress
						);
						printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
					}

				}

			}
	}
	if (!flag1)
		printf("|            Нет информации о продуктах                         |\n");
}

void search_p_in_order_by_name() {
	print_all_products_in_order();
	char answer[255];

	int j = 0, num, flag = -1;
	bool flag1 = false;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}

	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		cout << endl << "Введите название продукта в заказе для поиска: ";
		fflush;
		gets_s(answer, 225);
		while (string(answer) == "")
		{
			gets_s(answer, 225);
		}
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("                      Информация о продуктах,которые будут доставлены                  |\n");
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
		printf("+--------------------------------------------------------------------------------------+\n");

		if (mas_shop[0].name != NULL)
			for (int j = 0; mas_shop[j].ID != NULL; j++) {
				for (int i = 0; mas_shop[i].products_in_order[i].ID != NULL; i++)
				{
					if (_strnicmp(mas_shop[j].products_in_order[i].name, answer, string(answer).size()) == 0) {
						flag1 = true;
						printf("| %4d | %21s | %19s |  %14d | %13s |\n", mas_shop[j].products_in_order[i].ID, mas_shop[j].products_in_order[i].name,
							mas_shop[j].products_in_order[i].brand, mas_shop[j].products_in_order[i].quantity, mas_shop[j].products_in_order[i].order_date.date_format);
						printf("+--------------------------------------------------------------------------------------+\n");
					}

				}

			}
	}
	if (!flag1)
		printf("|            Нет информации о продуктах                         |\n");
}

void search_p_in_order_by_brand() {
	print_all_products_in_order();
	char answer[255];

	int j = 0, num, flag = -1;
	bool flag1 = false;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}

	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		cout << endl << "Введите название марки продукта в заказе для поиска: ";
		fflush;
		gets_s(answer, 225);
		while (string(answer) == "")
		{

			gets_s(answer, 225);
		}
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("                      Информация о продуктах,которые будут доставлены                  |\n");
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
		printf("+--------------------------------------------------------------------------------------+\n");

		if (mas_shop[0].name != NULL)
			for (int j = 0; mas_shop[j].ID != NULL; j++) {
				for (int i = 0; mas_shop[i].products_in_order[i].ID != NULL; i++)
				{
					if (_strnicmp(mas_shop[j].products_in_order[i].brand, answer, string(answer).size()) == 0) {
						flag1 = true;
						printf("| %4d | %21s | %19s |  %14d | %13s |\n", mas_shop[j].products_in_order[i].ID, mas_shop[j].products_in_order[i].name,
							mas_shop[j].products_in_order[i].brand, mas_shop[j].products_in_order[i].quantity, mas_shop[j].products_in_order[i].order_date.date_format);
						printf("+--------------------------------------------------------------------------------------+\n");
					}

				}

			}
	}
	if (!flag1)
		printf("|            Нет информации о продуктах                         |\n");
}

void search_p_in_order_by_id() {
	print_all_products_in_order();
	int answer;

	int j = 0, num, flag = -1;
	bool flag1 = false;
	int id_in_shop;
	int t;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}

	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		cout << endl << "Введите ID продукта в заказе для поиска: ";
		answer = int_checker();
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("                      Информация о продуктах,которые будут доставлены                  |\n");
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
		printf("+--------------------------------------------------------------------------------------+\n");

		if (mas_shop[0].name != NULL)
			for (int j = 0; mas_shop[j].ID != NULL; j++) {
				for (int i = 0; mas_shop[i].products_in_order[i].ID != NULL; i++)
				{
					if (mas_shop[j].products_in_order[i].ID == answer) {
						flag1 = true;
						printf("| %4d | %21s | %19s |  %14d | %13s |\n", mas_shop[j].products_in_order[i].ID, mas_shop[j].products_in_order[i].name,
							mas_shop[j].products_in_order[i].brand, mas_shop[j].products_in_order[i].quantity, mas_shop[j].products_in_order[i].order_date.date_format);
						printf("+--------------------------------------------------------------------------------------+\n");
					}

				}

			}
	}
	if (!flag1)
		printf("|            Нет информации о продуктах                         |\n");
}

void save_shops_to_file(Shop mass_shop[]) {
	FILE* F1 = fopen(shops, "w+");
	for (int i = 0; mass_shop[i].ID != NULL; i++) {
		fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
	}
	fclose(F1);
}

int view_edit_menu() {
	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//вниз
				choice++;
			if (ch == 72)//вверх
				choice--;
			if (choice > 3)//
				choice = 0;
			if (choice < 0)
				choice = 3;
			if (ch == 13)//enter
				return choice;
			printf(" .______________________________________________________.\n");
			printf(" |________________Редактирование поля___________________|  \n");
			if (choice == 0) {
				set_color("\x1b[38;5;15m");
				printf(" |        %c В магазине.                                 |\n", pointer);
				reset_color();
			}

			else
				printf(" |          В магазине.                                 |\n");
			if (choice == 1) {
				set_color("\x1b[38;5;15m");
				printf(" |        %c В конкретном продукте в магазине.           |\n", pointer);
				reset_color();
			}

			else
				printf(" |          В конкретном продукте в магазине.           |\n");
			if (choice == 2) {
				set_color("\x1b[38;5;15m");
				printf(" |        %c В конкретном продукте в заказе.             |\n", pointer);
				reset_color();
			}

			else
				printf(" |          В конкретном продукте в заказе.             |\n");

			if (choice == 3) {
				set_color("\x1b[38;5;15m");
				printf(" |        %c Выход в основное меню администратора.       |\n", pointer);
				reset_color();
			}

			else
				printf(" |          Выход в основное меню администратора.       |\n");


		}
		printf(" |______________________________________________________|\n");
		printf(" .______________________________________________________.\n");

		ch = _getch();
	}
}

void edit_menu() {
	bool flag = true;
	do
	{
		cls;
		switch (view_edit_menu())
		{
		case 0: {cls; edit_shop(); pause; break; }
		case 1: {cls; edit_p_in_stock(); pause; break; }
		case 2: {cls; edit_p_in_order(); pause; break; }
		

		case 3: {cls;
			flag = true;
			break; }
		default:  cls;
			printf("Такого пункта поиска меню нет!\n");
			pause;
			break;
		}
	} while (!flag);

}

void edit_shop() {
	int i = 0, num, flag_shop = -1, flag = 0;
	int g = 0;
	char o[1] = { '\0' };
	int id_in_shop;
	bool flag1 = false;
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
		cout << "Пустой файл! Необходимо добавить магазин!" << endl;
	else
	{
		print_all_shops();
		cout << "Введите ID магазина,который вы хотите изменить: " << endl;
		cin >> num; // проверка на ввод
		t_shop = index_by_id(mas_shop, num);

		cout <<"Выберите пункт поля, который вы хотите отредактировать: " << endl;
		cout << "1. Название магазина " << endl;
		cout << "2. Адрес магазина " << endl;
		cout << "3. Контактный телефон " << endl;
		char ch;
		cin.clear();
		cin >> ch;
		switch (ch)
		{

		case'1': {cls;
			while (g == 0) {
				cls;
				fflush(stdin);
				cout << "Введите новое название магазина: " << endl;
				gets_s(mas_shop[t_shop].name, 20);
				if (strcmp(mas_shop[t_shop].name, o) != 0)
					g = 1;
			}
			cls;
		    break; 
		}
		case'2': {cls;
			while (g == 0) {
				cls;
				fflush(stdin);
				cout << "Введите новый адрес магазина: " << endl;
				gets_s(mas_shop[t_shop].adress, 20);
				if (strcmp(mas_shop[t_shop].adress, o) != 0)
					g = 1;
			}
			
			cls;
			break;
		}
		case'3': {cls; 
				fflush(stdin);
				cout << "Введите контактный телефон магазина: " << endl;
				//mas_shop[t_shop].contact_tel_nomber = input_by_pattern("[0-9]+");
				mas_shop[t_shop].contact_tel_nomber = int_checker();
				cls;
				//pause; 
				break; 
		}

		case'0': { cls; flag = false; pause; break; }
		default: {cls; cout << "Такой операции не существует!" << endl;
			pause; break; }

		}


		FILE* F1 = fopen(shops, "w+");
		for (int i = 0; mas_shop[i].ID != NULL; i++) {
			fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
		}
		fclose(F1);

	}

}

void edit_p_in_stock() {
	int i = 0, num, answer, flag_shop = -1, flag = 0;
	int g = 0;
	char o[1] = { '\0' };
	int id_in_shop;
	bool flag1 = false;
	bool flag3 = true;
	int t_shop, t_product_stock;
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
		cout << "Пустой файл! Необходимо добавить магазин!" << endl;
	else
	{
		print_all_shops();
		cout << "Введите ID магазина,в котором вы хотите изменить информацию о продукте: " << endl;
		cin >> num; // проверка на ввод
		t_shop = index_by_id(mas_shop, num);

		cls;
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|                                                                Информация о продуктах,которые находятся в магазине                                                       |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
		printf("|  ID  | Название продукта |     Марка продукта     | Цена(руб) |      Вид      | Кол-во(един.) | Вес, объём | Дата доставки |  Срок годности  |       Местоположение      |\n");
		printf("+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

		print_products_in_stock(mas_shop[t_shop]);

		cout << "Ведите ID продукта , поле которого вы хотите изменить: " << endl;
		cin >> answer; // проверка на ввод
		t_product_stock = index_by_id(mas_shop[t_shop].products_in_stock, answer);


		cout << "Выберите пункт поля, который вы хотите отредактировать: " << endl;
		cout << "1. Название продукта: " << endl;
		cout << "2. Марка продукта: " << endl;
		cout << "3. Цена продукта: " << endl;
		cout << "4. Характеристика продукта: " << endl;
		cout << "5. Количество продуктов(единиц): " << endl;
		cout << "6. Вес продукта: " << endl;
		cout << "7. Срок годности: " << endl;
		cout << "8. Дата доставки: " << endl;
		
		char ch;
		cin.clear();
		cin >> ch;
		switch (ch)
		{

		case'1': {cls;
			while (g == 0) {
				cls;
				fflush(stdin);
				cout << "Введите новое название продукта:" << endl;
				gets_s(mas_shop[t_shop].products_in_stock[t_product_stock].name, 20);
				if (strcmp(mas_shop[t_shop].products_in_stock[t_product_stock].name, o) != 0)
					g = 1;
			}
			cls;
			break;
		}
		case'2': {cls;
			while (g == 0) {
				cls;
				fflush(stdin);
				cout << "Введите новое название марки продукта:" << endl;
				gets_s(mas_shop[t_shop].products_in_stock[t_product_stock].brand, 20);
				if (strcmp(mas_shop[t_shop].products_in_stock[t_product_stock].brand, o) != 0)
					g = 1;
			}
			cls;
			break;
		}
		case'3': {cls;
			
				fflush(stdin);
				cout << "Введите новую стоимость продукта (в белорусских рублях):" << endl;
				//mas_shop[t_shop].products_in_stock[t_product_stock].cost = input_by_pattern("[0-9]+");
				mas_shop[t_shop].products_in_stock[t_product_stock].cost = int_checker();

			cls;
			break;
		}
		case'4': {cls;
			while (g == 0) {
				cls;
				fflush(stdin);
				cout << "Введите новую характеристику продукта:" << endl;
				gets_s(mas_shop[t_shop].products_in_stock[t_product_stock].description, 20);
				if (strcmp(mas_shop[t_shop].products_in_stock[t_product_stock].description, o) != 0)
					g = 1;
			}
			cls;
			break;
		}
		case'5': {cls; 
			cls;
			fflush(stdin);
			cout << "Введите новое количество продукта:" << endl;
			//mas_shop[t_shop].products_in_stock[t_product_stock].quantity = input_by_pattern("[0-9]+");
			mas_shop[t_shop].products_in_stock[t_product_stock].quantity = int_checker();
				 cls;
			break;
		}
		case'6': {cls; while (g == 0) {
			cls;
			fflush(stdin);
			cout << "Введите новую весовую характеристику продукта:" << endl;
			gets_s(mas_shop[t_shop].products_in_stock[t_product_stock].quan_descr, 20);
			if (strcmp(mas_shop[t_shop].products_in_stock[t_product_stock].quan_descr, o) != 0)
				g = 1;
		}
				 cls;
			break;
		}
		case'7': {cls;

			while (flag3) {
				cout << "Введите новую дату срока годности продукта(Формат ввода : XX.XX.XXXX)  :" << endl;
				char check[30];
				fflush(stdin);
				cin >> check;
				if (check_date(check)) {
					flag3 = false;
					strcpy(mas_shop[t_shop].products_in_stock[t_product_stock].expiration_date.date_format, check);
					int d = 0;
					char dd[3], mm[3], yyyy[5];
					for (; d < 2; d++)
						dd[d] = check[d];
					dd[2] = '\0';
					mas_shop[t_shop].products_in_stock[t_product_stock].expiration_date.day = atoi(dd);

					for (int j = 0, d = 3; d < 5; d++, j++) {
						mm[j] = check[d];
					}
					mm[2] = '\0';
					mas_shop[t_shop].products_in_stock[t_product_stock].expiration_date.month = atoi(mm);
					for (int j = 0, d = 6; d < (int)strlen(check) + 1; d++, j++) {
						yyyy[j] = check[d];
					}
					yyyy[4] = '\0';
					mas_shop[t_shop].products_in_stock[t_product_stock].expiration_date.year = atoi(yyyy);

				}
				cls;
				break;
			}
		}

		case'8': {cls; while (flag3)
		{
			cout << "Введите новую дату доставки продукта(Формат ввода : XX.XX.XXXX)  :" << endl;
			char check[30];
			fflush(stdin);
			cin >> check;
			int ans = check_date(check);
			if (ans) {
				flag3 = false;
				strcpy(mas_shop[t_shop].products_in_stock[t_product_stock].delivery_date.date_format, check);
				int d = 0;
				char dd[3], mm[3], yyyy[5];
				for (; d < 2; d++)
					dd[d] = check[d];
				dd[2] = '\0';
				mas_shop[t_shop].products_in_stock[t_product_stock].delivery_date.day = atoi(dd);

				for (int j = 0, d = 3; d < 5; d++, j++) {
					mm[j] = check[d];
				}
				mm[2] = '\0';
				mas_shop[t_shop].products_in_stock[t_product_stock].delivery_date.month = atoi(mm);
				for (int j = 0, d = 6; d < (int)strlen(check) + 1; d++, j++) {
					yyyy[j] = check[d];
				}
				yyyy[4] = '\0';
				mas_shop[t_shop].products_in_stock[t_product_stock].delivery_date.year = atoi(yyyy);

			}
		}
		      cls;
			  break;
		}
		

		case'0': { cls; flag = false; pause; break; }

		default: {cls; cout << "Такой операции не существует!" << endl;
			pause; break; }
		}

		save_shops_to_file(mas_shop);
		//FILE* F1 = fopen(shops, "w+");
		//for (int i = 0; mas_shop[i].ID != NULL; i++) {
		//	fwrite(&mas_shop[i], sizeof(struct Shop), 1, F1);
		//}
		//fclose(F1);

	}
}

//изменить эту функцию
void edit_p_in_order() {
	int i = 0, num, answer, flag_shop = -1, flag = 0;
	int g = 0;
	char o[1] = { '\0' };
	int id_in_shop;
	bool flag1 = false;
	bool flag3 = true;
	int t_shop, t_product_order;
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
		cout << "Пустой файл! Необходимо добавить магазин!" << endl;
	else
	{
		print_all_shops();
		cout << "Введите ID магазина,в котором вы хотите изменить информацию о заказанном продукте: " << endl;
		cin >> num; // проверка на ввод
		t_shop = index_by_id(mas_shop, num);

		cls;
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("                      Информация о продуктах,которые будут доставлены                  |\n");
		printf("+--------------------------------------------------------------------------------------+\n");
		printf("|  ID  |   Название продукта   |    Марка продукта   | Количество(ед.) | Дата доставки | \n");
		printf("+--------------------------------------------------------------------------------------+\n");

		print_products_in_order(mas_shop[t_shop]);

		cout << "Ведите ID продукта , поле которого вы хотите изменить: " << endl;
		cin >> answer; // проверка на ввод
		t_product_order = index_by_id(mas_shop[t_shop].products_in_order, answer);


		cout << "Выберите пункт поля, который вы хотите отредактировать: " << endl;
		cout << "1. Название продукта: " << endl;
		cout << "2. Марка продукта: " << endl;
		cout << "3. Количество продуктов(единиц): " << endl;
		cout << "4. Дата доставки: " << endl;

		char ch;
		cin.clear();
		cin >> ch;
		switch (ch)
		{

		case'1': {cls;
			while (g == 0) {
				cls;
				fflush(stdin);
				cout << "Введите новое название продукта:" << endl;
				gets_s(mas_shop[t_shop].products_in_order[t_product_order].name, 20);
				if (strcmp(mas_shop[t_shop].products_in_order[t_product_order].name, o) != 0)
					g = 1;
			}
			cls;
			break;
		}
		case'2': {cls;
			while (g == 0) {
				cls;
				fflush(stdin);
				cout << "Введите новое название марки продукта:" << endl;
				gets_s(mas_shop[t_shop].products_in_order[t_product_order].brand, 20);
				if (strcmp(mas_shop[t_shop].products_in_order[t_product_order].brand, o) != 0)
					g = 1;
			}
			cls;
			break;
		}
		
		
		case'3': {cls;
			cls;
			fflush(stdin);
			cout << "Введите новое количество ввозимого продукта:" << endl;
			//mas_shop[t_shop].products_in_order[t_product_order].quantity = input_by_pattern("[0-9]+");
			mas_shop[t_shop].products_in_order[t_product_order].quantity = int_checker();
			cls;
			break;
		}
		

		case'4': {cls; while (flag3)
		{
			cout << "Введите новую дату доставки продукта(Формат ввода : XX.XX.XXXX)  :" << endl;
			char check[30];
			fflush(stdin);
			cin >> check;
			int ans = check_date(check);
			if (ans) {
				flag3 = false;
				strcpy(mas_shop[t_shop].products_in_order[t_product_order].order_date.date_format, check);
				int d = 0;
				char dd[3], mm[3], yyyy[5];
				for (; d < 2; d++)
					dd[d] = check[d];
				dd[2] = '\0';
				mas_shop[t_shop].products_in_order[t_product_order].order_date.day = atoi(dd);

				for (int j = 0, d = 3; d < 5; d++, j++) {
					mm[j] = check[d];
				}
				mm[2] = '\0';
				mas_shop[t_shop].products_in_order[t_product_order].order_date.month = atoi(mm);
				for (int j = 0, d = 6; d < (int)strlen(check) + 1; d++, j++) {
					yyyy[j] = check[d];
				}
				yyyy[4] = '\0';
				mas_shop[t_shop].products_in_order[t_product_order].order_date.year = atoi(yyyy);

			}
		}
				 cls;
				 break;
		}


		case'0': { cls; flag = false; pause; break; }

		default: {cls; cout << "Такой операции не существует!" << endl;
			pause; break; }
		}

		save_shops_to_file(mas_shop);


	}
}

bool is_product_in_vector(ProductsInStock product, vector<PopularProductsInStock>& popular_products) {
	for (int i = 0; i < popular_products.size(); i++) {
		if (_stricmp(popular_products[i].name, product.name) == 0) {
			return true;
		}
	
	}
	return false;

}

PopularProductsInStock count_all_products(ProductsInStock product, Shop mass_shop[]) {
	int counter_all_search = 0;

	for (int i = 0; mass_shop[i].ID != NULL; i++) {
		for (int j = 0; mass_shop[i].products_in_stock[j].ID != NULL; j++) {
			if (_stricmp(mass_shop[i].products_in_stock[j].name, product.name) == 0) {
				counter_all_search += mass_shop[i].products_in_stock[j].counter_search;
			}
		}
	}

	struct PopularProductsInStock p1;
	strcpy(p1.name, product.name);
	p1.all_search_counter = counter_all_search;
	return p1;

}

bool is_bigger_popular(PopularProductsInStock f_product, PopularProductsInStock s_product) {
	return f_product.all_search_counter > s_product.all_search_counter;
}

void print_popular_products(vector<PopularProductsInStock> popular_products) {
	int count = 0;
	cout << "|---------3 самых популярных продукта----------|" << endl;
	for (PopularProductsInStock product : popular_products) {
		if (count == NUMBER_OF_POPULAR_PRODUCTS) {
			break;
		}
		cout << "     \"" << product.name << "\"    " << " Количество поисков: "<< product.all_search_counter << endl;
		count++;
	}
	cout << "|----------------------------------------------|" << endl;
}


void main_task() {
	int j = 0, num, flag = -1;
	F1 = fopen(shops, "r+");
	while (!feof(F1))
	{
		fread(&mas_shop[j], sizeof(struct Shop), 1, F1);
		flag = j;
		j++;
	}

	fclose(F1);
	if (flag == -1)
		cout << "Пустой файл! Необходимо добавить магазин и находящиеся в нём продукты!" << endl;
	else
	{
		vector<PopularProductsInStock> popular_products;
		for (int i = 0; mas_shop[i].ID != NULL; i++) {
			for (int j = 0; mas_shop[i].products_in_stock[j].ID != NULL; j++) {
				if (!is_product_in_vector(mas_shop[i].products_in_stock[j], popular_products)) {
					popular_products.push_back(count_all_products(mas_shop[i].products_in_stock[j], mas_shop));

				}
			}

		}

		sort(popular_products.begin(), popular_products.end(), is_bigger_popular);
		print_popular_products(popular_products);
		system("pause");
	}

}