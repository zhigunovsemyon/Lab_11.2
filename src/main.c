/*
	Вычислить сумму данного ряда с выбранной пользователем точностью:
	SUM[1,inf] of (-1)^i * abs( cos(i!) ) * i / 2^(x^i)
	Выводить в процессе суммирования элементы ряда
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#define NOERRORS 0
#define MAXTRIES 128
#define TRUE 1
#define FALSE 0

long double factor(int factof);
long double formula(int i, int x);
long double Ipow(int base, int power);
void getnums(long double* pres, int* x);

int main(void)
{
	int x;
	long double pres, s = 0.0;
	getnums(&pres, &x);

	/*Вместо бесконечного цикла, он будет выполнятся некоторое
	  количество раз, на случай, если прогрессия не достигает
	  размера погрешности									*/
	for (int i = 1; i < MAXTRIES; ++i)
	{
		long double part = formula(i, x);
		printf("%d-й элемент равен: %.15lf\n", i, part);
		s += part;

		/*По достижении размера погрешности, цикл прерывается*/
		if (fabsl(part) < pres)
			break;
	}
	printf("\nСумма ряда равна: %.15lf\n", s);
	return NOERRORS;
}

//Функция вычисления факториала числа
long double factor(int factof)
{
	long double ret = 1;
	int i = 1;
	while (i <= factof)
		ret *= i++;
	return ret;
}

//Функция вычисления i-го члена ряда с параметром x
long double formula(int i, int x)
{
	double sign = ((i % 2 == 0) ? 1.0 : -1.0);
	long double numerator = sign * fabsl(cosl(factor(i)) * i);
	long double denominator = Ipow(2, Ipow(x, i));
	return numerator / denominator;
}

//Функция возвращает base в степени power
long double Ipow(int base, int power)
{/*long double используется, несмотря на целочисленное значение
 ввиду размера величины*/
	long double result = 1;
	for (int i = 0; i < power; ++i)
		result *= base;
	return result;
}

/*Ввод значений pres, x; проверка их на корректность*/
void getnums(long double* pres, int* x)
{
	do
	{
		puts("Введите желаемую точность и параметр x");
		scanf("%lf %d", pres, x);
		if ((*x <= 0) || (*pres <= 0))
		{
			printf("Неправильные значение.\n");
			continue;
		}
		/*else*/ return;
	} while (TRUE);
}

