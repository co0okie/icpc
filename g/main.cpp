#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}
};

// Cross product of (b - a) × (c - a)
// >0 for counter‐clockwise turn, <0 for clockwise, 0 for collinear
double ccw(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x)*(c.y - a.y)
         - (b.y - a.y)*(c.x - a.x);
}

// Find index of the point with minimal y (and minimal x to break ties)
size_t getMinYIndex(const std::vector<Point>& pts) {
    size_t minIdx = 0;
    for (size_t i = 1; i < pts.size(); ++i) {
        if (pts[i].y < pts[minIdx].y
         || (pts[i].y == pts[minIdx].y && pts[i].x < pts[minIdx].x))
        {
            minIdx = i;
        }
    }
    return minIdx;
}

// Compute the convex hull of pts (must have at least 3 points)
std::vector<Point> convexHull(std::vector<Point> pts) {
    if (pts.size() < 3) return pts;

    // 1) Find and move the min‐Y point to front
    size_t minIdx = getMinYIndex(pts);
    std::swap(pts[0], pts[minIdx]);
    Point ref = pts[0];

    // 2) Sort the rest by polar angle around ref
    std::sort(pts.begin() + 1, pts.end(),
        [&](const Point& b, const Point& c) {
            double cross = ccw(ref, b, c);
            if (cross == 0) {
                // collinear: closer one first
                double db = (b.x - ref.x)*(b.x - ref.x) + (b.y - ref.y)*(b.y - ref.y);
                double dc = (c.x - ref.x)*(c.x - ref.x) + (c.y - ref.y)*(c.y - ref.y);
                return db < dc;
            }
            return cross > 0;
        }
    );

    // 3) Graham scan
    std::deque<Point> st;
    st.push_back(pts[0]);
    st.push_back(pts[1]);

    for (size_t i = 2; i < pts.size(); ++i) {
        Point top = st.back();
        st.pop_back();
        // pop until we make a ccw turn
        while (!st.empty() && ccw(st.back(), top, pts[i]) <= 0) {
            top = st.back();
            st.pop_back();
        }
        st.push_back(top);
        st.push_back(pts[i]);
    }

    // 4) final check to include last point if non‐collinear
    Point last = st.back(); st.pop_back();
    if (!st.empty() && ccw(st.back(), last, ref) > 0) {
        st.push_back(last);
    }

    return std::vector<Point>(st.begin(), st.end());
}

int main() {
    std::vector<Point> points = {
        {2, 2},
        {-10, 10},
        {1, 1},
        {10, -10},
        {-1, 5},
        {10, 10},
        {3, 3},
        {1, 5},
        {-10, -10},
        // you can add more test points here
    };

    auto hull = convexHull(points);

    std::cout << "Convex Hull (" << hull.size() << " points):\n";
    for (auto& p : hull) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }
    return 0;
}
