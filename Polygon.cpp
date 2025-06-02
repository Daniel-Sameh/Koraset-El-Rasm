extern COLORREF FColor;

void Draw_Polygon(HDC hdc, vector<Point> v, COLORREF c) {
    Point p1 = v.back();
    for (int i = 0; i < v.size(); ++i) {
        clippingPoints.emplace_back(p1,v[i], c);
        DDA_Line(hdc, {p1, v[i]}, c);
        p1 = v[i];
    }
    clippingPolygons.push_back(v);
}

const int N = 800;

typedef struct {
    int xLeft, xRight;
} EdgeTableConvex[N];

const int inf = 1e9;

void initEdgeTableConvex(EdgeTableConvex tbl) {
    for (int i = 0; i < N; ++i) {
        tbl[i].xLeft = inf;
        tbl[i].xRight = -inf;
    }
}

void EdgeToTableConvex(Point p1, Point p2, EdgeTableConvex tbl) {
    if (p1.y == p2.y)
        return;
    else if (p1.y > p2.y)
        swap(p1, p2);
    int y = p1.y;
    double x = p1.x;
    double m = (double) (p2.x - p1.x) / (p2.y - p1.y);
    while (y < p2.y) {
        if (x < tbl[y].xLeft)
            tbl[y].xLeft = (int) ceil(x);
        if (x > tbl[y].xRight)
            tbl[y].xRight = (int) floor(x);
        x += m;
        y++;
    }
}

void DrawPolygon_ConvexFill(HDC hdc, vector<Point> &v, COLORREF c) {

    EdgeTableConvex tbl;
    initEdgeTableConvex(tbl);
    Point p1 = v.back();

    for (int i = 0; i < v.size(); ++i) {
        EdgeToTableConvex(p1, v[i], tbl);
        p1 = v[i];
    }

    for (int i = 0; i < N; ++i) {
        if (tbl[i].xLeft < tbl[i].xRight) {
            vector<Point> p = {{(double) tbl[i].xLeft, (double) i}, {(double) tbl[i].xRight, (double) i}};
            clippingPoints.emplace_back(p[0], p[1], FColor);
            DDA_Line(hdc, p, FColor);
        }
    }
    Draw_Polygon(hdc, v, c);
    clippingPolygons.push_back(v);
}

struct Node {
    double x;
    double m;
    int y;

    Node(double x, double m, int y) : x(x), m(m), y(y) {}

    bool operator< (Node const n1) const {
        return this->x < n1.x;
    }
};

typedef struct {
    list<Node> lst;
} EdgeTable[N];

void EdgeToTable(Point p1, Point p2, EdgeTable tbl) {
    if (p1.y == p2.y)
        return;
    else if (p1.y > p2.y)
        swap(p1, p2);
    auto [x1, y1] = p1;
    auto [x2, y2] = p2;
    double m = (double) (x2 - x1) / (y2 - y1);
    tbl[(int) y1].lst.emplace_back(x1, m, y2);
}

void DrawLines(HDC hdc, list<Node> lst, COLORREF c, int y) {
    while (!lst.empty()) {
        Node node1 = lst.front();
        lst.pop_front();
        Node node2 = lst.front();
        lst.pop_front();
        vector<Point> p = {{node1.x, (double) y}, {node2.x, (double) y}};
        clippingPoints.emplace_back(p[0],p[1], c);
        DDA_Line(hdc, p, c);
    }
}

void DrawPolygon_GeneralFill(HDC hdc, vector<Point> &v, COLORREF c) {
    Point p = v.back();
    // initializing the edge table
    EdgeTable tbl;
    for (int i = 0; i < v.size(); ++i) {
        EdgeToTable(p, v[i], tbl);
        p = v[i];
    }

    int y = 0;
    while (tbl[y].lst.empty())
        y++;

    list<Node> active = tbl[y].lst;
    while (!active.empty()) {
        // sort
        active.sort();
        // draw
        DrawLines(hdc, active, FColor, y);
        y++;
        // delete
        erase_if(active, [y](Node node) {return node.y == y;});
        // update
        for (Node &node : active) {
            node.x += node.m;
        }
        // insert
        for (Node node : tbl[y].lst) {
            active.push_back(node);
        }
    }
    Draw_Polygon(hdc, v, c);
    clippingPolygons.push_back(v);
}