//
// Created by PC on 5/22/2025.
//
#include "Windows.h"
#include "../Line.cpp"
#ifndef KORASET_EL_RASM_LINE_H
#define KORASET_EL_RASM_LINE_H
void Parametric_line(HDC hdc,vector<Point>p,COLORREF c);
void Bresenham_Line(HDC hdc,vector<Point>p,COLORREF c);
void DDA_Line(HDC hdc, vector<Point>p, COLORREF c);
#endif
