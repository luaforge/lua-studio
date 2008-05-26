#include "stdafx.h"
#include "LocalVarsWnd.h"


LocalVarsWnd::LocalVarsWnd()
{}

LocalVarsWnd::~LocalVarsWnd()
{}


void LocalVarsWnd::Notify(int event, int data, const Lua* lua)
{
	if (event == Lua::NewLine)
	{
		lua->GetLocalVars(vars_);
//		simulator->GetGlobalVars(globals_, true);

		ResetItems(vars_.size());
	}
}


extern void FormatName(const std::string& s, Lua::ValType type, std::string& out);
extern void FormatValue(const std::string& s, Lua::ValType type, std::string& out);


void LocalVarsWnd::GetDispInfo(size_t item, int column, std::string& buffer)
{
	if (item < vars_.size())
	{
		const Lua::Var& v= vars_[item];

		switch (column)
		{
		case 0:	// name
			FormatName(v.name, v.v.type, buffer);
			break;

		case 1:	// val
			FormatValue(v.v.value, v.v.type, buffer);
			break;

		case 2:	// type
			buffer = v.v.type_name;
			break;
		}
	}
}


void LocalVarsWnd::CreateColumns(CListCtrl& ctrl)
{
	ctrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);
	ctrl.InsertColumn(1, "Value", LVCFMT_LEFT, 200);
//	ctrl.InsertColumn(2, "Type", LVCFMT_LEFT, 60);
}
