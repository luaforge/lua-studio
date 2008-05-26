#if !defined(__WATCHBAR_H__)
#define __WATCHBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "scbarg.h"
#include "DynamicHelp.h"


/////////////////////////////////////////////////////////////////////////////
// CWatchBar window


class CWatchBar : public CDynamicHelp // CSizingControlBarG
{
// Construction
public:
	CWatchBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatchBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWatchBar();

protected:
	CEdit	child_wnd_;
//	CFont	font_;

	// Generated message map functions
protected:
	//{{AFX_MSG(CWatchBar)
	afx_msg int OnCreate(LPCREATESTRUCT create_struct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(__WATCHBAR_H__)
