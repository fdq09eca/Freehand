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

	
	assert(hoverPoint < 2);
	if (hoverPoint >= 0 && hoverPoint < 2) {
		pt[hoverPoint].draw(hdc_, 6, true);
	}
}



void Line::drawLine(HDC hdc_, const Point& pt0, const Point& pt1, HPEN hPen) {
	auto oldPen = SelectObject(hdc_, hPen);

	MoveToEx(hdc_, pt0.x, pt0.y, nullptr);
	LineTo(hdc_, pt1.x, pt1.y);

	SelectObject(hdc_, oldPen);
}

void Line::save(std::ofstream& f) {
	writeString(f, typeAsString());
	
	for (auto& p : pt) {
		p.save(f);
	}

	writeInt(f, hoverPoint);
	writeInt(f, dragPoint);
	f.put('\n');
}

void Line::load(std::ifstream& f, Line& line)
{
	char c;
	const int n = strlen(line.typeAsString());
	
	for (int i = 0; i < n; i++) {
		f.get(c); //skip typeAsString
		printf("%c", c);
	}
	
	for (auto& p : line.pt) {
		Point::load(f, p);
	}

	readInt(f, line.hoverPoint);
	readInt(f, line.dragPoint);
	return;
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



Point Line::lerp(const Point& p0, const Point& p1, float t)
{
	assert(t >= 0.0f && t <= 1.0f);
	return p0 * (1.0f - t) + p1 * t;
}

