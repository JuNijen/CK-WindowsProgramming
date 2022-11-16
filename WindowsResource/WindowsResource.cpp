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


	switch (message)
	{

	case WM_LBUTTONDOWN:
		//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_CPYP), hWnd, DlgProc);
		//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_CALC), hWnd, DlgProcCalc);
		//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_CHECK_DIALOG), hWnd, DlgProcCheckbox);
		//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SHAPES), hWnd, DlgProcShapes);
		DialogBox(hInst, MAKEINTRESOURCE(IDD_LISTBOX), hWnd, DlgListbox);
		break;

	case WM_COMMAND:
		status = LOWORD(wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RGB_Shapes(hdc, status);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
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

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR word[100];

	switch (iMsg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
			GetDlgItemText(hDlg, IDC_EDIT_ORIGINAL, word, 100);
			SetDlgItemText(hDlg, IDC_EDIT_COPY, word);
			break;
		case IDC_BUTTON_DELETE:
			SetDlgItemText(hDlg, IDC_EDIT_ORIGINAL, TEXT(" "));
			SetDlgItemText(hDlg, IDC_EDIT_COPY, TEXT(" "));
			break;
		case IDOK:
			EndDialog(hDlg, 0);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DlgProcCalc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int numA = GetDlgItemInt(hDlg, IDC_NUMBER_A, NULL, TRUE);
	int numB = GetDlgItemInt(hDlg, IDC_NUMBER_B, NULL, TRUE);

	switch (iMsg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_ADD:
			SetDlgItemInt(hDlg, IDC_RESULT, numA+numB, TRUE);
			break;
		case IDC_SUB:
			SetDlgItemInt(hDlg, IDC_RESULT, numA - numB, TRUE);
			break;
		case IDC_MUL:
			SetDlgItemInt(hDlg, IDC_RESULT, numA * numB, TRUE);
			break;
		case IDC_DIV:
			SetDlgItemInt(hDlg, IDC_RESULT, numA / numB, TRUE);
			break;
		case IDOK:
			EndDialog(hDlg, 0);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DlgProcCheckbox(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int Check[4], Radio;
	TCHAR hobby[][30] = { TEXT("Music"), TEXT("Book"), TEXT("Game"), TEXT("Exercise") };
	TCHAR gender[][30] = { TEXT("Male"), TEXT("Female"), TEXT("ETC") };
	TCHAR output[100];

	switch (iMsg) {
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_RADIO_MALE, IDC_RADIO_FEMALE, IDC_RADIO_ETC);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_CHECK_MUSIC:
			Check[0] = 1 - Check[0];
			break;
		case IDC_CHECK_BOOK:
			Check[1] = 1 - Check[1];
			break;
		case IDC_CHECK_GAME:
			Check[2] = 1 - Check[2];
			break;
		case IDC_CHECK_EXERCISE:
			Check[3] = 1 - Check[3];
			break;

		case IDC_RADIO_MALE:
			Radio = 0;
			break;
		case IDC_RADIO_FEMALE:
			Radio = 1;
			break;
		case IDC_RADIO_ETC:
			Radio = 2;
			break;

		case IDOK:
			_stprintf_s(output, TEXT("선택한 취미는 %s %s %s %s입니다.\r\n 선택한 성별은 %s 입니다."),
				Check[0] ? hobby[0] : TEXT(""), Check[1] ? hobby[1] : TEXT(""), Check[2] ? hobby[2] : TEXT(""), Check[3] ? hobby[3] : TEXT(""), gender[Radio]);

			SetDlgItemText(hDlg, IDC_EDIT_OUTPUT, output);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DlgProcShapes(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	enum SHAPE
	{
		SHAPE_NONE,
		SHAPE_RECT,
		SHAPE_CIRCLE,
	};
	static SHAPE state;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		state = SHAPE_NONE;
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RADIO_RECT:
			state = SHAPE_RECT;
			break;
		case IDC_RADIO_ELLIPSE:
			state = SHAPE_CIRCLE;
			break;
		case IDOK:
			EndDialog(hDlg, 0);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		InvalidateRect(hDlg, NULL, TRUE);

	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);

		if (state == SHAPE_RECT) { Rectangle(hdc, 10, 10, 100, 100); }
		else if (state == SHAPE_CIRCLE) { Ellipse(hdc, 10, 10, 100, 100); }

		EndPaint(hDlg, &ps);
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DlgListbox(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hList;
	static int selection;
	TCHAR name[20];

	switch (iMsg) {
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST1);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDC_JOIN:
			GetDlgItemText(hDlg, IDC_NAME, name, 20);
			if (_tcscmp(name, TEXT(""))) SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)name);
			break;

		case IDC_WITHDRAWAL:
			SendMessage(hList, LB_DELETESTRING, selection, 0);
			break;

		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_SELCHANGE)
				selection = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);
			break;

		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
