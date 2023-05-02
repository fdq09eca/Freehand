#pragma once
#include "Util.h"

class Point {

public:
	int x = 0;
	int y = 0;
	
	Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) { }
	
	Point(const POINT& p);

	inline POINT asPOINT() const { return POINT{ x, y }; }
	
	inline operator POINT () const { return asPOINT(); }
	// operator POINT* () const { return &asPOINT(); } // does it work?
	
	
	inline void operator=(const POINT& p) { *this = Point(p); }
	
	inline Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
	inline Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
	inline Point operator*(const Point& p) const { return Point(x * p.x, y * p.y); }
	inline Point operator/(const Point& p) const { return Point(x / p.x, y / p.y); }

	inline void operator+=(const Point& p) { x += p.x; y += p.y; }
	inline void operator-=(const Point& p) { x -= p.x; y -= p.y; }
	inline void operator*=(const Point& p) { x *= p.x; y *= p.y; }
	inline void operator/=(const Point& p) { x /= p.x; y /= p.y; }

	inline Point operator*(int v) const { return Point(x * v, y * v); }
	inline Point operator/(int v) const { return Point(x / v, y / v); }

	inline void operator*=(int v) { x *= v; y *= v; }
	inline void operator/=(int v) { x /= v; y /= v; }

	

	inline bool operator!=(const Point& p) const { return p.x == x || p.y == y; }
	inline bool operator==(const Point& p) const { return !operator!=(p);		 }

	bool inRange(const Point& p, int range) const;

	void draw(HDC hdc_, int size) const;

};

