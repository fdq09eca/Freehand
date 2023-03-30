#pragma once
#include <stdio.h>
#include <Windows.h>
#include "windowsx.h"

class NonCopyable {

private:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

public:
	NonCopyable() = default;
	~NonCopyable() = default;
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
	const MouseState& getState() const { return _state; }

	void setState(MouseState state_) {
		_state = state_;
	}
};



class AppObject : NonCopyable {

protected:
	POINT _pos{ 0, 0 };
	RECT _hitBox{ 0, 0, 0, 0 };
	bool _isSelected = false;
	bool _isTemp = true;

	const Mouse& _mouse; //owned by App
	void reset() {
		_pos = POINT{ 0, 0 };
		_hitBox = RECT{ 0, 0, 0, 0 };
		_isSelected = false;
	}

public:
	AppObject() = default;
	AppObject(const Mouse& mouse_) : _pos{ mouse_.getPos().x, mouse_.getPos().y }, _mouse{ mouse_ } {  }
	~AppObject() {
		reset();
	}

	POINT pos()		const { _pos; };
	void setPos(int x_, int y_) { _pos.x = x_; _pos.y = y_; };

	virtual void setHitBox(RECT rect) { _hitBox = rect; }
	RECT  hitbox()	const { return _hitBox; }

	bool isHovered() const { return PtInRect(&_hitBox, _mouse.getPos()); }

	void setTemp(bool isTemp_) { _isTemp = isTemp_; }
	bool getTemp() const { return _isTemp; }

	virtual void draw(HDC hdc_) const = 0;
	virtual void drawHitBox(HDC hdc_) const {
		if ((isHovered()) || _isSelected) {
			Rectangle(hdc_, _hitBox.left, _hitBox.top, _hitBox.right, _hitBox.bottom);
		}

	}
};