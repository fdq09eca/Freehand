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

inline void Curve::onLeftBtnDrag(const MouseEvent& ev) {
	assert(dragPoint != -1);
	printf("[%s id %d] [dragging] dragPoint: %d\n", typeAsString(), id, dragPoint);
}

inline void Curve::drawCurve(HDC hdc) const {
	printf("drawCurve();\n");
}

void Curve::draw(HDC hdc) const {
	

		assert(createPoint >= 0);
		for (int i = 0; i < createPoint + 1; i++) {
			pts[i].draw(hdc, 6);

			if (i == nPoints - 1) break;

			if (i + 1 < createPoint + 1) {
				Line::drawDash(hdc, pts[i], pts[i + 1]);
			}
		}
		if (isCreated()) {
			drawCurve(hdc);
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
				printf("[%s id %d] [LBtnDown] CreatePoint Current [%d] Next [%d]\n", typeAsString(), id, createPoint, createPoint + 1);
				printf("[%s id %d] [LBtnDown] CreatePoint Current [%d] pos(%d, %d)\n", typeAsString(), id, createPoint, pts[createPoint].x, pts[createPoint].y);
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
				
				return true;
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
