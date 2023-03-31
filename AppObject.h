#pragma once
#include "Util.h"

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
	AppObject() = delete;
	AppObject(const Mouse& mouse_) : _mouse{ mouse_ } { setPos(mouse_); }
	~AppObject() {
		reset();
	}

	
	virtual POINT pos()		const { return _pos; }
	void setPos(int x_, int y_) { _pos.x = x_; _pos.y = y_; }
	void setPos(const POINT& pos) { _pos = pos; }
	void setPos(const Mouse& mouse) { _pos = mouse.getPos(); }


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

	virtual void onDrag() = 0;


};
