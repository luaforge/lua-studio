/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

class CDialBar : public CDialogBar
{
  DECLARE_DYNAMIC(CDialBar)

  // Construction
public:
  BOOL Create(CWnd* parent_wnd, UINT id_template, UINT style, UINT id);
  virtual CSize CalcFixedLayout(bool stretch, bool horz);
  virtual CSize CalcDynamicLayout(int length, DWORD mode);
  CDialBar();
  ~CDialBar();

  //{{AFX_MSG(CDialBar)
  afx_msg void OnGetMinMaxInfo(MINMAXINFO *MMI);
  afx_msg void OnLButtonDown(UINT flags, CPoint point);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

private:
  CSize last_size_;
  CSize CalcLayout(int length, DWORD mode);
};
