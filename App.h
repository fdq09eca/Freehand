#pragma once
#include <vector>
#include <memory>
#include "AppObject.h"

class Rect;

class App : NonCopyable
{
private:
	static App* _instance;
	HWND _hWnd = NULL;
	BackBuffer backBuffer;
	MouseButton _mouseButtonState = MouseButton::NA;



public:
	HPEN dashRedPen;
	HBRUSH solidRedBrush;
	HPEN solidBlackPen;


	std::ofstream of;
	std::vector<std::unique_ptr<AppObject>> objList;
	std::unique_ptr<AppObject> tmpObj;
	AppObject* captureObj = nullptr;
	

	
	App() = default;
	
	static App* Instance() { return _instance; }
	
	~App() {  
		if (captureObj) { 
			captureObj = nullptr; // it should not be deleted. 
		}
		DeleteObject(dashRedPen);
		DeleteObject(solidBlackPen);
		DeleteObject(solidRedBrush);
	}

	void init();

	void setHwnd(HWND hWnd_);

	void draw(HDC hdc_) ;

	void onMouseEvent(const MouseEvent& ev);

	void _onWin32MouseEvent(UINT msg, WPARAM wp, LPARAM lp);

	void setCaptureObject(AppObject* obj);
	
	void clearCaptureObject();

	MouseButton mouseButtonState() const { return _mouseButtonState; }

	void save();

};

extern App* g_internal_app_ptr;

inline App* g_app() { return g_internal_app_ptr; };
inline void g_set_app(App* p) { g_internal_app_ptr = p; };