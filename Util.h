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

	RECT hitBox() const {
		RECT r{ _pos.x - 100, _pos.y - 100, _pos.x + 100, _pos.y + 100 };
		return r;
	}
};



