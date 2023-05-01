#pragma once
#include "Point.h"

class Line : public AppObject
{

public:
	Point pt[2];
	int dragPoint = -1;
	int hoverPoint = -1;
	
	Line() { _type = Type::Line; }

	virtual bool onMouseEvent(const MouseEvent& ev) override;

	void onCreate(const MouseEvent& ev);

	void draw(HDC hdc_) const override;

	inline void clearHoverPoint()	{ clearDragPoint(); }
	inline void clearDragPoint()	{ dragPoint = -1; hoverPoint = -1; } // no drag, no hover
	inline void setDragPoint(int i) { dragPoint =  i; hoverPoint =  i; } // no drag, no hover

	bool updateHoverPoint(const MouseEvent ev, const Point* points, int nPoints);

	


	
	
};

