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
	void setPos(){_pos = Point::midPoint(_pt0, _pt1);} // move whole line
	
	void onDrag() override {
		_pt1.setPos(_mouse);
	}

	RECT hitBox() const override {
		
		int left	= _pt0.x() < _pt1.x() ? _pt0.x() : _pt1.x();
		int right	= _pt0.x() < _pt1.x() ? _pt1.x() : _pt0.x();
		int top		= _pt0.y() < _pt1.y() ? _pt0.y() : _pt1.y();
		int bottom	= _pt0.y() < _pt1.y() ? _pt1.y() : _pt0.y();
		
		RECT r{ left, top, right, bottom };
		return r;
	}

	void draw(HDC hdc_) const override{
		drawHitBox(hdc_);
		MoveToEx(hdc_, _pt0.x(), _pt0.y(), nullptr);
		LineTo(hdc_, _pt1.x(), _pt1.y());
		drawDebugMessage(hdc_);
	}

	


	
	
};

