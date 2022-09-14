#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("������ ���α׷���");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;	 // ���α׷��� �ν��Ͻ� �ڵ� //(Ŀ���� �������α׷��� �ο��� ID)

	WndClass.cbClsExtra = 0; // ������ Ŭ���� ������ ���� ����
	WndClass.cbWndExtra = 0; // ������ ������ ���� ����

	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_NO);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	// ������ Ŭ������ ����ϰ� �� Ŭ������ ������� ���� �����츦 �޸𸮿� �ø���.
	hWnd = CreateWindow(
		lpszClass, // �����Ǵ� ������ Ŭ���� �̸�.
		TEXT("SIEUN Window Program"), // ������ Ÿ��Ʋ �ٿ� ��Ÿ���� ���ڿ�
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	//�޸𸮿� ������ �����츦 ȭ�鿡 ����.
	ShowWindow(hWnd, nCmdShow);

	//�ݺ����� ���� �Է� �̺�Ʈ�� �޴´�.
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}



// WndProc���� ���� �̺�Ʈ ����.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	RECT rt = { 50, 50, 400, 400 };


	switch (message)
	{
		//case WM_KEYDOWN:
		//	switch (wParam) 
		//	{
		//	case VK_LEFT:
		//		x -= 8;
		//		break;
		//	case VK_RIGHT:
		//		x += 8;
		//		break;
		//	case VK_UP:
		//		y -= 8;
		//		break;
		//	case VK_DOWN:
		//		y += 8;
		//		break;
		//	case ' ':
		//		if (cPrint == 'A')
		//		{
		//			cPrint = 'Z';
		//		}
		//		else
		//		{
		//			cPrint = 'A';
		//		}
		//		break;
		//	}
		//	InvalidateRect(hWnd, NULL, FALSE);
		//	return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		int i;
		for (i = 0; i < 1000; i++)
		{
			SetPixel(hdc, rand() % 400, rand() % 400, RGB(255, 0, 0));
		}

		EndPaint(hWnd, &ps);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUIT �޼����� �޽���ť�� �ִ´�.
		return 0;			// ���� ����ڰ� ó������ �� 0�� �����־�� �Ѵ�.
	}

	// WndProc���� ó������ ���� ������ �޼������� �������� �ü������ �ñ��.
	return (DefWindowProc(hWnd, message, wParam, lParam));
}