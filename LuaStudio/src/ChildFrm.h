/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _ChildFrame_
#define _ChildFrame_


class CChildFrame : public CMDIChildWnd
{
  DECLARE_DYNCREATE(CChildFrame)
public:
  CChildFrame();

  // Attributes
public:
	CSplitterWnd splitter_wnd_;

  // Operations
public:

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CChildFrame)
	public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
//	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* context);
	//}}AFX_VIRTUAL

	void ActivateFrame(int cmd_show);
  
  // Implementation
public:
  virtual ~CChildFrame();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CChildFrame)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
