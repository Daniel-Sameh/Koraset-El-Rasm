int Round(double x) {
    return static_cast<int>(x + 0.5);
}
void Draw8Points(HDC hdc,int xc,int yc,int x,int y,COLORREF c) {
    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc-x,yc-y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc-y,yc-x,c);
    SetPixel(hdc,xc+y,yc-x,c);
    SetPixel(hdc,xc+y,yc+x,c);
    SetPixel(hdc,xc-y,yc+x,c);
}
void Drawcirclecart(HDC hdc,int xc,int yc,int r,COLORREF c) {
    int x=0,y=r;
    Draw8Points(hdc,xc,yc,x,y,c);
    while (x<=y) {
        x++;
        y=Round(sqrt(r*r-x*x));
        Draw8Points(hdc,xc,yc,x,y,c);
    }
}