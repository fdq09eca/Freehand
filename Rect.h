#pragma once

#include "AppObject.h"
#include "Point.h"

class Rect : public AppObject // i want to call it Rectangle too..
{
private:
	enum class Corner {
		NONE = -1,
		LEFT_TOP = 0,
		LEFT_BOTTOM = 1,
		RIGHT_TOP = 2,
		RIGHT_BOTTOM = 3
	};


public:
	Point corners[4];
	Corner dragPoint = Corner::NONE;
	Corner hoverPoint = Corner::NONE;



	Point& leftTop() {
		return corners[static_cast<int>(Corner::LEFT_TOP)];
	}
	Point& leftBottom() { return corners[static_cast<int>(Corner::LEFT_BOTTOM)]; }
	Point& rightTop() { return corners[static_cast<int>(Corner::RIGHT_TOP)]; }
	Point& rightBottom() { return corners[static_cast<int>(Corner::RIGHT_BOTTOM)]; }


	const Point& leftTop()	 const { return corners[static_cast<int>(Corner::LEFT_TOP)]; }
	const Point& leftBottom()	 const { return corners[static_cast<int>(Corner::LEFT_BOTTOM)]; }
	const Point& rightTop()	 const { return corners[static_cast<int>(Corner::RIGHT_TOP)]; }
	const Point& rightBottom() const { return corners[static_cast<int>(Corner::RIGHT_BOTTOM)]; }


	void onCreate(const MouseEvent& ev) {
		for (auto& pt : corners) {
			pt = ev.pos;
		}
		setDragPoint(Corner::RIGHT_BOTTOM);
	}

	void updateCorner(Corner c, const POINT* pos = nullptr) {
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

	virtual bool onMouseEvent(const MouseEvent& ev, const MouseButton& buttonState) override {


		if (ev.isLButton()) {
			if (ev.isUp()) {
				setDragPoint(Corner::NONE);
				printf("b::LeftIsUp: dragPoint %d hoverPoint %d\n", dragPoint, hoverPoint);
				return true;
			}

			if (ev.isDown()) {
				if (hoverPoint != Corner::NONE) {
					setDragPoint(hoverPoint);
					printf("b::LeftIsDown: dragPoint %d hoverPoint %d\n", dragPoint, hoverPoint);
					
					return true;
				}
				return false;
			}
		}

		else if (ev.isMove()) {
			
			if (buttonState == MouseButton::Left) {
				printf("b::MoveAndLeftIsDown: dragPoint %d hoverPoint %d\n", dragPoint, hoverPoint); //bug here, create 2 rect and drag to reproduce.
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

				hoverPoint = Corner::NONE;
				const Corner checkCorners[] = { Corner::LEFT_TOP , Corner::LEFT_BOTTOM, Corner::RIGHT_TOP, Corner::RIGHT_BOTTOM };

				for (Corner c : checkCorners) {
					if (corners[static_cast<int>(c)].inRange(ev.pos, 3)) {
						hoverPoint = c;
						return true;
					}
				}

			}
		}


		return false;
	}

	void setDragPoint(Corner c) {
		dragPoint = c;
		hoverPoint = c;
	}

	virtual void draw(HDC hdc) const override {
		Point lt = leftTop();

		Point rb = rightBottom();
		::Rectangle(hdc, lt.x, lt.y, rb.x, rb.y);

		if (hoverPoint != Corner::NONE) {
			corners[(int)hoverPoint].draw(hdc, 6);
		}
	}

};