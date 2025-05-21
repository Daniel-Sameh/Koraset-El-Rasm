#ifndef PROJECT_CONTEXT_H
#define PROJECT_CONTEXT_H
#include <Windows.h>
#include <vector>
//#include "Util.cpp"
#include "strategies/DrawingStrategy.h"
#include "strategies/FillStrategy.h"
//#include "strategies/CircleStrategy.h"
using namespace std;

class Context {
private:
    DrawingStrategy* drawingStrategy;
    FillStrategy* fillStrategy;
//    CircleStrategy* circleStrategy;
public:
    Context(): drawingStrategy(nullptr), fillStrategy(nullptr){};
    void setDrawingStrategy(DrawingStrategy* strategy){
        drawingStrategy=strategy;
    }
    void setFillStrategy(FillStrategy* strategy){
        fillStrategy=strategy;
    }
//    void setCircleStrategy(CircleStrategy* strategy){
//        circleStrategy=strategy;
//    }
    void draw(HDC hdc, vector<Point>&p, COLORREF c){
        if (drawingStrategy){
            drawingStrategy->draw(hdc,p,c);
        }
    }
    void fill(HDC hdc, vector<Point> p, COLORREF borderColor, COLORREF fillColor){
        if (fillStrategy){
            fillStrategy->fill(hdc, p, borderColor, fillColor);
        }
    }
//    void drawCircle(HDC hdc, Point p, int r, COLORREF c){
//        if(circleStrategy){
//            circleStrategy->draw(hdc, p, r, c);
//        }
//    }

};


#endif
