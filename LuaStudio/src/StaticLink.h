////////////////////////////////////////////////////////////////
// 1998 Microsoft Systems Journal
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
//
// CStaticLink implements a static control that's a hyperlink
// to any file on your desktop or web. You can use it in dialog boxes
// to create hyperlinks to web sites. When clicked, opens the file/URL
//
#ifndef _STATLINK_H
#define _STATLINK_H

#include "HyperLink.h"

class CStaticLink : public CStatic
{
public:
	DECLARE_DYNAMIC(CStaticLink)
	CStaticLink(LPCTSTR text = NULL, BOOL delete_on_destroy= FALSE);
	~CStaticLink() { }

	// Use this if you want to subclass and also set different URL
	BOOL SubclassDlgItem(UINT id, CWnd* parent, LPCTSTR link= NULL)
	{
		link_ = link;
		return CStatic::SubclassDlgItem(id, parent);
	}

	// Hyperlink contains URL/filename. If NULL, I will use the window text.
	// (GetWindowText) to get the target.
	CHyperlink  link_;
	COLORREF    color_;

	// Default colors you can change
	// These are global, so they're the same for all links.
	static COLORREF g_colorUnvisited;
	static COLORREF g_colorVisited;

	// Cursor used when mouse is on a link--you can set, or
	// it will default to the standard hand with pointing finger.
	// This is global, so it's the same for all links.
	static HCURSOR   g_cursor_link;

	afx_msg HBRUSH CtlColor(CDC* dc, UINT ctl_color);

protected:
	CFont     font_;         // underline font for text control
	BOOL      delete_on_destroy_; // delete object when window destroyed?

	virtual void PostNcDestroy();

	// message handlers
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void  OnLButtonDown(UINT flags, CPoint point);
	afx_msg BOOL  OnSetCursor(CWnd* wnd, UINT hit_test, UINT message);
};

#endif _STATLINK_H
