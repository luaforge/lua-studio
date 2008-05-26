#pragma once
#include "stdafx.h"
#include "Lua.h"
#include <sstream>


extern void FormatName(const std::string& s, Lua::ValType type, std::string& out)
{
	std::ostringstream ost;
	ost << s;
	switch (type)
	{
	case Lua::Function:
		ost << "()";
		break;

	//case Lua::String:
	//	ost << "$";
	//	break;

	case Lua::Table:
		ost << " { }";
		break;

	//case Lua::LightUserData:
	//	ost << "()";
	//	break;

	default:
		break;
	}

//	enum ValType { None= -1, Nil, Bool, LightUserData, Number, String, Table, Function, UserData, Thread };

	out = ost.str();
}


extern void FormatValue(const std::string& s, Lua::ValType type, std::string& out)
{
	std::ostringstream ost;

	switch (type)
	{
	case Lua::String:
		ost << '"' << s << '"';
		break;

	case Lua::Nil:
		ost << "nil";
		break;

	case Lua::None:
		ost << '?';
		break;

	case Lua::Function:
		ost << "fn " << s;
		break;

	default:
		out = s;
		return;
	}

	out = ost.str();
}
