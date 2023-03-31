#pragma once
#include "AppObject.h"
#include <vector>
#include <memory>
#include "Point.h"
#include "Line.h"
#include "string"


class App : NonCopyable
{
	HWND _hWnd = NULL;

public:
	MouseEvent mouse;
	std::vector<std::unique_ptr<AppObject>> objList;
	std::unique_ptr<AppObject> tmpObj;
	

	
	App() = default;
	~App() { }

	void init() {
		/*auto p = std::make_unique<Line>();
		p->pt0.pos = POINT{ 100, 100 };
		p->pt1.pos = POINT{ 200, 200 };
		
		objList.emplace_back(std::move(p));*/
	}

	void setHwnd(HWND hWnd_) { _hWnd = hWnd_; }

	void draw(HDC hdc_) const { 
	
		for (const auto& p : objList) { 
			p->draw(hdc_);
		}
		
		if (tmpObj) {
			tmpObj->draw(hdc_);
		}

	}

	

	void onMouseEvent(const MouseEvent& ev);

	void _onWin32MouseEvent(UINT msg, WPARAM wp, LPARAM lp);
	

	
	
	
	

};

