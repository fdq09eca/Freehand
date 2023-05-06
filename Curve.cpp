#include "Curve.h"
#include "Line.h"
#include "App.h"

void Curve::onCreate(const MouseEvent& ev) {
	App::Instance()->setCaptureObject(this);
	createPoint = 0;
	hoverPoint = createPoint;
	pts[createPoint] = ev.pos;
	return;
}

bool Curve::updateHoverPoint(const MouseEvent ev, const Point* points, int nPoints) {
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

void Curve::onLeftBtnDrag(const MouseEvent& ev) {
	assert(dragPoint != -1);
	printf("[%s id %d] [dragging] dragPoint: %d\n", typeAsString(), id, dragPoint);
	setDragPoint(dragPoint);
	pts[dragPoint] = ev.pos;

	//snapping
	for (int i = 0; i < nPoints; i++) {
		if (i == dragPoint) 
			continue;
		
		if (pts[i].sanp(pts[dragPoint])) {
			printf("SNAP!");
		}
	}
}

void Curve::drawCurve(HDC hdc) const { // https://www.youtube.com/watch?v=pnYccz1Ha34
	assert(isCreated());
	
	Point prevPoint = pts[0];
	int n = 100;

	for (int v = 1; v <= n; v ++) {
		
		float t = static_cast<float>(v) / static_cast<float>(n);

		Point l0 = Line::lerp(pts[0], pts[1], t);
		Point l1 = Line::lerp(pts[1], pts[2], t);
		Point l2 = Line::lerp(pts[2], pts[3], t);

		Point q0 = Line::lerp(l0, l1, t);
		Point q1 = Line::lerp(l1, l2, t);

		Point c = Line::lerp(q0, q1, t);

		Line::drawLine(hdc, prevPoint, c, App::Instance()->solidBlackPen);
		prevPoint = c;
	
	}

	
}

void Curve::draw(HDC hdc) const {

		assert(createPoint >= 0);
		for (int i = 0; i < createPoint + 1; i++) {
			pts[i].draw(hdc, 6);

			if (i == nPoints - 1) break;

			if (i + 1 <= createPoint) {
				Line::drawLine(hdc, pts[i], pts[i + 1], App::Instance()->dashRedPen);
			}
		}
		if (isCreated()) {
			drawCurve(hdc);
		}

		if (hoverPoint >= 0 && hoverPoint < nPoints) {
			pts[hoverPoint].draw(hdc, 6, true);
		}
	}




bool Curve::onMouseEvent(const MouseEvent& ev) {
	if (ev.isLButton()) {
		if (ev.isUp()) {
			if (isCreated()) {
				App::Instance()->clearCaptureObject();
				clearHoverPoint();
				return true;
			}
			else {
				createPoint++;
				
				if (isCreated()) {
					App::Instance()->clearCaptureObject();
					clearHoverPoint();
					return true;
				}
				
				pts[createPoint] = ev.pos;
				hoverPoint++;
				return true;
			}
		}
		if (ev.isDown()) {
			if (isCreated()) {
				updateHoverPoint(ev, pts, nPoints);
				if (hoverPoint != -1) {
					App::Instance()->setCaptureObject(this);
					setDragPoint(hoverPoint);
					
					return true;
				}

			}
			else {
				
				return false;
			}
		}
	}
	else if (ev.isMove()) {
		if (isCreated()) {
			if (App::Instance()->mouseButtonState() == MouseButton::Left) {
				if (dragPoint == -1) { return false; }
				onLeftBtnDrag(ev);
				return true;
			}
			else {
				bool isUpdated = updateHoverPoint(ev, pts, nPoints);
				return isUpdated;
			}
		}
		else {
			pts[createPoint] = ev.pos;
			return true;
		}
	}


	return false;
}

void Curve::save(std::ofstream& f) {
	assert(_type == Type::Curve);
	writeString(f, typeAsString());

	f.put(':');
	
	for (auto& pt : pts) {
		pt.save(f); 
	}

	writeInt(f, hoverPoint);
	writeInt(f, dragPoint);
	writeInt(f, createPoint);
	f.put('\n');
}

void Curve::load(std::ifstream& f)
{
	auto p = std::make_unique<Curve>();
	Curve& curve = *p;

	for (auto& pt : curve.pts) {
		pt.load(f, pt);
	}


	readInt(f, curve.hoverPoint);
	readInt(f, curve.dragPoint);
	readInt(f, curve.createPoint);
	App::Instance()->objList.emplace_back(std::move(p));

	printf("[Curve]: (%d, %d), (%d, %d), (%d, %d), (%d, %d); h: %d, d: %d, c: %d\n",
		curve.pts[0].x, curve.pts[0].y,
		curve.pts[1].x, curve.pts[1].y,
		curve.pts[2].x, curve.pts[2].y,
		curve.pts[3].x, curve.pts[3].y,
		curve.hoverPoint, curve.dragPoint, curve.createPoint);
	
}


