#pragma once
#include "Point.h"

class Line : public AppObject
{

public:
	Point pt[2];
	int dragPoint = -1;
	int hoverPoint = -1;
	
	Line() { _type = Type::Line; }

	virtual bool onMouseEvent(const MouseEvent& ev) override;

	void onCreate(const MouseEvent& ev);

	void draw(HDC hdc_) const override {
		MoveToEx(hdc_, pt[0].x, pt[0].y, nullptr);
		LineTo  (hdc_, pt[1].x, pt[1].y);
		
		assert(hoverPoint < 2);
		if (hoverPoint >= 0 && hoverPoint < 2) { 
			pt[hoverPoint].draw(hdc_, 6); 
		}
		
		
	}

	


	
	
};

