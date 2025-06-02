#ifndef PROJECT_FILLING_H
#define PROJECT_FILLING_H

#include "../Filling.cpp"
#include "Util.h"
#include <Windows.h>

void FloodFill(HDC& hdc, Point p, COLORREF& bc, COLORREF& fc);
void FloodFillWithStack(HDC hdc, Point p1, COLORREF bc, COLORREF fc);
void FloodFillWithQueue(HDC hdc, Point p1, COLORREF bc, COLORREF fc);
void FillBarycentric(HDC hdc, Point p1, Point p2, Point p3, COLORREF c);
void FillQuarterCircleLines(HDC hdc,Point p1,int r,COLORREF bc,COLORREF fc);

#endif //PROJECT_FILLING_H
