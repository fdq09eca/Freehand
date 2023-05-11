#pragma once
#include <vector>
#include <memory>
#include "AppObject.h"
#include "Menu.h"
#include "Crosshair.h"

class App : NonCopyable
{
private:
	static App* _instance;
	HWND _hWnd = NULL;
	BackBuffer backBuffer;
	MouseButton _mouseButtonState = MouseButton::NA;


public:
	HPEN dashRedPen;
	HPEN solidRedPen;
	HPEN solidBlackPen;
	HBRUSH solidRedBrush;
	Menu menu;
	Crosshair crossHair;
	AppObjectType currentAppObjType = AppObjectType::Line;
	

	
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

	void initMenu();
	

	void setHwnd(HWND hWnd_);
	HWND hWnd() { return _hWnd; }

	void draw(HDC hdc_) ;

	void onMouseEvent(const MouseEvent& ev);

	void _onWin32MouseEvent(UINT msg, WPARAM wp, LPARAM lp);

	void setCaptureObject(AppObject* obj);
	
	void clearCaptureObject();

	MouseButton mouseButtonState() const { return _mouseButtonState; }

	void save(const wchar_t* fpath) const ;
	void load(const wchar_t* fpath) ;

};

extern App* g_internal_app_ptr;

inline App* g_app() { return g_internal_app_ptr; };
inline void g_set_app(App* p) { g_internal_app_ptr = p; };