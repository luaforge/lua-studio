/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// DockBarEx.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DockBarEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockBarEx

CDockBarEx::CDockBarEx()
{
	resize_ = false;
	resizing_ = false;
	delta_width_ = 0;
}

CDockBarEx::~CDockBarEx()
{}


BEGIN_MESSAGE_MAP(CDockBarEx, CDockBar)
	//{{AFX_MSG_MAP(CDockBarEx)
	ON_WM_SETCURSOR()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	ON_MESSAGE(WM_ENTERSIZEMOVE, OnEnterSizeMove)
	ON_MESSAGE(WM_EXITSIZEMOVE, OnExitSizeMove)
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDockBarEx message handlers

/*CSize CDockBarEx::CalcFixedLayout(BOOL stretch, BOOL horz)
{
	CSize raw_size= CDockBar::CalcFixedLayout(stretch, horz);
	return GetDockedCount() > 0 ? raw_size + CSize(8, 0) : raw_size;
}*/


BOOL CDockBarEx::OnSetCursor(CWnd* wnd, UINT hit_test, UINT message)
{
	if (GetDockedVisibleCount() == 0)
		return CDockBar::OnSetCursor(wnd, hit_test, message);

	switch (hit_test)
	{
	case HTLEFT:
	case HTRIGHT:
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		return true;
/*	case HTTOP:
	case HTBOTTOM:
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
		return true; */
	}

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return true;

//	return CDockBar::OnSetCursor(wnd, hit_test, message);
}


const int MARGIN= 5;

// Return screen coord rect of dockbar resizing area
//
CRect CDockBarEx::ResizeArea()
{
	CRect rect;
	GetWindowRect(rect);

	switch (GetDlgCtrlID())
	{
	case AFX_IDW_DOCKBAR_LEFT:
		rect.left = rect.right - MARGIN;
		break;
	case AFX_IDW_DOCKBAR_RIGHT:
		rect.right = rect.left + MARGIN;
		break;
	}

	return rect;
}

// Resize docked bars to requested width
//
void CDockBarEx::ResizeBars(int width)
{
	for (int i = 0; i < m_arrBars.GetSize(); i++)
	{
		if (CControlBar* bar= GetDockedControlBar(i))
			bar->CalcDynamicLayout(width, LM_HORZ | LM_HORZDOCK | 0x8000);
	}

	if (CFrameWnd* frame= static_cast<CFrameWnd*>(GetParent()))
	{
		frame->RecalcLayout();
		for (int i = 0; i < m_arrBars.GetSize(); i++)
		{
			if (CControlBar* bar= GetDockedControlBar(i))
			{
				bar->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ALLCHILDREN);
			}
		}
		frame->UpdateWindow();
	}
}


BOOL CDockBarEx::PreCreateWindow(CREATESTRUCT& cs)
{
	// turn on resizing edge
	if (cs.style & CBRS_ALIGN_LEFT)
		m_cyBottomBorder = MARGIN;
	else if (cs.style & CBRS_ALIGN_RIGHT)
		m_cyTopBorder = MARGIN;
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CDockBar::PreCreateWindow(cs);
}


// Report back resizing edge position
//
LRESULT CDockBarEx::OnNcHitTest(CPoint pos)
{
//	CPoint pos(0, 0);
//	::GetCursorPos(&pos);

	if (ResizeArea().PtInRect(pos))
	{
		switch (GetDlgCtrlID())
		{
		case AFX_IDW_DOCKBAR_LEFT:
			return HTRIGHT;
		case AFX_IDW_DOCKBAR_RIGHT:
			return HTLEFT;
		case AFX_IDW_DOCKBAR_TOP:
			return HTBOTTOM;
		case AFX_IDW_DOCKBAR_BOTTOM:
			return HTTOP;
		}
	}

	return CDockBar::OnNcHitTest(pos);
}

// Resizing
//
void CDockBarEx::OnSize(UINT type, int cx, int cy)
{
	CDockBar::OnSize(type, cx, cy);

	if (resizing_)
	{
		CRect rect;
		GetClientRect(rect);
		resizing_ = false;
		ResizeBars(rect.Width() + delta_width_);
		resizing_ = true;
	}
}

// Entering user initiated resizing
//
LRESULT CDockBarEx::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	delta_width_ = 4;
	// Calc difference between dockbar client area and docked bar width
/*	for (int i = 0; i < m_arrBars.GetSize(); i++)
	{
		if (CControlBar* bar= GetDockedControlBar(i))
			if (bar->IsWindowVisible())
			{
				CRect rect;
				GetClientRect(rect);
				delta_width_ = rect.Width() - CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK).cx;
				break;
			}
	}*/
	resizing_ = true;
	return Default();
}

LRESULT CDockBarEx::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	resizing_ = false;
	return Default();
}

// Suppress z-order changing (important for RecalcLayout)
//
void CDockBarEx::OnWindowPosChanging(WINDOWPOS FAR* wnd_pos)
{
	if (resizing_)
		wnd_pos->flags |= SWP_NOZORDER;
	CDockBar::OnWindowPosChanging(wnd_pos);
}
