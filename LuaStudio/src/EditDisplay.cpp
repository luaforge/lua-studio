/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// EditDisplay.cpp : implementation file
//

#include "StdAfx.h"
//#include "6502.h"
//#include "EditDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDisplay

CEditDisplay::CEditDisplay() : view_(NULL)
{
}

CEditDisplay::~CEditDisplay()
{
}


BEGIN_MESSAGE_MAP(CEditDisplay, CEdit)
  //{{AFX_MSG_MAP(CEditDisplay)
  ON_WM_PAINT()
  ON_WM_CHAR()
  ON_WM_KEYUP()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CEditDisplay::Subclass(CSrc6502View *view)
{
  view_ = view;
  SubclassWindow(view->GetEditCtrl().m_hWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CEditDisplay message handlers

void CEditDisplay::OnPaint() 
{
//  CPaintDC dc(this); // device context for painting
  
  // TODO: Add your message handler code here
  
  // Do not call CEdit::OnPaint() for painting messages
}

void CEditDisplay::OnChar(UINT chr, UINT rep_cnt, UINT flags) 
{
  // TODO: Add your message handler code here and/or call default
  
//  CEdit::OnChar(chr, rep_cnt, flags);
}

void CEditDisplay::OnKeyUp(UINT chr, UINT rep_cnt, UINT flags) 
{
  // TODO: Add your message handler code here and/or call default
  
//  CEdit::OnKeyUp(chr, rep_cnt, flags);
}

//-----------------------------------------------------------------------------

