/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// EditDisplay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditDisplay window
class CSrc6502View;

class CEditDisplay : public CEdit
{
  CSrc6502View *view_;

  void draw_pointer(CDC &dc, int x, int y, int h);
  void draw_breakpoint(CDC &dc, int x, int y, int h, bool active);

  void MarkBreakpoint(int line);

// Construction
public:
  CEditDisplay();
//  CEditDisplay(CSrc6502View *view);
  
  // Attributes
public:
  
  // Operations
public:
  void Subclass(CSrc6502View *view);

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CEditDisplay)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CEditDisplay();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CEditDisplay)
  afx_msg void OnPaint();
  afx_msg void OnChar(UINT chr, UINT rep_cnt, UINT flags);
  afx_msg void OnKeyUp(UINT chr, UINT rep_cnt, UINT flags);
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
