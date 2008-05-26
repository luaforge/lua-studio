#include "stdafx.h"
#include "ListCtrlBar.h"


ListCtrlBar::ListCtrlBar()
{}

ListCtrlBar::~ListCtrlBar()
{}


const int LIST_ID= 1000;

BEGIN_MESSAGE_MAP(ListCtrlBar, CSizingControlBarCF)
	ON_WM_CREATE()
	ON_NOTIFY(LVN_GETDISPINFO, LIST_ID, OnGetDispInfo)
  //ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
END_MESSAGE_MAP()


int ListCtrlBar::OnCreate(LPCREATESTRUCT cs)
{
	if (CSizingControlBarCF::OnCreate(cs) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

	if (!list_.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_OWNERDATA, CRect(0,0,0,0), this, LIST_ID))
		return -1;

	list_.SetExtendedStyle(LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);

	CreateColumns(list_);

	//list_.InsertColumn(0, "Index", LVCFMT_LEFT, 30);
	//list_.InsertColumn(1, "Value", LVCFMT_LEFT, 130);
	//list_.InsertColumn(2, "Type", LVCFMT_LEFT, 60);

	//if (!child_wnd_.Create(WS_CHILD | WS_VISIBLE, //	ES_MULTILINE|ES_WANTRETURN|ES_AUTOVSCROLL,
	//	CRect(0,0,0,0), this, 123))
	//	return -1;

	//child_wnd_.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

//	child_wnd_.SetFont(&font_);

	return 0;
}


//void ListCtrlBar::Notify(int event, int data, const Lua* lua)
//{
//	if (event == Lua::NewLine)
//	{
//		lua->GetValueStack(stack_);
//		list_.SetItemCount(static_cast<int>(stack_.size()));
//	}
//}


//extern void FormatName(const std::string& s, Lua::ValType type, std::string& out);
//extern void FormatValue(const std::string& s, Lua::ValType type, std::string& out);


void ListCtrlBar::OnGetDispInfo(NMHDR* nmhdr, LRESULT* result)
{
	LV_DISPINFO* disp_info = reinterpret_cast<LV_DISPINFO*>(nmhdr);

	static std::string buffer;

	if (disp_info->item.mask & LVIF_TEXT)
	{
		size_t index= disp_info->item.iItem;
		buffer.clear();
		GetDispInfo(index, disp_info->item.iSubItem, buffer);
		disp_info->item.pszText = const_cast<char*>(buffer.c_str());
	}
}


void ListCtrlBar::ResetItems(size_t count)
{
	list_.SetItemCount(static_cast<int>(count));
}
