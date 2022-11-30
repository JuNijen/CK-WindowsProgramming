#pragma once

#include "resource.h"
#include<iostream>
#include<fstream>

using namespace std;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgDancingBall(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgProc3(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

TCHAR* ReadTextFile(int arraySize, int charSize);

// 전역 변수:
#define MAX_LOADSTRING 100
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

TCHAR str[128] = TEXT("");
int x, y;
