#include "Rect.h"
#include "App.h"


void Rect::onCreate(const MouseEvent& ev) {
	for (auto& pt : corners) {
		pt = ev.pos;
	}
	App::Instance()->setCaptureObject(this);
	setDragAndHoverPoint(Corner::RIGHT_BOTTOM);
}

void Rect::updateCorner(Corner c, const POINT* pos) {
	if (pos) {
		corners[static_cast<int>(c)] = *pos;
		return;
	}


	switch (c)
	{

	case Rect::Corner::LEFT_TOP: {
		leftTop().x = leftBottom().x;
		leftTop().y = rightTop().y;
		return;
	}

	case Rect::Corner::LEFT_BOTTOM: {
		leftBottom().x = leftTop().x;
		leftBottom().y = rightBottom().y;
		return;
	}
	case Rect::Corner::RIGHT_TOP: {
		rightTop().x = rightBottom().x;
		rightTop().y = leftTop().y;
		return;
	}
	case Rect::Corner::RIGHT_BOTTOM: {
		rightBottom().x = rightTop().x;
		rightBottom().y = leftBottom().y;
		return;
	}

	default: {
		assert("corner update failed.");
		return;
	}

	}
}

bool Rect::onMouseEvent(const MouseEvent& ev) {

	if (ev.isLButton()) {
		if (ev.isUp()) {
			setDragAndHoverPoint(Corner::NONE);
			App::Instance()->clearCaptureObject();
			//printf("rect id : %d, b::LeftIsUp: dragPoint %d hoverPoint %d\n", id, dragPoint, hoverPoint);
			return true;
		}

		if (ev.isDown()) {
			updateHoverPoint(ev);
			if (hoverPoint != Corner::NONE) {
				App::Instance()->setCaptureObject(this);
				dragPoint = hoverPoint;
				//printf("rect id: %d, b::LeftIsDown: dragPoint %d hoverPoint %d\n", id, dragPoint, hoverPoint);
				return true;
			}
			return false;
		}
	}

	else if (ev.isMove()) {

		if (App::Instance()->mouseButtonState() == MouseButton::Left) {
			//printf("rect id:%d: b::MoveAndLeftIsDown: dragPoint %d hoverPoint %d\n", id, dragPoint, hoverPoint); //bug here, create 2 rect and drag to reproduce.
			switch (dragPoint) {
			
			default: {
				return false;
			}

			case Corner::NONE: {
				return false;
			}


			case Corner::LEFT_TOP: {
				updateCorner(Corner::LEFT_TOP, &ev.pos);
				updateCorner(Corner::RIGHT_TOP);
				updateCorner(Corner::LEFT_BOTTOM);
				return true;
			}

			case Corner::LEFT_BOTTOM: {
				updateCorner(Corner::LEFT_BOTTOM, &ev.pos);
				updateCorner(Corner::LEFT_TOP);
				updateCorner(Corner::RIGHT_BOTTOM);
				return true;
			}


			case Corner::RIGHT_TOP: {
				updateCorner(Corner::RIGHT_TOP, &ev.pos);
				updateCorner(Corner::LEFT_TOP);
				updateCorner(Corner::RIGHT_BOTTOM);
				return true;
			}


			case Corner::RIGHT_BOTTOM: {
				updateCorner(Corner::RIGHT_BOTTOM, &ev.pos);
				updateCorner(Corner::LEFT_BOTTOM);
				updateCorner(Corner::RIGHT_TOP);
				return true;
			}
			}
		}
		else {
			return updateHoverPoint(ev);
		}
	}


	return false;
}

void Rect::setDragAndHoverPoint(Corner c) {
	dragPoint = c;
	hoverPoint = c;
}

void Rect::draw(HDC hdc) const {
	Point lt = leftTop();

	Point rb = rightBottom();

	

	SelectBrush(hdc, GetStockBrush(NULL_BRUSH)); // color does not work.

	::Rectangle(hdc, lt.x, lt.y, rb.x, rb.y);

	if (hoverPoint != Corner::NONE) {
		corners[(int)hoverPoint].draw(hdc, 6, true);
	}
}

bool Rect::updateHoverPoint(const MouseEvent& ev) {
	hoverPoint = Corner::NONE;
	const Corner checkCorners[] = { Corner::LEFT_TOP , Corner::LEFT_BOTTOM, Corner::RIGHT_TOP, Corner::RIGHT_BOTTOM };

	for (Corner c : checkCorners) {
		if (corners[static_cast<int>(c)].inRange(ev.pos, 3)) {
			hoverPoint = c;
			return true;
		}
	}
	return false;
}

void Rect::save(std::ofstream& f) {
	writeString(f, typeAsString());
	f.put(':');
	
	for (auto& c : corners) {
		c.save(f);
	}

	writeInt(f, static_cast<int>(hoverPoint));
	writeInt(f, static_cast<int>(dragPoint));
	f.put('\n');
}

void Rect::load(std::ifstream& f) {
	auto p = std::make_unique<Rect>();
	Rect& rect = *p;
	
	for (auto& c : rect.corners) {
		Point::load(f, c);
	}

	int h;
	int d;

	readInt(f, h);
	readInt(f, d);
	
	rect.hoverPoint = static_cast<Corner>(h);
	rect.dragPoint = static_cast<Corner>(d);
	


	App::Instance()->objList.emplace_back(std::move(p));

	printf("[Rect]: (%d, %d), (%d, %d), (%d, %d), (%d, %d); h: %d, d: %d\n",
		rect.corners[0].x, rect.corners[0].y,
		rect.corners[1].x, rect.corners[1].y,
		rect.corners[2].x, rect.corners[2].y,
		rect.corners[3].x, rect.corners[3].y,
		rect.hoverPoint, rect.dragPoint);
}
