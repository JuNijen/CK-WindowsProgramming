#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("윈도우 프로그래밍");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;	 // 프로그램의 인스턴스 핸들 //(커널이 응용프로그램에 부여한 ID)

	WndClass.cbClsExtra = 0; // 윈도우 클래스 데이터 예약 영역
	WndClass.cbWndExtra = 0; // 윈도우 데이터 예약 영역

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_NO);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	// 윈도우 클래스를 등록하고 이 클래스를 기반으로 실제 윈도우를 메모리에 올린다.
	hWnd = CreateWindow(
		lpszClass, // 생성되는 윈도우 클래스 이름.
		TEXT("SIEUN Window Program"), // 윈도우 타이틀 바에 나타나는 문자열
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	//메모리에 생성된 윈도우를 화면에 띄운다.
	ShowWindow(hWnd, nCmdShow);

	//반복문을 통해 입력 이벤트를 받는다.
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}



// WndProc에서 각종 이벤트 진행.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;
	static bool isPressed[4] = { false, };

	int buttonPosition[4][2] =
	{
		{150, 100},
		{100, 150},
		{200, 150},
		{150, 200}
	};

	enum KEY
	{
		KEY_UP = 0,
		KEY_LEFT = 1,
		KEY_RIGHT = 2,
		KEY_DOWN = 3,
	};

	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		SelectObject(hdc, OldBrush);

		(isPressed[KEY_UP]) ? SelectObject(hdc, MyBrush) : SelectObject(hdc, OldBrush);
		Rectangle(hdc, 150, 100, 200, 150); //up
		(isPressed[KEY_UP]) ? TextOut(hdc, 165, 120, TEXT("UP"), 2) : TextOut(hdc, 165, 120, TEXT("  "), 2);

		(isPressed[KEY_LEFT]) ? SelectObject(hdc, MyBrush) : SelectObject(hdc, OldBrush);
		Rectangle(hdc, 100, 150, 150, 200); //left
		(isPressed[KEY_LEFT]) ? TextOut(hdc, 108, 170, TEXT("LEFT"), 4) : TextOut(hdc, 108, 170, TEXT("    "), 4);

		(isPressed[KEY_RIGHT]) ? SelectObject(hdc, MyBrush) : SelectObject(hdc, OldBrush);
		Rectangle(hdc, 200, 150, 250, 200); //right
		(isPressed[KEY_RIGHT]) ? TextOut(hdc, 205, 170, TEXT("RIGHT"), 5) : TextOut(hdc, 205, 170, TEXT("     "), 5);

		(isPressed[KEY_DOWN]) ? SelectObject(hdc, MyBrush) : SelectObject(hdc, OldBrush);
		Rectangle(hdc, 150, 200, 200, 250); //down
		(isPressed[KEY_DOWN]) ? TextOut(hdc, 153, 220, TEXT("DOWN"), 4) : TextOut(hdc, 153, 220, TEXT("    "), 4);


		//TextOut(hdc, 165, 120, TEXT("UP"), 2);
		//TextOut(hdc, 115, 170, TEXT("LEFT"), 4);
		//TextOut(hdc, 215, 170, TEXT("RIGHT"), 5);
		//TextOut(hdc, 165, 220, TEXT("DOWN"), 4);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_KEYDOWN:
		//hdc = BeginPaint(hWnd, &ps);
		//MyBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		//SelectObject(hdc, OldBrush);

		//hdc = BeginPaint(hWnd, &ps);

		switch (wParam)
		{
		case VK_UP:
			isPressed[KEY_UP] = true;
			break;
		case VK_LEFT:
			isPressed[KEY_LEFT] = true;
			break;
		case VK_RIGHT:
			isPressed[KEY_RIGHT] = true;
			break;
		case VK_DOWN:
			isPressed[KEY_DOWN] = true;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE); // 무효화 영역 다시 그리기
		return 0;

	case WM_KEYUP:
		//MyBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
		//hdc = BeginPaint(hWnd, &ps);


		switch (wParam)
		{
		case VK_UP:
			isPressed[KEY_UP] = false;
			break;
		case VK_LEFT:
			isPressed[KEY_LEFT] = false;
			break;
		case VK_RIGHT:
			isPressed[KEY_RIGHT] = false;
			break;
		case VK_DOWN:
			isPressed[KEY_DOWN] = false;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE); // 무효화 영역 다시 그리기

		return 0;
	case WM_DESTROY:
		//		DeleteObject(MyBrush);
		//		DeleteObject(MyPen);

		PostQuitMessage(0);	// WM_QUIT 메세지를 메시지큐에 넣는다.
		return 0;			// 직접 사용자가 처리했을 때 0을 돌려주어야 한다.
	}

	// WndProc에서 처리하지 않은 나머지 메세지들은 윈도우즈 운영체제에게 맡긴다.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}