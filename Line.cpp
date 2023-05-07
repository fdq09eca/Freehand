#include "Line.h"
#include "App.h"

bool Line::onMouseEvent(const MouseEvent& ev) {
	static Point _lastMousePos;
	
	if (ev.isUp() && ev.isLButton()) {
		if (dragPoint >= 0 && dragPoint < 2) {
			setDragPoint(-1);
			App::Instance()->clearCaptureObject();
			return true;
		}

		if (isDragLine) {
			App::Instance()->clearCaptureObject();
			setDragLine(false);
			return true;
		}
	}

	else if (ev.isDown() && ev.isLButton()) {
		if (updateHoverPoint(ev, pt, 2)) {
			App::Instance()->setCaptureObject(this);
			setDragPoint(hoverPoint);
			return true;
		}
		if (updateHoverLine(ev, 10)) {
			App::Instance()->setCaptureObject(this);
			setDragLine(true);
			_lastMousePos = ev.pos;
			return true;

		}
	}

	else if (ev.isMove()) {

		if (dragPoint >= 0 && dragPoint < 2) {
			pt[dragPoint] = ev.pos;
			return true;
		}

		if (isDragLine) {
			Point v = Point(ev.pos) - _lastMousePos;
			for (auto& p : pt) {
				p += v;
			}
			_lastMousePos = ev.pos;
			return true;
		}

		bool isUpdated = false;

		isUpdated = updateHoverLine(ev, 10);
		if (isUpdated) return true;
		
		isUpdated = updateHoverPoint(ev, pt, 2);
		if (isUpdated) return true;


		
		return false;
	}
	return false;
}

bool Line::updateHoverLine(const MouseEvent& ev, int distance = 10) {
	ishoverLine = false;
	// bug start here
	if (hoverPoint != -1) {
		return false; 
	}
	
	if (pt[0].inRange(ev.pos, 3) || pt[1].inRange(ev.pos, 3)) {
		return false; 
	}


	/*RECT r{ pt[0].x , pt[0].y, pt[1].x, pt[1].y };
	if (!PtInRect(&r, ev.pos)) {
		return false; 
	}*/
	// bug end here
	
	Vector2D v = pt[1] - pt[0];
	Vector2D m = Point(ev.pos) - pt[0];
	Vector2D u = v.unitVector();
	Vector2D projVector = pt[0].asVector2D() + m.project(v);
	double d = projVector.distance(Point(ev.pos));
	
	if (d < 0 || d > distance) { 
		return false; 
	}
	
	ishoverLine = true;
	return true;
}

void Line::onCreate(const MouseEvent& ev) {
	App::Instance()->setCaptureObject(this);
	pt[0] = ev.pos;
	pt[1] = ev.pos;
	setDragPoint(1);
}

void Line::draw(HDC hdc_) const {

	if (ishoverLine) {
		Line::drawLine(hdc_, pt[0], pt[1], App::Instance()->solidRedPen);
	}
	else {
		Line::drawLine(hdc_, pt[0], pt[1], GetStockPen(DC_PEN));
	}
	
	//MoveToEx(hdc_, pt[0].x, pt[0].y, nullptr);
	//LineTo(hdc_, pt[1].x, pt[1].y);

	
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
	
	f.put(':');
	
	for (auto& p : pt) {
		p.save(f);
	}

	writeInt(f, hoverPoint);
	writeInt(f, dragPoint);
	f.put('\n');
}

void Line::load(std::ifstream& f)
{
	auto p = std::make_unique<Line>();
	Line& line = *p;

	for (auto& c : line.pt) {
		Point::load(f, c);
	}

	readInt(f, line.hoverPoint);
	readInt(f, line.dragPoint);

	App::Instance()->objList.emplace_back(std::move(p));

	printf("[Line] p0(% d, % d), p1(% d, % d), h:% d, d : % d\n",
		line.pt[0].x, line.pt[0].y,
		line.pt[1].x, line.pt[1].y,
		line.hoverPoint, line.dragPoint
	);
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

