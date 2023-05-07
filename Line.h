#pragma once
#include "Point.h"
#include "AppObject.h"

class Line : public AppObject
{
private:
	Point _lastMousePos;
public:
	Point pt[2];
	int dragPoint = -1;
	int hoverPoint = -1;
	
	bool isDragLine = false;
	bool ishoverLine = false;
	
	Line() { _type = Type::Line; }

	virtual bool onMouseEvent(const MouseEvent& ev) override;


	void onCreate(const MouseEvent& ev);


	inline void clearHoverPoint()	{ clearDragPoint(); }
	inline void clearDragPoint()	{ dragPoint = -1; hoverPoint = -1; } // no drag, no hover
	inline void setDragPoint(int i) { dragPoint =  i; hoverPoint =  i; } // no drag, no hover
	inline void setDragLine(bool b, const MouseEvent& ev) { 
		isDragLine	=  b; 
		ishoverLine =  b; 
	} // no drag, no hover

	bool updateHoverPoint(const MouseEvent ev, const Point* points, int nPoints);
	bool updateHoverLine(const MouseEvent& ev, int distance);
	
	
	static Point lerp(const Point& p0, const Point& p1, float t = 0);

	void draw(HDC hdc_) const override;

	static void drawLine(HDC hdc_, const Point& pt0, const Point& pt1, HPEN hpen);

	void save(std::ofstream& f);

	static void load(std::ifstream& f);
	
};

