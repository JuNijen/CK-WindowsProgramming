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

	static RECT rectView;
	static int x = 50, y = 50;
	static bool bIsEdge = false;
	static bool bIsReturn = false;
	static bool bIsReverse = false;

	const int radius = 20;
	const int movement = 10;


	switch (iMessage)
	{
	case WM_CREATE:
		x = radius; y = radius;
		GetClientRect(hWnd, &rectView);
		return 0;


	case WM_TIMER:
		//KillTimer(hWnd, 1);
		if (bIsReturn)
		{
			if (!bIsReverse)
			{
				if (x + movement < rectView.right)
				{
					x += movement;
				}
				else if (x + movement >= rectView.right)
				{
					bIsReverse = true;
				}
			}
			else
			{
				if (x - movement > rectView.left)
				{
					x -= movement;
				}
				else if (x - movement <= rectView.left)
				{
					bIsReverse = false;
				}
			}
			InvalidateRect(hWnd, NULL, TRUE); // 무효화 영역 다시 그리기
		}
		//InvalidateRect(hWnd, NULL, TRUE);
		return 0;



	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		(bIsEdge) ? MyPen = CreatePen(PS_SOLID, 3, RGB(50, 50, 50)) : MyPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		(bIsEdge) ? MyBrush = CreateSolidBrush(RGB(50, 50, 50)) : MyBrush = CreateSolidBrush(RGB(255, 0, 255));
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

		Ellipse(hdc, x - radius / 2, y - radius / 2, x + radius / 2, y + radius / 2);

		EndPaint(hWnd, &ps);
		return 0;



	case WM_KEYDOWN:
		switch ((TCHAR)wParam)
		{
		case VK_UP:
			if (y - movement > rectView.top)
			{
				y -= movement;

				if ((x - movement > rectView.left) && (x + movement < rectView.right))
				{
					bIsEdge = false;
				}
			}
			else 
			{
				bIsEdge = true;
			}
			break;
		case VK_LEFT:
			if (x - movement > rectView.left)
			{
				x -= movement;
				
				if ((y - movement > rectView.top) && (y + movement < rectView.bottom))
				{
					bIsEdge = false;
				}
			}
			else
			{
				bIsEdge = true;
			}
			break;
		case VK_RIGHT:
			if (x + movement < rectView.right)
			{
				x += movement;

				if ((y - movement > rectView.top) && (y + movement < rectView.bottom))
				{
					bIsEdge = false;
				}
			}
			else
			{
				bIsEdge = true;
			}
			break;
		case VK_DOWN:
			if (y + movement < rectView.bottom)
			{
				y += movement;

				if ((x - movement > rectView.left) && (x + movement < rectView.right))
				{
					bIsEdge = false;
				}
			}
			else
			{
				bIsEdge = true;
			}
			break;
		case VK_RETURN:
			bIsReturn = true;
			SetTimer(hWnd, 1, 50, NULL);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE); // 무효화 영역 다시 그리기
		return 0;



	case WM_KEYUP:
		InvalidateRect(hWnd, NULL, TRUE); // 무효화 영역 다시 그리기
		return 0;



	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUIT 메세지를 메시지큐에 넣는다.
		return 0;			// 직접 사용자가 처리했을 때 0을 돌려주어야 한다.
	}

	// WndProc에서 처리하지 않은 나머지 메세지들은 윈도우즈 운영체제에게 맡긴다.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}