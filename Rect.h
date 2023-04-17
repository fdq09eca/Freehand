#pragma once

#include "AppObject.h"
#include "Point.h"

class Rect : public AppObject
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
	Point corners[4]; //reduce computation.
	Corner dragPoint = Corner::NONE;
	Corner hoverPoint = Corner::NONE;

	Point& leftTop() { return corners[(int)Corner::LEFT_TOP]; }
	Point& leftBottom() { return corners[(int)Corner::LEFT_BOTTOM]; }
	Point& rightTop() { return corners[(int)Corner::RIGHT_TOP]; }
	Point& rightBottom() { return corners[(int)Corner::RIGHT_BOTTOM]; }


	const Point& leftTop()	 const	{ return corners[(int)Corner::LEFT_TOP]; }
	const Point& leftBottom()	 const	{ return corners[(int)Corner::LEFT_BOTTOM]; }
	const Point& rightTop()	 const	{ return corners[(int)Corner::RIGHT_TOP]; }
	const Point& rightBottom() const	{ return corners[(int)Corner::RIGHT_BOTTOM]; }

	//using LT = leftTop;


	void onCreate(const MouseEvent& ev) {
		for (auto& pt : corners) {
			pt = ev.pos;
		}
		setDragPoint(Corner::RIGHT_BOTTOM);
	}



	virtual bool onMouseEvent(const MouseEvent& ev) override {
		if (ev.isMove()) {
			if (dragPoint != Corner::NONE) {
				corners[(int)dragPoint] = ev.pos;
				return true;
			}
			
			hoverPoint = Corner::NONE;
			
			// TODO: it is insane, change it.
			for (int i = 0; i < 4; i++) {
				if (corners[i].inRange(ev.pos, 3)) {
					// isHover
					hoverPoint = (Corner) i;
					return true;
				}
			}

			return false;
		}

		if (ev.isLButton()) {
			if (ev.isUp()) {

				Point& lt = leftTop();
				Point& lb = leftBottom();
				Point& rt = rightTop();
				Point& rb = rightBottom();

				switch (dragPoint) {
					case Corner::NONE: { return false; }
					default: { return false; }


					case Corner::LEFT_TOP: {
						lt = ev.pos;
						setDragPoint(Corner::NONE);
						return true;
					}

					case Corner::LEFT_BOTTOM: {
						lb = ev.pos;
						lt.x = lb.x;
						rb.y = lb.y;
						setDragPoint(Corner::NONE);
						return true;
					}


					case Corner::RIGHT_TOP: {
						rt = ev.pos;
						lt.y = rt.y;
						rb.x = rt.x;
						setDragPoint(Corner::NONE);
						return true;
					}


					case Corner::RIGHT_BOTTOM: {
						rb = ev.pos;
						setDragPoint(Corner::NONE);
						return true;

					}
				}
			}
			if (ev.isDown()){
				//check if any point isHovered.
			}

		}




	}

	void setDragPoint(Corner c) {
		dragPoint = c;
		hoverPoint = c;
	}



	void draw(HDC hdc) const override {
		Point lt = leftTop();
		Point rb = rightBottom();
		::Rectangle(hdc, lt.x, lt.y, rb.x, rb.y);
		printf("lt.x: %i, lt.y: %i, rb.x: %i, rb.y: %i\n", lt.x, lt.y, rb.x, rb.y);
	}

};