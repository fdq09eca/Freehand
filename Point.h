#pragma once
#include "AppObject.h"
class Point {

public:
	int x = 0;
	int y = 0;
	
	Point(int x_ = 0, int y_ = 0) :x(x_), y(y_) { }
	
	Point(const POINT& p) { //implicit convert
		x = p.x;
		y = p.y;
	}

	POINT asPOINT() const { return POINT{ x, y }; }
	operator POINT () const { return asPOINT(); }
	
	void operator=(const POINT& p) { *this = Point(p); }
	
	Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
	Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
	Point operator*(const Point& p) const { return Point(x * p.x, y * p.y); }
	Point operator/(const Point& p) const { return Point(x / p.x, y / p.y); }

	void operator+=(const Point& p) { x += p.x; y += p.y; }
	void operator-=(const Point& p) { x -= p.x; y -= p.y; }
	void operator*=(const Point& p) { x *= p.x; y *= p.y; }
	void operator/=(const Point& p) { x /= p.x; y /= p.y; }

	bool operator!=(const Point& p) const { return p.x == x || p.y == y; }
	bool operator==(const Point& p) const { return !operator!=(p);		 }

	bool inRange(const Point& p, int range) const {
		auto d = p - *this;
		return abs(d.x) <= range && abs(d.y) <= range;
	}

	void draw(HDC hdc_, int size) const {
		int s = size / 2;
		Rectangle(hdc_, x - s, y - s, x + s, y + s);
	}

};

