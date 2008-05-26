/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// DialEditBrkp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialEditBreakpoint dialog

class CDialEditBreakpoint : public CDialog, CAsm
{
  // Construction
public:
  CDialEditBreakpoint(Breakpoint bp, CWnd* parent = NULL);   // standard constructor

  // Dialog Data
  //{{AFX_DATA(CDialEditBreakpoint)
  enum { IDD = IDD_EDIT_BREAKPOINT };
  bool	disabled_;
  bool	execute_;
  bool	read_;
  bool	write_;
  //}}AFX_DATA


  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDialEditBreakpoint)
protected:
  virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
  //}}AFX_VIRTUAL

  // Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CDialEditBreakpoint)
		// NOTE: the ClassWizard will add member functions here
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
