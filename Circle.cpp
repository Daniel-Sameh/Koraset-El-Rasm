void DrawCircleCartesian(HDC hdc, Point P1, int r, COLORREF c) {
    int x = 0, y = r;
    Draw8Points(hdc, P1, Point(x,y), c);
    while (x <= y) {
        x++;
        y = Round(sqrt(r * r - x * x));
        Draw8Points(hdc, P1, Point(x,y), c);
    }
}

void DrawCircleBresenhamDDA(HDC hdc, Point P1, int r, COLORREF c) {
    double x=0,y=r;
    Draw8Points(hdc, P1,Point(x,y), c);
    float d=1-r;
    int d1=3;
    int d2=5-2*r;
    while (x<y) {
        if (d>0) {
            d+=d2;
            d1+=2;
            d2+=4;
            x++;
            y--;
        }
        else {
            d+=d1;
            d1+=2;
            d2+=2;
            x++;
        }
        Draw8Points(hdc, P1,Point(x,y), c);
    }
}
 
void DrawCircleBresenham(HDC hdc, Point P1, int r, COLORREF c) {
    double x=0,y=r;
    Draw8Points(hdc, P1,Point(x,y), c);
    while (x<y) {
        float d=pow(x+1,2)+pow(y-0.5,2)-pow(r,2);
        if (d>0) {
            x++;
            y--;
        }
        else {
            x++;
        }
        Draw8Points(hdc, P1,Point(x,y), c);
    }
}

void DrawCirclePolarIterative(HDC hdc, Point P1, int r, COLORREF c) {
    double x=r,y=0;
    double ct=cos(1.0/r);
    double st=sin(1.0/r);
    Draw8Points(hdc, P1,Point(x,y), c);
    while (x>y) {
        double x1=x*ct-y*st;
        y=x*st+y*ct;
        x=x1;
        Draw8Points(hdc, P1,Point(Round(x),Round(y)), c);

    }
}

void DrawCirclePolar(HDC hdc, Point P1, int r, COLORREF c) {
    int x=r,y=0;
    Draw8Points(hdc, P1,Point(x,y), c);
    double theta=0,dtheta=1.0/r;
    while (x>=y) {
        theta+=dtheta;
        x=Round(r*cos(theta));
        y=Round(r*sin(theta));
        Draw8Points(hdc, P1,Point(x,y), c);

    }
}
