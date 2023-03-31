#pragma once
#include "Util.h"

class Point : public AppObject{
	int _size = 0;
	COLORREF _color = RGB(0, 0, 0);
public:

	Point(const Mouse& mouse_, int size_, COLORREF color_) : AppObject(mouse_), _size(size_), _color(color_)
	{
		
	}

	void draw(HDC hdc_) const override {	
		drawHitBox(hdc_);
		SetPixel(hdc_, _pos.x, _pos.y, _color);
	}

	RECT hitBox() const override {
		return RECT{ _pos.x - _size, _pos.y - _size, _pos.x + _size, _pos.y + _size};
	}


	void setSize(int size_) { _size = size_; }

	


};

