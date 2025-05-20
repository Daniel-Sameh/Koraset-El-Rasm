//
// Created by Daniel Sameh on 5/21/2025.
//

#ifndef PROJECT_CIRCLE_H
#define PROJECT_CIRCLE_H

#include "../Circle.cpp"
#include "Util.h"
#include <Windows.h>

void DrawCircleCartesian(HDC hdc, Point P1, int r, COLORREF c);

void DrawCircleBresenhamDDA(HDC hdc, Point P1, int r, COLORREF c);

void DrawCircleBresenham(HDC hdc, Point P1, int r, COLORREF c);

void DrawCirclePolarIterative(HDC hdc, Point P1, int r, COLORREF c);

void DrawCirclePolar(HDC hdc, Point P1, int r, COLORREF c);

#endif //PROJECT_CIRCLE_H
