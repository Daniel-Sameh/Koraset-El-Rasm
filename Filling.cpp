void FloodFill(HDC hdc, Point p1, COLORREF bc, COLORREF fc) {
     COLORREF c = GetPixel(hdc, p1.x, p1.y);
     if (c == bc || c == fc) {
         return;
     }
     SetPixel(hdc, p1.x, p1.y, fc);
     FloodFill(hdc, Point(p1.x + 1, p1.y), bc, fc);
     FloodFill(hdc, Point(p1.x - 1, p1.y), bc, fc);
     FloodFill(hdc, Point(p1.x, p1.y + 1), bc, fc);
     FloodFill(hdc, Point(p1.x, p1.y - 1), bc, fc);
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
     for (double t1 = 0; t1 <= 1; t1 += 0.01) {
         for (double t2 = 0; t2 <= 1 - t1; t2 += 0.01) {
             Point p = p1 * t1 + p2 * t2 + p3 * (1 - t1 - t2);
             SetPixel(hdc, p.x, p.y, c);
         }
     }
}