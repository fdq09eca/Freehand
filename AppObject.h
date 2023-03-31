#pragma once
#include "Util.h"



enum class AppObjectType {
	NA = 0,
	AppObject,
	Point,
	Line,
};

class AppObject : NonCopyable {

public:
	using Type = AppObjectType;

protected:

	Type _type = Type::AppObject;
	bool _isSelected : 1;
	bool _isHovered : 1;
	
	void reset() {
		_isSelected = false;
		_isHovered = false;
	}



public:
	AppObject() { reset(); }
	virtual ~AppObject() { }
	virtual void draw(HDC hdc_) const { };
	virtual bool onMouseEvent(const MouseEvent& e) { return false; }
	Type type() const { return _type; }





};


