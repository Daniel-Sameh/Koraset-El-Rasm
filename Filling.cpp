#include<omp.h>
void FloodFill(HDC& hdc, Point p, COLORREF& bc, COLORREF& fc) {
     if (p.x>1000||p.y>1000||p.x<0||p.y<0)return;
     COLORREF c = GetPixel(hdc, p.x, p.y);
     if (c == bc || c == fc) {
         return;
     }
     SetPixel(hdc, p.x, p.y, fc);
     Point p1= Point(p.x + 1, p.y);
     Point p2= Point(p.x - 1, p.y);
     Point p3= Point(p.x, p.y + 1);
     Point p4= Point(p.x, p.y - 1);
     FloodFill(hdc, p1, bc, fc);
     FloodFill(hdc, p2, bc, fc);
     FloodFill(hdc, p3, bc, fc);
     FloodFill(hdc, p4, bc, fc);
}

void FloodFillWithStack(HDC hdc, Point p1, COLORREF bc, COLORREF fc) {
     std::stack<Point> s;
     s.push(Point(p1.x, p1.y));
     while (!s.empty()) {
         Point p = s.top();
         s.pop();
         COLORREF c = GetPixel(hdc, p.x, p.y);
         if (c == bc || c == fc) {
             continue;
         }
         SetPixel(hdc, p.x, p.y, fc);

         s.push(Point(p.x, p.y - 1));
         s.push(Point(p.x, p.y + 1));
         s.push(Point(p.x - 1, p.y));
         s.push(Point(p.x + 1, p.y));
     }
}

void FloodFillWithQueue(HDC hdc, Point p1, COLORREF bc, COLORREF fc) {
     std::queue<Point> q;
     q.push(Point(p1.x, p1.y));
     while (!q.empty()) {
         Point p = q.front();
         q.pop();
         COLORREF c = GetPixel(hdc, p.x, p.y);
         if (c == bc || c == fc) {
             continue;
         }
         SetPixel(hdc, p.x, p.y, fc);
         q.push(Point(p.x, p.y - 1));
         q.push(Point(p.x, p.y + 1));
         q.push(Point(p.x - 1, p.y));
         q.push(Point(p.x + 1, p.y));
     }
}

void FillBarycentric(HDC hdc, Point p1, Point p2, Point p3, COLORREF c) {
     for (double t1 = 0; t1 <= 1; t1 += 0.003) {
         for (double t2 = 0; t2 <= 1 - t1; t2 += 0.003) {
             Point p = p1 * t1 + p2 * t2 + p3 * (1 - t1 - t2);
             SetPixel(hdc, Round(p.x), Round(p.y), c);
         }
     }
}
void FillQuarterCircleLines(HDC hdc,Point p1,int r,COLORREF bc,COLORREF fc) {
    DrawCircleBresenhamDDA(hdc,p1,r, bc);
    cout<<"Enter The desired quarter:"<<endl;
    cout<<"1 for Top right\n";
    cout<<"2 for Top left\n";
    cout<<"3 for Bottom left\n";
    cout<<"4 for Bottom right\n";
    int quarter;
    cin>>quarter;
    auto[xc,yc]=p1;
    for (int y = 0; y <= r; y++) {
        int x=sqrt(r*r-y*y);
        switch (quarter) {
            case 1://top right

                DDA_Line(hdc, {{xc, yc - y}, {xc + x, yc - y}}, fc);// yc-y 34an tetla3 lfo2
                break;
            case 2://top left
                DDA_Line(hdc, {{xc, yc - y}, {xc - x, yc - y}}, fc);
                break;
            case 3://bottom left
                DDA_Line(hdc, {{xc, yc + y}, {xc - x, yc + y}},fc);
                break;
            case 4://bottom right
                DDA_Line(hdc, {{xc, yc + y}, {xc + x, yc + y}},fc);
                break;
            default:
                MessageBox(NULL, "Invalid Quarter", "Error", MB_OK);
        }
    }
}

void FillQuarterCircleCircles(HDC hdc,Point p1,int r,COLORREF bc,COLORREF fc) {
    DrawCircleBresenhamDDA(hdc,p1,r, bc);
    cout<<"Enter The desired quarter:"<<endl;
    cout<<"1 for Top right\n";
    cout<<"2 for Top left\n";
    cout<<"3 for Bottom left\n";
    cout<<"4 for Bottom right\n";
    int quarter;
    cin>>quarter;
    auto [xc,yc] = p1;
    for (int nr = 0; nr < r; ++nr) {
        int x = 0, y = nr;
        while (x <= y) {
            switch (quarter) {
                case 1: // top right
                    SetPixel(hdc, xc + x, yc - y, fc);
                    SetPixel(hdc, xc + y, yc - x, fc);
                    break;
                case 2: // top left
                    SetPixel(hdc, xc - x, yc - y, fc);
                    SetPixel(hdc, xc - y, yc - x, fc);
                    break;
                case 3: // bottom left
                    SetPixel(hdc, xc - x, yc + y, fc);
                    SetPixel(hdc, xc - y, yc + x, fc);
                    break;
                case 4: // bottom right
                    SetPixel(hdc, xc + x, yc + y, fc);
                    SetPixel(hdc, xc + y, yc + x, fc);
                    break;
            }
            x++;
            y = Round(sqrt(nr * nr - x * x));
        }
    }
}

void FillWithHermiteCurves(HDC hdc, int xLeft, int xRight, int yBottom, int yTop, double slopeLeft, double slopeRight, COLORREF fillColor){
    if(xLeft>xRight){
        swap(xLeft, xRight);
    }
    if (yBottom > yTop)
        swap(yBottom, yTop);

    int rBase = GetRValue(fillColor);
    int gBase = GetGValue(fillColor);
    int bBase = GetBValue(fillColor);

    int rHighlight = min(rBase + 50, 255); // Ensure values don't exceed 255
    int gHighlight = min(gBase + 50, 255);
    int bHighlight = min(bBase + 50, 255);

    COLORREF highlightColor = RGB(rHighlight, gHighlight, bHighlight);

//    #pragma omp parallel for shared(xLeft, xRight)
    for (int i=yBottom; i<=yTop; ++i){
        Point p[]={{(double) xLeft,(double) i},{slopeLeft,slopeLeft},{(double) xRight,(double) i},{slopeRight,slopeRight}};

//        #pragma omp critical
        DrawHermiteCurve(hdc,p,fillColor,highlightColor,2000);
    }
}

void FillWithBezierCurves(HDC hdc, int xLeft, int xRight, int yBottom, int yTop, COLORREF fillColor){
    if(xLeft>xRight){
        swap(xLeft, xRight);
    }
    if (yBottom > yTop) {
        swap(yBottom, yTop);
    }
    for(int i=xLeft; i<=xRight; ++i){
        vector<Point>points={{(double) i, (double) yBottom},{(double) i, (double) ((yBottom+yTop)/2.0)},{(double)i, (double)yTop}};
        DrawBezierCurve(hdc, points, fillColor, 1000);
    }
}
