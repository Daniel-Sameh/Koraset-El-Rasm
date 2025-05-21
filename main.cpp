#include <Windows.h>
#include<math.h>
#include <stack>
#include <queue>
//#include "Util.cpp"
//#include "Circle.cpp"
//#include "Filling.cpp"
#include "Context.h"
#include <bits/stdc++.h>
using namespace std;
static int LCurrentDrawMode = 0,LCounter=0,RCurrentDrawMode=0,RCounter=0;

static COLORREF bgColor = RGB(255, 255, 255);
static COLORREF PColor = RGB(0, 0, 0);
static COLORREF FColor = RGB(255, 255, 255);
static HCURSOR CURC = LoadCursor(NULL, IDC_ARROW);
static  Point RPoints[1000], LPoints[1000];
vector<Point> points;
bool isDrawing = true;
LRESULT WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    CHOOSECOLOR cc;
    static COLORREF clr[16] = { 0 };
    static Context context;
    static DrawingStrategy* drawingStrategy;
    static FillStrategy* fillStrategy;
    switch (m) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case 901:CURC = LoadCursor(NULL, IDC_ARROW); break;
                case 902:CURC = LoadCursor(NULL, IDC_CROSS); break;
                case 903:CURC = LoadCursor(NULL, IDC_HAND); break;
                case 904:CURC = LoadCursor(NULL, IDC_IBEAM); break;
                case 905:CURC = LoadCursor(NULL, IDC_WAIT); break;
                case 906:bgColor = RGB(0, 0, 0);InvalidateRect(hwnd, NULL, TRUE);break;
                case 907:bgColor = RGB(255, 255, 255);InvalidateRect(hwnd, NULL, TRUE);break;
                case 908:
                    ZeroMemory(&cc, sizeof(cc));
                    cc.lStructSize = sizeof(cc);
                    cc.hwndOwner = hwnd;
                    cc.lpCustColors = clr;
                    cc.rgbResult = bgColor;
                    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
                    if (ChooseColor(&cc)) {
                        bgColor = cc.rgbResult;
                        InvalidateRect(hwnd, NULL, TRUE);
                    }
                    break;
                case 909:
                    ZeroMemory(&cc, sizeof(cc));
                    cc.lStructSize = sizeof(cc);
                    cc.hwndOwner = hwnd;
                    cc.lpCustColors = clr;
                    cc.rgbResult = bgColor;
                    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
                    if (ChooseColor(&cc)) {
                        PColor = cc.rgbResult;
//                            InvalidateRect(hwnd, NULL, TRUE);
                    }
                    break;
                case 910:
                    ZeroMemory(&cc, sizeof(cc));
                    cc.lStructSize = sizeof(cc);
                    cc.hwndOwner = hwnd;
                    cc.lpCustColors = clr;
                    cc.rgbResult = bgColor;
                    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
                    if (ChooseColor(&cc)) {
                        FColor = cc.rgbResult;
//                            InvalidateRect(hwnd, NULL, TRUE);
                    }
                    break;
                case 911:
                    InvalidateRect(hwnd, NULL, TRUE);
                    LCurrentDrawMode = 0, RCurrentDrawMode = 0;
                    break;
                case 200:
                    drawingStrategy = new CircleCartesian();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 200;
                    break;
                case 201:
                    drawingStrategy = new CirclePolar();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 201;
                    break;
                case 202:
                    drawingStrategy = new CirclePolarIterative();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 202;
                    break;
                case 203:
                    drawingStrategy = new CircleBresenham();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 203;
                    break;
                case 204:
                    drawingStrategy = new CircleBresenhamDDA();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 204;
                    break;
                case 100:
                    fillStrategy = new RecFloodFillStrategy();
                    context.setFillStrategy(fillStrategy);
                    RCurrentDrawMode = 100;
                    break;
                case 101:
                    fillStrategy = new FloodFillWithStackStrategy();
                    context.setFillStrategy(fillStrategy);
                    RCurrentDrawMode = 101;
                    break;
                case 102:
                    fillStrategy = new FloodFillWithQueueStrategy();
                    context.setFillStrategy(fillStrategy);
                    RCurrentDrawMode = 102;
                    break;
                case 303:
                    fillStrategy = new BarycentricFillStrategy();
                    context.setFillStrategy(fillStrategy);
                    RCurrentDrawMode = 303;
                    break;
                case 301:
                    drawingStrategy = new QuadraticCurve();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 301;
                    break;
                case 801:
                    drawingStrategy = new MidPointBezier();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 801;
                    RCurrentDrawMode = 199;
                    break;
                case 802:
                    drawingStrategy = new RecursiveBezier();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 802;
                    RCurrentDrawMode = 199;
                    break;
                case 400:
                    drawingStrategy= new CardinalSpline();
                    context.setDrawingStrategy(drawingStrategy);
                    LCurrentDrawMode = 803;
                    RCurrentDrawMode = 199;
                    break;
            }

        break;

        case WM_ERASEBKGND:{
            hdc = (HDC)wp;
            RECT rc;
            GetClientRect(hwnd, &rc);
            HBRUSH hBrush = CreateSolidBrush(bgColor);
            FillRect(hdc, &rc, hBrush);
            DeleteObject(hBrush);
        break;
        }

        case WM_LBUTTONDOWN: {
            int req = LCurrentDrawMode / 100;
            if (LCounter < req) {
                points.push_back(Point(LOWORD(lp), HIWORD(lp)));
                LCounter++;
            }
            break;
        }
        case WM_LBUTTONUP: {
            int req = LCurrentDrawMode / 100;
            if (LCounter < req && LOWORD(lp) != points.back().x && HIWORD(lp) != points.back().y) {
                points.push_back(Point(LOWORD(lp), HIWORD(lp)));
                LCounter++;
            }
            if (req == LCounter) {
                vector<Point> copy(points);
                hdc = GetDC(hwnd);
                thread([=](){
                    context.draw(hdc, copy, PColor);
                    ReleaseDC(hwnd, hdc);
                }).detach();
                points.clear();
                LCounter = 0;
            }

            break;
        }

        case WM_RBUTTONDOWN: {
            int req = RCurrentDrawMode / 100;
            if (req > RCounter) {
                if (RCurrentDrawMode % 100 != 99) // if the click were to fill = save the position of the click
                    points.push_back(Point(LOWORD(lp), HIWORD(lp)));
                RCounter++;
            }
            break;
        }


        case WM_RBUTTONUP: {
            int req = RCurrentDrawMode / 100;
            if (req == RCounter) {
                vector<Point> copy(points);
                hdc = GetDC(hwnd);
                if (RCurrentDrawMode % 100 == 99 && !copy.empty()) { // draw curve after the right click
                    thread([=](){
                        context.draw(hdc, copy, PColor);
                        ReleaseDC(hwnd, hdc);
                    }).detach();
                    LCounter = 0;
                }
                else { // fill after the right click
                    thread([=](){
                        context.fill(hdc, copy, PColor, FColor);
                        ReleaseDC(hwnd, hdc);
                    }).detach();
                }
                points.clear();
                RCounter=0;
            }
            break;
        }
        case WM_SETCURSOR:
            SetCursor(CURC);
        break;

        case WM_CLOSE:
            DestroyWindow(hwnd); break;
        case WM_DESTROY:
            PostQuitMessage(0); break;
        default:return DefWindowProc(hwnd, m, wp, lp);
    }
    return 0;
}
int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR cmd, int nsh) {
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.lpszClassName = "MyClass";
    wc.lpszMenuName = NULL;
    wc.lpfnWndProc = WndProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = hi;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("MyClass", "Koraset El Rasm", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hi, 0);


    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU DrawMenu = CreatePopupMenu();
    HMENU CircleMenu = CreatePopupMenu();
    AppendMenu(DrawMenu, MF_POPUP, (UINT_PTR)CircleMenu, "Circle");

    AppendMenu(CircleMenu, MF_STRING, 200, "Cartesian");
    AppendMenu(CircleMenu, MF_STRING, 201, "Polar");
    AppendMenu(CircleMenu, MF_STRING, 202, "Polar Iterative");
    AppendMenu(CircleMenu, MF_STRING, 203, "Bresenham");
    AppendMenu(CircleMenu, MF_STRING, 204, "Bresenham DDA");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU CurveMenu = CreatePopupMenu();
    AppendMenu(DrawMenu, MF_POPUP, (UINT_PTR)CurveMenu, "Curve");

    AppendMenu(CurveMenu, MF_STRING, 301, "Quadratic Curve");
    AppendMenu(CurveMenu, MF_STRING, 801, "MidPoint Bezier");
    AppendMenu(CurveMenu, MF_STRING, 802, "Recursive Bezier");
    AppendMenu(CurveMenu, MF_STRING, 400, "Cardinal Spline");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU FillMenu = CreatePopupMenu();
    AppendMenu(FillMenu, MF_STRING, 100, "FloodFillRecursive");
    AppendMenu(FillMenu, MF_STRING, 101, "FloodFillWithStack");
    AppendMenu(FillMenu, MF_STRING, 102, "FloodFillWithQueue");
    AppendMenu(FillMenu, MF_STRING, 303, "FillBarycentric");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU CursorMenu = CreatePopupMenu();
    AppendMenu(CursorMenu, MF_STRING, 901, "Arrow");
    AppendMenu(CursorMenu, MF_STRING, 902, "Cross");
    AppendMenu(CursorMenu, MF_STRING, 903, "Hand");
    AppendMenu(CursorMenu, MF_STRING, 904, "I-Beam");
    AppendMenu(CursorMenu, MF_STRING, 905, "Wait");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU BackGroundMenu = CreatePopupMenu();
    AppendMenu(BackGroundMenu, MF_STRING, 906, "Black");
    AppendMenu(BackGroundMenu, MF_STRING, 907, "White");
    AppendMenu(BackGroundMenu, MF_STRING, 908, "Custom");
    ///////////////////////////////////////////////////////////////////////////////////////////
//    HMENU ShapeCMenu = CreatePopupMenu();
//    AppendMenu(ShapeCMenu, MF_STRING, 110, "Red");
//    AppendMenu(ShapeCMenu, MF_STRING, 108, "Green");
//    AppendMenu(ShapeCMenu, MF_STRING, 109, "Blue");
    ///////////////////////////////////////////////////////////////////////////////////////////
//    HMENU FillCMenu = CreatePopupMenu();
//    AppendMenu(FillCMenu, MF_STRING, 114, "Red");
//    AppendMenu(FillCMenu, MF_STRING, 112, "Green");
//    AppendMenu(FillCMenu, MF_STRING, 113, "Blue");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU ColorMenu = CreateMenu();
    AppendMenu(ColorMenu, MF_STRING, 909, "Shape");
    AppendMenu(ColorMenu, MF_STRING, 910, "Fill");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU Menu = CreateMenu();
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)DrawMenu, "Draw");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)FillMenu, "Fill");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)CursorMenu, "Cursor");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)BackGroundMenu, "Background");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)ColorMenu, "Color");
    ///////////////////////////////////////////////////////////////////////////////////////////
    AppendMenu(Menu, MF_STRING, 911, "Clear");
    ///////////////////////////////////////////////////////////////////////////////////////////
    SetMenu(hwnd, Menu);


    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
