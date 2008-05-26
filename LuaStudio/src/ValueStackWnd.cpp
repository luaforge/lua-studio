#include "stdafx.h"
#include "ValueStackWnd.h"


ValueStackWnd::ValueStackWnd()
{}

ValueStackWnd::~ValueStackWnd()
{}


void ValueStackWnd::Notify(int event, int data, const Lua* lua)
{
	if (event == Lua::NewLine)
	{
		lua->GetValueStack(stack_);

		ResetItems(stack_.size());
	}
}

//extern void FormatName(const std::string& s, Lua::ValType type, std::string& out);
extern void FormatValue(const std::string& s, Lua::ValType type, std::string& out);


void FormatNumber(int n, std::string& buffer)
{
	char buf[100];
	_itot(n, buf, 10);
	buffer = buf;
}


void ValueStackWnd::GetDispInfo(size_t item, int column, std::string& buffer)
{
	if (item < stack_.size())
	{
		const Lua::Value& v= stack_[item];

		switch (column)
		{
		case 0:	// index
			FormatNumber(stack_.size() - item, buffer);
			break;

		case 1:	// val
			FormatValue(v.value, v.type, buffer);
			break;

		case 2:	// type
			buffer = v.type_name;
			break;
		}
	}
}


void ValueStackWnd::CreateColumns(CListCtrl& ctrl)
{
	ctrl.InsertColumn(0, "Index", LVCFMT_LEFT, 30);
	ctrl.InsertColumn(1, "Value", LVCFMT_LEFT, 130);
	ctrl.InsertColumn(2, "Type", LVCFMT_LEFT, 60);
}
