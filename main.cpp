#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string>

using namespace std;

TCHAR szTitle[] = L"���������� ���������";
TCHAR szTitleSimpson[] =L"����� ���������";
TCHAR szTitleSquares[] =L"����� ���������";
TCHAR szWindowClass[] = L"main";
TCHAR szWindowClassSimpson[] =L"simpson";
TCHAR szWindowClassSquares[] =L"squares";

HINSTANCE hInst;

HWND mainWnd; // ����������� ������� ����
HWND simpsonWnd;
HWND squaresWnd;

// RegisterClass
ATOM MainRegisterClass(HINSTANCE);
ATOM SimpsonRegisterClass(HINSTANCE);
ATOM SquaresRegisterClass(HINSTANCE);

// InitInstance
BOOL InitMainInstance(HINSTANCE, int);
BOOL InitSimpsonInstance(HINSTANCE, int);
BOOL InitSquaresInstance(HINSTANCE, int);

// Handlers
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SimpsonWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SquaresWndProc(HWND, UINT, WPARAM, LPARAM);

// Functions

bool ContainsErrors(WCHAR *str) {
	int count = 0;
	for (int i = 0; i < wcslen(str); i++) {
		count = count + 1;
		if (iswalpha(str[i])) {
			return TRUE;
		}
	}
	if (count == 0) return TRUE;
	if ( (count == 1) && (!isdigit(str[0])) ) return TRUE;
	return FALSE;
}
// returns 0.0 if can't get double
double ToDouble(WCHAR *str) {
	double result = _wtof(str);
	return result;
}

double solveFunction(double arg1, double arg2, double x) {
	double solution;
	solution = arg1*x*x + arg2*x;
	return solution;
}

double solveBySimpson(double arg1, double arg2, double left, double right) {
	double eps = 0.02;
	double I=eps+1, I1=0;//I-���������� ����������� �������� ���������, I1-�����, � ������� N.

	for (int N=2; (N<=4)||(fabs(I1-I)>eps); N*=2)
	{
		double h, sum2=0, sum4=0, sum=0;
		h=(right-left)/(2*N);//��� ��������������.
		for (int i=1; i<=2*N-1; i+=2)
		{   
			sum4+=solveFunction(arg1, arg2, left+h*i);//�������� � ��������� ���������, ������� ����� �������� �� 4.
			sum2+=solveFunction(arg1, arg2, left+h*(i+1));//�������� � ������� ���������, ������� ����� �������� �� 2.
		}
		sum=solveFunction(arg1, arg2, left)+4*sum4+2*sum2-solveFunction(arg1, arg2, right);//�������� �������� f(b) ��� ��� ����� ��������� ��� ������. 
		I=I1;
		I1=(h/3)*sum;
	}
	return I1;
}

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

// *** Main window
HWND simpsonLableMain, squareLableMain;
HWND simpsonButtonMain, squareButtonMain;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	hInst = hInstance;
	if (!MainRegisterClass(hInstance)) return FALSE;
	if (!InitMainInstance(hInstance, nCmdShow)) return FALSE;
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {                  
		TranslateMessage(&msg);//��������� ���������� ��������� WM_KEYDOWN, WM_KEYUP � WM_CHAR ��� WM_DEADCHAR
		                       //� ���������� WM_SYSKEYDOWN, WM_SYSKEYUP � WM_SYSCHAR ��� WM_SYSDEADCHAR � ��������� �� � �������. 
		DispatchMessage(&msg);//�������� �-� ��������� �����-�, ��� ������ ���� ������� DispatchMessage �������� � ��������� message
		                      //������������� ���������. �� ����� �������������� ������������ ������� � ����������� �����-���� ��������
		                      //(�������� �� ���������).
	}
	return (int)msg.wParam;
}

ATOM MainRegisterClass(HINSTANCE hInstance) //������� ����
{
	WNDCLASSEXW wcex; //������ ���������, ��� ��������� � ������ ������ WNDCLASSEX

	wcex.cbSize = sizeof(WNDCLASSEX); //�������� ��������� (� ������)
	wcex.style = CS_HREDRAW | CS_VREDRAW; // ����� ������ ������
	wcex.lpfnWndProc = MainWndProc; //��������� �� �������
	wcex.cbClsExtra = 0; // ����� ������������� ������ ��� �������� ���������� ����������
	wcex.cbWndExtra = 0; // ����� ������������� ������ � ����� ���������
	wcex.hInstance = hInstance;// ��������� �� ������, ���������� ��� ����, ������������ ��� ������
	wcex.hIcon = LoadIcon(NULL, NULL); // ���������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //���������� ������� ����
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);// ���������� ����� ��� �������� ���� ����
	wcex.lpszMenuName = NULL;// ��������� �� const-������, ���������� ��� ����, ������������ ��� ������
	wcex.lpszClassName = szWindowClass;// ��������� �� const-������, ���������� ��� ������
	wcex.hIconSm = LoadIcon(NULL, NULL);// ���������� ��������� ����������� (� ����)

	return RegisterClassExW(&wcex); //��������, ��� �� ���� ������ ����������������
}

ATOM SimpsonRegisterClass(HINSTANCE hInstance) 
{
	WNDCLASSEXW wcex;//������ ���������, ��� ��������� � ������ ������ WNDCLASSEX

	wcex.cbSize = sizeof(WNDCLASSEX);//�������� ��������� (� ������)
	wcex.style = CS_HREDRAW | CS_VREDRAW;// ����� ������ ������
	wcex.lpfnWndProc = SimpsonWndProc;//��������� �� �������
	wcex.cbClsExtra = 0;// ����� ������������� ������ ��� �������� ���������� ����������
	wcex.cbWndExtra = 0;// ����� ������������� ������ � ����� ���������
	wcex.hInstance = hInstance;// ��������� �� ������, ���������� ��� ����, ������������ ��� ������
	wcex.hIcon = LoadIcon(NULL, NULL);// ���������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);//���������� ������� ����
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);// ���������� ����� ��� �������� ���� ����
	wcex.lpszMenuName = NULL;// ��������� �� const-������, ���������� ��� ����, ������������ ��� ������
	wcex.lpszClassName = szWindowClassSimpson;// ��������� �� const-������, ���������� ��� ������
	wcex.hIconSm = LoadIcon(NULL, NULL);// ���������� ��������� ����������� (� ����)

	return RegisterClassExW(&wcex);//��������, ��� �� ���� ������ ����������������
}

ATOM SquaresRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;//������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
	wcex.cbSize = sizeof(WNDCLASSEX);//�������� ��������� (� ������)
	wcex.style = CS_HREDRAW | CS_VREDRAW;// ����� ������ ������
	wcex.lpfnWndProc = SquaresWndProc;//��������� �� �������
	wcex.cbClsExtra = 0;// ����� ������������� ������ ��� �������� ���������� ����������
	wcex.cbWndExtra = 0;// ����� ������������� ������ � ����� ���������
	wcex.hInstance = hInstance;// ��������� �� ������, ���������� ��� ����, ������������ ��� ������
	wcex.hIcon = LoadIcon(NULL, NULL);// ���������� ������
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);//���������� ������� ����
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);// ���������� ����� ��� �������� ���� ����
	wcex.lpszMenuName = NULL;// ��������� �� const-������, ���������� ��� ����, ������������ ��� ������
	wcex.lpszClassName = szWindowClassSquares;// ��������� �� const-������, ���������� ��� ������
	wcex.hIconSm = LoadIcon(NULL, NULL);// ���������� ��������� ����������� (� ����)

	return RegisterClassExW(&wcex);//��������, ��� �� ���� ������ ����������������
}

BOOL InitMainInstance(HINSTANCE hInstance, int nCmdShow) {
	mainWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_POPUP,
		200, 200, 350, 180, NULL, NULL, hInstance, NULL);
	if (!mainWnd) return FALSE;

	ShowWindow(mainWnd, nCmdShow);
	return TRUE;
}

BOOL InitSimpsonInstance(HINSTANCE hInstance, int nCmdShow)
{
	simpsonWnd = CreateWindowW(szWindowClassSimpson, szTitleSimpson,  WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_POPUP,
		300, 300, 350, 200, mainWnd, NULL, hInstance, NULL);//mainwnd - ����������� ������������ ����

	if (!simpsonWnd) return FALSE;

	EnableWindow(mainWnd, FALSE);
	ShowWindow(simpsonWnd, nCmdShow);
	return TRUE;
}

BOOL InitSquaresInstance(HINSTANCE hInstance, int nCmdShow)
{
	squaresWnd = CreateWindowW(szWindowClassSquares, szTitleSquares, WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_POPUP,
		300, 300, 350, 200, mainWnd, NULL, hInstance, NULL);

	if (!squaresWnd) return FALSE;

	EnableWindow(mainWnd, FALSE);
	ShowWindow(squaresWnd, nCmdShow);

	return TRUE;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		if (!SimpsonRegisterClass(hInst)) return FALSE;
		if (!SquaresRegisterClass(hInst)) return FALSE;

		simpsonLableMain = CreateWindowW(L"static", L"����� ��������:", WS_CHILD | WS_VISIBLE,
			20, 20, 250, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(simpsonLableMain, SW_SHOWNORMAL);

		simpsonButtonMain= CreateWindowW(L"button", L"�������", WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 50, 100, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(simpsonButtonMain, SW_SHOWNORMAL);

		squareLableMain = CreateWindowW(L"static", L"����� ���������:", WS_CHILD | WS_VISIBLE,
			180, 20, 200, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(squareLableMain, SW_SHOWNORMAL);

		squareButtonMain = CreateWindowW(L"button", L"�������", WS_CHILD | WS_VISIBLE | WS_BORDER,
			180, 50, 100, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(squareButtonMain, SW_SHOWNORMAL);
		break;
	case WM_COMMAND:
	{
		if (lParam == (LPARAM)simpsonButtonMain) {
			InitSimpsonInstance(hInst, SW_SHOWNORMAL);
		} else if (lParam == (LPARAM)squareButtonMain) {
			InitSquaresInstance(hInst, SW_SHOWNORMAL);
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//��� �������������� ��������� ���������� ���� Windows
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}// ����� ������� ����������� ���������

// *** Simpson window

HWND labelFrom, labelTo, labelAnswer, functionLabel, labelRange, x1Label, x2Label;
HWND editTextFrom, editTextTo, x1Edit, x2Edit;
HWND buttonCalculate;

LRESULT CALLBACK SimpsonWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
	switch (message) {
	case WM_CREATE: {	
		functionLabel = CreateWindowW(L"static", L"f(x) = ", WS_CHILD | WS_VISIBLE,
			20, 120, 100, 40, hWnd, NULL, NULL, NULL);
		ShowWindow(functionLabel, SW_SHOWNORMAL);

		x1Edit = CreateWindowW(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			55, 120, 30, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(x1Edit, SW_SHOWNORMAL);

		x1Label = CreateWindowW(L"static", L"x^2 +", WS_CHILD | WS_VISIBLE,
			90, 120, 100, 40, hWnd, NULL, NULL, NULL);
		ShowWindow(x1Label, SW_SHOWNORMAL);

		x2Edit = CreateWindowW(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			130, 120, 30, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(x2Edit, SW_SHOWNORMAL);

		x2Label = CreateWindowW(L"static", L"x ", WS_CHILD | WS_VISIBLE,
			165, 120, 100, 40, hWnd, NULL, NULL, NULL);
		ShowWindow(x2Label, SW_SHOWNORMAL);

		labelRange = CreateWindowW(L"static", L"��������", WS_CHILD | WS_VISIBLE,
			20, 20, 100, 40, hWnd, NULL, NULL, NULL);
		ShowWindow(labelRange, SW_SHOWNORMAL);

		labelFrom = CreateWindowW(L"static", L"��:", WS_CHILD | WS_VISIBLE,
			80, 40, 50, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(labelFrom, SW_SHOWNORMAL);

		editTextFrom = CreateWindowW(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			120, 40, 30, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(editTextFrom, SW_SHOWNORMAL);

		labelTo = CreateWindowW(L"static", L"��:", WS_CHILD | WS_VISIBLE,
			80, 70, 50, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(labelTo, SW_SHOWNORMAL);

		editTextTo = CreateWindowW(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			120, 70, 30, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(editTextTo, SW_SHOWNORMAL);

		buttonCalculate = CreateWindowW(L"button", L"���������", WS_CHILD | WS_VISIBLE | WS_BORDER,
			165, 40, 100, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(buttonCalculate, SW_SHOWNORMAL);

		labelAnswer = CreateWindowW(L"static", L"�����:", WS_CHILD | WS_VISIBLE,
			165, 70, 150, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(labelAnswer, SW_SHOWNORMAL);

		break;
	}
	case WM_COMMAND: {
		if (lParam == (LPARAM)buttonCalculate) {
				WCHAR value[5];
				GetWindowText(editTextFrom, value, 5);
				if (ContainsErrors(value)) {
					MessageBox(hWnd, L"�������� ���� ���������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				double from = ToDouble(value);
				GetWindowText(editTextTo, value, 5);
				if (ContainsErrors(value)) {
					MessageBox(hWnd, L"�������� ���� ���������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				double to = ToDouble(value);
				if (from == to) {
					MessageBox(hWnd, L"�������� ��������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				GetWindowText(x1Edit, value, 5);
				if (ContainsErrors(value)) {
					MessageBox(hWnd, L"�������� ���� ����������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				double x1Value = ToDouble(value);

				GetWindowText(x2Edit, value, 5);
				if (ContainsErrors(value)) {
					MessageBox(hWnd, L"�������� ���� ����������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				double x2Value = ToDouble(value);
				double answerBySimpson = solveBySimpson(x1Value, x2Value, from, to);
				
				std::wstring answer = L"�����: " + std::to_wstring(answerBySimpson);
				SetWindowText(labelAnswer, answer.c_str());
		}
		break;
	}
	case WM_CLOSE:
		EnableWindow(mainWnd, true);
		DestroyWindow(simpsonWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK SquaresWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE: {	
		functionLabel = CreateWindowW(L"static", L"f(x) = ", WS_CHILD | WS_VISIBLE,
			20, 120, 100, 40, hWnd, NULL, NULL, NULL);
		ShowWindow(functionLabel, SW_SHOWNORMAL);

		x1Edit = CreateWindowW(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			55, 120, 30, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(x1Edit, SW_SHOWNORMAL);

		x1Label = CreateWindowW(L"static", L"x^2 +", WS_CHILD | WS_VISIBLE,
			90, 120, 100, 40, hWnd, NULL, NULL, NULL);
		ShowWindow(x1Label, SW_SHOWNORMAL);

		x2Edit = CreateWindowW(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			130, 120, 30, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(x2Edit, SW_SHOWNORMAL);

		x2Label = CreateWindowW(L"static", L"x ", WS_CHILD | WS_VISIBLE,
			165, 120, 100, 40, hWnd, NULL, NULL, NULL);
		ShowWindow(x2Label, SW_SHOWNORMAL);

		labelRange = CreateWindowW(L"static", L"��������", WS_CHILD | WS_VISIBLE,
			20, 20, 100, 40, hWnd, NULL, NULL, NULL);
		ShowWindow(labelRange, SW_SHOWNORMAL);

		labelFrom = CreateWindowW(L"static", L"��:", WS_CHILD | WS_VISIBLE,
			80, 40, 50, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(labelFrom, SW_SHOWNORMAL);

		editTextFrom = CreateWindowW(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			120, 40, 30, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(editTextFrom, SW_SHOWNORMAL);

		labelTo = CreateWindowW(L"static", L"��:", WS_CHILD | WS_VISIBLE,
			80, 70, 50, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(labelTo, SW_SHOWNORMAL);

		editTextTo = CreateWindowW(L"edit", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			120, 70, 30, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(editTextTo, SW_SHOWNORMAL);

		buttonCalculate = CreateWindowW(L"button", L"���������", WS_CHILD | WS_VISIBLE | WS_BORDER,
			165, 40, 100, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(buttonCalculate, SW_SHOWNORMAL);

		labelAnswer = CreateWindowW(L"static", L"�����:", WS_CHILD | WS_VISIBLE,
			165, 70, 150, 20, hWnd, NULL, NULL, NULL);
		ShowWindow(labelAnswer, SW_SHOWNORMAL);
		break;
	}
	case WM_COMMAND: {
		if (lParam == (LPARAM)buttonCalculate) {
				WCHAR value[5];
				GetWindowText(editTextFrom, value, 5);
				if (ContainsErrors(value)) {
					MessageBox(hWnd, L"�������� ���� ���������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				double from = ToDouble(value);
				GetWindowText(editTextTo, value, 5);
				if (ContainsErrors(value)) {
					MessageBox(hWnd, L"�������� ���� ���������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				double to = ToDouble(value);
				if (from == to) {
					MessageBox(hWnd, L"�������� ��������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				GetWindowText(x1Edit, value, 5);
				if (ContainsErrors(value)) {
					MessageBox(hWnd, L"�������� ���� ����������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				double x1Value = ToDouble(value);

				GetWindowText(x2Edit, value, 5);
				if (ContainsErrors(value)) {
					MessageBox(hWnd, L"�������� ���� ����������", L"������", MB_OK | MB_TASKMODAL);
					break;
				}
				double x2Value = ToDouble(value);
				double answerBySquares = solveBySquares(x1Value, x2Value, from, to);
				
				std::wstring answer = L"�����: " + std::to_wstring(answerBySquares);
				SetWindowText(labelAnswer, answer.c_str());
		}
		break;
	}
	case WM_CLOSE:
		EnableWindow(mainWnd, true);
		DestroyWindow(squaresWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}