/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#if !defined(AFX_SYNTAXEXAMPLE_H__95642D27_FE87_4AD4_8404_9EB9599F46FA__INCLUDED_)
#define AFX_SYNTAXEXAMPLE_H__95642D27_FE87_4AD4_8404_9EB9599F46FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SyntaxExample.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSyntaxExample window

class CSyntaxExample : public CButton
{
// Construction
public:
	CSyntaxExample();

// Attributes
public:
	int tab_stop_;
	HFONT editor_font_;
	COLORREF rgb_background_;
	COLORREF rgb_text_;
	COLORREF rgb_instruction_;
	COLORREF rgb_directive_;
	COLORREF rgb_comment_;
	COLORREF rgb_number_;
	COLORREF rgb_string_;
	COLORREF rgb_selection_;
	bool vb_bold_[5];

// Operations
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT draw_item_struct);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSyntaxExample)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSyntaxExample();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSyntaxExample)
	afx_msg BOOL OnEraseBkgnd(CDC* dc);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNTAXEXAMPLE_H__95642D27_FE87_4AD4_8404_9EB9599F46FA__INCLUDED_)
