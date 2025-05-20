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
void Draw8Points(HDC hdc,int xc,int yc,int x,int y,COLORREF c) {
    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc-x,yc-y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc-y,yc-x,c);
    SetPixel(hdc,xc+y,yc-x,c);
    SetPixel(hdc,xc+y,yc+x,c);
    SetPixel(hdc,xc-y,yc+x,c);
}