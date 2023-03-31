#pragma once
#include "AppObject.h"
#include <vector>
#include "Point.h"
#include "Line.h"
#include "string"


enum class AppObjectType {
	NA = 0,
	Point,
	Line,
};

class App : NonCopyable
{
	HWND _hWnd = NULL;

public:
	Mouse mouse;
	std::vector<AppObject*> appObjPtrs;
	COLORREF currentColor = RGB(0, 0, 0);

	
	App() = default;
	~App() { for (auto p : appObjPtrs) { delete p; } }

	void setHwnd(HWND hWnd_) { _hWnd = hWnd_; }

	void draw(const HDC hdc_) const { 

		drawDebugMsgBox(hdc_);
		for (auto p : appObjPtrs) { 
			p->draw(hdc_); 
		}

		/*RECT mRect = mouse.hitBox();
		Rectangle(hdc_, mRect.left, mRect.top, mRect.right, mRect.bottom);*/
	}
	
	void initPoint() {
		Point* p = new Point(mouse);
		appObjPtrs.push_back(p);
	}

	void initLine() {
		Line* p = new Line(mouse);
		appObjPtrs.push_back(p);
	}

	void init(AppObjectType type) {
		switch (type)
		{
			case AppObjectType::NA:		{ assert(false);	} break;
			case AppObjectType::Point:	{ initPoint();		} break;
			case AppObjectType::Line:	{ initLine();		} break;
			default: break;
		}
	}

	

	AppObject* lastItemPtr() { return appObjPtrs.back(); }
	

	void drawDebugMsgBox(const HDC hdc_) const {
		RECT debugRect{ 0, 0, 500, 100 };
		char debugMsg[200]{ 0 };
		sprintf_s(debugMsg, 200,
			"appObjPtrs.size: %d\n"
			"MouseState: %s\n"
			"mousePos: x:%d, y:%d\n\0",
			appObjPtrs.size(),
			mouse.stateAsString(),
			mouse.getPos().x,
			mouse.getPos().y
		);	
		DrawTextA(hdc_, debugMsg, strlen(debugMsg), &debugRect, DT_TOP | DT_LEFT);
	}

	void drawHover() {
		HDC hdc = GetDC(_hWnd);
		for (AppObject* p : appObjPtrs) {
			if (!p) {
				assert(false);
				return;
			}
			if (p->isHovered()) {
				p->drawHitBox(hdc);
			}
		}
		ReleaseDC(_hWnd, hdc);
	}

	void onMouseMove(LPARAM lp) {
		mouse.setPos(lp);

		for (AppObject* p : appObjPtrs) {
			assert(p);
			if (p->isHovered()) {
				HDC hdc = GetDC(_hWnd);
				p->drawHitBox(hdc);
				ReleaseDC(_hWnd, hdc);
			}
		}

		if (mouse.state() == MouseState::LeftButtonDown) {
			//dragging.
			AppObject* p = lastItemPtr();
			assert(p);
			p->setPos(mouse.getPos());

		}

		InvalidateRect(_hWnd, nullptr, true); // for real?
		
	}
	

	
	
	
	

};

