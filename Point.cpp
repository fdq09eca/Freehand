#include "Point.h"

Point::Point(const POINT& p) { //implicit convert
	x = p.x;
	y = p.y;
}

bool Point::inRange(const Point& p, int range) const {
	auto d = p - *this;
	return abs(d.x) <= range && abs(d.y) <= range;
}

void Point::draw(HDC hdc_, int size) const {
	int s = size / 2;
	Rectangle(hdc_, x - s, y - s, x + s, y + s);
	
}
