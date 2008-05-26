////////////////////////////////////////////////////////////////
// PixieLib(TM) Copyright 1997 Paul DiLascia
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// CStaticLink implements a static control that's a hyperlink
// to any file on your desktop or web. You can use it in dialog boxes
// to create hyperlinks to web sites. When clicked, opens the file/URL
//
#include "StdAfx.h"
#include "StaticLink.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF CStaticLink::g_colorUnvisited = RGB(0,0,255);     // blue
COLORREF CStaticLink::g_colorVisited   = RGB(128,0,128);     // purple

HCURSOR CStaticLink::g_cursor_link = NULL;

IMPLEMENT_DYNAMIC(CStaticLink, CStatic)

BEGIN_MESSAGE_MAP(CStaticLink, CStatic)
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

///////////////////
// Constructor sets default colors = blue/purple.
// delete_on_destroy is used internally by PixieLib in CPixieDlg.
//
CStaticLink::CStaticLink(LPCTSTR text, BOOL delete_on_destroy)
{
	link_ = text;                // link text (NULL ==> window text)
	color_ = g_colorUnvisited;       // not visited yet
	delete_on_destroy_ = delete_on_destroy;  // delete object with window?
}

//////////////////
// Normally,  a static control does not get mouse events unless it has
// SS_NOTIFY. This achieves the same effect as SS_NOTIFY, but it's fewer
// lines of code and more reliable than turning on SS_NOTIFY in OnCtlColor
// because Windows doesn't send WM_CTLCOLOR to bitmap static controls.
//
LRESULT CStaticLink::OnNcHitTest(CPoint point)
{
	return HTCLIENT;
}

//////////////////
// Handle reflected WM_CTLCOLOR to set custom control color.
// For a text control, use visited/unvisited colors and underline font.
// For non-text controls, do nothing. Also ensures SS_NOTIFY is on.
//
HBRUSH CStaticLink::CtlColor(CDC* dc, UINT ctl_color)
{
	ASSERT(ctl_color == CTLCOLOR_STATIC);
	DWORD dwStyle = GetStyle();
  
	HBRUSH hbr = NULL;
	if ((dwStyle & 0xFF) <= SS_RIGHT)
	{
		// this is a text control: set up font and colors
		if (!(HFONT)font_)
		{
			// first time init: create font
			LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfUnderline = TRUE;
			font_.CreateFontIndirect(&lf);
		}

		// use underline font and visited/unvisited colors
		dc->SelectObject(&font_);
		dc->SetTextColor(color_);
		dc->SetBkMode(TRANSPARENT);

		// return hollow brush to preserve parent background color
		hbr = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	}
	return hbr;
}

/////////////////
// Handle mouse click: navigate link
//
void CStaticLink::OnLButtonDown(UINT flags, CPoint point)
{
	if (link_.IsEmpty()) {   // if URL/filename not set..
		GetWindowText(link_);  // ..get it from window text
		if (link_.IsEmpty())
			return;
	}

	// Call ShellExecute to run the file.
	// For an URL, this means opening it in the browser.
	//
	HINSTANCE h = link_.Navigate();
	if ((UINT)h > 32) {            // success!
		color_ = g_colorVisited;      // change color
		Invalidate();              // repaint 
	}
	else
	{
		MessageBeep(0);   // unable to execute file!
		TRACE(_T("*** WARNING: CStaticLink: unable to navigate link %s\n"), (LPCTSTR)link_);
	}
}

//////////////////
// Set "hand" cursor to cue user that this is a link.
//
BOOL CStaticLink::OnSetCursor(CWnd* wnd, UINT hit_test, UINT message)
{
	if (g_cursor_link == NULL)
	{
		g_cursor_link = AfxGetApp()->LoadCursor(IDC_LINK);
	}
	if (g_cursor_link)
	{
		::SetCursor(g_cursor_link);
		return TRUE;
	}

	return FALSE;
}

//////////////////
// Normally, a control class is not destoyed when the window is;
// however, CPixieDlg creates static controls with "new" instead of
// as class members, so it's convenient to allow the option of destroying
// object with window. In applications where you want the object to be
// destoyed along with the window, you can call constructor with
// delete_on_destroy=TRUE.
//
void CStaticLink::PostNcDestroy()
{
	if (delete_on_destroy_)
		delete this;
}
