#ifndef PROJECT_CIRCLESTRATEGY_H
#define PROJECT_CIRCLESTRATEGY_H
#include <Windows.h>
#include "../Util.cpp"
#include "DrawingStrategy.h"
#include "../Circle.cpp"
using namespace std;
class CircleStrategy{
public:
    void draw(HDC hdc, Point p, int r, COLORREF c);
};

#endif