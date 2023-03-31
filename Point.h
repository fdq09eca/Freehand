#pragma once
#include "AppObject.h"

class Point : public AppObject {
	int _hitBoxsize = 6;
	COLORREF _color = RGB(0, 0, 0);
public:
	Point() = delete;
	Point(const Mouse& mouse_) : AppObject(mouse_) { };

	void draw(HDC hdc_) const override {	
		drawHitBox(hdc_);
		SetPixel(hdc_, _pos.x, _pos.y, _color);
	}

	RECT hitBox() const override {
		return RECT{ _pos.x - _hitBoxsize, _pos.y - _hitBoxsize, _pos.x + _hitBoxsize, _pos.y + _hitBoxsize};
	}

	int x() const { return _pos.x;}
	int y() const { return _pos.y;}

	static POINT midPoint(const Point& pt0, const Point& pt1)  {
		return POINT{ (pt0.x() + pt1.x()) / 2, (pt0.y() + pt1.y()) / 2};
	}
	
	void onDrag() override {
		setPos(_mouse);
	}


};

