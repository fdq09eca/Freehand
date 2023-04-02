#include "App.h"

void App::setHwnd(HWND hWnd_) {
	_hWnd = hWnd_;
}

void App::draw(HDC hdc_)  {
#if !true
	for (const auto& p : objList) {
		p->draw(hdc_);
	}

	if (tmpObj) { tmpObj->draw(hdc_); }
#else
	backBuffer.create(_hWnd);
	for (const auto& p : objList) {
		p->draw(backBuffer.dc());
	}
	

	if (tmpObj) {
		tmpObj->draw(backBuffer.dc());
	}
	
	backBuffer.draw(hdc_);
	backBuffer.destroy();
#endif


}

void App::onMouseEvent(const MouseEvent& ev) {
	
	if (tmpObj) {
		if (ev.isMove()) {
			tmpObj->onMouseEvent(ev);
			return;
		}
		

		if (ev.isUp()) {
			if (ev.isLButton()) {
				tmpObj->onMouseEvent(ev); //onEndCreateTmpObj
				objList.emplace_back(std::move(tmpObj));
				tmpObj = nullptr;
				return;
			}
		}
	}
	else {
		
		for (auto& p : objList) { 
			if (p->onMouseEvent(ev)) {
				return;
			}
		}

		if (ev.isDown()) {
			if (ev.isLButton()) {
				auto p = std::make_unique<Line>(); //create current selected Object
				p->onMouseLeftBtnDown(ev); //onBeginCreateTmpObj
				tmpObj = std::move(p);
				return;
			}
		}
	}

}

void App::_onWin32MouseEvent(UINT msg, WPARAM wp, LPARAM lp) {

	MouseEvent ev;
	ev.pos = POINT{ GET_X_LPARAM(lp) , GET_Y_LPARAM(lp) };

	switch (msg)
	{
		using B = MouseButton;
		using T = MouseEventType;

	case WM_LBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Left;   } break;
	case WM_MBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Middle; } break;
	case WM_RBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Right;  } break;
	
	case WM_LBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Left;   } break;
	case WM_MBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Middle; } break;
	case WM_RBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Right;  } break;

	case WM_MOUSEMOVE: { ev.eventType = T::Move; } break;
	
	default: { assert(false); return; } break;
	}
	//ev.btnState // do it later


	onMouseEvent(ev);
	InvalidateRect(_hWnd, nullptr, false);

}
