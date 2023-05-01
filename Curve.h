#pragma once
#include "Line.h"

class Curve : AppObject
{
public:
	Curve() { _type = Type::Curve; }
	Line lines[3]; // search for beize curve;

	
};

