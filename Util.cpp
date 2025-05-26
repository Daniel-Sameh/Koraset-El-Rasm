#include <Windows.h>
struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator*(double a) const {
        return Point(a * x, a * y);
    }

    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

};


int Round(double x) {
    return static_cast<int>(x + 0.5);
}

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void Draw8Points(HDC hdc, Point p1, Point p2, COLORREF c) {
    SetPixel(hdc, p1.x + p2.x, p1.y + p2.y, c);
    SetPixel(hdc, p1.x + p2.x, p1.y - p2.y, c);
    SetPixel(hdc, p1.x - p2.x, p1.y - p2.y, c);
    SetPixel(hdc, p1.x - p2.x, p1.y + p2.y, c);
    SetPixel(hdc, p1.x - p2.y, p1.y - p2.x, c);
    SetPixel(hdc, p1.x + p2.y, p1.y - p2.x, c);
    SetPixel(hdc, p1.x + p2.y, p1.y + p2.x, c);
    SetPixel(hdc, p1.x - p2.y, p1.y + p2.x, c);
}

struct Line{
    Point p1;
    Point p2;
    COLORREF c;
};
