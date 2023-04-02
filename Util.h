#pragma once
#include <stdio.h>
#include <Windows.h>
#include "windowsx.h"
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>

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
	Left = 1 << 0,    // 1, 0001
	Middle = 1 << 1,  // 2, 0010 
	Right = 1 << 2,   // 4, 0100
	
};



enum class MouseEventType {
	None = 0,
	Up,
	Down,
	Move,
};

class MouseEvent {
public:
	using Type = MouseEventType;
	using Button = MouseButton;
	POINT pos;
	Type eventType = Type::None;
	Button button = Button::NA;
	Button buttonState = Button::NA;
	
	bool isUp()	  const { return eventType == Type::Up; }
	bool isDown() const { return eventType == Type::Down; }
	bool isMove() const { return eventType == Type::Move; }
	
	bool isLButton() const { return button == Button::Left; }
	bool isMButton() const { return button == Button::Middle; }
	bool isRButton() const { return button == Button::Right; }
};

class Pixel {
	int8_t _r, _g, _b, _a = 0;

public:
	void set(int r_, int g_, int b_) { _r = r_; _g = g_; _b = b_; }
	const int8_t& r() const { return _r; }
	const int8_t& g() const { return _g; }
	const int8_t& b() const { return _b; }

};


class BitMap : NonCopyable{


	HBITMAP _bmp = NULL;
	std::vector<Pixel> pixels;
	int _w = 0;
	int _h = 0;

	
public:
	friend class BackBuffer;
	void create(int w,  int h) {
		_w = w; _h = h;
		pixels.resize(_w * _h);
		_bmp = CreateBitmap(_w, _h, 1, sizeof(Pixel), pixels.data());
		assert(_bmp != NULL);
	}
 
	void destroy() {
		if (_bmp) {
			DeleteObject(_bmp);
			_bmp = NULL;
			_w = 0; _h = 0;
			pixels.clear();
		}
	}

	HBITMAP hBitMap() const { return _bmp; }
	int width() const { return _w; };
	int height() const { return _h; };

	void draw(HDC hdc, int x = 0, int y = 0) const {
		if (!hdc || !_bmp) return;
		HDC _srcDC = CreateCompatibleDC(hdc);
		SelectObject(_srcDC, _bmp);
		BitBlt(hdc, x, y, _w, _h, _srcDC, 0, 0, SRCCOPY);
		DeleteDC(_srcDC);
	}
};



class BackBuffer :NonCopyable {
	HBITMAP _bmp = NULL;
	HDC _dc = NULL;
	int _w = 0;
	int _h = 0;

public:
	void create(HWND hWnd) {
		RECT rc;
		GetClientRect(hWnd, &rc);
		_w = rc.right - rc.left;
		_h = rc.bottom - rc.top;

		HDC wndDC = GetDC(hWnd);
		
		_dc = CreateCompatibleDC(wndDC);
		_bmp = CreateCompatibleBitmap(_dc, _w, _h);
		SelectObject(_dc, _bmp);
		auto brush = (HBRUSH)GetStockObject(WHITE_BRUSH);
		FillRect(_dc, &rc, brush);
		
		ReleaseDC(hWnd, wndDC);
	}
	~BackBuffer() { destroy(); }
	
	HDC dc() const { return _dc; }
	 
	void destroy() {
		if (_bmp) { DeleteObject(_bmp); }
		if (_dc) { DeleteDC(_dc); }
	}

	void draw(HDC hdc, int x = 0, int y = 0) const {
		if (!hdc || !_dc || !_bmp) return;
		BitBlt(hdc, x, y, _w, _h, _dc, 0, 0, SRCCOPY);
	}
};

class MyBackBuffer {
	BitMap _bitmap;
	HDC _dc;
public:
	void create(HWND hWnd_) {

		HDC wndDC = GetDC(hWnd_);
		_dc = CreateCompatibleDC(wndDC);
		ReleaseDC(hWnd_, wndDC);
		RECT rc;
		GetClientRect(hWnd_, &rc);
		_bitmap.create(rc.right - rc.left, rc.bottom - rc.top);
		SelectObject(_dc, _bitmap.hBitMap());
		
		
	}

	HDC dc() const { return _dc; }

	void destroy() {
		DeleteDC(_dc);
		_bitmap.destroy();
	}

	void draw(HDC hdc, int x = 0, int y = 0) const {
		BitBlt(hdc, x, y, _bitmap.width(), _bitmap.height(), _dc, 0, 0, SRCCOPY);
	}



};