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
	SYSTEMTIME st;

	static TCHAR sTime[128];
	const int timer_1sec = 1000;
	const int timer_5sec = 5000;
	const int pos = 100;


	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, timer_1sec, NULL);
		SetTimer(hWnd, 2, timer_5sec, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		break;


	case WM_TIMER:
		GetLocalTime(&st);
		MessageBeep(1);
		wsprintf(sTime, TEXT("현재 시간은 %d시 %d분 %d초 입니다."), st.wHour, st.wMinute, st.wSecond);
		InvalidateRect(hWnd, NULL, TRUE);
		break;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, pos, pos, sTime, lstrlen(sTime));
		EndPaint(hWnd, &ps);
		break;


	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);	// WM_QUIT 메세지를 메시지큐에 넣는다.
		break;			// 직접 사용자가 처리했을 때 0을 돌려주어야 한다.
	}

	// WndProc에서 처리하지 않은 나머지 메세지들은 윈도우즈 운영체제에게 맡긴다.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}