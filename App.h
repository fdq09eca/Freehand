#pragma once
#include "AppObject.h"
#include <vector>
#include <memory>
#include "Point.h"
#include "Line.h"
#include "Rect.h"
#include "string"



class App : NonCopyable
{
	HWND _hWnd = NULL;
	BackBuffer backBuffer;
	MouseButton mouseButtonState = MouseButton::NA; // 

public:
	std::vector<std::unique_ptr<AppObject>> objList;
	std::unique_ptr<AppObject> tmpObj;
	

	
	App() = default;
	
	std::string func(const std::string& s) {
		std::string s1 = s + "11";
		return s1; //(rvo) move(s1)
	}
	
	~App() {  
		std::string _s = "0";
		_s = func(_s); // "011"
	}

	void init();

	void setHwnd(HWND hWnd_);

	void draw(HDC hdc_) ;

	void onMouseEvent(const MouseEvent& ev);

	void _onWin32MouseEvent(UINT msg, WPARAM wp, LPARAM lp);
	

	
	
	
	

};

