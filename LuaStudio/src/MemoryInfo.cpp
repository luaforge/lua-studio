/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// MemoryInfo.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MemoryInfo.h"
#include "ZeroPageView.h"
#include "StackView.h"
#include "Broadcast.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//CRect CMemoryInfo::wnd_rect_;
//bool CMemoryInfo::hidden_;

//-----------------------------------------------------------------------------
// Rejestracja klasy okien

bool CMemoryInfo::registered_= FALSE;
CString CMemoryInfo::class_;

void CMemoryInfo::RegisterWndClass()
{
  ASSERT(!registered_);
  if (registered_)
    return;
  class_ = AfxRegisterWndClass(CS_VREDRAW|CS_HREDRAW/*CS_DBLCLKS*/,::LoadCursor(NULL,IDC_ARROW),0,
    AfxGetApp()->LoadIcon(IDI_MEMORY_INFO));
  registered_ = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMemoryInfo

IMPLEMENT_DYNCREATE(CMemoryInfo, CMiniFrameWnd)


void CMemoryInfo::init()
{
  if (!registered_)
    RegisterWndClass();
  doc_.auto_delete_ = FALSE;
}


CMemoryInfo::CMemoryInfo()
{
  m_hWnd = 0;
  init();
  hidden_ = false;
}

CMemoryInfo::~CMemoryInfo()
{}


//-----------------------------------------------------------------------------
// Nowe okno

bool CMemoryInfo::Create(COutputMem *mem, UINT16 addr, ViewType view)
{
  mem_ = mem;
  addr_ = addr;

  CString title;
  CCreateContext ctx;
  if (view == VIEW_MEMORY)
  {
    ctx.m_pNewViewClass = RUNTIME_CLASS(CMemoryView);
    title.LoadString(IDS_MEMORY_TITLE);
  }
  else if (view == VIEW_ZEROPAGE)
  {
    ctx.m_pNewViewClass = RUNTIME_CLASS(CZeroPageView);
    title.LoadString(IDS_ZMEMORY_TITLE);
  }
  else if (view == VIEW_STACK)
  {
    ctx.m_pNewViewClass = RUNTIME_CLASS(CStackView);
    title.LoadString(IDS_STACK);
  }
  else
  { ASSERT(false); }

  ctx.m_pCurrentDoc = &doc_;	// dokument
  ctx.m_pNewDocTemplate = NULL;	// template
  ctx.m_pLastView = NULL;	// lastView
  ctx.m_pCurrentFrame = this;	// current frame

  if (!CMiniFrameWnd::Create(class_, title,
    WS_POPUP | WS_CAPTION | WS_SYSMENU | MFS_THICKFRAME | MFS_SYNCACTIVE,
    wnd_rect_, AfxGetMainWnd(), 0))
    return FALSE;

  if (!CreateView(&ctx))
  {
//    delete this;
    return FALSE;
  }
  RecalcLayout();
  doc_.SetData(mem_, addr_);
  InitialUpdateFrame(&doc_, FALSE);
  return TRUE;
}

//-----------------------------------------------------------------------------

#include <AFXPRIV.H>

BEGIN_MESSAGE_MAP(CMemoryInfo, CMiniFrameWnd)
  //{{AFX_MSG_MAP(CMemoryInfo)
  ON_WM_DESTROY()
  ON_WM_SHOWWINDOW()
  ON_WM_CLOSE()
  //}}AFX_MSG_MAP
  ON_MESSAGE(CBroadcast::WM_USER_PROG_MEM_CHANGED, OnChangeCode)
  ON_MESSAGE(CBroadcast::WM_USER_START_DEBUGGER, OnStartDebug)
  ON_MESSAGE(CBroadcast::WM_USER_EXIT_DEBUGGER, OnExitDebug)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryInfo message handlers


void CMemoryInfo::PostNcDestroy() 
{
// CMiniFrameWnd::PostNcDestroy();
}


void CMemoryInfo::OnDestroy() 
{
  GetWindowRect(wnd_rect_);
  CMiniFrameWnd::OnDestroy();
}

//-----------------------------------------------------------------------------

afx_msg LRESULT CMemoryInfo::OnChangeCode(WPARAM wParam, LPARAM lParam)
{
  if (lParam == -1)
    SendMessage(WM_CLOSE);		// nie ma kodu - zamkniêcie okna
  else
    InvalidateRect(NULL);		// przerysowanie ca³ego okna
  return 0;
}

//=============================================================================

afx_msg LRESULT CMemoryInfo::OnStartDebug(WPARAM /*wParam*/, LPARAM /* lParam */)
{

  if (!hidden_)		// okno by³o widoczne?
    if (m_hWnd)
      ShowWindow(SW_NORMAL);
//    else
//      Create();

  return 1;
}


afx_msg LRESULT CMemoryInfo::OnExitDebug(WPARAM /*wParam*/, LPARAM /* lParam */)
{

  if (m_hWnd && (GetStyle() & WS_VISIBLE))	// okno aktualnie wyœwietlone?
  {
    hidden_ = FALSE;				// info - okno by³o wyœwietlane
    ShowWindow(SW_HIDE);			// ukrycie okna
  }
  else
    hidden_ = TRUE;				// info - okno by³o ukryte

  return 1;
}

//=============================================================================


void CMemoryInfo::OnShowWindow(BOOL show, UINT status)
{
  CMiniFrameWnd::OnShowWindow(show, status);

  doc_.UpdateAllViews(0, 'show', 0);
}


void CMemoryInfo::OnClose()
{
    hidden_ = FALSE;

	CMiniFrameWnd::OnClose();
}


void CMemoryInfo::InvalidateView(UINT16 stack_ptr/*= 0*/)
{
  doc_.stack_ptr_ = stack_ptr;
  doc_.UpdateAllViews(0, 'invl', 0);
}


void CMemoryInfo::Invalidate()
{
	if (CWnd* view= GetActiveView())
		view->Invalidate();
}


void CMemoryInfo::Notify(int event, int data, CSym6502* simulator)
{
	if (CStackView* view= dynamic_cast<CStackView*>(GetActiveView()))
	{
		view->Notify(event, data, simulator);
	}
}
