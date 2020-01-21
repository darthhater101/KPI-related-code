#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//��� setlocale
#include "Algorithms.h"
#include "3arr.h"
#include "Alg_vec.h"
#include "Vec.h"
#include "Measurement.h"

#define AlgNumber 4
#define Type 3
#define Item 4

char Algs[AlgNumber][255] = {
"�������� ����������",
"����� ������� ������",
"���������� �����",
"����� ����� ������� �2"
};

char Types[Type][255] = {
"³�����������",
"����������",
"�������� ������������"
};

char Items[Item][255] = {
"���������� ����������� ������",
"���������� �������",
"�������� ������ ��� ����������� ������",
"�����"
};

void test_3Darr(int alg, int type)// ��� ����� ������� ��������� ��� ������� ���� ����������� ������
{
    if(alg == 0)
    {
        if(type == 0) printf("��� ������ = %d", Time_Measurememt(Cocktail_Sort, 1));
        else if(type == 1) printf("��� ������ = %d",Time_Measurememt(Cocktail_Sort, 2));
        else if(type == 2) printf("��� ������ = %d",Time_Measurememt(Cocktail_Sort, 3));
    }
    else if(alg == 1)
    {
        if(type == 0) printf("��� ������ = %d",Time_Measurememt(Selection_Sort, 1));
        else if(type == 1) printf("��� ������ = %d",Time_Measurememt(Selection_Sort, 2));
        else if(type == 2) printf("��� ������ = %d",Time_Measurememt(Selection_Sort, 3));
    }
    else if(alg == 2)
    {
        if(type == 0) printf("��� ������ = %d",Time_Measurememt(Shell_Sort, 1));
        else if(type == 1) printf("��� ������ = %d",Time_Measurememt(Shell_Sort, 2));
        else if(type == 2) printf("��� ������ = %d",Time_Measurememt(Shell_Sort, 3));
    }
    else if(alg == 3)
    {
        if(type == 0) printf("��� ������ = %d",Time_Measurememt(Insertion_Sort, 1));
        else if(type == 1) printf("��� ������ = %d",Time_Measurememt(Insertion_Sort, 2));
        else if(type == 2) printf("��� ������ = %d",Time_Measurememt(Insertion_Sort, 3));
    }
    printf("\n");
    printf("�������� ��� �����������...");
    getch();
}

void all_tests_vec()//�������� ������ ��� �������
{
	system("cls");
	printf("���������� ������ �������� N = %d\n", N);
	printf("+-----------------------------------------------------------------------+\n");
    printf("���������    /     �����³������������������� ����������������������\n");
    printf("+-----------------------+-------------+----------------------+----------�\n");
    printf("�  �������� ����������  �");
    printf("%13d�",Time_Measurememt_Vec(Cocktail_Sort_Vec, 1));
    printf("%22d�",Time_Measurememt_Vec(Cocktail_Sort_Vec, 2));
    printf("%10d�\n",Time_Measurememt_Vec(Cocktail_Sort_Vec, 3));

    printf("+-----------------------+-------------+----------------------+----------�\n");
    printf("������ ������� ������ �6�");
    printf("%13d�",Time_Measurememt_Vec(Selection_Sort_Vec, 1));
    printf("%22d�",Time_Measurememt_Vec(Selection_Sort_Vec, 2));
    printf("%10d�\n",Time_Measurememt_Vec(Selection_Sort_Vec, 3));

    printf("+-----------------------+-------------+----------------------+----------�\n");
    printf("�    ���������� �����   �");
    printf("%13d�",Time_Measurememt_Vec(Shell_Sort_Vec, 1));
    printf("%22d�",Time_Measurememt_Vec(Shell_Sort_Vec, 2));
    printf("%10d�\n",Time_Measurememt_Vec(Shell_Sort_Vec, 3));

    printf("+-----------------------+-------------+----------------------+----------�\n");
    printf("������ ����� ������� �2�");
    printf("%13d�",Time_Measurememt_Vec(Insertion_Sort_Vec, 1));
    printf("%22d�",Time_Measurememt_Vec(Insertion_Sort_Vec, 2));
    printf("%10d�\n",Time_Measurememt_Vec(Insertion_Sort_Vec,3));

    printf("+-----------------------------------------------------------------------+\n");
    printf("�������� ��� �����������...");
    getch();
}

void all_tests()// �������� ������ ��� ����������� ������

{
	system("cls");
	printf("���������� ����� �������� P = %d N = %d\n", P, N);
	printf("ĳ������� ������� %d\n", N);
	printf("+-----------------------------------------------------------------------+\n");
    printf("���������    /     �����³������������������� ����������������������\n");
    printf("+-----------------------+-------------+----------------------+----------�\n");
    printf("�  �������� ����������  �");
    printf("%13d�",Time_Measurememt(Cocktail_Sort, 1));
    printf("%22d�",Time_Measurememt(Cocktail_Sort, 2));
    printf("%10d�\n",Time_Measurememt(Cocktail_Sort, 3));

    printf("+-----------------------+-------------+----------------------+----------�\n");
    printf("������ ������� ������ �6�");
    printf("%13d�",Time_Measurememt(Selection_Sort, 1));
    printf("%22d�",Time_Measurememt(Selection_Sort, 2));
    printf("%10d�\n",Time_Measurememt(Selection_Sort, 3));

    printf("+-----------------------+-------------+----------------------+----------�\n");
    printf("�    ���������� �����   �");
    printf("%13d�",Time_Measurememt(Shell_Sort, 1));
    printf("%22d�",Time_Measurememt(Shell_Sort, 2));
    printf("%10d�\n",Time_Measurememt(Shell_Sort, 3));

    printf("+-----------------------+-------------+----------------------+----------�\n");
    printf("������ ����� ������� �2�");
    printf("%13d�",Time_Measurememt(Insertion_Sort, 1));
    printf("%22d�",Time_Measurememt(Insertion_Sort, 2));
    printf("%10d�\n",Time_Measurememt(Insertion_Sort ,3));

    printf("+-----------------------------------------------------------------------+\n");
    printf("�������� ��� �����������...");
    getch();
}

void Menu()//��������� ��������
{
    while(1){
		system("cls");
		int i;
		for(i = 0; i < Item; i++){
			printf("%d. %s\n", i+1, Items[i]);
		}
		printf("������ ��� ������� ��������: ");
		char buff;
		while(1){
			buff = getch();
			if(buff < '1' || buff > '4'){
				printf("\n������� ���, ��������: ");
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
                printf("������ ��������: ");
                while(1)
                {
                    buff = getch();
                    if(buff < '1' || buff > '4')
                    {
                        printf("\n������� ���, ��������: ");
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
                    printf("������ ��� ����������: ");
                    while(1)
                    {
                        buff = getch();
                        if(buff < '1' || buff > '3')
                        {
                            printf("\n������� ���, ��������: ");
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
    system("chcp 65001");//������������ ��������� UTF-8 ��� ������
	setlocale(LC_CTYPE, "ukr");//������������ ��������� ��� ������
	system("cls");
    Menu();
	return 0;
}
