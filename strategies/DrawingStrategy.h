#ifndef PROJECT_DRAWINGSTRATEGY_H
#define PROJECT_DRAWINGSTRATEGY_H
#include <Windows.h>
#include "../headers/Util.h"

#include <vector>
#include <thread>
#include <memory>
#include "../headers/Circle.h"
#include "../headers/Curve.h"
#include "../headers/Line.h"
#include "../headers/Clipping.h"
using namespace std;

class DrawingStrategy {
public:
    virtual void draw(HDC hdc, vector<Point>p, COLORREF c) = 0;
    virtual void showHelp(HWND hwnd) = 0;
    virtual ~DrawingStrategy() = default;
};

class CircleCartesian: public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        DrawCircleCartesian(hdc, p[0], r, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a circle using the Cartesian method.", "Circle Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class CircleBresenham : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        DrawCircleBresenham(hdc, p[0], r, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a circle using the Bresenham method.", "Circle Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class CircleBresenhamDDA : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        DrawCircleBresenhamDDA(hdc, p[0], r, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a circle using the Bresenham DDA method.", "Circle Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class CirclePolar : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        DrawCirclePolar(hdc, p[0], r, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a circle using the Polar method.", "Circle Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class CirclePolarIterative : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        DrawCirclePolarIterative(hdc, p[0], r, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a circle using the Polar Iterative method.", "Circle Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class QuadraticCurve : public DrawingStrategy {
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        DrawQuadraticCurve(hdc, p, c, 1000);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click one 3 points to draw a quadratic curve.", "Quadratic Curve Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class MidPointBezier : public DrawingStrategy {
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        RecursiveMidPointBezier(hdc, p, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click left 4 points then click right to draw a MidPoint Bezier curve.", "MidPoint Bezier Curve Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class RecursiveBezier : public DrawingStrategy {
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        DrawBezierCurve(hdc, p, c, 1000);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click left 4 points then click right to draw a Recursive Bezier curve.", "Recursive Bezier Curve Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class CardinalSpline : public DrawingStrategy {
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        DrawCardinalSpline(hdc, p, c, 1000, 1);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click left up to 8 points then click right to draw a Cardinal Spline curve.", "Cardinal Spline Curve Drawing", MB_OK | MB_ICONINFORMATION);
    }
};
class ParametricLine: public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        clippingPoints.emplace_back(p[0],p[1]);
        Parametric_line(hdc,p,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a parametric line.", "Parametric Line Drawing", MB_OK | MB_ICONINFORMATION);
    }
};
class BresenhamLine: public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        clippingPoints.emplace_back(p[0],p[1]);
        Bresenham_Line(hdc,p,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a Bresenham line.", "Bresenham Line Drawing", MB_OK | MB_ICONINFORMATION);
    }
};
class DDALine: public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        clippingPoints.emplace_back(p[0],p[1]);
        DDA_Line(hdc,p,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a DDA line.", "DDA Line Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

#endif