#pragma once
#include "ListCtrlBar.h"
#include "Lua.h"


class LocalVarsWnd : public ListCtrlBar
{
public:
	LocalVarsWnd();

	virtual ~LocalVarsWnd();

	void Notify(int event, int data, const Lua* lua);

private:
	virtual void GetDispInfo(size_t item, int column, std::string& buffer);
	virtual void CreateColumns(CListCtrl& ctrl);

	std::vector<Lua::Var> vars_;
};
