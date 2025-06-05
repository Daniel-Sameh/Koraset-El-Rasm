//
// Created by Daniel Sameh on 6/5/2025.
//

#ifndef PROJECT_ELLIPSE_H
#define PROJECT_ELLIPSE_H
#include "../Ellipse.cpp"
#include "Util.h"
#include <Windows.h>

void drawEllipseDirect(HDC hdc,Point p1, int a, int b,COLORREF c);
void drawEllipsePolar(HDC hdc,Point p1, int a, int b,COLORREF c);
void DrawMidpointEllipse(HDC hdc, Point p1, int a, int b,COLORREF c);
#endif //PROJECT_ELLIPSE_H
