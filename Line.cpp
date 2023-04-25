#include "Line.h"

bool Line::onMouseEvent(const MouseEvent& ev, const MouseButton& buttonState) {

	if (ev.isUp() && ev.isLButton()) {
		if (dragPoint >= 0 && dragPoint < 2) {
			pt[dragPoint] = ev.pos;
			dragPoint = -1;
			hoverPoint = -1;
			return true;
		}
	}

	else if (ev.isDown() && ev.isLButton()) {
		if (hoverPoint >= 0 && hoverPoint < 2) {
			dragPoint = hoverPoint;
			return true;
		}
	}

	else if (ev.isMove()) {

		if (dragPoint >= 0 && dragPoint < 2) {
			pt[dragPoint] = ev.pos;
			return true;
		}
		
		//dragPoint = -1; //should i ?
		hoverPoint = -1;
		for (int i = 0; i < 2; i++) {
			if (pt[i].inRange(ev.pos, 3)) {
				// isHover
				hoverPoint = i;
				return true;
			}
		}
	}
	return false;
}

void Line::onCreate(const MouseEvent& ev) {
	pt[0] = ev.pos;
	pt[1] = ev.pos;
	dragPoint = 1;
}
