#include "stdafx.h"
#include "GlobalVarsWnd.h"


GlobalVarsWnd::GlobalVarsWnd()
{}

GlobalVarsWnd::~GlobalVarsWnd()
{}


void GlobalVarsWnd::Notify(int event, int data, const Lua* lua)
{
	if (event == Lua::NewLine)
	{
		lua->GetGlobalVars(globals_, true);

		ResetItems(globals_.size());
	}
}


extern void FormatName(const std::string& s, Lua::ValType type, std::string& out);
extern void FormatValue(const std::string& s, Lua::ValType type, std::string& out);


void GlobalVarsWnd::GetDispInfo(size_t item, int column, std::string& buffer)
{
	if (item < globals_.size())
	{
		const Lua::Field& f= globals_[item];

		switch (column)
		{
		case 0:	// name
			FormatName(f.key.value, f.val.type, buffer);
			break;

		case 1:	// val
			FormatValue(f.val.value, f.val.type, buffer);
			break;

		case 2:	// type
			buffer = f.val.type_name;
			break;
		}
	}
}


void GlobalVarsWnd::CreateColumns(CListCtrl& ctrl)
{
	ctrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);
	ctrl.InsertColumn(1, "Value", LVCFMT_LEFT, 200);
//	ctrl.InsertColumn(2, "Type", LVCFMT_LEFT, 60);
}
