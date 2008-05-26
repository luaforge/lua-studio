/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

class LuaSrcDoc;
class CMainFrame;
#include "scintilla-mfc\ScintillaDocView.h"
typedef CScintillaView CBaseView;


class LuaSrcView : public CBaseView
{
public:
	static CFont font_;
	static LOGFONT log_font_;
	static COLORREF rgb_text_color_;
	static COLORREF rgb_bkgnd_color_;
	static int tab_step_;
	static bool auto_syntax_;
	static bool auto_uppercase_;
	static COLORREF vrgb_color_syntax_[];
	static BYTE vby_font_style_[];

	void SelectEditFont();

protected: // create from serialization only
	LuaSrcView();
	DECLARE_DYNCREATE(LuaSrcView)

	// Attributes
public:
	void RemoveBreakpoint(int line, bool draw= TRUE);
	void ClearAllBreakpoints(bool draw= true);
	void AddBreakpoint(int line, Defs::Breakpoint bp, bool draw= TRUE);
	int GetCurrLineNo();
	void SetErrMark(int line);
	void SetPointer(int line, bool scroll= FALSE);
	LuaSrcDoc* GetDocument();

	afx_msg LRESULT OnPaintPointer(WPARAM /* wParam */, LPARAM /* lParam */);

	// edit view info
	void GetDispInfo(int& top_line, int& line_count, int& line_height);

	int GetPointerLine() const      { return actual_pointer_line_; }
	int GetErrorMarkLine() const    { return actual_err_mark_line_; }

	// return breakpoint info for line 'line'
	BYTE GetBreakpoint(int line) const;

	int GetLineCount()			{ return GetCtrl().GetLineCount(); }

	void GetText(CString& text);

public:
	// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

	// Implementation
	virtual ~LuaSrcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* info);
	virtual void OnBeginPrinting(CDC* dc, CPrintInfo* info);
	virtual void OnEndPrinting(CDC* dc, CPrintInfo* info);
	afx_msg int OnCreate(LPCREATESTRUCT create_struct);
	afx_msg void OnEnUpdate();
	afx_msg void OnContextMenu(CWnd* wnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	virtual void OnUpdateUI(SCNotification* notification);
	void OnDestroy();
	void set_position_info(HWND wnd);

	CMap<int, int, BYTE, BYTE> breakpoints_map_;	//TODO: move to the doc

	static LRESULT (CALLBACK *pfn_old_proc_)(HWND,UINT,WPARAM,LPARAM);

	static LRESULT CALLBACK EditWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void draw_breakpoints(HDC dc= NULL);
	int ScrollToLine(int line, int &height, bool scroll= FALSE);

	void RedrawMarks(int line= -1);
	void EraseMark(int line);

	int actual_pointer_line_;	//TODO: move to the doc
	int actual_err_mark_line_;	//TODO: move to the doc

	void disp_warning(int line, CString &msg);
	afx_msg LRESULT OnRemoveErrMark(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG
inline LuaSrcDoc* LuaSrcView::GetDocument()
{ return (LuaSrcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
