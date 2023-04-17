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

class BackBuffer : NonCopyable {
	HBITMAP _bitmap;
	HBRUSH _bgColor = NULL;
	HDC _dc = NULL;
	int _w = 0;
	int _h = 0;

public:

	~BackBuffer(){ destroy(); }
	
	void create(HWND hWnd_) {
		destroy();
		HDC wndDC = GetDC(hWnd_);	
		_dc = CreateCompatibleDC(wndDC);
		
		RECT rc;
		GetClientRect(hWnd_, &rc);
		_h = rc.bottom - rc.top;
		_w = rc.right - rc.left;
		_bitmap = CreateCompatibleBitmap(_dc, _w, _h);
		SelectObject(_dc, _bitmap);
		_bgColor = (HBRUSH)GetStockObject(WHITE_BRUSH);
		
		ReleaseDC(hWnd_, wndDC);
	}

	HDC dc() const { return _dc; }

	void destroy() {
		if (_dc) {
			DeleteDC(_dc);
			_dc = NULL;
		}
		
		if (_bitmap) {
			DeleteObject(_bitmap);
			_bitmap = NULL;
		}
	}

	void clear() { 
		RECT rc{ 0, 0, _w, _h };
		FillRect(_dc, &rc, _bgColor);
	}

	void draw(HDC hdc, int x = 0, int y = 0)  {
		BitBlt(hdc, x, y, _w, _h, _dc, 0, 0, SRCCOPY);
	}
};