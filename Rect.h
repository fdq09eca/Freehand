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
	Rect() { _type = Type::Rect; }

	Point corners[4];
	Corner dragPoint = Corner::NONE;
	Corner hoverPoint = Corner::NONE;

	inline Point& leftTop()		{ return corners[static_cast<int>(Corner::LEFT_TOP)]; }
	inline Point& leftBottom()	{ return corners[static_cast<int>(Corner::LEFT_BOTTOM)]; }
	inline Point& rightTop()	{ return corners[static_cast<int>(Corner::RIGHT_TOP)]; }
	inline Point& rightBottom()	{ return corners[static_cast<int>(Corner::RIGHT_BOTTOM)]; }

	inline const Point& leftTop()		const { return corners[static_cast<int>(Corner::LEFT_TOP)]; }
	inline const Point& leftBottom()	const { return corners[static_cast<int>(Corner::LEFT_BOTTOM)]; }
	inline const Point& rightTop()		const { return corners[static_cast<int>(Corner::RIGHT_TOP)]; }
	inline const Point& rightBottom()	const { return corners[static_cast<int>(Corner::RIGHT_BOTTOM)]; }


	void onCreate(const MouseEvent& ev);

	void updateCorner(Corner c, const POINT* pos = nullptr);

	virtual bool onMouseEvent(const MouseEvent& ev) override;

	void setDragAndHoverPoint(Corner c);

	virtual void draw(HDC hdc) const override;

	bool updateHoverPoint(const MouseEvent& ev);

};