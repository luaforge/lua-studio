/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// ChildFrm.cpp : implementation of the CChildFrame class

#include "stdafx.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{}

CChildFrame::~CChildFrame()
{}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::ActivateFrame(int cmd_show)
{
	if (cmd_show == -1)
	{
		if (CMDIFrameWnd* frame= GetMDIFrame())
		{
			BOOL maximized;
			CWnd* child= frame->MDIGetActive(&maximized);

			if (child == 0)
			{
				// if first MDI window is being activated, maximize it

				ModifyStyle(0, WS_MAXIMIZE);
			}
		}

	}

	CMDIChildWnd::ActivateFrame(cmd_show);
}
