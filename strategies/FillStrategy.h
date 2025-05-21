#ifndef PROJECT_FILLSTRATEGY_H
#define PROJECT_FILLSTRATEGY_H
#include <Windows.h>
#include "../headers/Util.h"
#include "../headers/Filling.h"
#include <vector>

using namespace std;

class FillStrategy {
public:
    virtual void fill(HDC hdc, vector<Point> points, COLORREF borderColor, COLORREF fillColor) = 0;
    virtual ~FillStrategy() = default;
};

class RecFloodFillStrategy : public FillStrategy {
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor, COLORREF fillColor){
        FloodFill(hdc, points.back(), borderColor, fillColor);
    };
};

class FloodFillWithStackStrategy : public FillStrategy {
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor, COLORREF fillColor){
        FloodFillWithStack(hdc, points.back(), borderColor, fillColor);
    };
};

class FloodFillWithQueueStrategy : public FillStrategy {
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor, COLORREF fillColor){
        FloodFillWithQueue(hdc, points.back(), borderColor, fillColor);
    };
};

class BarycentricFillStrategy : public FillStrategy {
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor ,COLORREF fillColor){
        int n= (int)points.size();
        FillBarycentric(hdc, points[n-3], points[n-2], points[n-1], fillColor);
    };
};

#endif
