#pragma once

#include "resource.h"

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgDancingBall(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgProc3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
void RGB_Shapes(HDC hdc, int status);

// ���� ����:
#define MAX_LOADSTRING 100
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

TCHAR str[128] = TEXT("");
int x, y;
