#ifndef KORASET_EL_RASM_POLYGON_H
#define KORASET_EL_RASM_POLYGON_H

#include "../Polygon.cpp"
#include "Util.h"
#include <vector>

using namespace std;

void Draw_Polygon(HDC hdc, vector<Point> v, COLORREF c);

void DrawPolygon_ConvexFill(HDC hdc, vector<Point> &v, COLORREF c);

void DrawPolygon_GeneralFill(HDC hdc, vector<Point> &v, COLORREF c);

#endif
