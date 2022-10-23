#include "WindowsProgramming.h"


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

enum TILE_TYPE
{
	TILE_TYPE_NONE = 0,
	TILE_TYPE_WALL,
	TILE_TYPE_PLAYER,
};


// WndProc에서 각종 이벤트 진행.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const int boardX = 8;
	const int boardY = 8;
	const int boardSize = 75;
	const int wallCount = 10;

	static TILE_TYPE gameBoard[boardX][boardY];
	static int playerX, playerY;
	HBRUSH currentBrush, oldBrush;


	switch (iMessage)
	{
	case WM_CREATE:
		gameBoard[boardX][boardY] = { TILE_TYPE_NONE, };

		for (int count = 0; count < wallCount; count++) 
		{
			gameBoard[rand() % boardX][rand() % boardY] = TILE_TYPE_WALL;
		}

		playerX = rand() % boardX;
		playerY = rand() % boardY;
		gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
		break;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int x = 0; x < boardX; x++) 
		{
			for (int y = 0; y < boardY; y++)
			{
				// initalize
				Rectangle(hdc, x*boardSize, y*boardSize, (x + 1)*boardSize, (y + 1)*boardSize);
				COLORREF color;
				color = RGB(255, 255, 255);
				//currentBrush = CreateSolidBrush(RGB(255, 255, 255));
				//oldBrush = (HBRUSH)SelectObject(hdc, currentBrush);

				switch (gameBoard[x][y]) 
				{
				case TILE_TYPE_NONE:
					continue;
				case TILE_TYPE_WALL:
					color = RGB(255, 0, 255);
					//currentBrush = CreateSolidBrush(RGB(255, 0, 255));
					//oldBrush = (HBRUSH)SelectObject(hdc, currentBrush);
					//DeleteObject(currentBrush);
					break;
				case TILE_TYPE_PLAYER:
					color = RGB(0, 0, 255);
					//currentBrush = CreateSolidBrush(RGB(0, 0, 255));
					//oldBrush = (HBRUSH)SelectObject(hdc, currentBrush);
					//DeleteObject(currentBrush);
					break;
				}
				currentBrush = CreateSolidBrush(color);
				oldBrush = (HBRUSH)SelectObject(hdc, currentBrush);
				Ellipse(hdc, x*boardSize, y*boardSize, (x + 1)*boardSize, (y + 1)*boardSize);
				SelectObject(hdc, oldBrush);
				DeleteObject(currentBrush);
			}
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			if (playerY - 1 >= 0)
			{
				if (gameBoard[playerX][playerY - 1] == TILE_TYPE_NONE) 
				{
					gameBoard[playerX][playerY] = TILE_TYPE_NONE;
					playerY--;
					gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
				}
				else if (playerY - 2 >= 0 && gameBoard[playerX][playerY - 1] == TILE_TYPE_WALL)
				{
					if (gameBoard[playerX][playerY - 2] == TILE_TYPE_NONE) 
					{
						gameBoard[playerX][playerY] = TILE_TYPE_NONE;
						playerY--;
						gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
						gameBoard[playerX][playerY - 1] = TILE_TYPE_WALL;
					}
				}
			}
			break;
		case VK_DOWN:
			if (playerY + 1 < boardY)
			{
				if (gameBoard[playerX][playerY + 1] == TILE_TYPE_NONE) 
				{
					gameBoard[playerX][playerY] = TILE_TYPE_NONE;
					playerY++;
					gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
				}
				else if (playerY + 2 < boardY && gameBoard[playerX][playerY + 1] == TILE_TYPE_WALL)
				{
					if (gameBoard[playerX][playerY + 2] == TILE_TYPE_NONE)
					{
						gameBoard[playerX][playerY] = TILE_TYPE_NONE;
						playerY++;
						gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
						gameBoard[playerX][playerY + 1] = TILE_TYPE_WALL;
					}
				}
			}
			break;
		case VK_LEFT:
			if (playerX - 1 >= 0)
			{
				if (gameBoard[playerX - 1][playerY] == TILE_TYPE_NONE)
				{
					gameBoard[playerX][playerY] = TILE_TYPE_NONE;
					playerX--;
					gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
				}
				else if (playerX - 2 >= 0 && gameBoard[playerX - 1][playerY] == TILE_TYPE_WALL)
				{
					if (gameBoard[playerX - 2][playerY] == TILE_TYPE_NONE)
					{
						gameBoard[playerX][playerY] = TILE_TYPE_NONE;
						playerX--;
						gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
						gameBoard[playerX - 1][playerY] = TILE_TYPE_WALL;
					}
				}
			}
			break;
		case VK_RIGHT:
			if (playerX + 1 < boardX)
			{
				if (gameBoard[playerX + 1][playerY] == TILE_TYPE_NONE) 
				{
					gameBoard[playerX][playerY] = TILE_TYPE_NONE;
					playerX++;
					gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
				}
				else if (playerX + 2 < boardX && gameBoard[playerX + 1][playerY] == TILE_TYPE_WALL)
				{
					if (gameBoard[playerX + 2][playerY] == TILE_TYPE_NONE)
					{
						gameBoard[playerX][playerY] = TILE_TYPE_NONE;
						playerX++;
						gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
						gameBoard[playerX + 1][playerY] = TILE_TYPE_WALL;
					}
				}
			}
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);

		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		break;

	case WM_DESTROY:
		//DeleteObject(currentBrush);
		//DeleteObject(oldBrush);
		PostQuitMessage(0);	// WM_QUIT 메세지를 메시지큐에 넣는다.
		break;						// 직접 사용자가 처리했을 때 0을 돌려주어야 한다.
	}


	// WndProc에서 처리하지 않은 나머지 메세지들은 윈도우즈 운영체제에게 맡긴다.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//void CheckMoving(int x, int y, int tx, int ty, int *pTarget) 
//{
//	if (x != -1) 
//	{
//		if (tx < boardX && gameBoard[playerX][playerY + 1] == TILE_TYPE_NONE)
//		{
//			gameBoard[playerX][playerY] = TILE_TYPE_NONE;
//			playerY++;
//			gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
//		}
//	}
//	else if (y != -1) 
//	{
//		if (playerY + 1 < boardY && gameBoard[playerX][playerY + 1] == TILE_TYPE_NONE)
//		{
//			gameBoard[playerX][playerY] = TILE_TYPE_NONE;
//			playerY++;
//			gameBoard[playerX][playerY] = TILE_TYPE_PLAYER;
//		}
//	}
// }