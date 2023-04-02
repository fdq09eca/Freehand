#pragma once
#include "Point.h"

class Line : public AppObject
{

public:
	Point pt[2];
	int dragPoint = -1;
	int hoverPoint = -1;
	
	Line() { _type = Type::Line; }

	virtual bool onMouseEvent(const MouseEvent& ev) override {
		
		
		if (ev.isUp() && ev.isLButton()) {
			dragPoint = -1;
			pt[1] = ev.pos;
			return true;
		} 
		
		else if (ev.isMove()) {

			if (dragPoint >= 0 && dragPoint < 2 ) {
				pt[dragPoint] = ev.pos;
				return true;
			}	


			for (int i = 0; i < 2; i++) {
				hoverPoint = -1;
				if (pt[i].inRange(ev.pos, 3)) {
					// isHover
					hoverPoint = i;
					return true;
				}
			}
		}
		return false;
	}

	void onMouseLeftBtnDown(const MouseEvent& ev) {
		pt[0] = ev.pos;
		pt[1] = ev.pos;
		dragPoint = 1;
	}

	void draw(HDC hdc_) const override {
		MoveToEx(hdc_, pt[0].x, pt[0].y, nullptr);
		LineTo  (hdc_, pt[1].x, pt[1].y);
		
		assert(hoverPoint < 2);
		if (hoverPoint >= 0 && hoverPoint < 2) { 
			pt[hoverPoint].draw(hdc_, 6); 
		}
		
		
	}

	


	
	
};

