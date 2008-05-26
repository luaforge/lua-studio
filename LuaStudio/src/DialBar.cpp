/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "StdAfx.h"
#include "DialBar.h"
#include "AFXPRIV.H"


BEGIN_MESSAGE_MAP(CDialBar, CDialogBar)
	//{{AFX_MSG_MAP(CDialBar)
	ON_WM_GETMINMAXINFO()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


IMPLEMENT_DYNAMIC(CDialBar, CDialogBar)


CDialBar::CDialBar() : last_size_(50,50)
{
}


CDialBar::~CDialBar()
{
}


void CDialBar::OnGetMinMaxInfo(MINMAXINFO *MMI) 
{
  CDialogBar::OnGetMinMaxInfo(MMI);

  MMI->max_size = CPoint(200,600);
  MMI->max_position = CPoint(20,20);
  MMI->max_track_size = CPoint(200,600);
  MMI->ptMinTrackSize = CPoint(100,100);
}


CSize CDialBar::CalcDynamicLayout(int length, DWORD mode)
{
//  TRACE2("length = %d \tmode = %x\n", length, (int)mode);

  if ((length == -1) && !(mode & LM_MRUWIDTH) && !(mode & LM_COMMIT) &&
    ((mode & LM_HORZDOCK) || (mode & LM_VERTDOCK)))
  {
    return CalcFixedLayout(mode & LM_STRETCH, mode & LM_HORZDOCK);
  }
  return CalcLayout(length,mode);
}


CSize CDialBar::CalcLayout(int length, DWORD mode)
{
  if (mode & LM_HORZDOCK)
    return last_size_;
/*  {
    CRect rect;
    AfxGetMainWnd()->GetClientRect(rect);
    return CSize( rect.Width(), last_size_.cy );
  }*/
//    return last_size_;
//    return CSize( GetSystemMetrics(SM_CXSCREEN), last_size_.cy );
  else if (mode & LM_VERTDOCK)
    return last_size_;
/*  {
    CRect rect;
    AfxGetMainWnd()->GetClientRect(rect);
    return CSize( last_size_.cx, rect.Height() );
  }*/
//    return last_size_;
//    return CSize( last_size_.cx, GetSystemMetrics(SM_CYSCREEN) );
  else if (length!=-1 && !(mode & LM_MRUWIDTH) && !(mode & LM_COMMIT))
  {
    length &= ~0xF;
    if (length < 50)
      length = 50;

    if (mode & LM_LENGTHY)
      last_size_.cy = length;
    else
      last_size_.cx = length;
  }

  return last_size_;
}


CSize CDialBar::CalcFixedLayout(bool stretch, bool horz)
{
  return last_size_;
/*
  DWORD mode = stretch ? LM_STRETCH : 0;
  mode |= horz ? LM_HORZ : 0;

  return CalcLayout(-1,mode);
*/
/*
  CRect rect;
  GetWindowRect(rect);
  CSize size(rect.Size());
  if (size.cx == 0)
    size.cx = 50;
  if (size.cy == 0)
    size.cy = 50;
  if (stretch)	   // if not docked stretch to fit
    return CSize(horz ? 32767 : size.cx, horz ? size.cy : 32767);
  else
    return size;
*/
}

bool CDialBar::Create(CWnd* parent_wnd, UINT id_template, UINT style, UINT id)
{
  bool ret= CDialogBar::Create(parent_wnd, id_template, style, id);

  if (!ret)
    return false;

  CString title;
  if (title.LoadString(id_template))
    SetWindowText(title);

  return true;
}

// style &= ~MFS_4THICKFRAME;

void CDialBar::OnLButtonDown(UINT flags, CPoint point)
{
  CWnd *wnd= GetParent();
  if (wnd && (wnd=wnd->GetParent()))
    wnd->ModifyStyle(MFS_4THICKFRAME,MFS_THICKFRAME);

  CDialogBar::OnLButtonDown(flags, point);
}
