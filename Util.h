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
	Left = 1 << 0,    // 1, 0001
	Middle = 1 << 1, // 2,  0010 
	Right = 1 << 2, // 4,   0100
	
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
	Button buttonState = Button::NA; // 0101
	
	bool isUp()	  const { return eventType == Type::Up; }
	bool isDown() const { return eventType == Type::Down; }
	bool isMove() const { return eventType == Type::Move; }
	
	bool isLButton() const { return button == Button::Left; }
	bool isMButton() const { return button == Button::Middle; }
	bool isRButton() const { return button == Button::Right; }

	
};



