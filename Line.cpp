#include "Line.h"
#include "App.h"

bool Line::onMouseEvent(const MouseEvent& ev) {

	if (ev.isUp() && ev.isLButton()) {
		if (dragPoint >= 0 && dragPoint < 2) {
			pt[dragPoint] = ev.pos;
			setDragPoint(-1);
			App::Instance()->clearCaptureObject();
			return true;
		}
	}

	else if (ev.isDown() && ev.isLButton()) {
		if (updateHoverPoint(ev, pt, 2)) {
			App::Instance()->setCaptureObject(this);
			setDragPoint(hoverPoint);
			return true;
		}
	}

	else if (ev.isMove()) {

		if (dragPoint >= 0 && dragPoint < 2) {
			pt[dragPoint] = ev.pos;
			return true;
		}

		bool isUpdated = updateHoverPoint(ev, pt, 2);
		return isUpdated;
	}
	return false;
}

void Line::onCreate(const MouseEvent& ev) {
	App::Instance()->setCaptureObject(this);
	pt[0] = ev.pos;
	pt[1] = ev.pos;
	setDragPoint(1);
}

void Line::draw(HDC hdc_) const {
	
	
	MoveToEx(hdc_, pt[0].x, pt[0].y, nullptr);
	LineTo(hdc_, pt[1].x, pt[1].y);
	
	SelectObject(hdc_, oldPen);
	
	
	assert(hoverPoint < 2);
	if (hoverPoint >= 0 && hoverPoint < 2) {
		pt[hoverPoint].draw(hdc_, 6);
	}
}

bool Line::updateHoverPoint(const MouseEvent ev, const Point* points, int nPoints) {
	assert(points != nullptr);

	clearHoverPoint();
	for (int i = 0; i < nPoints; i++) {
		if (points[i].inRange(ev.pos, 3)) {
			hoverPoint = i;
			return true;
		}
	}

	return false;

}

Point Line::lerp(int t) const {
	assert(t >= 0 && t <= 1);
	return pt[0] * (1 - t) + pt[1] * t;
}

void Line::drawDash(HDC hdc_) const {
	auto oldPen = SelectObject(hdc_, App::Instance()->dashPen);
	draw(hdc_);
	SelectObject(hdc_, oldPen);
}
