#include "App.h"

void App::onMouseEvent(const MouseEvent& ev) {
	
	if (tmpObj) {
		

		if (ev.isUp()) {
			if (ev.isLButton()) {
				tmpObj->onMouseEvent(ev);
				objList.emplace_back(std::move(tmpObj));
				tmpObj = nullptr;
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
				auto p = std::make_unique<Line>();
				p->onMouseLeftBtnDown(ev);
				tmpObj = std::move(p);
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

	case WM_LBUTTONUP: { ev.eventType = T::Up;	ev.button = B::Left;   } break;
	case WM_MBUTTONUP: { ev.eventType = T::Up;	ev.button = B::Middle; } break;
	case WM_RBUTTONUP: { ev.eventType = T::Up;	ev.button = B::Right;  } break;

	case WM_MOUSEMOVE: { ev.eventType = T::Move; } break;
	default: { assert(false); return; } break;
	}
	//ev.btnState // do it later


	onMouseEvent(ev);
	InvalidateRect(_hWnd, nullptr, true);

}
