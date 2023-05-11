#pragma once
#include "Line.h"




class Crosshair
{
	Line hLine;
	Line vLine;
public:	

	int maxX() const ;
	int maxY() const ;

	void updateHline(Point mPos);
	
	void updateVline(Point mPos);

	bool onMouseEvent(const MouseEvent& ev);

	virtual void draw(HDC hdc_) const;
};

