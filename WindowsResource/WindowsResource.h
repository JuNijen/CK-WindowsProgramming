#pragma once

#include "resource.h"
#include<iostream>
#include<fstream>

using namespace std;

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgDancingBall(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgProc3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

TCHAR* ReadTextFile(int arraySize, int charSize);

// ���� ����:
#define MAX_LOADSTRING 100
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

TCHAR str[128] = TEXT("");
int x, y;
