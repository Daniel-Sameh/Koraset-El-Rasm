#ifndef PROJECT_DRAWINGSTRATEGY_H
#define PROJECT_DRAWINGSTRATEGY_H
#include <Windows.h>
#include "../headers/Util.h"
#include <vector>
#include <thread>
#include <memory>
#include "../headers/Circle.h"
using namespace std;

class DrawingStrategy {
public:
    virtual void draw(HDC hdc, vector<Point>p, COLORREF c) = 0;
//    virtual void draw(HDC hdc, Point p, int r, COLORREF c) = 0;
    virtual ~DrawingStrategy() = default;
};

class CircleCartesian: public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c){
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        DrawCircleCartesian(hdc, p[0], r, c);
    }
};

class CircleBresenham : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c){
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
//        thread(DrawCircleBresenham, hdc, p[0], r, c).detach();
        DrawCircleBresenham(hdc, p[0], r, c);
    }
};

class CircleBresenhamDDA : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c){
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
//        thread(DrawCircleBresenhamDDA, hdc, p[0], r, c).detach();
        DrawCircleBresenhamDDA(hdc, p[0], r, c);
    }
};

class CirclePolar : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c){
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
//        thread(DrawCirclePolar, hdc, p[0], r, c).detach();
        DrawCirclePolar(hdc, p[0], r, c);
    }
};

class CirclePolarIterative : public DrawingStrategy{
public:
    void draw(HDC hdc, vector<Point> p, COLORREF c){
        auto [x1, y1] = p[0];
        auto [x2, y2] = p[1];
        int r = (int) sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
//        thread(DrawCirclePolarIterative, hdc, p[0], r, c).detach();
        DrawCirclePolarIterative(hdc, p[0], r, c);
    }
};

#endif
