#include "App.h"
#include "Line.h"
#include "Rect.h"
#include "Curve.h"

App* App::_instance = nullptr;

void App::init() {
	assert(_instance == nullptr);
	_instance = this;

	// create pen and brush..
	dashRedPen = ::CreatePen(PS_DOT, 1, RGB(255, 0, 0)); // red dash pen
	solidBlackPen = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // black solid pen
	solidRedBrush = ::CreateSolidBrush(RGB(255, 0, 0)); // red solid brush
	
	
	// for testing purpose...

	auto p = std::make_unique<Line>();
	p->pt[0] = POINT{ 200, 200 };
	p->pt[1] = POINT{ 400, 400 };
	objList.emplace_back(std::move(p));

	auto r = std::make_unique<Rect>();
	r->corners[0] = POINT{ 500, 500 };
	r->corners[3] = POINT{ 600, 600 };
	objList.emplace_back(std::move(r));
}

void App::setHwnd(HWND hWnd_) {
	_hWnd = hWnd_;
	backBuffer.create(_hWnd);
}

void App::draw(HDC hdc_)  {
	backBuffer.clear();
	
	for (const auto& p : objList) {
		p->draw(backBuffer.dc());
	}
	
	if (tmpObj) {
		tmpObj->draw(backBuffer.dc());
	}

	
	backBuffer.draw(hdc_);
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
		if (captureObj) {
			captureObj->onMouseEvent(ev);
			return;
		}


		for (auto& p : objList) { 
			if (p->onMouseEvent(ev)) {
				return;
			}
		}

		if (ev.isDown()) {
			if (ev.isLButton()) {
				auto p = std::make_unique<Curve>();
				p->onCreate(ev); 
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

	case WM_LBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Left;   _mouseButtonState |=  B::Left;	} break;
	case WM_MBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Middle; _mouseButtonState |=  B::Middle;	} break;
	case WM_RBUTTONDOWN: { ev.eventType = T::Down;  ev.button = B::Right;  _mouseButtonState |=  B::Right;	} break;
	
	case WM_LBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Left;   _mouseButtonState &= ~B::Left;	} break;
	case WM_MBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Middle; _mouseButtonState &= ~B::Middle;	} break;
	case WM_RBUTTONUP:	 { ev.eventType = T::Up;	ev.button = B::Right;  _mouseButtonState &= ~B::Right;	} break;

	case WM_MOUSEMOVE: { ev.eventType = T::Move; } break;
	
	default: { assert(false); return; } break;
	}
	//ev.btnState // do it later


	onMouseEvent(ev);
	InvalidateRect(_hWnd, nullptr, false);

}

void App::setCaptureObject(AppObject* obj) {
	assert(captureObj == nullptr);
	captureObj = obj;
	printf("[set] captureObj [%s id: %d]\n", obj->typeAsString(), obj->id);
}

void App::clearCaptureObject() {
	assert(captureObj != nullptr);
	printf("[clear] captureObj [%s id: %d]\n", captureObj->typeAsString(), captureObj->id);
	captureObj = nullptr;
}

void App::save() {
	
		if (of.is_open()) {
			of.close();
		}
		of.open("saveApp.txt", std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
		for (auto& obj : objList) {
			obj->save(of);
		}
		of.close();
	
}

void App::load() {
	using Type = AppObjectType;
	using Obj = AppObject;
	objList.clear();
	std::ifstream ifs;
	ifs.open("saveApp.txt", std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
	char c;
	int i = 0;
	std::string objType;
	
	while (ifs.get(c)) {
		if (c == '\n' || c == ' ') continue;
	
		objType += c;
		
		if (c == ':') {
			if (objType == Obj::typeAsString(Type::Line)) {  Line::load(ifs); } 
			if (objType == Obj::typeAsString(Type::Rect)) { Rect::load(ifs); }			
			if (objType == Obj::typeAsString(Type::Curve)) { Curve::load(ifs); }
			objType.clear();
			continue;
		}
	}
	
	ifs.close();
}