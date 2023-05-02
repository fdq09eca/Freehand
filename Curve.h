#pragma once

#include "Point.h"
#include "AppObject.h"

class Curve : public AppObject
{
public:
	static const int nPoints = 4; // why not const int nPoints = 4
	Point pts[nPoints];
	Curve() { _type = Type::Curve; }
	int hoverPoint = -1;
	int dragPoint = -1;
	int createPoint = -1;

	void onCreate(const MouseEvent& ev);

	inline bool isCreated() const { return !(createPoint >= -1 && createPoint < 4); }
	inline void clearHoverPoint() { clearDragPoint(); }
	inline void clearDragPoint() { dragPoint = -1; hoverPoint = -1; } // no drag, no hover
	inline void setDragPoint(int i) { dragPoint = i; hoverPoint = i; } // no drag, no hover

	bool updateHoverPoint(const MouseEvent ev, const Point* points, int nPoints);

	void onLeftBtnDrag(const MouseEvent& ev);
	
	void drawCurve(HDC hdc) const;

	virtual void draw(HDC hdc) const override;
	
	virtual bool onMouseEvent(const MouseEvent& ev);

	
};

