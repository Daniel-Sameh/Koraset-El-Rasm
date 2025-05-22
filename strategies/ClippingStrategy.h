//
// Created by Daniel Sameh on 5/20/2025.
//

#ifndef PROJECT_CLIPPINGSTRATEGY_H
#define PROJECT_CLIPPINGSTRATEGY_H
#include <Windows.h>
#include <bits/stdc++.h>
#include "../headers/Util.h"
#include "../headers/Clipping.h"
using namespace std;
class ClippingStrategy{
public:
    virtual void clip(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c) = 0;
//    virtual void showHelp(HWND hwnd) = 0;
    virtual ~ClippingStrategy() = default;
};

class LineClippingStrategy: public ClippingStrategy{
public:
    LineClippingStrategy(){
        cout<<"hello";
    };
    void clip(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c) override{
        clipWindow(hwnd, hdc, xLeft, xRight, yBottom, yTop, c);
    }
};

#endif //PROJECT_CLIPPINGSTRATEGY_H
