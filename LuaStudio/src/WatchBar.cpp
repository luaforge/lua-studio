// mybar.cpp : implementation file
//

#include "stdafx.h"
#include "WatchBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatchBar

CWatchBar::CWatchBar()
{
}

CWatchBar::~CWatchBar()
{
}


BEGIN_MESSAGE_MAP(CWatchBar, CDynamicHelp)
	//{{AFX_MSG_MAP(CWatchBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWatchBar message handlers

int CWatchBar::OnCreate(LPCREATESTRUCT create_struct) 
{
	if (CDynamicHelp::OnCreate(create_struct) == -1)
		return -1;

//	SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

	if (!child_wnd_.Create(WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_WANTRETURN|ES_AUTOVSCROLL,
		CRect(0,0,0,0), this, 123))
		return -1;

	child_wnd_.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	//if (!font_.CreateStockObject(DEFAULT_GUI_FONT))
	//	if (!font_.CreatePointFont(80, "MS Sans Serif"))
	//		return -1;

	//child_wnd_.SetFont(&font_);

	return 0;
}
