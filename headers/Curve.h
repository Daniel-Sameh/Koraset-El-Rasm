#ifndef KORASET_EL_RASM_CURVE_H
#define KORASET_EL_RASM_CURVE_H

#include "../Curve.cpp"
#include <Windows.h>
#include "Util.h"
#include <vector>

using namespace std;

void DrawQuadraticCurve(HDC hdc, vector<Point> p, COLORREF c, int num);

void RecursiveMidPointBezier(HDC hdc, vector<Point> p, COLORREF c);

void DrawBezierCurve(HDC hdc, vector<Point> &arr, COLORREF c, int num);

void DrawCardinalSpline(HDC hdc, vector<Point> v, COLORREF color, int count, double c);

#endif
