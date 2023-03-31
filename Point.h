#pragma once
#include "AppObject.h"

class Point : public AppObject {
	

public:
	int hitBoxsize = 6;
	POINT pos{0, 0};
	
	Point() { _type = Type::Point; };

	RECT hitBox() const  {
		return RECT{ pos.x - hitBoxsize, pos.y - hitBoxsize, pos.x + hitBoxsize, pos.y + hitBoxsize};
	}

	void draw(HDC hdc_) const override {
		RECT r = hitBox();
		COLORREF color = RGB(0, 0, 0);
		if (_isHovered) { 
			color = RGB(255, 0, 0);
		}

		SetPixel(hdc_, pos.x, pos.y, color);

	}


};

