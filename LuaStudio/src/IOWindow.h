/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// IOWindow.h : header file
//

#ifndef _io_window_
#define _io_window_

#include "Defs.h"
#include "Broadcast.h"

/////////////////////////////////////////////////////////////////////////////
// CIOWindow frame

class CInputBuffer
{
public:
	CInputBuffer() : head_(vch_buffer_), tail_(vch_buffer_)
	{}

	char GetChar();			// get next available character (returns 0 if there are no chars)
	void PutChar(char c);	// places char in the buffer (char is ignored if there is no space)
	void Paste(const char* text);		// paste clipboard text into buffer

private:
	enum { BUF_SIZE= 32 * 1024 };
	char vch_buffer_[BUF_SIZE];
	char* head_;
	char* tail_;
};


class CIOWindow : public CMiniFrameWnd
{
  UINT8 *data_;		// pamiêæ okna
  int width_, height_;	// rozmiar okna (kolumn x wierszy)
  int char_h_, char_w_;	// rozmiar znaków
  static CString class_;
  static bool registered_;
  void RegisterWndClass();
  int pos_x_, pos_y_;		// po³o¿enie znaku do wypisania (i kursora)
  int cursor_count_;		// licznik ukryæ kursora
  bool cursor_on_;				// flag: cursor on/off
  bool cursor_visible_;		// flag: cursor currently visible
  UINT timer_;
  CInputBuffer input_buffer_;	// keyboard input buffer

  int put(char chr, int x, int y);
  int puts(const char *str, int len, int x, int y);
  int scroll(int dy);		// przesuniêcie napisów o 'dy' wierszy
  int invalidate(int x, int y);	// obszar znaku pod (x,y) do przerysowania

  afx_msg LRESULT OnCls(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnPutC(WPARAM wParam, LPARAM /* lParam */);
  afx_msg LRESULT OnStartDebug(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnExitDebug(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnInput(WPARAM /*wParam*/, LPARAM /* lParam */);
  afx_msg LRESULT OnPosition(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnOutputReady(WPARAM wParam, LPARAM lParam);

  DECLARE_DYNCREATE(CIOWindow)
public:
  static bool hidden_;
  CIOWindow();           // protected constructor used by dynamic creation

  // Attributes
public:
  static CFont font_;
  static LOGFONT log_font_;
  static CPoint wnd_pos_;		// po³o¿enie okna
  static int init_w_, init_h_;
  static COLORREF rgb_text_color_, rgb_backgnd_color_;

  // Operations
private:
  void CalcFontSize();			// obliczenie rozmiaru znaków
  void DrawCursor();			// draw cursor
  void DrawCursor(int x, int y, bool visible);
  void HideCursor();			// hide cursor if it's on
public:
  enum Commands				// rozkazy dla okna terminala
  { CMD_CLS = CBroadcast::WM_USER_OFFSET+100, CMD_PUTC, CMD_PUTS, CMD_IN, CMD_POSITION };
  bool Create();
  void SetSize(int w, int h, int resize= 1);
  void GetSize(int &w, int &h);
  void Resize();
  void SetWndPos(const POINT &p);
  CPoint GetWndPos();
  void Paste();

  void SetColors(COLORREF text, COLORREF backgnd);
  void GetColors(COLORREF &text, COLORREF &backgnd);

  int PutC(int chr);			// wydrukowanie znaku
  int PutChr(int chr);			// wydrukowanie znaku (verbatim)
  int PutS(const char *str, int len= -1);	// ci¹g znaków do wydrukowania
  int PutH(int n);			// wydrukowanie liczby hex (8 bitow)
  bool SetPosition(int x, int y);	// ustawienie po³o¿enia dla tekstu
  void GetPosition(int &x, int &y);	// odczyt po³o¿enia
  bool ShowCursor(bool visible= TRUE);	// w³¹czenie/wy³¹czenie kursora
  bool ResetCursor();			// w³¹cza kursor, zeruje licznik ukryæ
  bool Cls();				// wyczyszczenie okna
  int  Input();				// input

  bool IsWaiting() const;
  void ExitModalLoop();

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CIOWindow)
	public:
	virtual BOOL PreTranslateMessage(MSG* msg);
	protected:
  virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

  // Implementation
public:
  virtual ~CIOWindow();
protected:

  // Generated message map functions
  //{{AFX_MSG(CIOWindow)
  afx_msg void OnPaint();
  afx_msg void OnGetMinMaxInfo(MINMAXINFO* MMI);
  afx_msg void OnSize(UINT type, int cx, int cy);
  afx_msg void OnDestroy();
  afx_msg void OnTimer(UINT id_event);
  afx_msg void OnChar(UINT chr, UINT rep_cnt, UINT flags);
  afx_msg void OnClose();
	afx_msg void OnKeyDown(UINT chr, UINT rep_cnt, UINT flags);
	afx_msg void OnContextMenu(CWnd* wnd, CPoint point);
	afx_msg void OnPaste();
	//}}AFX_MSG
  virtual BOOL ContinueModal();
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
