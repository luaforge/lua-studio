/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// IOWindow.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "IOWindow.h"
#include "Broadcast.h"
//#include <memory.h>
#include "App.h"
#include <algorithm>
#include <utility>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//-----------------------------------------------------------------------------
bool CIOWindow::registered_= FALSE;
bool CIOWindow::hidden_;
CString CIOWindow::class_;
CFont CIOWindow::font_;
LOGFONT CIOWindow::log_font_=
{
  13,	// LONG lfHeight;
  0,	// LONG lfWidth;
  0,	// LONG lfEscapement;
  0,	// LONG lfOrientation;
  0,	// LONG lfWeight;
  0,	// BYTE lfItalic;
  0,	// BYTE lfUnderline;
  0,	// BYTE lfStrikeOut;
  0,	// BYTE lfCharSet;
  0,	// BYTE lfOutPrecision;
  0,	// BYTE lfClipPrecision;
  0,	// BYTE lfQuality;
  FIXED_PITCH,	// BYTE lfPitchAndFamily;
  "Courier"	// CHAR lfFaceName[LF_FACESIZE];
};

CPoint CIOWindow::wnd_pos_= CPoint(0,0);	// po³o¿enie okna
int CIOWindow::init_w_= 80;
int CIOWindow::init_h_= 25;
COLORREF CIOWindow::rgb_text_color_= RGB(0,0,0);
COLORREF CIOWindow::rgb_backgnd_color_= RGB(255,255,255);

//-----------------------------------------------------------------------------
// Rejestracja klasy okien

void CIOWindow::RegisterWndClass()
{
  ASSERT(!registered_);
  if (registered_)
    return;
  class_ = AfxRegisterWndClass(0/*CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS*/,
    ::LoadCursor(NULL,IDC_ARROW), 0, AfxGetApp()->LoadIcon(IDI_IO_WINDOW));
  registered_ = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CIOWindow

IMPLEMENT_DYNCREATE(CIOWindow, CMiniFrameWnd)

CIOWindow::CIOWindow()
{
  m_hWnd = 0;
  data_ = NULL;
  width_ = height_ = 0;

  pos_x_ = pos_y_ = 0;	// po³o¿enie znaku do wypisania (i kursora)
  cursor_count_ = 0;		// licznik ukryæ kursora

  if (!registered_)
    RegisterWndClass();

  hidden_ = FALSE;

  cursor_on_ = false;
  cursor_visible_ = false;

  timer_ = 0;
}

CIOWindow::~CIOWindow()
{
  if (data_)
    delete []data_;
}

//-----------------------------------------------------------------------------
// Nowe okno

bool CIOWindow::Create()
{
  ASSERT(m_hWnd==0);
  CString title;
  title.LoadString(IDS_IO_WINDOW);

  RECT rect= {0,0,100,100};
  rect.left = wnd_pos_.x;
  rect.top = wnd_pos_.y;
  if (!CMiniFrameWnd::CreateEx(WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE, class_, title,
    WS_POPUP | WS_CAPTION | WS_SYSMENU | MFS_MOVEFRAME /*| MFS_SYNCACTIVE*/,
    rect, AfxGetMainWnd(), 0))
    return FALSE;

  ModifyStyleEx(0,WS_EX_WINDOWEDGE|WS_EX_CLIENTEDGE);
//  SetFont(font_,FALSE);
//  CalcFontSize();
  SetSize(init_w_,init_h_);

  timer_ = SetTimer(101, 250, 0);

  SetFocus();

  return TRUE;
}


void CIOWindow::CalcFontSize()		// obliczenie rozmiaru znaków
{
  ASSERT(m_hWnd);
  CClientDC dc(this);
  dc.SelectObject(&font_);
  TEXTMETRIC tm;
  dc.GetTextMetrics(&tm);
  char_h_ = (int)tm.tmHeight + (int)tm.tmExternalLeading;
  char_w_ = (int)tm.tmAveCharWidth;
}

//-----------------------------------------------------------------------------
// Ustawienie wymiarów okna

void CIOWindow::SetSize(int w, int h, int resize/* =1*/)
{
  ASSERT(w > 0);
  ASSERT(h > 0);
  init_w_ = w;
  init_h_ = h;
  if (m_hWnd==0)	// nie ma jeszcze okna?
    return;
  int new_size= w * h;
  int old_size= width_ * height_;
  bool change=  width_ != w || height_ != h;
  width_ = w;
  height_ = h;
  if (data_==NULL || new_size!=old_size)
  {
    if (data_)
      delete []data_;
    data_ = new UINT8[new_size];
  }

  if (resize == 0)	// bez zmiany wymiarów okna?
    return;
  if (resize == -1 && !change)
    return;
  Resize();
}


void CIOWindow::Resize()
{
  CalcFontSize();
  CRect size(0,0,char_w_*width_, char_h_*height_);
  CalcWindowRect(&size,CWnd::adjustOutside);
  SetWindowPos(NULL,0,0,size.Width(),size.Height(),SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
  Cls();
}

  // odczyt wymiarów okna
void CIOWindow::GetSize(int &w, int &h)
{
  w = m_hWnd ? width_ : init_w_;
  h = m_hWnd ? height_ : init_h_;
}

  // ustawienie po³o¿enia okna
void CIOWindow::SetWndPos(const POINT &p)
{
  wnd_pos_ = p;
  if (m_hWnd==0)	// nie ma jeszcze okna?
    return;
  SetWindowPos(NULL,p.x,p.y,0,0,SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
}

  // odczyt po³o¿enia okna
CPoint CIOWindow::GetWndPos()
{
  if (m_hWnd==0)	// nie ma jeszcze okna?
    return wnd_pos_;
  CRect rect;
  GetWindowRect(rect);
  return rect.TopLeft();
}


//-----------------------------------------------------------------------------

int CIOWindow::put(char chr, int x, int y)
{
  if (data_==NULL)
    return -1;
  if (x > width_ || y > height_ || x < 0 || y < 0)
    return -2;
  data_[x + y * width_] = (UINT8)chr;
  return 0;
}

/*
int CIOWindow::puts(const char *str, int len, int x, int y)
{
  if (data_==NULL)
    return -1;
  if (x > width_ || y > height_ || x < 0 || y < 0)
    return -2;

  return 0;
}
*/

int CIOWindow::invalidate(int x, int y)	// obszar znaku pod (x,y) do przerysowania
{
  RECT rect;
//  GetClientRect(rect);
  ASSERT(char_h_ > 0 && char_w_ > 0);
  rect.left = x * char_w_;
  rect.top = y * char_h_;
  rect.right = rect.left + char_w_;
  rect.bottom = rect.top + char_h_;
//  ASSERT(rect.bottom >= rect.top);
  InvalidateRect(&rect);
  return 0;
}


int CIOWindow::scroll(int dy)		// przesuniêcie napisów o 'dy' wierszy
{
  if (data_==NULL)
    return -1;
  if (dy > height_ || dy < 0)
    return -2;
  // przesuniêcie wierszy
  memmove(data_, data_ + dy * width_, (height_ - dy) * width_);
  // na odkryte miejsce zera
  memset(data_ + (height_ - dy) * width_, 0, dy * width_);
  // ca³e okno do przerysowania
  Invalidate();
  return 0;
}

//-----------------------------------------------------------------------------
int CIOWindow::PutH(int chr)			// wydrukowanie liczby hex (8 bitow)
{
	int h1= (chr >> 4) & 0x0f;
	int h2= chr & 0x0f;
	char buf[4];
	buf[0] = h1 > 9 ? h1 + 'A' - 10 : h1 + '0';
	buf[1] = h2 > 9 ? h2 + 'A' - 10 : h2 + '0';
	buf[2] = '\0';
	return PutS(buf);
}


int CIOWindow::PutC(int chr)			// wydrukowanie znaku
{
	HideCursor();

	if (chr == 0x0a) // line feed?
	{
		if (++pos_y_ >= height_)
		{
			ASSERT(pos_y_ == height_);
			pos_y_--;
			scroll(1);		// przesuniêcie napisów o jeden wiersz
		}
		pos_x_ = 0;
	}
	else if (chr == 0x0d) // carriage return?
		pos_x_ = 0;
	else if (chr == 0x08) // backspace?
	{
		if (--pos_x_ < 0)
		{
			pos_x_ = width_ - 1;
			if (--pos_y_ < 0)
			{
				pos_y_ = 0;
				return 0;
			}
		}
		if (put(' ', pos_x_, pos_y_) < 0)
			return -1;
		invalidate(pos_x_, pos_y_);	// obszar pod znakiem do przerysowania
	}
	else if (chr == '\t') // tab?
	{
		const int tab_step= 8;
		const int spaces= tab_step - pos_x_ % tab_step;
		for (int i= 0; i < spaces; ++i)
			PutChr(' ');
	}
	else
		return PutChr(chr);

	return 0;
}


int CIOWindow::PutChr(int chr)			// wydrukowanie znaku (verbatim)
{
	HideCursor();
  if (put(chr,pos_x_,pos_y_) < 0)
    return -1;
  invalidate(pos_x_,pos_y_);	// obszar pod znakiem do przerysowania
  if (++pos_x_ >= width_)
  {
    pos_x_ = 0;
    if (++pos_y_ >= height_)
    {
      ASSERT(pos_y_ == height_);
      pos_y_--;
      scroll(1);		// przesuniêcie napisów o jeden wiersz
    }
  }
  return 0;
}


int CIOWindow::PutS(const char *str, int len/*= -1*/)	// ci¹g znaków do wydrukowania
{
  for (int i=0; i<len || len==-1; i++)
  {
    if (str[i] == '\0')
      break;
    if (PutC(str[i]) < 0)
      return -1;
  }
  return 0;
}


bool CIOWindow::SetPosition(int x, int y)	// ustawienie po³o¿enia dla tekstu
{
  if (x > width_ || y > height_ || x < 0 || y < 0)
    return FALSE;
  pos_x_ = x;
  pos_y_ = y;
  return TRUE;
}


void CIOWindow::GetPosition(int &x, int &y)	// odczyt po³o¿enia
{
  x = pos_x_;
  y = pos_y_;
}


bool CIOWindow::Cls()			// wyczyszczenie okna
{
  if (data_==NULL)
    return FALSE;
  memset(data_,0,height_*width_);	// wyzerowanie
  pos_x_ = pos_y_ = 0;
  Invalidate();				// ca³e okno do przerysowania
  return TRUE;
}


int CIOWindow::Input()			// input
{
	cursor_on_ = true;
//	SetFocus();

	return input_buffer_.GetChar();		// returns available char or 0 if buffer is empty
}

/*
int CIOWindow::Input()			// input
{
  if (theApp.global_.GetSimulator()->IsBroken())	// execution broken?
    return -1;

  cursor_on_ = true;
  cursor_visible_ = true;
  timer_ = SetTimer(1, 250, 0);
  DrawCursor();

  SetFocus();

  RunModalLoop();

  KillTimer(timer_);
  timer_ = 0;
  if (cursor_visible_)
  {
    cursor_visible_ = false;
    DrawCursor();
  }
  cursor_on_ = false;

  if (theApp.global_.GetSimulator()->IsBroken())	// execution broken?
    AfxGetMainWnd()->SetFocus();

  return modal_result_;
}
*/

//-----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CIOWindow, CMiniFrameWnd)
	//{{AFX_MSG_MAP(CIOWindow)
	ON_WM_PAINT()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_WM_CLOSE()
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PASTE, OnPaste)
	//}}AFX_MSG_MAP
	ON_MESSAGE(CIOWindow::CMD_CLS, OnCls)
	ON_MESSAGE(CIOWindow::CMD_PUTC, OnPutC)
	ON_MESSAGE(CBroadcast::WM_USER_START_DEBUGGER, OnStartDebug)
	ON_MESSAGE(CBroadcast::WM_USER_EXIT_DEBUGGER, OnExitDebug)
	ON_MESSAGE(CIOWindow::CMD_IN, OnInput)
	ON_MESSAGE(CIOWindow::CMD_POSITION, OnPosition)

	ON_MESSAGE(CBroadcast::WM_APP_OUTPUT, OnOutputReady)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIOWindow message handlers

void CIOWindow::OnPaint()
{
  CPaintDC dc(this);	// device context for painting

  if (data_==NULL)
    return;

  dc.SelectObject(&font_);
  dc.SetBkMode(OPAQUE);
  dc.SetTextColor(rgb_text_color_);
  dc.SetBkColor(rgb_backgnd_color_);

  CString line;
  UINT8 *src= data_;
  for (int y=0,pos_y=0; y<height_; y++,pos_y+=char_h_)
  {
    TCHAR *dst= line.GetBuffer(width_);
    for (int i=0; i<width_; i++)	// znaki jednego wiersza do bufora 'line'
      if ( (*dst++ = TCHAR(*src++)) == 0 )
        dst[-1] = ' ';			// zast¹pienie znaku '\0' przez ' '
    line.ReleaseBuffer(width_);
    dc.TextOut(0,pos_y,line);		// wydrukowanie wiersza
  }

  DrawCursor();
}

//=============================================================================

void CIOWindow::OnDestroy()
{
  CRect rect;
  GetWindowRect(&rect);
  wnd_pos_ = rect.TopLeft();	// zapamiêtanie po³o¿enia okna

  if (timer_)
    KillTimer(timer_);
  timer_ = 0;

  CMiniFrameWnd::OnDestroy();
}

//=============================================================================

void CIOWindow::PostNcDestroy()
{
//	CMiniFrameWnd::PostNcDestroy();
  m_hWnd = NULL;
}

//=============================================================================

void CIOWindow::OnGetMinMaxInfo(MINMAXINFO* MMI)
{
  CMiniFrameWnd::OnGetMinMaxInfo(MMI);

  CRect size(0,0,char_w_*width_,char_h_*height_);
  CalcWindowRect(&size,CWnd::adjustOutside);
  int w= size.Width();
  if (GetStyle() & WS_VSCROLL)
    w += ::GetSystemMetrics(SM_CXVSCROLL);
  int h= size.Height();
  if (GetStyle() & WS_HSCROLL)
    h += ::GetSystemMetrics(SM_CYHSCROLL);

  MMI->ptMaxSize.x = w;
  MMI->ptMaxSize.y = h;
  MMI->ptMaxTrackSize.x = w;
  MMI->ptMaxTrackSize.y = h;
}

//=============================================================================

void CIOWindow::OnSize(UINT type, int cx, int cy) 
{
  CMiniFrameWnd::OnSize(type,cx,cy);

  if (type == SIZE_RESTORED)
  {
    int w= (GetStyle() & WS_VSCROLL) ? ::GetSystemMetrics(SM_CXVSCROLL) : 0;
    int h= (GetStyle() & WS_HSCROLL) ? ::GetSystemMetrics(SM_CYHSCROLL) : 0;
    CRect rect(0,0,char_w_*width_, char_h_*height_);
    CSize size(rect.Width(),rect.Height());
    bool remove= ( cx+w >= size.cx && cy+h >= size.cy );
    SCROLLINFO si_horz=
    {
      sizeof si_horz,
      SIF_PAGE | SIF_RANGE,
      0, size.cx-1,		// min i max
      remove ? size.cx : cx,
      0, 0
    };
    SCROLLINFO si_vert=
    {
      sizeof si_vert,
      SIF_PAGE | SIF_RANGE,
      0, size.cy-1,		// min i max
      remove ? size.cy : cy,
      0, 0
    };
    SetScrollInfo(SB_HORZ,&si_horz);
    SetScrollInfo(SB_VERT,&si_vert);
  }
  else if (type == SIZE_MAXIMIZED)
    cx = 0;
}

//-----------------------------------------------------------------------------

void CIOWindow::SetColors(COLORREF text, COLORREF backgnd)	// ust. kolorów
{
  rgb_backgnd_color_ = backgnd;
  rgb_text_color_ = text;
  if (m_hWnd)
    Invalidate();
}

void CIOWindow::GetColors(COLORREF &text, COLORREF &backgnd)	// odczyt kolorów
{
  text = rgb_text_color_;
  backgnd = rgb_backgnd_color_;
}

//=============================================================================

afx_msg LRESULT CIOWindow::OnStartDebug(WPARAM /*wParam*/, LPARAM /* lParam */)
{
  VERIFY( Cls() );
  if (!hidden_)		// okno by³o widoczne?
    if (m_hWnd)
      ShowWindow(SW_NORMAL);
    else
      Create();
  return 1;
}


afx_msg LRESULT CIOWindow::OnExitDebug(WPARAM /*wParam*/, LPARAM /* lParam */)
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

afx_msg LRESULT CIOWindow::OnCls(WPARAM /*wParam*/, LPARAM /* lParam */)
{
  VERIFY( Cls() );
  return 1;
}


afx_msg LRESULT CIOWindow::OnPutC(WPARAM wParam, LPARAM lParam)
{
  if (lParam == 0)
    VERIFY( PutC(int(UINT8(wParam))) == 0 );
  else if (lParam == 1)
    VERIFY( PutChr(int(UINT8(wParam))) == 0 );
  else if (lParam == 2)
    VERIFY( PutH(int(UINT8(wParam))) == 0 );
  else
  { ASSERT(false); }
  return 1;
}


afx_msg LRESULT CIOWindow::OnInput(WPARAM /*wParam*/, LPARAM /* lParam */)
{
  return Input();
}


afx_msg LRESULT CIOWindow::OnPosition(WPARAM wParam, LPARAM lParam)
{
	bool X_pos= !!(wParam & 1);

	if (wParam & 2)	// get pos?
	{
		return X_pos ? pos_x_ : pos_y_;
	}
	else				// set pos
	{
		int x= pos_x_;
		int y= pos_y_;

		if (X_pos)
			x = lParam;
		else
			y = lParam;

		if (x >= width_)
			x = width_ - 1;
		if (y >= height_)
			y = height_ - 1;

		if (x != pos_x_ || y != pos_y_)
		{
			if (cursor_visible_ && cursor_on_)
				DrawCursor(pos_x_, pos_y_, false);

			pos_x_ = x;
			pos_y_ = y;

			if (cursor_visible_ && cursor_on_)
				DrawCursor(pos_x_, pos_y_, true);
		}
	}

  return 0;
}

//=============================================================================

void CIOWindow::HideCursor()
{
	if (cursor_visible_)
	{
		DrawCursor(pos_x_, pos_y_, false);
		cursor_visible_ = false;
	}
	cursor_on_ = false;
}

// draw cursor
//
void CIOWindow::DrawCursor()
{
  if (cursor_on_)
    DrawCursor(pos_x_, pos_y_, cursor_visible_);
}


void CIOWindow::DrawCursor(int x, int y, bool visible)
{
  if (data_==NULL)
    return;
  if (x > width_ || y > height_ || x < 0 || y < 0)
  {
    ASSERT(false);
    return;
  }

  // character under the cursor
  char buf[2]= { data_[x + y * width_], '\0' };
  if (buf[0] == '\0')
    buf[0] = ' ';

  CClientDC dc(this);

  dc.SelectObject(&font_);
  dc.SetBkMode(OPAQUE);

  if (visible)
  {
    dc.SetTextColor(rgb_backgnd_color_);
    dc.SetBkColor(rgb_text_color_);
  }
  else
  {
    dc.SetTextColor(rgb_text_color_);
    dc.SetBkColor(rgb_backgnd_color_);
  }

  // cursor pos & size
  CPoint pos(x * char_w_, y * char_h_);
  CRect rect(pos, CSize(char_w_, char_h_));

  dc.DrawText(buf, 1, rect, DT_TOP | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
}



void CIOWindow::OnTimer(UINT id_event)
{
	cursor_visible_ = !cursor_visible_;

	DrawCursor();

	if (!cursor_visible_)
		cursor_on_ = false;

//  CMiniFrameWnd::OnTimer(id_event);
}


void CIOWindow::OnChar(UINT chr, UINT rep_cnt, UINT flags)
{
	char c= char(chr);
	if (c)
		input_buffer_.PutChar(c);

	//  EndModalLoop(chr);
}


BOOL CIOWindow::ContinueModal()
{
	if (theApp.global_.GetDebugger().IsStopped())	// execution stopped?
		return false;

	return CMiniFrameWnd::ContinueModal();
}


void CIOWindow::OnClose()
{
  if (IsWaiting())
  {
    EndModalLoop(-1);	// break
    return;
  }

	ShowWindow(SW_HIDE);
//  CMiniFrameWnd::OnClose();
}


bool CIOWindow::IsWaiting() const
{
	return false;
//  return (flags_ & WF_MODALLOOP) != 0;	// in modal loop waiting for input?
}

void CIOWindow::ExitModalLoop()
{
  if (IsWaiting())
    EndModalLoop(-1);
}


void CIOWindow::Paste()
{
	if (!::IsClipboardFormatAvailable(CF_TEXT))
		return;

	if (!OpenClipboard())
		return;

	if (HANDLE glb= ::GetClipboardData(CF_TEXT))
	{
		if (VOID* str= ::GlobalLock(glb))
		{
			input_buffer_.Paste(reinterpret_cast<char*>(str));
			GlobalUnlock(glb);
		}
	}

	CloseClipboard();
}

///////////////////////////////////////////////////////////////////////////////

char CInputBuffer::GetChar()		// get next available character (returns 0 if there are no chars)
{
	char c= 0;

	if (head_ != tail_)
	{
		c = *tail_++;
		if (tail_ >= vch_buffer_ + BUF_SIZE)
			tail_ = vch_buffer_;
	}

	return c;
}

void CInputBuffer::PutChar(char c)	// places char in the buffer (char is ignored if there is no space)
{
	char* next= head_ + 1;

	if (next >= vch_buffer_ + BUF_SIZE)
		next = vch_buffer_;

	if (next != tail_)	// is there a place in buffer?
	{
		*head_ = c;
		head_ = next;
	}
}


void CInputBuffer::Paste(const char* text)
{
	int max= min(strlen(text), BUF_SIZE);

	for (int i= 0; i < max; ++i)
		PutChar(text[i]);
}


void CIOWindow::OnKeyDown(UINT chr, UINT rep_cnt, UINT flags)
{
	if (chr == VK_INSERT)
		Paste();
	else
		CMiniFrameWnd::OnKeyDown(chr, rep_cnt, flags);
}


BOOL CIOWindow::PreTranslateMessage(MSG* msg)
{
	if (GetFocus() == this)
	{
		if (msg->message == WM_KEYDOWN || msg->message == WM_KEYUP)
		{
			if (msg->wParam >= VK_SPACE && msg->wParam <= 'Z')
			{
				if (::GetKeyState(VK_CONTROL) < 0 && ::GetKeyState(VK_SHIFT) >= 0)
				{
					// skip the rest of PreTranslateMessage() functions, cause they will
					// eat some of those messages (as accel shortcuts); translate and
					// dispatch them now

					::TranslateMessage(msg);
					::DispatchMessage(msg);
					return true;
				}
			}
		}
	}

	return CMiniFrameWnd::PreTranslateMessage(msg);
}


void CIOWindow::OnContextMenu(CWnd* wnd, CPoint point)
{
	CMenu menu;
	if (!menu.LoadMenu(IDR_POPUP_TERMINAL))
		return;
	CMenu *popup = menu.GetSubMenu(0);
	ASSERT(popup != NULL);

	if (point.x == -1 && point.y == -1)		// menu wywo³ane przy pomocy klawiatury?
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		point = rect.CenterPoint();
	}

	popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CIOWindow::OnPaste()
{
	Paste();
}


LRESULT CIOWindow::OnOutputReady(WPARAM wParam, LPARAM lParam)
{
	try
	{
		std::vector<char> out;
		theApp.global_.GetOutput(out);

		if (!out.empty())
			PutS(&out.front(), out.size());
	}
	catch (...)
	{
		ASSERT(false);
	}
	return 0;
}
