/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#if !defined(AFX_DOCKBAREX_H__CCF8FACC_8FB1_4DCF_825E_9E754C796CB8__INCLUDED_)
#define AFX_DOCKBAREX_H__CCF8FACC_8FB1_4DCF_825E_9E754C796CB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DockBarEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDockBarEx window

class CDockBarEx : public CDockBar
{
// Construction
public:
	CDockBarEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockBarEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDockBarEx();
//	virtual CSize CalcFixedLayout(BOOL stretch, BOOL horz);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDockBarEx)
	afx_msg BOOL OnSetCursor(CWnd* wnd, UINT hit_test, UINT message);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSize(UINT type, int cx, int cy);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnExitSizeMove(WPARAM wParam, LPARAM lParam);

	CRect ResizeArea();
	bool resize_;
	CPoint start_;
	int start_width_;
	void ResizeBars(int width);
	bool resizing_;
	int delta_width_;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKBAREX_H__CCF8FACC_8FB1_4DCF_825E_9E754C796CB8__INCLUDED_)
