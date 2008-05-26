#include "stdafx.h"
#include "StackWnd.h"


StackWnd::StackWnd()
{}

StackWnd::~StackWnd()
{}


void StackWnd::Notify(int event, int data, const Lua* lua)
{
	if (event == Lua::NewLine)
	{
		if (lua->GetCallStack(stack_))
			ResetItems(stack_.size());
	}
}


extern void FormatName(const std::string& s, Lua::ValType type, std::string& out);
extern void FormatValue(const std::string& s, Lua::ValType type, std::string& out);


void StackWnd::GetDispInfo(size_t item, int column, std::string& buffer)
{
	if (item < stack_.size())
	{
		const Lua::StackFrame& e= stack_[item];

		switch (column)
		{
		case 0:	// src
			buffer = e.source;
			break;

		case 1:	// line
			{
				char buf[100];
				if (e.current_line > 0)
					_itoa(e.current_line, buf, 10);
				else
					strcpy(buf, "-");

				buffer = buf;
			}
			break;

		case 2:	// name
			buffer = e.name_what;
			break;

		case 3:	// type
			switch (e.type)
			{
			case Lua::StackFrame::Err:
				buffer = "Error";
				break;
			case Lua::StackFrame::LuaFun:
				buffer = "Lua";
				break;
			case Lua::StackFrame::MainChunk:
				buffer = "Main";
				break;
			case Lua::StackFrame::CFun:
				buffer = "C";
				break;
			case Lua::StackFrame::TailCall:
				buffer = "Tail Call";
				break;
			default:
				ASSERT(false);
				break;
			}
		}
	}
}


void StackWnd::CreateColumns(CListCtrl& ctrl)
{
	ctrl.InsertColumn(0, "File", LVCFMT_LEFT, 200);
	ctrl.InsertColumn(1, "Line", LVCFMT_LEFT, 40);
	ctrl.InsertColumn(2, "Name", LVCFMT_LEFT, 100);
	ctrl.InsertColumn(3, "What", LVCFMT_LEFT, 60);
}
