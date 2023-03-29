#pragma once
#include <stdio.h>
#include <Windows.h>


class NonCopyable {

private:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

public:
	NonCopyable() = default;
	~NonCopyable() = default;
};

class AppObject : NonCopyable {

protected:
	POINT _pos{ 0, 0 };
	RECT _hitBox{ 0, 0, 0, 0 };
	bool isSelected = false;

public:
	AppObject() = default;
	AppObject(int x_, int y_) : _pos{ x_, y_ } {  }

	void setPos(int x_, int y_) { _pos.x = x_; _pos.y = y_; };
	void setHitBox(RECT box) { _hitBox = box; }

	POINT pos()		const { _pos; };
	RECT  hitbox()	const { return _hitBox; }

	bool isHovered(int mouseX, int mouseY) const {
		POINT mousePos{ mouseX, mouseY };
		return PtInRect(&_hitBox, _pos);
	}

	virtual void draw(const HDC hdc_) const = 0;
};


class Point : public AppObject {
	int _size = 0;
	COLORREF _color = RGB(0, 0, 0);

public:
	Point(int x_ = 0, int y_ = 0, int size_ = 5, COLORREF color_ = RGB(0, 0, 0)) : AppObject(x_, y_), _size(size_), _color(color_)
	{
		int hw = 5;
		if (size_ > hw) {
			hw = size_ * 1.1;
		}

		setHitBox({ _pos.x - hw, _pos.y - hw, _pos.x + hw, _pos.y + hw });
	}

	void draw(const HDC hdc_) const override {
		if (_size) {
			RECT r{ _pos.x - _size, _pos.y - _size, _pos.x + _size, _pos.y + _size };
			FillRect(hdc_, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		else {
			//Rectangle(hdc_, r.left, r.top, r.right, r.bottom);
			SetPixel(hdc_, _pos.x, _pos.y, _color);
		}
	}

	void setSize(int size_) { _size = size_; }


};

class Line : AppObject
{
	Point _pt0;
	Point _pt1;

	Line(int x0_, int y0_, int x1_, int y1_) : _pt0(x0_, y0_), _pt1(x1_, y1_)
	{

	}
};

