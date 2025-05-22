#ifndef PROJECT_CLIPPING_H
#define PROJECT_CLIPPING_H
#include <Windows.h>
#include "Util.h"
#include <bits/stdc++.h>
#include "../Clipping.cpp"
using namespace std;
union Outcode;
Outcode getOutCode(double x, double y, double xLeft, double xRight, double yBottom, double yTop);
Point VIntersect(double xEdge, Point&p1, Point&p2);
Point HIntersect(double yEdge, Point&p1, Point&p2);
bool cohenClipping(Point&p1, Point&p2, double xLeft, double xRight, double yBottom, double yTop);
void clip(HWND hwnd, HDC hdc);

#endif //PROJECT_CLIPPING_H
