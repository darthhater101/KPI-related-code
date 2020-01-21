#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//для setlocale
#include "Algorithms.h"
#include "3arr.h"
#include "Alg_vec.h"
#include "Vec.h"
#include "Measurement.h"

#define AlgNumber 4
#define Type 3
#define Item 4

char Algs[AlgNumber][255] = {
"Шейкерне сортування",
"Метод прямого вибору",
"Сортування Шелла",
"Метод прямої вставки №2"
};

char Types[Type][255] = {
"Відсортований",
"Випадковий",
"Обернено відсортований"
};

char Items[Item][255] = {
"Сортування тривимірного масиву",
"Сортування вектора",
"Пакетний запуск для тривимірного масиву",
"Вихід"
};

void test_3Darr(int alg, int type)// для тесту певного алгоритму для певного типу тривимірного масиву
{
    if(alg == 0)
    {
        if(type == 0) printf("Час роботи = %d", Time_Measurememt(Cocktail_Sort, 1));
        else if(type == 1) printf("Час роботи = %d",Time_Measurememt(Cocktail_Sort, 2));
        else if(type == 2) printf("Час роботи = %d",Time_Measurememt(Cocktail_Sort, 3));
    }
    else if(alg == 1)
    {
        if(type == 0) printf("Час роботи = %d",Time_Measurememt(Selection_Sort, 1));
        else if(type == 1) printf("Час роботи = %d",Time_Measurememt(Selection_Sort, 2));
        else if(type == 2) printf("Час роботи = %d",Time_Measurememt(Selection_Sort, 3));
    }
    else if(alg == 2)
    {
        if(type == 0) printf("Час роботи = %d",Time_Measurememt(Shell_Sort, 1));
        else if(type == 1) printf("Час роботи = %d",Time_Measurememt(Shell_Sort, 2));
        else if(type == 2) printf("Час роботи = %d",Time_Measurememt(Shell_Sort, 3));
    }
    else if(alg == 3)
    {
        if(type == 0) printf("Час роботи = %d",Time_Measurememt(Insertion_Sort, 1));
        else if(type == 1) printf("Час роботи = %d",Time_Measurememt(Insertion_Sort, 2));
        else if(type == 2) printf("Час роботи = %d",Time_Measurememt(Insertion_Sort, 3));
    }
    printf("\n");
    printf("Натисніть для продовження...");
    getch();
}

void all_tests_vec()//пакетний запуск для вектора
{
	system("cls");
	printf("Вимірюється вектор розмірами N = %d\n", N);
	printf("+-----------------------------------------------------------------------+\n");
    printf("¦Алгоритм    /     Масив¦Відсортований¦Обернено відсортований¦Випадковий¦\n");
    printf("+-----------------------+-------------+----------------------+----------¦\n");
    printf("¦  Шейкерне сортування  ¦");
    printf("%13d¦",Time_Measurememt_Vec(Cocktail_Sort_Vec, 1));
    printf("%22d¦",Time_Measurememt_Vec(Cocktail_Sort_Vec, 2));
    printf("%10d¦\n",Time_Measurememt_Vec(Cocktail_Sort_Vec, 3));

    printf("+-----------------------+-------------+----------------------+----------¦\n");
    printf("¦Метод прямого вибору №6¦");
    printf("%13d¦",Time_Measurememt_Vec(Selection_Sort_Vec, 1));
    printf("%22d¦",Time_Measurememt_Vec(Selection_Sort_Vec, 2));
    printf("%10d¦\n",Time_Measurememt_Vec(Selection_Sort_Vec, 3));

    printf("+-----------------------+-------------+----------------------+----------¦\n");
    printf("¦    Сортування Шелла   ¦");
    printf("%13d¦",Time_Measurememt_Vec(Shell_Sort_Vec, 1));
    printf("%22d¦",Time_Measurememt_Vec(Shell_Sort_Vec, 2));
    printf("%10d¦\n",Time_Measurememt_Vec(Shell_Sort_Vec, 3));

    printf("+-----------------------+-------------+----------------------+----------¦\n");
    printf("¦Метод прямої вставки №2¦");
    printf("%13d¦",Time_Measurememt_Vec(Insertion_Sort_Vec, 1));
    printf("%22d¦",Time_Measurememt_Vec(Insertion_Sort_Vec, 2));
    printf("%10d¦\n",Time_Measurememt_Vec(Insertion_Sort_Vec,3));

    printf("+-----------------------------------------------------------------------+\n");
    printf("Натисніть для продовження...");
    getch();
}

void all_tests()// пакетний запуск для тривимірного масиву

{
	system("cls");
	printf("Вимірюється масив розмірами P = %d N = %d\n", P, N);
	printf("Діагональ розміром %d\n", N);
	printf("+-----------------------------------------------------------------------+\n");
    printf("¦Алгоритм    /     Масив¦Відсортований¦Обернено відсортований¦Випадковий¦\n");
    printf("+-----------------------+-------------+----------------------+----------¦\n");
    printf("¦  Шейкерне сортування  ¦");
    printf("%13d¦",Time_Measurememt(Cocktail_Sort, 1));
    printf("%22d¦",Time_Measurememt(Cocktail_Sort, 2));
    printf("%10d¦\n",Time_Measurememt(Cocktail_Sort, 3));

    printf("+-----------------------+-------------+----------------------+----------¦\n");
    printf("¦Метод прямого вибору №6¦");
    printf("%13d¦",Time_Measurememt(Selection_Sort, 1));
    printf("%22d¦",Time_Measurememt(Selection_Sort, 2));
    printf("%10d¦\n",Time_Measurememt(Selection_Sort, 3));

    printf("+-----------------------+-------------+----------------------+----------¦\n");
    printf("¦    Сортування Шелла   ¦");
    printf("%13d¦",Time_Measurememt(Shell_Sort, 1));
    printf("%22d¦",Time_Measurememt(Shell_Sort, 2));
    printf("%10d¦\n",Time_Measurememt(Shell_Sort, 3));

    printf("+-----------------------+-------------+----------------------+----------¦\n");
    printf("¦Метод прямої вставки №2¦");
    printf("%13d¦",Time_Measurememt(Insertion_Sort, 1));
    printf("%22d¦",Time_Measurememt(Insertion_Sort, 2));
    printf("%10d¦\n",Time_Measurememt(Insertion_Sort ,3));

    printf("+-----------------------------------------------------------------------+\n");
    printf("Натисніть для продовження...");
    getch();
}

void Menu()//інтерфейс програми
{
    while(1){
		system("cls");
		int i;
		for(i = 0; i < Item; i++){
			printf("%d. %s\n", i+1, Items[i]);
		}
		printf("Введіть тип запуску програми: ");
		char buff;
		while(1){
			buff = getch();
			if(buff < '1' || buff > '4'){
				printf("\nНевірний ввід, повторіть: ");
				continue;
			}
			break;
		}
		int buffItem = buff - '1';
		system("cls");
		if(buffItem == 0)
		{
		    while(1)
            {
                for(i = 0; i < AlgNumber; i++)
                {
                    printf("%d. %s\n", i+1, Algs[i]);
                }
                printf("Введіть алгоритм: ");
                while(1)
                {
                    buff = getch();
                    if(buff < '1' || buff > '4')
                    {
                        printf("\nНевірний ввід, повторіть: ");
                        continue;
                    }
                    break;
                }
                int buffAlg = buff - '1';
                system("cls");
                while(1)
                {
                    for(i = 0; i < Type; i++)
                    {
                        printf("%d. %s\n", i+1, Types[i]);
                    }
                    printf("Введіть тип заповнення: ");
                    while(1)
                    {
                        buff = getch();
                        if(buff < '1' || buff > '3')
                        {
                            printf("\nНевірний ввід, повторіть: ");
                            continue;
                        }
                        break;
                    }
                    int buffType = buff - '1';
                    system("cls");
                    test_3Darr(buffAlg, buffType);
                    break;
                }
                break;
            }
		}
        else if(buffItem == 1)
        {
            all_tests_vec();
        }
        else if(buffItem == 2)
        {
            all_tests();
        }
        else
        {
            break;
        }

}
    }

int main()
{
    system("chcp 65001");//встановлення кодування UTF-8 для консолі
	setlocale(LC_CTYPE, "ukr");//встановлення української для консолі
	system("cls");
    Menu();
	return 0;
}
