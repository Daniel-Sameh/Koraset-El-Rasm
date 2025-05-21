//
// Created by PC on 5/22/2025.
//

void Parametric_line(HDC hdc,vector<Point>p,COLORREF c){
    int alpha1=p[1].x-p[0].x;
    int alpha2=p[1].y-p[0].y;
    double step=1.0/max(abs(alpha1),abs(alpha2));
    for (double t = 0; t <= 1; t+=step) {
        double x=alpha1*t+p[0].x;
        double y=alpha2*t+p[0].y;
        SetPixel(hdc, Round(x), Round(y),c);
    }
}
void Bresenham_Line(HDC hdc,vector<Point>p,COLORREF c){
    int dx=p[1].x-p[0].x;
    int dy=p[1].y-p[0].y;
    double m=(double)dy/dx;
    if(m>0&&m<=1){
        if(p[0].x>p[1].x){
            swap(p[0].x,p[1].x);
            swap(p[0].y,p[1].y);
            int dx=p[1].x-p[0].x;
            int dy=p[1].y-p[0].y;
        }
        int d=dx-2*dy;
        int d1=-2*dy;
        int d2=2*(dx-dy);
        int x=p[0].x;
        int y=p[0].y;
        SetPixel(hdc,x,y,c);
        while(x<p[1].x){
            if(d>0){
                d+=d1;
            }else{
                d+=d2;
                y++;
            }
            x++;
            SetPixel(hdc,x,y,c);
        }
    }else if(m>1){
        if(p[0].y>p[1].y){
            swap(p[0].x,p[1].x);
            swap(p[0].y,p[1].y);
            int dx=p[1].x-p[0].x;
            int dy=p[1].y-p[0].y;
        }
        int d=dy-2*dx;
        int d1=-2*dx;
        int d2=2*(dy-dx);
        int x=p[0].x;
        int y=p[0].y;
        SetPixel(hdc,x,y,c);
        while(y<p[1].y){
            if(d>0){
                d+=d1;
            }else{
                d+=d2;
                x++;
            }
            y++;
            SetPixel(hdc,x,y,c);
        }
    }else if(m<0 && m>-1){
        if(p[0].x>p[1].x){
            swap(p[0].x,p[1].x);
            swap(p[0].y,p[1].y);
            int dx=p[1].x-p[0].x;
            int dy=p[1].y-p[0].y;
        }
        int d=dx+2*dy;
        int d1=2*dy;
        int d2=2*(dx+dy);
        int x=p[0].x;
        int y=p[0].y;
        SetPixel(hdc,x,y,c);
        while(x<p[1].x){
            if(d>0){
                d+=d1;
            }else{
                d+=d2;
                y--;
            }
            x++;
            SetPixel(hdc,x,y,c);
        }
    }else{
        if(p[0].y>p[1].y){
            swap(p[0].x,p[1].x);
            swap(p[0].y,p[1].y);
            int dx=p[1].x-p[0].x;
            int dy=p[1].y-p[0].y;
        }
        int d=dy+2*dx;
        int d1=2*dx;
        int d2=2*(dy+dx);
        int x=p[0].x;
        int y=p[0].y;
        SetPixel(hdc,x,y,c);
        while(y<p[1].y){
            if(d>0){
                d+=d1;
            }else{
                d+=d2;
                x--;
            }
            y++;
            SetPixel(hdc,x,y,c);
        }
    }
}
void DDA_Line(HDC hdc, vector<Point>p, COLORREF c) {
    int dx=p[1].x-p[0].x;
    int dy=p[1].y-p[0].y;
    SetPixel(hdc,p[0].x,p[0].y,c);
    if(abs(dx)>=abs(dy)){
        double m= (double)dy/dx;
        double x,y;
        if(p[0].x>p[1].x){
            x=p[1].x;
            y=p[1].y;
            while(x<p[0].x){
                x++;
                y+=m;
                SetPixel(hdc,x,Round(y),c);
            }
        }else{
            x=p[0].x;
            y=p[0].y;
            while(x<p[1].x){
                x++;
                y+=m;
                SetPixel(hdc,x,Round(y),c);
            }
        }
    }else{
        double mi= (double)dx/dy;
        double x,y;
        if(p[0].y>p[1].y){
            x=p[1].x;
            y=p[1].y;
            while(y<p[0].y){
                x+=mi;
                y++;
                SetPixel(hdc,Round(x),y,c);
            }
        }else{
            x=p[0].x;
            y=p[0].y;
            while(y<p[1].y){
                x+=mi;
                y++;
                SetPixel(hdc,Round(x),y,c);
            }
        }
    }
}

