// что-то по слау.cpp 
// тупо решаем
// ОШИБКА В СКОРАХ 77-94
// СТРОКИ ВРОДЕ МЕНЯЮТСЯ А ВТОДЕ И НЕТ
// НУЖНО РАЗОБРАТЬСЯ



#include "pch.h"
#include "locale.h"
#include "math.h"
#include "stdio.h"
#include "malloc.h"

// вывод матрицы
void printSLAU(double **a, int lines, int columns)
{
	printf("\n");
	for (int i = 0; i < lines; i++)
	{
		printf("\n");
		for (int j = 0; j < columns; j++)
		{
			printf(" %0.2lf ", *(*(a + i) + j));
		}
	}
}

// проверка сходимости
// если 1 - сходимость есть
// если 0 - ее нет
int convergence(double **a, int lines, int columns) 
{
	int num = 0;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns-1; j++)
		{
			if ((i == j) && (*(*(a + i) + j)) != 0) { num++; }
		}
	}
	if (num == lines) { num = 1; }
	else { num = 0; }
	return num;
}

// SFTS - search for the same (поиск одинаковых)
// тут ищятся одинаковые или квивалентные сткочки
//
void sfts(double **a, int lines, int columns, int *err, int *lin)
{
	int numE = 0; // число для ошибок
	int numI; // число для запоминания строки
	// int *numL;
	// numL = &lines;

	for (int i = 0; i < lines; i++)
	{
		for (int k = 0; k < lines; k++)
		{
			int numC = 0; // число для проверки
			for (int j = 0; j < columns; j++)
			{
				if (i != j)
				{
					if (*(*(a + i) + j) == *(*(a + k) + j)) { numC++; }
				}
			}
			if (numC == columns) { numE = 1; numI = k; } // поиск номера эквивалентной строки
		}
	}

	if (numE == 0) { *err = 0; }
	else { *lin = numI; }

}

// удаление строк
void dellines(double **a, int *plines, int columns, int *lin)
{
	int line = *lin;
	int lines = *plines;

	for (int j = 0; j < columns; j++)
	{
		double num;
		num = *(*(a + 4) + j); 
		*(*(a + 2) + j) = num;
		 printf(" %0.2lf ", *(*(a + 2) + j));
	}

	int l;
	l = *plines;
	l--;
	*plines = l;
}



int main()
{
	setlocale(LC_ALL, "RUS");

	int lines = 0;  //строчки
	int *plines;
	plines = &lines;

	int columns = 0; //столбцы
	int *pcolumns;
	pcolumns = &columns;

//	ВВОД МАТРИЦЫ (СЛАУ)


	printf("Введите кол-во уравнений \n");
	scanf_s("%d", &lines);  // Ввод кол-ва строчек

	printf("Введите кол-во неизвестных \n");
	scanf_s("%d", &columns); // Ввод кол-ва столбцов, так же +1 так как еще столбик с ответами

	columns++; 

	double** SLAU = (double**)malloc(lines * sizeof(double*)); // Выделение памяти для строк с укозателями

	for (int i = 0; i < lines; i++) // Выделение памяти в каждой строке для столбцов указателей
	{
		SLAU[i] = (double*)malloc(lines * sizeof(double));
	}

	// заполнение чтобы не делать это вручную каждый раз
	int x = 0;
	for (int i = 0; i < lines; i++)
	{
		printf("\n");
		for (int j = 0; j < columns; j++)
		{
			x++;
			SLAU[i][j] = x;
			//SLAU[0][0] = 0;
			SLAU[1][1] = 0;
			//SLAU[2][2] = 0;
			SLAU[1][0] = 1; SLAU[1][1] = 2; SLAU[1][2] = 3; SLAU[1][3] = 4; SLAU[1][4] = 5; SLAU[1][5] = 6;
		}
	}

	printSLAU(SLAU, lines, columns);


	// поиск и удаление одинаковых строк
	int error = 1; // для ошибок
	int *err; // указатель на переменную для ошибок
	err = &error;
	int *lin; // указатель на номер строчки которую нужно заменить
	int line; // для номера строчки которую нужно заменить
	lin = &line;
	
	while (error != 0)
	{
		sfts(SLAU, lines, columns, err, lin); // для поиска спроки
		dellines(SLAU, plines, columns, lin); // ее удаление
		sfts(SLAU, lines, columns, err, lin); // "есть ли еквивалентные строчки еще?"
	}

	printSLAU(SLAU, lines, columns);

	if (lines > columns) { printf("Решений нет"); }
	else if (lines < columns) { printf("Решений многочисленное кол-во и вскоре разраб все сделает"); }
	else if (lines == columns)
	{
		// решение
	}

	printSLAU(SLAU, lines, columns);


}
