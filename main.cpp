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

static COLORREF bgColor = RGB(0, 0, 0);
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

                    case 101: CURC = LoadCursor(NULL, IDC_ARROW); break;
                    case 102: CURC = LoadCursor(NULL, IDC_CROSS); break;
                    case 103: CURC = LoadCursor(NULL, IDC_HAND); break;
                    case 104: CURC = LoadCursor(NULL, IDC_IBEAM); break;
                    case 105: CURC = LoadCursor(NULL, IDC_WAIT); break;
                    case 106: bgColor = RGB(0, 0, 0); InvalidateRect(hwnd, NULL, TRUE); break;
                    case 107: bgColor = RGB(255, 255, 255); InvalidateRect(hwnd, NULL, TRUE); break;
                    case 108:
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
                    case 109:
                        ZeroMemory(&cc, sizeof(cc));
                        cc.lStructSize = sizeof(cc);
                        cc.hwndOwner = hwnd;
                        cc.lpCustColors = clr;
                        cc.rgbResult = bgColor;
                        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
                        if (ChooseColor(&cc)) {
                            PColor = cc.rgbResult;
                            InvalidateRect(hwnd, NULL, TRUE);
                        }
                        break;
                    case 110:
                        ZeroMemory(&cc, sizeof(cc));
                        cc.lStructSize = sizeof(cc);
                        cc.hwndOwner = hwnd;
                        cc.lpCustColors = clr;
                        cc.rgbResult = bgColor;
                        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
                        if (ChooseColor(&cc)) {
                            FColor = cc.rgbResult;
                            InvalidateRect(hwnd, NULL, TRUE);
                        }
                        break;
                    case 111: InvalidateRect(hwnd, NULL, TRUE); LCurrentDrawMode = 0, RCurrentDrawMode = 0; break;
                    case 300:
                        drawingStrategy = new CircleCartesian();
                        context.setDrawingStrategy(drawingStrategy);
                        LCurrentDrawMode=300;
                        break;
                    case 301:
                        drawingStrategy = new CirclePolar();
                        context.setDrawingStrategy(drawingStrategy);
                        LCurrentDrawMode=301;
                        break;
                    case 302:
                        drawingStrategy = new CirclePolarIterative();
                        context.setDrawingStrategy(drawingStrategy);
                        LCurrentDrawMode=302;
                        break;
                    case 303:
                        drawingStrategy = new CircleBresenham();
                        context.setDrawingStrategy(drawingStrategy);
                        LCurrentDrawMode=303;
                        break;
                    case 304:
                        drawingStrategy = new CircleBresenhamDDA();
                        context.setDrawingStrategy(drawingStrategy);
                        LCurrentDrawMode=304;
                        break;
                    case 200:
                        fillStrategy = new RecFloodFillStrategy();
                        context.setFillStrategy(fillStrategy);
                        RCurrentDrawMode = 200;
                        break;
                    case 201:
                        fillStrategy = new FloodFillWithStackStrategy();
                        context.setFillStrategy(fillStrategy);
                        RCurrentDrawMode = 201;
                        break;
                    case 202:
                        fillStrategy = new FloodFillWithQueueStrategy();
                        context.setFillStrategy(fillStrategy);
                    RCurrentDrawMode = 202;
                        break;
                    case 203:
                        fillStrategy = new BarycentricFillStrategy();
                        context.setFillStrategy(fillStrategy);

                        break;

                    default:
                        if (LOWORD(wp) >= 300 && LOWORD(wp) <= 304) {
                            LCurrentDrawMode = LOWORD(wp);
                        }
                        if (LOWORD(wp) >= 200 && LOWORD(wp) <= 204) {
                            RCurrentDrawMode = LOWORD(wp);
                        }
                    break;
                }

        break;

        case WM_ERASEBKGND:{
            HDC hdc = (HDC)wp;
            RECT rc;
            GetClientRect(hwnd, &rc);
            HBRUSH hBrush = CreateSolidBrush(bgColor);
            FillRect(hdc, &rc, hBrush);
            DeleteObject(hBrush);
        break;
        }

        case WM_LBUTTONDOWN:
            if(LCurrentDrawMode>=300&&LCurrentDrawMode<=304){
                points.push_back(Point(LOWORD(lp), HIWORD(lp)));
                LCounter++;
            }
            break;
        case WM_LBUTTONUP:
            if (LCurrentDrawMode>=300&&LCurrentDrawMode<=304) {
                points.push_back(Point(LOWORD(lp), HIWORD(lp)));
                LCounter++;
                if (LCounter == 2) {
                    hdc = GetDC(hwnd);
                    context.draw(hdc, points, PColor);
                    ReleaseDC(hwnd, hdc);
                    LCounter = 0;
                    points.clear();
                }
            }

            break;
        case WM_RBUTTONDOWN:
            if (RCurrentDrawMode>=200&&RCurrentDrawMode<203) {
                RPoints[0].x = LOWORD(lp);
                RPoints[0].y = HIWORD(lp);
                hdc = GetDC(hwnd);
                switch (RCurrentDrawMode) {
                    case 200: FloodFill(hdc, RPoints[0], PColor, FColor); break;
                    case 201: FloodFillWithStack(hdc, RPoints[0] ,PColor, FColor); break;
                    case 202: FloodFillWithQueue(hdc, RPoints[0], PColor, FColor); break;
                }
                ReleaseDC(hwnd, hdc);
            }
            if (RCurrentDrawMode==203) {
                RPoints[RCounter].x = LOWORD(lp);
                RPoints[RCounter].y = HIWORD(lp);
                if (++RCounter == 3) {
                    hdc = GetDC(hwnd);
                    FillBarycentric(hdc, RPoints[0], RPoints[1], RPoints[2], FColor);
                    ReleaseDC(hwnd, hdc);
                    RCounter=0;
                }

            }
        break;
        
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
    HWND hwnd = CreateWindow("MyClass", "Project", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hi, 0);


    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU DrawMenu = CreatePopupMenu();
    HMENU CircleMenu = CreatePopupMenu();
    AppendMenu(DrawMenu, MF_POPUP, (UINT_PTR)CircleMenu, "Draw Circle");

    AppendMenu(CircleMenu, MF_STRING, 300, "Cartesian");
    AppendMenu(CircleMenu, MF_STRING, 301, "Polar");
    AppendMenu(CircleMenu, MF_STRING, 302, "Polar Iterative");
    AppendMenu(CircleMenu, MF_STRING, 303, "Bresenham");
    AppendMenu(CircleMenu, MF_STRING, 304, "Bresenham DDA");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU FillMenu = CreatePopupMenu();
    AppendMenu(FillMenu, MF_STRING, 200, "FloodFillRecursive");
    AppendMenu(FillMenu, MF_STRING, 201, "FloodFillWithStack");
    AppendMenu(FillMenu, MF_STRING, 202, "FloodFillWithQueue");
    AppendMenu(FillMenu, MF_STRING, 203, "FillBarycentric");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU CursorMenu = CreatePopupMenu();
    AppendMenu(CursorMenu, MF_STRING, 101, "Arrow");
    AppendMenu(CursorMenu, MF_STRING, 102, "Cross");
    AppendMenu(CursorMenu, MF_STRING, 103, "Hand");
    AppendMenu(CursorMenu, MF_STRING, 104, "I-Beam");
    AppendMenu(CursorMenu, MF_STRING, 105, "Wait");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU BackGroundMenu = CreatePopupMenu();
    AppendMenu(BackGroundMenu, MF_STRING, 106, "Black");
    AppendMenu(BackGroundMenu, MF_STRING, 107, "White");
    AppendMenu(BackGroundMenu, MF_STRING, 108, "Custom");
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
    AppendMenu(ColorMenu, MF_STRING, 109, "Shape");
    AppendMenu(ColorMenu, MF_STRING, 110, "Fill");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU Menu = CreateMenu();
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)DrawMenu, "Draw");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)FillMenu, "Fill");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)CursorMenu, "Cursor");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)BackGroundMenu, "Background");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)ColorMenu, "Color");
    ///////////////////////////////////////////////////////////////////////////////////////////
    AppendMenu(Menu, MF_STRING, 111, "Clear");
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
