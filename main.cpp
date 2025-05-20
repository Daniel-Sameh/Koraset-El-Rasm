#include <Windows.h>
#include<math.h>
#include "Circle.cpp"
static int currentDrawMode = 0,Counter=0;

static COLORREF bgColor = RGB(0, 0, 0);
static COLORREF PColor = RGB(0, 0, 0);
static HCURSOR CURC = LoadCursor(NULL, IDC_ARROW);
struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator*(double a) const {
        return Point(a * x, a * y);
    }

    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }
};

static  Point Points[1000];
LRESULT WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    switch (m) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case 100:
                    currentDrawMode=100;
                break;

                case 101:
                    CURC=LoadCursor(NULL, IDC_ARROW);
                break;

                case 102:
                    CURC=LoadCursor(NULL, IDC_CROSS);
                break;

                case 103:
                    CURC=LoadCursor(NULL, IDC_HAND);
                break;

                case 104:
                    CURC=LoadCursor(NULL, IDC_IBEAM);
                break;

                case 105:
                    CURC=LoadCursor(NULL, IDC_WAIT);
                break;

                case 106:
                    bgColor = RGB(0, 0, 0);
                    InvalidateRect(hwnd, NULL, TRUE);
                break;

                case 107:
                    bgColor = RGB(255, 255, 255);
                    InvalidateRect(hwnd, NULL, TRUE);
                break;

                case 108:
                    PColor = RGB(0, 255, 0);
                break;


                case 109:
                    PColor = RGB(0, 0, 255);
                break;

                case 110:
                    PColor = RGB(255, 0, 0);
                break;

                case 111:
                    InvalidateRect(hwnd, NULL, TRUE);
                    currentDrawMode = 0;
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
            if (currentDrawMode>=100||currentDrawMode<=105) {
                if (Counter==0) {
                    Points[Counter].x = LOWORD(lp);
                    Points[Counter].y = HIWORD(lp);
                    Counter++;
                }
                else if (Counter==1) {
                    Points[Counter].x = LOWORD(lp);
                    Points[Counter].y = HIWORD(lp);
                    if (currentDrawMode==100) {
                        hdc = GetDC(hwnd);
                        int Radius=sqrt(pow(Points[0].x-Points[1].x,2)+pow(Points[0].y-Points[1].y,2));
                        Drawcirclecart(hdc, Points[0].x, Points[0].y, Radius, PColor);
                        ReleaseDC(hwnd, hdc);
                    }
                    Counter=0;
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
    AppendMenu(DrawMenu, MF_STRING, 100, "Draw Circle");
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
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU ShapeCMenu = CreatePopupMenu();
    AppendMenu(ShapeCMenu, MF_STRING, 108, "Green");
    AppendMenu(ShapeCMenu, MF_STRING, 109, "Blue");
    AppendMenu(ShapeCMenu, MF_STRING, 110, "Red");
    ///////////////////////////////////////////////////////////////////////////////////////////
    HMENU Menu = CreateMenu();
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)DrawMenu, "Draw");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)CursorMenu, "Cursor");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)BackGroundMenu, "Background");
    AppendMenu(Menu, MF_POPUP, (UINT_PTR)ShapeCMenu, "Color");
    AppendMenu(Menu, MF_STRING, 111, "Clear");

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
