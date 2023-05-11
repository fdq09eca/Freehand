#include "Crosshair.h"
#include "App.h"


int Crosshair::maxX() const { return getClientWidth(App::Instance()->hWnd()); }
int Crosshair::maxY() const { return getClientHeight(App::Instance()->hWnd()); }


void Crosshair::updateHline(Point mPos) {
	hLine.pt[0] = POINT{ mPos.x, 0     };
	hLine.pt[1] = POINT{ mPos.x, maxY()};
}

void Crosshair::updateVline(Point mPos) {
	vLine.pt[0] = POINT{ 0     , mPos.y };
	vLine.pt[1] = POINT{ maxX(), mPos.y};
}

bool Crosshair::onMouseEvent(const MouseEvent& ev) {

	if (ev.isMove()) {
		updateVline(ev.pos);
		updateHline(ev.pos);
		return true;
	}
	return false;
}

void Crosshair::draw(HDC hdc_) const {
	Line::drawLine(hdc_, vLine.pt[0], vLine.pt[1], App::Instance()->dashRedPen);
	Line::drawLine(hdc_, hLine.pt[0], hLine.pt[1], App::Instance()->dashRedPen);
}
