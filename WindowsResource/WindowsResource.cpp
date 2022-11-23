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
	HDC hdc, MemDC;
	PAINTSTRUCT ps;
	HBITMAP MyBitmap, OldBitmap;
	int imgWidth, imgHeight, imgX, imgY;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_PROC3), hWnd, DlgProc3);
		break;

	case WM_COMMAND:
		status = LOWORD(wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MemDC = CreateCompatibleDC(hdc);

		MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

		RECT rt;
		GetClientRect(hWnd, &rt);

		imgWidth = rt.right / 5;
		imgHeight = rt.bottom / 5;

		for (int countX = 0; countX < 5; countX ++) 
		{
			imgX = imgWidth * countX;

			for (int countY = 0; countY < 5; countY++)
			{
				imgY = imgHeight * countY;

				StretchBlt(hdc, imgX, imgY, imgX + imgWidth, imgY + imgHeight, MemDC, 0, 0, 612, 571, SRCCOPY);
			}
		}

		SelectObject(MemDC, OldBitmap);
		DeleteObject(MyBitmap);
		DeleteDC(MemDC);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}


void RGB_Shapes(HDC hdc, int status)
{
	static HBRUSH hB, oldB;
	static HPEN hP, oldP;

	switch (status)
	{
	case ID_LINE_RED:
		hB = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case ID_LINE_GREEN:
		hB = CreateSolidBrush(RGB(0, 255, 0));
		break;
	case ID_LINE_BLUE:
		hB = CreateSolidBrush(RGB(0, 0, 255));
		break;
	}

	if (status == ID_CIRCLE_RED || status == ID_SQUARE_RED) hB = CreateSolidBrush(RGB(255, 0, 0));
	else if (status == ID_CIRCLE_GREEN || status == ID_SQUARE_GREEN) hB = CreateSolidBrush(RGB(0, 255, 0));
	else if (status == ID_CIRCLE_BLUE || status == ID_SQUARE_BLUE) hB = CreateSolidBrush(RGB(0, 0, 255));
	else if (status == ID_LINE_RED) hP = CreatePen(BS_SOLID, 1, RGB(255, 0, 0));
	else if (status == ID_LINE_GREEN) hP = CreatePen(BS_SOLID, 1, RGB(0, 255, 0));
	else if (status == ID_LINE_BLUE) hP = CreatePen(BS_SOLID, 1, RGB(0, 0, 255));

	oldB = (HBRUSH)SelectObject(hdc, hB);
	oldP = (HPEN)SelectObject(hdc, hP);

	switch (status)
	{
	case ID_CIRCLE_RED:
	case ID_CIRCLE_GREEN:
	case ID_CIRCLE_BLUE:
		Ellipse(hdc, 100, 100, 200, 200);
		break;
	case ID_SQUARE_RED:
	case ID_SQUARE_GREEN:
	case ID_SQUARE_BLUE:
		Rectangle(hdc, 100, 100, 200, 200);
		break;
	case ID_LINE_RED:
	case ID_LINE_GREEN:
	case ID_LINE_BLUE:
		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 200, 200);
		break;
	}

	SelectObject(hdc, oldB);
	SelectObject(hdc, oldP);
	DeleteObject(hB);
	DeleteObject(hP);
}

INT_PTR CALLBACK DlgDancingBall(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DlgProc3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	enum GENDER
	{
		GENDER_FEMALE,
		GENDER_MALE,
	};

	TCHAR sName[6];				//IDC_EDIT_NAME
	TCHAR sPhoneNumber[12]; //IDC_EDIT_PHONE_NUMBER
	TCHAR sBirthY[6];			//IDC_COMBO_BIRTH_Y
	int nGender = (int)GENDER_FEMALE; //IDC_RADIO_M, F
	static int selection;
	static HWND hList;
	static HWND hCombo;
	HDC hdc;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST1);
		hCombo = GetDlgItem(hDlg, IDC_COMBO_BIRTH_Y);

		SetDlgItemText(hDlg, IDC_EDIT_NAME, _T(""));
		SetDlgItemText(hDlg, IDC_EDIT_PHONE_NUMBER, _T(""));
		CheckRadioButton(hDlg, IDC_RADIO_F, IDC_RADIO_M, IDC_RADIO_F);
		selection = 0;
		nGender = (int)GENDER_FEMALE;

		
		for (int i = 1970; i < 2010; i++)
		{
			_stprintf_s(sBirthY, _T("%d"), i);
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)sBirthY);
		}
		return (INT_PTR)TRUE;

	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hDlg, &ps); 

		EndPaint(hDlg, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_SELCHANGE)
				selection = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);
			break;
		case ID_JOIN:
			GetDlgItemText(hDlg, IDC_EDIT_NAME, sName, 6);
			GetDlgItemText(hDlg, IDC_EDIT_PHONE_NUMBER, sPhoneNumber, 12);
			GetDlgItemText(hDlg, IDC_COMBO_BIRTH_Y, sBirthY, 6);

			if (_tcscmp(sName, TEXT(""))) 
			{
				int year = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				TCHAR sGender[][30] = { _T("여자"),_T("남자") };
				TCHAR output[50];

				GetDlgItemText(hDlg, IDC_EDIT_PHONE_NUMBER, sPhoneNumber, 12);

				_stprintf_s(sBirthY, _T("%d"), 1970 + year);
				_stprintf_s(output, _T("이름:%s, 전화번호:%s, 성별:%s, 출생연도:%s"), sName, sPhoneNumber, sGender[nGender], sBirthY);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)output);
			}
			break;
		case ID_REMOVE:
			SendMessage(hList, LB_DELETESTRING, selection, 0);
			break;
		case ID_CANCEL:
			EndDialog(hDlg, 0);
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		break;
	default:
		break;
	}

	return (INT_PTR)FALSE;
}