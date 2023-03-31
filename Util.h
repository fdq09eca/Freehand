#pragma once
#include <stdio.h>
#include <Windows.h>
#include "windowsx.h"
#include <string>
#include <cassert>

class NonCopyable {

private:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

public:
	NonCopyable() = default;
	~NonCopyable() = default;
};

enum class MouseButton {
	NA = 0,
	Left,
	Middle,
	Right,
};

enum class MouseState {
	None = 0,
	LeftButtonDown,
	RightButtonDown,
};

class Mouse {
	POINT _pos;
	MouseState _state = MouseState::None;

public:

	void setPos(LPARAM lp) {
		_pos.x = GET_X_LPARAM(lp);
		_pos.y = GET_Y_LPARAM(lp);
	}

	const POINT& getPos() const { return _pos; }
	//POINT getPos() { return _pos; }
	const MouseState& state() const { return _state; }
	
	const char* stateAsString() const { 
		switch (_state)
		{
			case MouseState::None: return "MouseState::None";
			case MouseState::LeftButtonDown: return "MouseState::LeftButtonDown";
			case MouseState::RightButtonDown: return "MouseState::RightButtonDown";
		}
		assert(false);
	}

	void setState(MouseState state_) {
		_state = state_;
	}

	RECT hitBox() {
		RECT r{ _pos.x - 100, _pos.y, _pos.x + 100, _pos.y + 100 };
		return r;
	}
};



class AppObject : NonCopyable {

protected:
	POINT _pos{ 0, 0 };
	RECT _hitBox{ 0, 0, 0, 0 };
	bool _isSelected = false;
	

	const Mouse& _mouse; //owned by App
	void reset() {
		_pos = POINT{ 0, 0 };
	
		_isSelected = false;
	}

public:
	AppObject() = default;
	AppObject(const Mouse& mouse_) : _pos{ mouse_.getPos().x, mouse_.getPos().y }, _mouse{ mouse_ } {  }
	~AppObject() {
		reset();
	}

	POINT pos()		const { _pos; }
	void setPos(int x_, int y_) { _pos.x = x_; _pos.y = y_; }
	void setPos(const POINT& pos) { _pos = pos; }

	
	bool isHovered() const { 

		RECT hBox = hitBox();
		return PtInRect(&hBox, _mouse.getPos());
	}

	virtual RECT  hitBox()	const = 0;
	virtual void draw(HDC hdc_) const = 0;
	virtual void drawHitBox(HDC hdc_) const {
		if ((isHovered()) || _isSelected) {
			RECT hBox = hitBox();
			Rectangle(hdc_, hBox.left, hBox.top, hBox.right, hBox.bottom);
		}
	}
	

	
};