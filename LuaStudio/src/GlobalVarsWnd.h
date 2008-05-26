#pragma once
#include "ListCtrlBar.h"
#include "Lua.h"


class GlobalVarsWnd : public ListCtrlBar
{
public:
	GlobalVarsWnd();

	virtual ~GlobalVarsWnd();

	void Notify(int event, int data, const Lua* lua);

private:
	virtual void GetDispInfo(size_t item, int column, std::string& buffer);
	virtual void CreateColumns(CListCtrl& ctrl);

	Lua::TableInfo globals_;
};
