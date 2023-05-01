#pragma once
#include "Util.h"

enum class AppObjectType {
	NA = 0,
	AppObject,
	Point,
	Line,
	Rect,
	Curve,
	/*Circle,*/
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
	int id = 0;
	
	AppObject() { 
		static int next_id = 0;
		id = next_id;
		next_id++;
		reset(); 
	}
	
	virtual ~AppObject() { }
	virtual void draw(HDC hdc_) const { };
	virtual bool onMouseEvent(const MouseEvent& e) { return false; }
	Type type() const { return _type; }
	
	const char* typeAsString() const {
		switch (_type)
		{
			case Type::NA: { return "NA"; }
			case Type::Line: { return "Line"; }
			case Type::Rect: { return "Rect"; }
			case Type::Curve: { return "Curve"; }
			case Type::AppObject: { return "AppObject"; }
			default: break;
		}
		assert(false);
		return "[ERR] Unknown Type";
	}

};


