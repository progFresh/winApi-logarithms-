#include <iostream>
using namespace std;
#include "simpson_solution.h"

double solveFunction(double arg1, double arg2, double x) {
	double solution;
	solution = arg1*x*x + arg2*x;
	return solution;
}

double solveBySimpson(double arg1, double arg2, double left, double right) {
	double eps = 0.02;
	double I=eps+1, I1=0;//I-предыдущее вычисленное значение интеграла, I1-новое, с большим N.

	for (int N=2; (N<=4)||(fabs(I1-I)>eps); N*=2)
	{
		double h, sum2=0, sum4=0, sum=0;
		h=(right-left)/(2*N);//Шаг интегрирования.
		for (int i=1; i<=2*N-1; i+=2)
		{   
			sum4+=solveFunction(arg1, arg2, left+h*i);//Значения с нечётными индексами, которые нужно умножить на 4.
			sum2+=solveFunction(arg1, arg2, left+h*(i+1));//Значения с чётными индексами, которые нужно умножить на 2.
		}
		sum=solveFunction(arg1, arg2, left)+4*sum4+2*sum2-solveFunction(arg1, arg2, right);//Отнимаем значение f(b) так как ранее прибавили его дважды. 
		I=I1;
		I1=(h/3)*sum;
	}
	return I1;
}