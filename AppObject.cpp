#include "AppObject.h"

const char* AppObject::typeAsString() const {
	return typeAsString(_type);
}


const char* AppObject::typeAsString(AppObjectType t) {
	using Type = AppObjectType;
	
	switch (t)
	{
	case Type::NA: { return "NA"; }
	case Type::AppObject: { return "AppObject"; }
	case Type::Point: { return "Point"; }
	case Type::Line: { return "Line"; }
	case Type::Rect: { return "Rect"; }
	case Type::Curve: { return "Curve"; }
	default: break;
	}
	assert(false);
	return "[ERR] Unknown Type";

}