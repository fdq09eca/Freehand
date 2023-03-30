#pragma once
#include "Util.h"

class Point : public AppObject{
	int _size = 0;
	COLORREF _color = RGB(0, 0, 0);
public:

	Point(const Mouse& mouse_, int size_, COLORREF color_) : AppObject(mouse_), _size(size_), _color(color_)
	{
		
		RECT hitBox{ _pos.x - size_, _pos.y - size_, _pos.x + size_, _pos.y + size_ };
		setHitBox(hitBox);
		
	}

	void draw(HDC hdc_) const override {
		if (_isTemp) return;
		drawHitBox(hdc_);
		SetPixel(hdc_, _pos.x, _pos.y, _color);
	}


	void setSize(int size_) { _size = size_; }

	


};

