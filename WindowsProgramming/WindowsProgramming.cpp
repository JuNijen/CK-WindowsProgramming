#include "WindowsProgramming.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("윈도우 프로그래밍");


//과제 2 : 고양이와 쥐 게임
// 윈도우의(100, 100) 좌표에 “고양이"라는 단어를 출력한다.
// 마우스 왼쪽 버튼을 누르면 포인터 위치에 “쥐"를 출력하고 버튼을 떼면 이 글자가 사라진다.
// 마우스 왼쪽 버튼을 누른채 마우스를 이동하면 고양이가 쥐를 잡으려고 움직이기 시작한다.마
//우스 버튼을 떼면 쥐는 사라지고 고양이는 움직임을 멈춘다.
// 쥐가 화면에서 사라지면 고양이는 움직임을 멈춘다.
// 고양이는 마우스 버튼을 누른 채 움직이지 않아야 고양이가 쥐를 잡을 수 있다.마우스 버튼을
//누른 채 마우스를 움직이면 고양이는 쥐를 쫓아다니기만 한다.
// 고양이가 쥐를 쫓아가는 동선 : 고양이의 위치 – 쥐의 위치
// 이 때 고양이의 위치에서 쥐의 위치까지 고양이는 한 번에(고양이의 위치 – 쥐의 위치) / 10 만큼
//씩 움직인다.
// 마우스가 눌린 채로 움직이지 않을 때 고양이는 쥐를 10번 뛰어가서 잡을 수 있다.이 때 고양이
//는 자동으로 움직인다. (타이머 이용)
// 그런데 고양이가 10번 뛰었을 때 고양이 좌표와 쥐 좌표값은 일치하지 않을 수도 있다.그러므
//로 고양이가 쥐를 잡는 것은 좌표로 확인해서는 안되고 마우스 눌린 고정 상태에서 고양이가 자
//동으로 10번을 뛰면 잡은 것으로 간주한다.
//stepX = (mouse.x - cat.x) / 10;
//stepY = (mouse.y - cat.y) / 10;


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

	const TCHAR* catText = L"고양이";
	const TCHAR* mouseText = L"쥐";
	const TCHAR* catchText = L"잡았습니다!";

	const int timerNumber = 1;
	const int timerSec = 300;
	const int countMax = 10;

	static int catPosX, catPosY;
	static int mousePosX, mousePosY;
	static int moveX, moveY;
	static int moveCount;
	static bool bIsClick, bIsCatch;

	HBRUSH currentBrush, oldBrush;


	switch (iMessage)
	{
	case WM_CREATE:
		catPosX = 100;
		catPosY = 100;

		mousePosX = 0;
		mousePosY = 0;
		moveCount = 0;

		bIsClick = false;
		bIsCatch = false;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, catPosX, catPosY, catText, lstrlen(catText));

		if (mousePosX && mousePosY) //위치 정보가 있을 경우 
		{
			TextOut(hdc, mousePosX, mousePosY, mouseText, lstrlen(mouseText));
		}
		if (bIsCatch)
		{
			TextOut(hdc, mousePosX, mousePosY, catchText, lstrlen(catchText));
		}

		EndPaint(hWnd, &ps);
		break;

	//• [참고]두 원의 거리사이의 좌표 :
	// (y2 - y1) / (x2 - x1) = 기울기a 일 때 y - y2 = a * (x - x2)
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		moveX = mousePosX - catPosX;
		moveY = mousePosY - catPosY;
		moveCount = 0;

		bIsClick = true;
		bIsCatch = false;
		SetTimer(hWnd, timerNumber, timerSec, NULL);

		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_LBUTTONUP:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		moveX = mousePosX - catPosX;
		moveY = mousePosY - catPosY;

		bIsClick = false;
		bIsCatch = false;
		KillTimer(hWnd, timerNumber);
		break;

	case WM_MOUSEMOVE:
		if (	bIsClick) 
		{
			mousePosX = LOWORD(lParam);
			mousePosY = HIWORD(lParam);

			moveX = mousePosX - catPosX;
			moveY = mousePosY - catPosY;
			moveCount = 0;

			bIsCatch = false;
			SetTimer(hWnd, timerNumber, timerSec, NULL);

			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	case WM_TIMER:
		if (moveCount < countMax)
		{
			catPosX += moveX / countMax;
			catPosY += moveY / countMax;
			moveCount++;
		}
		else 
		{
			bIsCatch = true;
			KillTimer(hWnd, timerNumber);
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUIT 메세지를 메시지큐에 넣는다.
		break;						// 직접 사용자가 처리했을 때 0을 돌려주어야 한다.
	}


	// WndProc에서 처리하지 않은 나머지 메세지들은 윈도우즈 운영체제에게 맡긴다.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}