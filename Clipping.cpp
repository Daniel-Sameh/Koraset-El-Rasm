#include <Windows.h>
#include <bits/stdc++.h>
#include "headers/Util.h"
//#include "headers/Line.h"

using namespace std;

union Outcode{ //for Clipping
    struct{ unsigned left:1, right:1, bottom:1, top:1; };
    unsigned all:4;
};
vector<Line>clippingPoints;
vector<vector<Point>> clippingPolygons;
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
void clipWindow(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c, bool draw=true){
//    if (clippingPoints.empty()){
//        MessageBox(hwnd, "Please draw lines to clip", "No lines was found", MB_ICONSTOP);
//        return;
//    }
    vector<Line>newPoints;
    bool clip=false;
    for(auto&[p1,p2,c]:clippingPoints){
        clip=cohenClipping(p1, p2, xLeft, xRight, yBottom, yTop);
        if (clip){
            if(draw){
                SetPixel(hdc, Round(p1.x), Round(p1.y), RGB(0, 0, 0));
                SetPixel(hdc, Round(p2.x), Round(p2.y), RGB(0, 0, 0));
                DDA_Line(hdc, {p1,p2}, c);
            }
            newPoints.emplace_back(p1, p2,c);
        }
    }
    clippingPoints=newPoints;
}

vector<Point> clipLeft(vector<Point> polygon, int xLeft) {
    if (polygon.empty())
        return {};
    Point p1 = polygon.back();
    vector<Point> ret;
    for (int i = 0; i < polygon.size(); ++i) {
        Point p2 = polygon[i];
        bool in1 = p1.x >= xLeft;
        bool in2 = p2.x >= xLeft;
        if (in1 && in2)
            ret.push_back(p2);
        else if (in2) {
            ret.push_back(VIntersect(xLeft, p1, p2));
            ret.push_back(p2);
        }
        else if (in1)
            ret.push_back(VIntersect(xLeft, p1, p2));
        p1 = p2;
    }
    return ret;
}

vector<Point> clipRight(vector<Point> polygon, int xRight) {
    if (polygon.empty())
        return {};
    Point p1 = polygon.back();
    vector<Point> ret;
    for (int i = 0; i < polygon.size(); ++i) {
        Point p2 = polygon[i];
        bool in1 = p1.x <= xRight;
        bool in2 = p2.x <= xRight;
        if (in1 && in2)
            ret.push_back(p2);
        else if (in2) {
            ret.push_back(VIntersect(xRight, p1, p2));
            ret.push_back(p2);
        }
        else if (in1)
            ret.push_back(VIntersect(xRight, p1, p2));
        p1 = p2;
    }
    return ret;
}

vector<Point> clipTop(vector<Point> polygon, int yTop) {
    if (polygon.empty())
        return {};
    Point p1 = polygon.back();
    vector<Point> ret;
    for (int i = 0; i < polygon.size(); ++i) {
        Point p2 = polygon[i];
        bool in1 = p1.y >= yTop;
        bool in2 = p2.y >= yTop;
        if (in1 && in2)
            ret.push_back(p2);
        else if (in2) {
            ret.push_back(HIntersect(yTop, p1, p2));
            ret.push_back(p2);
        }
        else if (in1)
            ret.push_back(HIntersect(yTop, p1, p2));
        p1 = p2;
    }
    return ret;
}

vector<Point> clipBottom(vector<Point> polygon, int yBottom) {
    if (polygon.empty())
        return {};
    Point p1 = polygon.back();
    vector<Point> ret;
    for (int i = 0; i < polygon.size(); ++i) {
        Point p2 = polygon[i];
        bool in1 = p1.y <= yBottom;
        bool in2 = p2.y <= yBottom;
        if (in1 && in2)
            ret.push_back(p2);
        else if (in2) {
            ret.push_back(HIntersect(yBottom, p1, p2));
            ret.push_back(p2);
        }
        else if (in1)
            ret.push_back(HIntersect(yBottom, p1, p2));
        p1 = p2;
    }
    return ret;
}

void draw_Polygon(HDC hdc, vector<Point> polygon, COLORREF c) {
    Point p1 = polygon.back();
    for (auto  p : polygon) {
        DDA_Line(hdc, {p1, p}, c);
        p1 = p;
    }
}

void ClipPolygons(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c) {
    clipWindow(hwnd, hdc, xLeft, xRight, yBottom, yTop, c);
    vector<vector<Point>> newPolygons;
    for (vector<Point> polygon : clippingPolygons) {
        polygon = clipLeft(polygon, xLeft);
        polygon = clipRight(polygon, xRight);
        polygon = clipTop(polygon, yTop);
        polygon = clipBottom(polygon, yBottom);
        if (!polygon.empty()) {
            draw_Polygon(hdc, polygon, c);
            newPolygons.push_back(polygon);
        }
    }
    clippingPolygons = newPolygons;
}

//void clipWindowWithoutDrawing(HWND hwnd, HDC hdc, double xLeft, double xRight, double yBottom, double yTop, COLORREF c){
//    vector<Line>newPoints;
//    bool clip=false;
//    for(auto&[p1,p2,c]:clippingPoints){
//        clip=cohenClipping(p1, p2, xLeft, xRight, yBottom, yTop);
//        if (clip){
//            newPoints.emplace_back(p1, p2,c);
//        }
//    }
//    clippingPoints=newPoints;
//}