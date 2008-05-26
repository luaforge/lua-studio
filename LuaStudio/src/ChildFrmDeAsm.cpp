/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// ChildFrm.cpp : implementation of the CChildFrameDeAsm class
//

#include "stdafx.h"
#include "ChildFrmDeAsm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrameDeAsm

IMPLEMENT_DYNCREATE(CChildFrameDeAsm, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrameDeAsm, CMDIChildWnd)
  //{{AFX_MSG_MAP(CChildFrameDeAsm)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrameDeAsm construction/destruction

CChildFrameDeAsm::CChildFrameDeAsm()
{
  // TODO: add member initialization code here
	
}

CChildFrameDeAsm::~CChildFrameDeAsm()
{
}

BOOL CChildFrameDeAsm::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrameDeAsm diagnostics

#ifdef _DEBUG
void CChildFrameDeAsm::AssertValid() const
{
  CMDIChildWnd::AssertValid();
}

void CChildFrameDeAsm::Dump(CDumpContext& dc) const
{
  CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrameDeAsm message handlers

BOOL CChildFrameDeAsm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* context) 
{
	return CMDIChildWnd::OnCreateClient(lpcs, context);
}
