double solveFunction(double arg1, double arg2, double x) {
	double solution;
	solution = arg1*x*x + arg2*x;
	return solution;
}

__declspec(dllexport)
double solveBySquares(double arg1, double arg2, double left, double right) {
	int n = 30; // count of squares
	double s=(solveFunction(arg1, arg2, left) + solveFunction(arg1, arg2, right))/2;
	double h=(right-left)/n;
	for (int i=1; i<=n-1; i++)
	{ 
		s+=solveFunction(arg1, arg2, left+i*h);
	}
	double I=h*s;
	return I;
}