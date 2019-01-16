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
#define LINE 5
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
			printf("%2d  ", arr[i][j]);
		putchar('\n');
	}
	putchar('\n');
}

// создаём вспомогательный массив / create an auxiliary array
void secondMatr(int arr[][COLUMN], int arr2[][COLUMN], int L)
{
	arr2[0][0] = arr[0][0];

	for (int j = 1; j < L; j++)
		arr2[0][j] = arr2[0][j - 1] + arr[0][j];
	
	for (int i = 1; i < COLUMN; i++)
		arr2[i][0] = arr2[i-1][0] + arr[i][0];

	for (int i = 1; i < COLUMN; i++)
		for (int j = 1; j < L; j++)
			if (arr2[i - 1][j] > arr2[i][j - 1])
				arr2[i][j] = arr2[i - 1][j] + arr[i][j];
			else
				arr2[i][j] = arr2[i][j - 1] + arr[i][j];
}

// печать вспомогательного массива / printing an auxiliary array
void printSecondMatr(int arr2[][COLUMN], int L)
{
	for (int i = 0; i < COLUMN; i++)
	{
		for (int j = 0; j < L; j++)
			printf("%2d  ", arr2[i][j]);
		putchar('\n');
	}
	putchar('\n');
}

// изменяем исходный массив, обозначая в нём путь (знаки минус) / change the original array, denoting the path (minus signs)
void markWay(int arr[][COLUMN], int arr2[][COLUMN], int L)
{
	int i = 0;
	int j = 0;
	int select_elem;

	arr[0][0] *= (-1); // чтобы было такое же значение, но только со знаком минус (to have the same value, but only with a minus sign)

	while (i < L && j < COLUMN)
	{
		if (arr2[i + 1][j] > arr2[i][j + 1])
		{
			i++;
			arr[i][j] *= (-1);
		}
		else
		{
			j++;
			arr[i][j] *= (-1);
		}
	}
}

void printWayCheck(int arr[][COLUMN], int L)
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			printf("%2d  ", arr[i][j]);
		putchar('\n');
	}
	putchar('\n');
}


void SetColor(int text, int background) 
{
	/*Получение дескриптора*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((background << 4) | text));
}


void printWay(int arr[][COLUMN], int L)
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
			if (arr[i][j] >= 0)
				printf("%2d  ", arr[i][j]);
			else
			{
				SetColor(Magenta, Black); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
				printf("%2d  ", arr[i][j] * (-1)); // возвращаем исходное неотрицательное значение элемента массива / return the original non-negative value of the array element
				SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
			}
		}
		putchar('\n');
	}
	putchar('\n');
}

int main()
{
	int arr[LINE][COLUMN];
	genArr(arr, LINE);
	printArr(arr, LINE);
	

	int matr[LINE][COLUMN];
	secondMatr(arr, matr, LINE);
	printSecondMatr(matr, LINE);
	
	

	markWay(arr, matr, LINE);

	printWay(arr, LINE);
	putchar('\n');


	return 0;
}
