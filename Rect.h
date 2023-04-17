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
	Point corners[4]; //reduce computation.
	Corner dragPoint = Corner::NONE;
	Corner hoverPoint = Corner::NONE;

	Point& leftTop() { return corners[(int)Corner::LEFT_TOP]; }
	Point& leftBottom() { return corners[(int)Corner::LEFT_BOTTOM]; }
	Point& rightTop() { return corners[(int)Corner::RIGHT_TOP]; }
	Point& rightBottom() { return corners[(int)Corner::RIGHT_BOTTOM]; }


	const Point& leftTop()	 const { return corners[(int)Corner::LEFT_TOP]; }
	const Point& leftBottom()	 const { return corners[(int)Corner::LEFT_BOTTOM]; }
	const Point& rightTop()	 const { return corners[(int)Corner::RIGHT_TOP]; }
	const Point& rightBottom() const { return corners[(int)Corner::RIGHT_BOTTOM]; }

	//using LT = leftTop;


	void onCreate(const MouseEvent& ev) {
		for (auto& pt : corners) {
			pt = ev.pos;
		}
		setDragPoint(Corner::RIGHT_BOTTOM);
	}

	void updateCorner(Corner c, const POINT* pos = nullptr) {
		if (pos) {
			corners[(int)c] = *pos;
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

	virtual bool onMouseEvent(const MouseEvent& ev) override {
		

		if (ev.isLButton()) {
			if (ev.isUp()) {


				switch (dragPoint) {
				case Corner::NONE: { return false; }
				default: { return false; }


				case Corner::LEFT_TOP: {
					updateCorner(Corner::LEFT_TOP, &ev.pos);
					updateCorner(Corner::RIGHT_TOP);
					updateCorner(Corner::LEFT_BOTTOM);
					setDragPoint(Corner::NONE);
					return true;
				}

				case Corner::LEFT_BOTTOM: {
					updateCorner(Corner::LEFT_BOTTOM, &ev.pos);
					updateCorner(Corner::LEFT_TOP);
					updateCorner(Corner::RIGHT_BOTTOM);
					setDragPoint(Corner::NONE);
					return true;
				}


				case Corner::RIGHT_TOP: {
					updateCorner(Corner::RIGHT_TOP, &ev.pos);
					updateCorner(Corner::LEFT_TOP);
					updateCorner(Corner::RIGHT_BOTTOM);

					setDragPoint(Corner::NONE);
					return true;
				}


				case Corner::RIGHT_BOTTOM: {
					updateCorner(Corner::RIGHT_BOTTOM, &ev.pos);
					updateCorner(Corner::LEFT_BOTTOM);
					updateCorner(Corner::RIGHT_TOP);
					setDragPoint(Corner::NONE);
					return true;

				}
				}
			}
			if (ev.isDown()) {
				//check if any point isHovered.
				return false;
			}

		} else if (ev.isMove()) {
			//printf("dragPoint = %i", (int) dragPoint);
			if (dragPoint != Corner::NONE) {
				corners[(int)dragPoint] = ev.pos;
				return true;
			}

			hoverPoint = Corner::NONE;

			// TODO: it is insane, change it.
			for (int i = 0; i < 4; i++) {
				if (corners[i].inRange(ev.pos, 3)) {
					// isHover
					hoverPoint = (Corner)i;
					return true;
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
		// TODO: draw hoverPoint.

		if (hoverPoint != Corner::NONE) {
			corners[(int)hoverPoint].draw(hdc, 6);
		}
	}

};