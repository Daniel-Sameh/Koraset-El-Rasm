#ifndef PROJECT_CONTEXT_H
#define PROJECT_CONTEXT_H
#include <Windows.h>
#include <vector>
//#include "Util.cpp"
#include "strategies/DrawingStrategy.h"
#include "strategies/FillStrategy.h"
#include "strategies/ClippingStrategy.h"
//#include "strategies/CircleStrategy.h"
using namespace std;

class Context {
private:
    DrawingStrategy* drawingStrategy;
    FillStrategy* fillStrategy;
    ClippingStrategy* clippingStrategy;
public:
    Context(): drawingStrategy(nullptr), fillStrategy(nullptr), clippingStrategy(new LineClippingStrategy()){};
    void setDrawingStrategy(DrawingStrategy* strategy){
        drawingStrategy=strategy;
    }
    void setFillStrategy(FillStrategy* strategy){
        fillStrategy=strategy;
    }
    void setClippingStrategy(ClippingStrategy* strategy){
        clippingStrategy=strategy;
    }
    void draw(HDC hdc, vector<Point> p, COLORREF c){
        if (drawingStrategy){
            drawingStrategy->draw(hdc,p,c);
        }
    }
    void fill(HDC hdc, vector<Point> p, COLORREF borderColor, COLORREF fillColor){
        if (fillStrategy){
            fillStrategy->fill(hdc, p, borderColor, fillColor);
        }
    }

    void showHelp(HWND hwnd){
        if (!drawingStrategy&&!fillStrategy){
            MessageBox(hwnd, "Please select a drawing or fill tool first.", "Error", MB_OK | MB_ICONERROR);
        }
        else if (drawingStrategy){
            drawingStrategy->showHelp(hwnd);
        }
        else if (fillStrategy){
            MessageBox(hwnd, "Fill strategy selected.", "Info", MB_OK | MB_ICONINFORMATION);
        }
    }

    void clip(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c){
        clippingStrategy->clip(hwnd, hdc, xLeft, xRight, yBottom, yTop, c);
    }
};


#endif
