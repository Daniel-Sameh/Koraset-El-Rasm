//
// Created by Daniel Sameh on 6/5/2025.
//
//#include <Windows.h>
void drawEllipseDirect(HDC hdc,Point p1, int a, int b,COLORREF c) {
    for (int x = 0; x <= a; x++) {
        float y = b * sqrt(1.0 - (float)(x * x) / (a * a));
        drawEllipsePoints(hdc,p1, x, round(y),c);
    }
    for (int y = 0; y <= b; y++) {
        float x = a * sqrt(1.0 - (float)(y * y) / (b * b));
        drawEllipsePoints(hdc,p1, round(x), y, c);
    }
}
void drawEllipsePolar(HDC hdc,Point p1, int a, int b,COLORREF c) {
    float theta = 0;
    float step = 1.0 / std::max(a, b);
    while (theta <= 3.14159265358979323846/2 ) {
        int x = round(a * cos(theta));
        int y = round(b * sin(theta));
        drawEllipsePoints(hdc,p1, x, y,c);
        theta += step;
    }
}

double calc(double x, double y, double a, double b) {
    return (b * b * x * x) + (a * a * y * y) - (a * a * b * b);
}

void DrawMidpointEllipse(HDC hdc, Point p1, int a, int b, COLORREF c) {
    auto [xc, yc] = p1;
    double x = 0;
    double y = b;
    drawEllipsePoints(hdc, p1, x, y, c);
    while (2 * b * b * x < 2 * a * a * y) {
        double d = calc(x + 1, y - 0.5, a, b);
        if (d > 0) {
            y--;
        }
        x++;
        drawEllipsePoints(hdc, p1, x, y, c);
    }
    while (y >= 0) {
        double d = calc(x + 0.5, y - 1, a, b);
        if (d <= 0) {
            x++;
        }
        y--;
        drawEllipsePoints(hdc, p1, x, y, c);
    }
}