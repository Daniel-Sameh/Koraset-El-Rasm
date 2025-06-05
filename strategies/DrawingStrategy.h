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
#include "../headers/Polygon.h"
#include "../headers/Ellipse.h"
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
class EllipseDirect : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        auto [x3,y3]  = p[2];
        int a = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        int b = (int) sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        drawEllipseDirect(hdc,p[0],a,b,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click three times first for the centre second for the radius a and third for radius b", "Ellipse Drawing", MB_OK | MB_ICONINFORMATION);
    }
};
class EllipsePolar : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        auto [x3,y3]  = p[2];
        int a = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        int b = (int) sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        drawEllipsePolar(hdc,p[0],a,b,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click three times first for the centre second for the radius a and third for radius b", "Ellipse Drawing", MB_OK | MB_ICONINFORMATION);
    }
};
class MidpointEllipse : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        auto [x3,y3]  = p[2];
        int a = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        int b = (int) sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        DrawMidpointEllipse(hdc,p[0],a,b,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click three times first for the centre second for the radius a and third for radius b", "Ellipse Drawing", MB_OK | MB_ICONINFORMATION);
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
    void draw(HDC hdc, vector<Point> p, COLORREF color) override{
        HWND hwnd = WindowFromDC(hdc);
        MessageBox(hwnd,"Please enter the tension factor in the console", "Cardinal Spline Tension", MB_HELP);
        double c=1;
        cin>>c;
        DrawCardinalSpline(hdc, p, color, 1000, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click left up to 8 points then click right to draw a Cardinal Spline curve.", "Cardinal Spline Curve Drawing", MB_OK | MB_ICONINFORMATION);
    }
};
class ParametricLine: public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        clippingPoints.emplace_back(p[0],p[1],c);
        Parametric_line(hdc,p,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a parametric line.", "Parametric Line Drawing", MB_OK | MB_ICONINFORMATION);
    }
};
class BresenhamLine: public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        clippingPoints.emplace_back(p[0],p[1],c);
        Bresenham_Line(hdc,p,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a Bresenham line.", "Bresenham Line Drawing", MB_OK | MB_ICONINFORMATION);
    }
};
class DDALine: public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override{
        clippingPoints.emplace_back(p[0],p[1], c);
        DDA_Line(hdc,p,c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Click and drag to draw a DDA line.", "DDA Line Drawing", MB_OK | MB_ICONINFORMATION);
    }
};

class DrawPolygon : public DrawingStrategy {
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override {
        Draw_Polygon(hdc, p, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Left click on multiple points then right click to draw a polygon!", "Draw Polygon:", MB_OK | MB_ICONINFORMATION);
    }
};

class DrawPolygonConvexFill : public DrawingStrategy {
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override {
        DrawPolygon_ConvexFill(hdc, p, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Left click on multiple points then right click to draw a convex filled polygon!", "Draw Convex Filled Polygon:", MB_OK | MB_ICONINFORMATION);
    }
};

class DrawPolygonGeneralFill : public DrawingStrategy {
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c) override {
        DrawPolygon_GeneralFill(hdc, p, c);
    }
    void showHelp(HWND hwnd) override{
        MessageBox(hwnd, "Left click on multiple points then right click to draw a general filled polygon!", "Draw General Filled Polygon:", MB_OK | MB_ICONINFORMATION);
    }
};
#endif