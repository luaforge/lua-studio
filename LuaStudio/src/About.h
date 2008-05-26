/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "resource.h"
#include "StaticLink.h"


class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

// Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  CStatic	title_ctrl_;
  CString	version_string_;
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
protected:
  virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

	CStaticLink web_page_link_;
	CStaticLink lua_org_link_;
	CBitmap about_;
	CFont title_font_;

	afx_msg BOOL OnEraseBkgnd(CDC* dc);
	afx_msg HBRUSH OnCtlColor(CDC* dc, CWnd* wnd, UINT ctl_color);
};
