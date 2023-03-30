#pragma once
#include "Util.h"
#include <vector>
#include "Point.h"

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
		for (auto p : appObjPtrs) { 
			p->draw(hdc_); 
		} 
	}
	
	void initTempPoint() { 
		Point* p = new Point(mouse, 6, currentColor); // why cannot?
		appObjPtrs.push_back(p);
		
	}


	AppObject* lastItemPtr() { return appObjPtrs.back(); }
	
	

	
	
	
	

};

