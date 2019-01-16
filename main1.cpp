//задача о черепашке
/*
из левой верхней клетки должна доползти в правую нижнюю клетку.
может ползти только вниз и право.
собрать максимальную последовательность чисел при движении.
*/

//the task about the turtle
/*
from the upper left cell must crawl to the lower right cell.
can only crawl down and right.
collect the maximum sequence of numbers when moving.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define MAX 10
#define LINE 7
#define COLUMN 5


//генерация массива / the generation of the array
void genArr(int arr[][COLUMN], int L)
{
	for (int i = 0; i < L; i++)
		for (int j = 0; j < COLUMN; j++)
			arr[i][j] = rand() % MAX;
}

//печать массива / printing an array
void printArr(int arr[][COLUMN], int L)
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			printf("%4d ", arr[i][j]);
		putchar('\n');
	}
	putchar('\n');
}

// создаём вспомогательный массив / create an auxiliary array
void secondMatr(int arr[][COLUMN], int arr2[][COLUMN], int L)
{
	arr2[0][0] = arr[0][0];

	for (int j = 1; j < COLUMN; j++)
		arr2[0][j] = arr2[0][j - 1] + arr[0][j];
	
	for (int i = 1; i < L; i++)
		arr2[i][0] = arr2[i-1][0] + arr[i][0];

	for (int i = 1; i < L; i++)
		for (int j = 1; j < COLUMN; j++)
			if (arr2[i - 1][j] > arr2[i][j - 1])
				arr2[i][j] = arr2[i - 1][j] + arr[i][j];
			else
				arr2[i][j] = arr2[i][j - 1] + arr[i][j];
}

// печать вспомогательного массива / printing an auxiliary array
void printSecondMatr(int arr2[][COLUMN], int L)
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			printf("%4d ", arr2[i][j]);
		putchar('\n');
	}
	putchar('\n');
}

// изменяем массив, обозначая в нём путь (-1) / change the array, denoting the path (-1)
void markWay(int arr2[][COLUMN], int L)
{
	int pathValue = -1;
	int i = L - 1;
	int j = COLUMN - 1;

	arr2[i][j] = pathValue; 

	while (i > 0 && j > 0)
	{
		if (arr2[i - 1][j] > arr2[i][j - 1])
		{
			i--;
			arr2[i][j] = pathValue;
		}
		else if (arr2[i - 1][j] < arr2[i][j - 1])
		{
			j--;
			arr2[i][j] = pathValue;
		}
		else if (arr2[i - 1][j] == arr2[i][j - 1])
			if (i >= 2 && j >= 2)
			{
				if (arr2[i - 2][j] > arr2[i][j - 2])
				{
					i--;
					arr2[i][j] = pathValue;
				}
				else
				{
					j--;
					arr2[i][j] = pathValue;
				}
			}
			else if (i < 2 && j >= 2)
				if (arr2[i][j - 2] < arr2[i - 1][j - 1])
				{
					i--;
					arr2[i][j] = pathValue;
				}
				else
				{
					j--;
					arr2[i][j] = pathValue;
				}
			else if (i >= 2 && j < 2)
				if (arr2[i - 2][j] > arr2[i - 1][j - 1])
				{
					i--;
					arr2[i][j] = pathValue;
				}
				else
				{
					j--;
					arr2[i][j] = pathValue;
				}
	}

	if (i == 0 && j > 0)
		for (int k = 0; k < j; k++)
			arr2[i][k] = pathValue;
	else if (j == 0 && i > 0)
		for (int k = 0; k < i; k++)
			arr2[k][j] = pathValue;
}

void printWayCheck(int arr2[][COLUMN], int L)
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			printf("%4d ", arr2[i][j]);
		putchar('\n');
	}
	putchar('\n');
}


void SetColor(int text, int background) 
{
	/*Получение дескриптора / Getting a descriptor*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((background << 4) | text));
}


void printWay(int arr[][COLUMN], int arr2[][COLUMN], int L)
{
	enum ConsoleColor {
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};


	CONSOLE_SCREEN_BUFFER_INFO start_attribute;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &start_attribute); // исходный цвет консоли / the original color of the console


	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (arr2[i][j] >= 0)
				printf("%4d ", arr[i][j]);
			else
			{
				SetColor(Magenta, Black); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
				printf("%4d ", arr[i][j]);
				SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
			}
		}
		putchar('\n');
	}
	putchar('\n');
}

int main()
{
	srand(time(0));
	int arr[LINE][COLUMN];
	genArr(arr, LINE);
	printArr(arr, LINE);
	

	int matr[LINE][COLUMN];
	secondMatr(arr, matr, LINE);
	printSecondMatr(matr, LINE);

	markWay(matr, LINE);

	//printWayCheck(matr, LINE); // function for check / функция для проверки
	printWay(arr, matr, LINE);
	putchar('\n');


	return 0;
}
