//
// Created by Daniel Sameh on 5/20/2025.
//

#ifndef PROJECT_CLIPPINGSTRATEGY_H
#define PROJECT_CLIPPINGSTRATEGY_H
#include <Windows.h>
#include <bits/stdc++.h>
#include "../headers/Util.h"
#include "../headers/Clipping.h"
#include<omp.h>
using namespace std;
class ClippingStrategy{
public:
    virtual void clip(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c) = 0;
//    virtual void showHelp(HWND hwnd) = 0;
    virtual ~ClippingStrategy() = default;
};

class LineClippingStrategy: public ClippingStrategy{
public:
    LineClippingStrategy(){};
    void clip(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c) override{
        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
        clipWindow(hwnd, hdc, xLeft, xRight, yBottom, yTop, c);
    }
};
class PointClippingStrategy: public ClippingStrategy{
public:
    PointClippingStrategy(){}
    void clip(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c) override {
        // 1) get client size
        RECT rcClient;
        GetClientRect(hwnd, &rcClient);
        LONG W = rcClient.right;
        LONG H = rcClient.bottom;

        // 2) normalize your passed window coords
        LONG x1 = static_cast<LONG>(xLeft);
        LONG x2 = static_cast<LONG>(xRight);
        LONG y1 = static_cast<LONG>(yTop);
        LONG y2 = static_cast<LONG>(yBottom);

        LONG xl = min(x1, x2);
        LONG xr = max(x1, x2);
        LONG yt = min(y1, y2);
        LONG yb = max(y1, y2);

        // 3) define the 4 outside-window “bands”
        RECT rTop    = { 0,   0,   W,  yt };
        RECT rBottom = { 0,  yb,  W,  H  };
        RECT rLeft   = { 0,   yt,  xl, yb };
        RECT rRight  = { xr,  yt,  W,  yb };

        // 4) invalidate them (TRUE → erase to background)
        InvalidateRect(hwnd, &rTop,    TRUE);
        InvalidateRect(hwnd, &rBottom, TRUE);
        InvalidateRect(hwnd, &rLeft,   TRUE);
        InvalidateRect(hwnd, &rRight,  TRUE);

        // 5) force an immediate WM_PAINT (optional)
        UpdateWindow(hwnd);
    }
};
#endif //PROJECT_CLIPPINGSTRATEGY_H
