#pragma once
#include "Util.h"
#include <vector>
#include "Point.h"
#include "string"

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
	}
	
	void initPoint() { 
		Point* p = new Point(mouse, 6, currentColor);
		appObjPtrs.push_back(p);
		
	}

	AppObject* lastItemPtr() { return appObjPtrs.back(); }
	

	void drawDebugMsgBox(const HDC hdc_) const {
		RECT debugRect{ 0, 0, 500, 100 };
		char debugMsg[200]{ 0 };
		sprintf_s(debugMsg, 200,
			"appObjPtrs.size: %d\n"
			"MouseState: %s\n\0",
			appObjPtrs.size(),
			mouse.stateAsString());	
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

