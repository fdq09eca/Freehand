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

public:
	int id = 0;
	
	AppObject() { 
		static int next_id = 0;
		id = next_id;
		next_id++;
	}
	
	virtual ~AppObject() { }
	virtual void draw(HDC hdc_) const { };
	virtual bool onMouseEvent(const MouseEvent& e) { return false; }
	Type type() const { return _type; }
	
	const char* typeAsString() const {
		switch (_type)
		{
			case Type::NA:			{ return "NA"; }
			case Type::AppObject:	{ return "AppObject"; }
			case Type::Point:		{ return "Point"; }
			case Type::Line:		{ return "Line"; }
			case Type::Rect:		{ return "Rect"; }
			case Type::Curve:		{ return "Curve"; }
			default: break;
		}
		assert(false);
		return "[ERR] Unknown Type";
	}

};


