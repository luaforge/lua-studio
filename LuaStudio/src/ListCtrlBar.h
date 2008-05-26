#pragma once

#include "scbarcf.h"
//#include "Lua.h"


class ListCtrlBar : public CSizingControlBarCF
{
public:
	ListCtrlBar();

	virtual ~ListCtrlBar();

	//void Notify(int event, int data, const Lua* lua);

protected:
	void ResetItems(size_t count);

private:
	afx_msg int OnCreate(LPCREATESTRUCT cs);
	afx_msg void OnGetDispInfo(NMHDR* nmhdr, LRESULT* result);

	DECLARE_MESSAGE_MAP()

private:
	CListCtrl list_;

	virtual void CreateColumns(CListCtrl& ctrl) = 0;
	virtual void GetDispInfo(size_t item, int column, std::string& buffer) = 0;
};
