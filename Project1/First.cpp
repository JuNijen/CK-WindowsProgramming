#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Text Out");
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_NO);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW|WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 100, 100, 300, 300 };
	const TCHAR* str = TEXT("������ �ؿ�����" "���� ����� ġ��" "������ �ӿ�����" "��ȭ�� �ɸ����� ư��.");
		//"���� �ӿ�����" "���� ����� ����� ã��" "�縷�� ���� �ӿ�����", "�ΰ��� ���ƽý��� �״��� ã�´�.");

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, TEXT("Hello World"), 11);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 150, 150, TEXT("Hello World"), 11);
		DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}