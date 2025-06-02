#ifndef PROJECT_FILLSTRATEGY_H
#define PROJECT_FILLSTRATEGY_H
#include <Windows.h>
#include "../headers/Util.h"
#include "../headers/Filling.h"
#include <vector>
#include<omp.h>

using namespace std;

class FillStrategy {
public:
    virtual void fill(HDC hdc, vector<Point> points, COLORREF borderColor, COLORREF fillColor) = 0;
    virtual ~FillStrategy() = default;
};

class RecFloodFillStrategy : public FillStrategy {
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor, COLORREF fillColor){
        #pragma omp parallel
        #pragma omp single
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

class FillQuarterCircleWithLines : public FillStrategy {
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor, COLORREF fillColor){
        auto [x1, y1] = points[0];
        auto [x2, y2] = points[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        FillQuarterCircleLines(hdc,points[0],r,borderColor,fillColor);
    };
};

class BarycentricFillStrategy : public FillStrategy {
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor ,COLORREF fillColor){
        int n= (int)points.size();
        FillBarycentric(hdc, points[n-3], points[n-2], points[n-1], fillColor);
    };
};

class HermiteWindowFilling: public FillStrategy{
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor ,COLORREF fillColor){
        FillWithHermiteCurves(hdc, points[0].x, points[1].x, points[0].y, points[1].y, fillColor);
    }
};
class BezierWindowFilling: public FillStrategy{
public:
    void fill(HDC hdc, vector<Point> points, COLORREF borderColor ,COLORREF fillColor){
        FillWithBezierCurves(hdc, points[0].x, points[1].x, points[0].y, points[1].y, fillColor);
    }
};
#endif
