#include <Windows.h>
#include <bits/stdc++.h>
#include "headers/Util.h"
//#include "headers/Line.h"

using namespace std;

union Outcode{ //for Clipping
    struct{ unsigned left:1, right:1, bottom:1, top:1; };
    unsigned all:4;
};
vector<pair<Point,Point>>clippingPoints;
///Utility Functions:
Outcode getOutCode(double x, double y, double xLeft, double xRight, double yBottom, double yTop){
    Outcode out; out.all=0;
    if (x<xLeft) out.left=1; else if (x>xRight) out.right=1;
    if (y>yBottom) out.bottom=1; else if (y<yTop) out.top=1;
    return out;
}
Point VIntersect(double xEdge, Point&p1, Point&p2){
    Point res;
    res.x=xEdge;
    res.y= p1.y + (xEdge-p1.x)*(p2.y-p1.y)/(p2.x-p1.x);
    return res;
}
Point HIntersect(double yEdge, Point&p1, Point&p2){
    Point res;
    res.y=yEdge;
    res.x= p1.x + (yEdge-p1.y)*(p2.x-p1.x)/(p2.y-p1.y);
    return res;
}
///Cohen Sutherland Clipping Algorithm:
bool cohenClipping(Point&p1, Point&p2, double xLeft, double xRight, double yBottom, double yTop){
    Outcode out1 = getOutCode(p1.x, p1.y, xLeft, xRight, yBottom, yTop);
    Outcode out2 = getOutCode(p2.x, p2.y, xLeft, xRight, yBottom, yTop);
    while (true){
        if (out1.all==0 && out2.all==0) return true; //the line is inside the window
        if (out1.all&out2.all) return false; //the line is totally clipped out of the window (intersection in the outCodes)
        if (out1.all){
            if (out1.left) p1= VIntersect(xLeft, p1,p2);
            else if (out1.right) p1= VIntersect(xRight, p1, p2);
            else if (out1.bottom) p1= HIntersect(yBottom, p1, p2);
            else p1= HIntersect(yTop, p1, p2);
            out1= getOutCode(p1.x, p1.y, xLeft, xRight, yBottom, yTop);
        }else{
            if (out2.left) p2= VIntersect(xLeft, p1,p2);
            else if (out2.right) p2= VIntersect(xRight, p1, p2);
            else if (out2.bottom) p2= HIntersect(yBottom, p1, p2);
            else p2= HIntersect(yTop, p1, p2);
            out2= getOutCode(p2.x, p2.y, xLeft, xRight, yBottom, yTop);
        }
    }
    return true;
}
///Main Clip:
void clipWindow(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c){
    if (clippingPoints.empty()){
        MessageBox(hwnd, "Please draw lines to clip", "No lines was found", MB_ICONSTOP);
        return;
    }
    vector<pair<Point,Point>>oldPoints=clippingPoints;
    bool clip=false;
    for(auto&[p1,p2]:clippingPoints){
        clip=cohenClipping(p1, p2, xLeft, xRight, yBottom, yTop);
        if (clip){
            SetPixel(hdc, Round(p1.x), Round(p1.y), RGB(0, 0, 0));
            SetPixel(hdc, Round(p2.x), Round(p2.y), RGB(0, 0, 0));
            DDA_Line(hdc, {p1,p2}, c);
        }
    }
    clippingPoints=oldPoints;
}