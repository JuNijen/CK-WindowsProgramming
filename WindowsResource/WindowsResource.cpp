// WindowsResource.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "WindowsResource.h"
#include "resource.h"
#include <commdlg.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.



	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSRESOURCE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSRESOURCE));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//  함수: MyRegisterClass()
//  용도: 창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSRESOURCE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}


//   함수: InitInstance(HINSTANCE, int)
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//   주석:
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//  용도: 주 창의 메시지를 처리합니다.
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int status;
	PAINTSTRUCT ps;
	HDC hdc, memDC;
	static HBITMAP bgBitmap, oldBgBitmap;
	static RECT rect;

	static TCHAR* targetTextStr[64];
	static POINT* targetTextPos;
	static int respawnCounter;
	const int respawnTiming = 250;
	const int randomTextCount = 5;
	const int falingRepeatTime = 45;

	static TCHAR userInput[64];
	const int chatWidth = 250;
	const int chatHeight = 30;
	const int chatHeightEmpty = 30;
	static int textLength, backspace;
	static int chatX, chatY;
	static bool check = false;


	switch (message)
	{
	case WM_CREATE:
		bgBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_GAME_BG));
		GetClientRect(hWnd, &rect);
		respawnCounter = 0;
		
		for (int i = 0; i < randomTextCount; i++) 
		{
			targetTextStr[i] = new TCHAR[randomTextCount];
		}

		targetTextStr[0] = TEXT("Ctrl");
		targetTextStr[1] = TEXT("Alt");
		targetTextStr[2] = TEXT("Shift");
		targetTextStr[3] = TEXT("Tab");
		targetTextStr[4] = TEXT("Insert");

		targetTextPos = new POINT[randomTextCount];
		for (int i = 0; i < randomTextCount; i++)
			targetTextPos[i].x = -100;

		textLength = lstrlen(userInput);
		backspace = textLength;
		userInput[0] = *L"  ";

		targetTextPos[0].x = rand() % rect.right;
		targetTextPos[0].y = 0;

		SetTimer(hWnd, 1, falingRepeatTime, NULL);
		break;

	case WM_KEYDOWN:
		switch (wParam) 
		{
		case VK_RETURN:
			for(int i = 0; i < randomTextCount; i++)
			{				
				for (int j = 0; j < textLength; j++) 
				{
					if (targetTextStr[i][j] == userInput[j])
					{
						check = true;
					}
					else 
					{
						check = false;
						break;
					}
				}
				if (check) 
				{
					for (int j = 0; j < randomTextCount; j++)
					{
						if (targetTextPos[j].x < 0 || targetTextPos[j].y > rect.bottom)
						{
							targetTextPos[j].x = rand() % rect.right;
							targetTextPos[j].y = 0;
							break;
						}
					}
					respawnCounter = 0;

					targetTextPos[i].x = -100;
					targetTextPos[i].y = 0;
					targetTextStr[i] = TEXT("COMPLETE!");

					break;
				}
			}

			userInput[0] = '\0';
			userInput[1] = '\0';
			textLength = lstrlen(userInput);
			break;
		case VK_BACK:
			if (textLength-1 >= 0) 
			{
				userInput[backspace] = (TCHAR)"";
				userInput[backspace--] = '\0';
				textLength = lstrlen(userInput);
			}
			break;
		}
		break;
	case WM_CHAR:
		if (textLength + 2 >= chatWidth/4)
		{
			userInput[0] = '\0';
			textLength = lstrlen(userInput);
		}
		if (wParam != VK_BACK && wParam != VK_RETURN)
		{
			textLength = lstrlen(userInput);
			backspace = textLength;

			userInput[textLength] = (TCHAR)wParam;
			userInput[textLength + 1] = '\0';
		}
		break;

	case WM_COMMAND:
		status = LOWORD(wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);

		if (respawnCounter >= respawnTiming)
		{
			for (int i = 0; i < randomTextCount; i++)
			{
				if (targetTextPos[i].x < 0 || targetTextPos[i].y > rect.bottom)
				{
					targetTextPos[i].x = rand() % rect.right;
					targetTextPos[i].y = 0;
					break;
				}
			}
			respawnCounter = 0;
		}

		memDC = CreateCompatibleDC(hdc);
		oldBgBitmap = (HBITMAP)SelectObject(memDC, bgBitmap);
		StretchBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, 1200, 627, SRCCOPY);

		for (int i = 0; i < randomTextCount; i++)
		{
			TextOut(hdc, targetTextPos[i].x - chatWidth , targetTextPos[i].y, targetTextStr[i], lstrlen(targetTextStr[i]));
		}

		chatX = rect.right /2;
		chatY = rect.bottom - chatHeightEmpty;
		Rectangle(hdc, chatX - chatWidth, chatY - chatHeight, chatX + chatWidth, chatY + chatHeight);

		// 눈속임일 뿐이고, 잘못되었다고 생각하는 부분입니다.
		if (textLength > 0) 
		{
			if (textLength == backspace) 
			{
				TextOut(hdc, chatX - (textLength * 4), chatY, (TCHAR*)userInput, textLength + 1);
			}
			else
			{
				TextOut(hdc, chatX - (textLength * 4), chatY, (TCHAR*)userInput, textLength);
			}
		}

		DeleteDC(memDC);
		EndPaint(hWnd, &ps);
		break;

	case WM_TIMER:
		for (int i = 0; i < randomTextCount; i++)
		{
			targetTextPos[i].y++;
		}
		respawnCounter++;
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

//TCHAR* ReadTextFile(int arraySize, int charSize)
//{
//	static TCHAR* targetTextStr[64];
//	char* result = new char[charSize];
//	//char** result = new char*[arraySize];
//	//for (int i = 0; i < arraySize; i++)
//	//{
//	//	result[i] = new char[charSize];
//	//}
//
//	//Opening the file
//	ifstream inputfile("words.txt");
//
//	if (!inputfile.is_open()) 
//	{
//		cout << "Error opening file";
//	}
//
//	//Defining the loop for getting input from the file
//
//	for (int i = 0; i < arraySize; i++) //Outer loop for rows
//	{
//		inputfile >> result;  //Take input from file and put into myArray
//		WideCharToMultiByte(CP_ACP, 0, targetTextStr[i], charSize, result, charSize, NULL, NULL);
//	}
//
//	return *targetTextStr;
//}