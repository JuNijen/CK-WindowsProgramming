#pragma once
#include "resource.h"
#include <windows.h>
#include <math.h>
#define BSIZE 40


// 원 안에 마우스가 있는지 체크하는 알고리즘. 저장 해 둘 것.
double LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
} 
BOOL InCircle(int x, int y, int mx, int my) 
{
	if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
	else return FALSE;
}