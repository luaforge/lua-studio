/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "stdafx.h"
#include "MainFrm.h"


  // wys³anie komunikatu do wszystkich okien otwartych dokumentów
void CBroadcast::SendMessageToViews(UINT msg, WPARAM wParam/*= 0*/, LPARAM lParam/*= 0*/)
{
  CWinApp *app= AfxGetApp();
  POSITION posTempl= app->GetFirstDocTemplatePosition();
  while (posTempl != NULL)
  {
    CDocTemplate *templ= app->GetNextDocTemplate(posTempl);
    POSITION posDoc= templ->GetFirstDocPosition();
    while (posDoc != NULL)
    {
      CDocument *doc= templ->GetNextDoc(posDoc);
      POSITION posView = doc->GetFirstViewPosition();
      while (posView != NULL)
      {
	CView* view = doc->GetNextView(posView);
	view->SendMessage(msg,wParam,lParam);
      }
    }
  }   
}


  // wys³anie komunikatu do okien zapisanych w g_windows[]
void CBroadcast::SendMessageToPopups(UINT msg, WPARAM wParam/*= 0*/, LPARAM lParam/*= 0*/)
{
  for (int i=0; CMainFrame::windows_[i]; i++)
  {
    HWND wnd= *CMainFrame::windows_[i];
    if (wnd && ::IsWindow(wnd))
      ::SendMessage(wnd, msg, wParam, lParam);
  }
}
