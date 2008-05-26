////////////////////////////////////////////////////////////////
// CFlatToolBar 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This code compiles with Visual C++ 5.0 on Windows 95
//
#ifndef TBSTYLE_FLAT
#define TBSTYLE_FLAT 0x0800	// (in case you don't have the new commctrl.h)
#endif

//////////////////
// "Flat" style tool bar. Use instead of CToolBar in your CMainFrame
// or other window to create a tool bar with the flat look.
//
// CFlatToolBar fixes the display bug described in the article. It also has
// overridden load functions that modify the style to TBSTYLE_FLAT. If you
// don't create your toolbar by loading it from a resource, you should call
// ModifyStyle(0, TBSTYLE_FLAT) yourself.
//
class CFlatToolBar : public CToolBar
{
public:
  BOOL LoadToolBar(LPCTSTR resource_name);
  BOOL LoadToolBar(UINT id_resource)
  { return LoadToolBar(MAKEINTRESOURCE(id_resource)); }
protected:
  DECLARE_DYNAMIC(CFlatToolBar)
  virtual void OnUpdateCmdUI(CFrameWnd* target, BOOL disable_if_no_hndler);
  DECLARE_MESSAGE_MAP()
  afx_msg void OnWindowPosChanging(LPWINDOWPOS wnd_pos);
  afx_msg void OnWindowPosChanged(LPWINDOWPOS wnd_pos);
};
