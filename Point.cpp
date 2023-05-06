#include "Point.h"
#include "App.h"

Point::Point(const POINT& p) { //implicit convert
	x = p.x;
	y = p.y;
}

bool Point::inRange(const Point& p, int range) const {
	auto d = p - *this;
	return abs(d.x) <= range && abs(d.y) <= range;
}

void Point::draw(HDC hdc_, int size, bool isHover) const
{
	
	if (isHover) {
		draw(hdc_, size, App::Instance()->solidBlackPen, App::Instance()->solidRedBrush);
	}
	else {
		draw(hdc_, size, App::Instance()->solidBlackPen, (HBRUSH) GetStockObject(NULL_BRUSH));
	}
}

void Point::draw(HDC hdc_, int size, HPEN hpen, HBRUSH hBrush) const {
	int s = size / 2;
	auto oldPen = SelectPen(hdc_, hpen);
	auto oldBrush = SelectBrush(hdc_, hBrush);

	Rectangle(hdc_, x - s, y - s, x + s, y + s);
	SelectPen(hdc_, oldPen);
	SelectPen(hdc_, oldBrush);
}

void Point::save(std::ofstream& f)  { 
	writeInt(f, x); 
	writeInt(f, y); 
}

void Point::load(std::ifstream& f, Point& p)
{
	readInt(f, p.x);
	readInt(f, p.y);
}

