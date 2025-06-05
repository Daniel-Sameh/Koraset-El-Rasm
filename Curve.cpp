using namespace std;
void DrawQuadraticCurve(HDC hdc, vector<Point> p, COLORREF c, int num) {
    int matrix[3][3] = {{2, -4, 2}, {-3, 4, -1}, {1, 0, 0}};
    double step = 1.0 / num;
    for (double t = 0; t <= 1; t += step) {
        int x, y;
        int *vals[2] = {&x, &y};
        for (int var = 0; var < 2; ++var) {
            double val = t * t;
            double temp = 0;
            for (int i = 0; i < 3; ++i) {
                int a[3] = {}; // alpha, beta, gamma
                for (int j = 0; j < 3; ++j) {
                    int par = (var == 0) ? p[j].x : p[j].y;
                    a[i] += matrix[i][j] * par;
                }
                temp += a[i] * val;
                if (t > 0)
                    val /= t;
            }
            *vals[var] = Round(temp);
        }
        SetPixel(hdc, x, y, c);
    }
}
///////

void RecursiveMidPointBezier(HDC hdc, vector<Point> p, COLORREF c) {
    if (distance(p.front(), p.back()) <= 1)
        return;
    vector<vector<Point>> points;
    points.push_back(p);
    for (int i = 0; i < p.size() - 1; ++i) {
        vector<Point> v;
        int n = (int) points.back().size();
        for (int j = 0; j < n - 1; ++j) {
            v.push_back((points.back()[j] + points.back()[j + 1]) * 0.5); // q1 = 0.5 * (p1 + p2)
        }
        points.push_back(v);
    }
    Point mid = points.back().back();
    SetPixel(hdc, Round(mid.x), Round(mid.y), c);
    vector<Point> v;
    for (auto arr : points) {
        v.push_back(arr.front());
    }
    RecursiveMidPointBezier(hdc, v, c);
    v.clear();
    for (int i = (int) points.size() - 1; i >= 0; --i) {
        v.push_back(points[i].back());
    }
    RecursiveMidPointBezier(hdc, v, c);
}
////////////////////////////////////////////////////////////////////////////////
Point RecBezier(vector<Point> &arr, int l, int r, double t) {
    if (l == r) {
        return arr[l];
    }
    return (RecBezier(arr, l, r - 1, t)*(1 - t)  ) + ( RecBezier(arr, l + 1, r, t)*t);
}

void DrawBezierCurve(HDC hdc, vector<Point> &arr, COLORREF c, int num) {
    double step = (double) 1.0 / num;
    for (double t = 0; t < 1; t += step) {
        Point p = RecBezier(arr, 0, arr.size() - 1, t);
        SetPixel(hdc, Round(p.x), Round(p.y), c);
    }
}
///////////////////////////////////////////////////////////////////////////////////
void DrawHermiteCurve(HDC hdc, Point* arr, COLORREF c, int count) {
    int mat[][4] = {{2, 1, -2, 1}, {-3, -2, 3, -1}, {0, 1, 0, 0}, {1, 0, 0, 0}};
    double step = 1.0 / count;
    for (double t = 0; t < 1; t += step) {
        Point p;
        for (int i = 0; i < 2; ++i) {
            int par[4];
            double sum = 0;
            double current = t * t * t;
            for (int j = 0; j < 4; ++j) {
                par[j] = 0;
                for (int k = 0; k < 4; ++k) {
                    if (i == 0) {
                        par[j] += mat[j][k] * (int) arr[k].x;
                    }
                    else {
                        par[j] += mat[j][k] * (int) arr[k].y;
                    }
                }
                sum += par[j] * current;
                current /= t;
            }
            if (i == 0)
                p.x = sum;
            else
                p.y = sum;
        }
        SetPixel(hdc, Round(p.x), Round(p.y), c);
    }
}

void DrawCardinalSpline(HDC hdc,vector<Point> controlPoints,COLORREF color,int count, double c) {
    std::vector<Point> slopes(controlPoints.size());
    for (size_t i = 1; i < controlPoints.size()-1 ; ++i) {

        slopes[i] = (controlPoints[i + 1] - controlPoints[i-1 ]) * c;
    }
    for (int i = 1; i < controlPoints.size() - 1; ++i) {
        Point arr[] = {controlPoints[i], slopes[i],controlPoints[i+1], slopes[i+1]};
        DrawHermiteCurve(hdc, arr, color,count);
    }
    Point arr[]={controlPoints[0] , slopes[1] ,controlPoints[1] , slopes[1]};
    DrawHermiteCurve(hdc,  arr, color,count);

}

void DrawHermiteCurve(HDC hdc, Point* arr, COLORREF baseColor, COLORREF highlightColor, int count) {
    static int mat[][4] = {{2, 1, -2, 1}, {-3, -2, 3, -1}, {0, 1, 0, 0}, {1, 0, 0, 0}};
    double step = 1.0 / count;
    for (double t = 0; t < 1; t += step) {
        Point p;
        for (int i = 0; i < 2; ++i) {
            int par[4];
            double sum = 0;
            double current = t * t * t;
            for (int j = 0; j < 4; ++j) {
                par[j] = 0;
                for (int k = 0; k < 4; ++k) {
                    if (i == 0) {
                        par[j] += mat[j][k] * (int)arr[k].x;
                    } else {
                        par[j] += mat[j][k] * (int)arr[k].y;
                    }
                }
                sum += par[j] * current;
                current /= t;
            }
            if (i == 0)
                p.x = sum;
            else
                p.y = sum;
        }

        int rBase = GetRValue(baseColor);
        int gBase = GetGValue(baseColor);
        int bBase = GetBValue(baseColor);

        int rHighlight = GetRValue(highlightColor);
        int gHighlight = GetGValue(highlightColor);
        int bHighlight = GetBValue(highlightColor);

        int r = rBase + t * (rHighlight - rBase);
        int g = gBase + t * (gHighlight - gBase);
        int b = bBase + t * (bHighlight - bBase);

        COLORREF shadedColor = RGB(r, g, b);

        SetPixel(hdc, Round(p.x), Round(p.y), shadedColor);
    }
}