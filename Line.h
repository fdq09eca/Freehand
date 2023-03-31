#pragma once
#include "Point.h"

class Line : public AppObject
{

public:
	Point pt[2];
	int dragPoint = -1;
	
	Line() { _type = Type::Line; }

	virtual bool onMouseEvent(const MouseEvent& ev) override {
		
		if (ev.isUp() && ev.isLButton()) {
			dragPoint = -1;
			pt[1].pos = ev.pos;
			return true;
		} 
		
		else if (ev.isMove()) {
			if (dragPoint >= 0 && dragPoint < 2 ) {
				pt[dragPoint].pos = ev.pos;
				return true;
			}	
		}
		
		return false;
	}

	void createByMouse(const MouseEvent& ev) {
		pt[0].pos = ev.pos;
		pt[1].pos = ev.pos;
		dragPoint = 1;
	}

	void draw(HDC hdc_) const override {
		MoveToEx(hdc_, pt[0].pos.x, pt[0].pos.y, nullptr);
		LineTo  (hdc_, pt[1].pos.x, pt[1].pos.y);
		
		pt[0].draw(hdc_);
		pt[1].draw(hdc_);
	}

	


	
	
};

