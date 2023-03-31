#pragma once
#include "Point.h"

class Line : public AppObject
{
	Point _pt0;
	Point _pt1;
	
	Line() = delete;
public:
	Line(const Mouse& mouse_) : AppObject(mouse_), _pt0(mouse_), _pt1(mouse_)
	{
		
	}

	POINT pos() const override { return Point::midPoint(_pt0, _pt1); }
	void setPos(){}
	
	void onDrag() override {
		_pt1.setPos(_mouse);
		
	}

	RECT hitBox() const {
		RECT r;
		return r;
	}

	void draw(HDC hdc) const override{

	}

	static void drawLine(HDC hdc, const Point& pt0_, const Point& pt1_) {
		MoveToEx(hdc, pt0_.x(), pt0_.y(), nullptr);
		LineTo(hdc, pt1_.x(), pt1_.y());
	}
};

