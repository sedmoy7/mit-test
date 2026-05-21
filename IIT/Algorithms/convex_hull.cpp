#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Point
{
    int x, y;
};

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;             
    return (val > 0) ? 1 : 2; 
}

int dist(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

Point p0;

bool compare(Point p1, Point p2)
{
    int o = orientation(p0, p1, p2);
    if (o == 0)
        return dist(p0, p1) < dist(p0, p2);
    return (o == 2);
}

void convex_hull(std::vector<Point>& points, int n)
{
    if (n < 3) return;
	
	int min_y = points[0].y, min_x = points[0].x, min_idx = 0;
	for (int i = 1; i < n; i++)
	{
		if ((points[i].y < min_y) || (points[i].y == min_y && points[i].x < min_x))
		{
			min_y = points[i].y;
			min_x = points[i].x;
			min_idx = i;
		}
	}
	std::swap(points[0], points[min_idx]);
	p0 = points[0];

	std::sort(points.begin() + 1, points.end(), compare);

    std::vector<Point> hull;

    hull.push_back(points[0]);
	hull.push_back(points[1]);
	hull.push_back(points[2]);

	for (int i = 3; i < n; i++)
	{
		while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2)
		{
			hull.pop_back();
		}
		hull.push_back(points[i]);
	}

	if (orientation(hull[0], hull[1], hull[2]) != 2)
	{
		std::reverse(hull.begin() + 1, hull.end());
	}

    for (int i = 0; i < hull.size(); i++)
    {
        std::cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
    }  
}

int main()
{
    int n, x, y;
    Point temp;
    std::vector<Point> points;
    std::cout << "Enter number of points: ";
    std::cin >> n;
    points.resize(n);
    std::cout << "Enter points (x,y): ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> points[i].x >> points[i].y;
    }

    convex_hull(points, n);

    return 0;
}