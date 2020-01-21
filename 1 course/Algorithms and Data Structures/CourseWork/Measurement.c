#include "Measurement.h"
#include "3arr.h"
#include "Vec.h"
#include <stdlib.h>
#include <time.h>

clock_t Res[measurements_number];

int Time_Measurememt(void (*f)(int***), int filltype)
{
	int i;

	for(i = 0;i < measurements_number;i++)
	{
		int ***arr = create_arr();
		if(filltype == 1)	fill_sort(arr);
		else if(filltype == 2)	fill_rev_sort(arr);
		else if(filltype == 3)	fill_random(arr);

		clock_t start = clock();
		f(arr);//������ ������� ����������
		clock_t end = clock();
		Res[i] = end - start;
		free_arr(arr);
	}
	return MeasurementProcessing();// ���������� ���������� ����������
}

int Time_Measurememt_Vec(void (*f)(int*), int filltype)
{
	int i;
	int *vec = create_vec();

	for(i = 0;i < measurements_number;i++)
	{
		if(filltype == 1)	fill_sort_vec(vec);
		else if(filltype == 2)	fill_rev_sort_vec(vec);
		else if(filltype == 3)	fill_random_vec(vec);

		clock_t start = clock();
		f(vec);//������ ������� ����������
		clock_t end = clock();
		Res[i] = end - start;
	}
	free(vec);
	return MeasurementProcessing()*P*2;// ���������� ���������� ���������� ���������� �� 2(������� ���������) � �� P(������� �������)
}

int MeasurementProcessing()
{
	int i;
    long int Sum,Min1,Min2,Min3,Max1,Max2,Max3;
    int imin1,imin2,imin3,imax1,imax2,imax3;

    // ��� ������ ����� (0-� �� 1-�) �����������
    // ����� ����� �������� ��������� ��� ��������� �� ��� ������������
    // �������� � ������� �� �������� �� �������� ����

    // ��������� ��������� �� ������������ �������� � ��������� �� � ���������
    // ������, ����������� �� �������� -1

    Sum = Res[2]; Min1 = Res[2]; Max1 = Res[2]; imin1 = 2; imax1 = 2;
    for (i = 3; i < measurements_number; i++)
    {
        Sum = Sum + Res[i];
        if (Res[i] > Max1) { Max1 = Res[i]; imax1 = i; }
        else if (Res[i] < Min1) { Min1 = Res[i]; imin1 = i; }
    }
    Res[imin1]=-1; Res[imax1]=-1;

    // ��������� ������ ��������� �� ������ ������������ ��������
    // � ��������� �� � ��������� ������, ����������� �� �������� -1

    if (Res[2] == -1) {Min2 = Res[3]; imin2 = 3;}
    else {Min2 = Res[2]; imin2 = 2;}
    Max2 = Res[2]; imax2 = 2;
    for (i = 3; i < measurements_number; i++)
    {
        if (Res[i] > Max2) { Max2 = Res[i]; imax2 = i; }
        else if (Res[i]<Min2 && Res[i]!=-1) { Min2 = Res[i]; imin2 = i; }
    }
    Res[imin2]=-1; Res[imax2]=-1;

    // ��������� ����� ��������� �� ����� ������������ ��������

    if (Res[2] == -1)
        if (Res[3] == -1) {Min3 = Res[4]; imin3 = 4;}
        else {Min3 = Res[3]; imin3 = 3;}
    else {Min3 = Res[2]; imin3 = 2;}
    Max3 = Res[2]; imax3 = 2;
    for (i = 3; i < measurements_number; i++)
    {
        if (Res[i] > Max3) { Max3 = Res[i]; imax3 = i; }
        else if (Res[i]<Min3 && Res[i]!=-1) { Min3 = Res[i]; imin3 = i; }
    }

    // ���� ��� ����� ���� ��� ������������ �� ��� ��������� �������� ���� �������� �� 0-�� �������� ������ Res

    Res[0] = Sum - Min1 - Min2 - Min3 - Max1 - Max2 - Max3;

    //ĳ���� �������� �������� �� ������� ��� � ������ ��
    // ������� �����, �� �� ���������

    return Res[0]/20;
}
