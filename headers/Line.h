//
// Created by Daniel Sameh on 5/21/2025.
//

#ifndef PROJECT_LINE_H
#define PROJECT_LINE_H
#include <Windows.h>
void DrawBresLineDDA(HDC hdc,int x1,int y1,int x2,int y2,COLORREF c);
void Drawlinebresenham(HDC hdc, int x1, int y1, int x2, int y2,COLORREF c);
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2,COLORREF c);
void drawlineparametric(HDC hdc, int x1, int y1, int x2, int y2,COLORREF c) {
    int alpha1=x2-x1;
    int alpha2=y2-y1;
    double t=0;
    double step=1.0/(std::max(abs(alpha1),abs(alpha2)));

    while (t<1) {
        t+=step;
        double x=x1+alpha1*t;
        double y=y1+alpha2*t;
        SetPixel(hdc,Round(x),Round(y),c);
    }
}
#endif //PROJECT_LINE_H
