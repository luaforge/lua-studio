/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// EditBrkpDial.cpp : implementation file
//

#include "stdafx.h"
//#include "6502.h"
#include "EditBrkpDial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialEditBreakpoint dialog


CDialEditBreakpoint::CDialEditBreakpoint(Breakpoint bp, CWnd* parent /*=NULL*/)
  : CDialog(CDialEditBreakpoint::IDD, parent)
{
  //{{AFX_DATA_INIT(CDialEditBreakpoint)
  //}}AFX_DATA_INIT
  execute_ = (bp & BPT_EXEC) != 0;
  read_ = (bp & BPT_READ) != 0;
  write_ = (bp & BPT_WRITE) != 0;
  disabled_ = (bp & BPT_DISABLED) != 0;
}


void CDialEditBreakpoint::DoDataExchange(CDataExchange* DX)
{
  CDialog::DoDataExchange(DX);
  //{{AFX_DATA_MAP(CDialEditBreakpoint)
  DDX_Check(DX, IDC_EDIT_BP_DISABLED, disabled_);
  DDX_Check(DX, IDC_EDIT_BP_EXEC, execute_);
  DDX_Check(DX, IDC_EDIT_BP_READ, read_);
  DDX_Check(DX, IDC_EDIT_BP_WRITE, write_);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialEditBreakpoint, CDialog)
//{{AFX_MSG_MAP(CDialEditBreakpoint)
// NOTE: the ClassWizard will add message map macros here
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialEditBreakpoint message handlers

