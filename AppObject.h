#pragma once
#include "Util.h"

class AppObject : NonCopyable {

protected:
	POINT _pos{ 0, 0 };
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
		POINT mPos = _mouse.getPos();
		bool r = PtInRect(&hBox, mPos);
		return r;
	}

	virtual RECT  hitBox()  const = 0;
	virtual void draw(HDC hdc_) const = 0;
	
	virtual void drawHitBox(HDC hdc_) const {
		RECT hBox = hitBox();
		Rectangle(hdc_, hBox.left, hBox.top, hBox.right, hBox.bottom);
	}

	virtual void onDrag() = 0;
	
	virtual void drawDebugMessage(HDC hdc_) const {
		RECT b = hitBox();
		wchar_t buff[100];
		
		swprintf_s(buff, 100, L"x:%d, y:%d\n"
			L"hitBox(%d, %d, %d, %d)\n"
			L"isHovered: %s\n"

			, _pos.x, _pos.y,
			b.left, b.top, b.right, b.bottom,
			isHovered() ? L"YES" : L"NO"
		);
		RECT r{ _pos.x + 5 , _pos.y + 5,  _pos.x + 250, _pos.y + 250 };
		DrawText(hdc_, buff, wcslen(buff), &r, DT_TOP | DT_LEFT);
	}

};
