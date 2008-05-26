/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// LuaView.cpp : implementation of the LuaSrcView class
//

#include "stdafx.h"
#include "MainFrm.h"
#include "LuaDoc.h"
#include "LuaView.h"
#include "SciLexer.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int LuaSrcView::tab_step_= 4;
bool LuaSrcView::auto_syntax_ = TRUE;
bool LuaSrcView::auto_uppercase_ = TRUE;
CFont LuaSrcView::font_;
LOGFONT LuaSrcView::log_font_;
COLORREF LuaSrcView::rgb_text_color_;
COLORREF LuaSrcView::rgb_bkgnd_color_;
COLORREF LuaSrcView::vrgb_color_syntax_[6]=
{
	RGB(0, 0, 160),		// instructions
	RGB(128, 0, 128),	// directives
	RGB(128, 128, 128),	// comments
	RGB(0, 0, 255),		// number
	RGB(0, 128, 128),	// string
	RGB(192, 192, 224)	// selection
};
BYTE LuaSrcView::vby_font_style_[6]=
{
	0, 0, 0, 0, 0, 0
};


const int MARKER_POINTER= 3;
const int MARKER_ERROR= 2;
const int MARKER_BREAKPOINT= 1;

/////////////////////////////////////////////////////////////////////////////
// LuaSrcView

IMPLEMENT_DYNCREATE(LuaSrcView, CScintillaView)

BEGIN_MESSAGE_MAP(LuaSrcView, CBaseView)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_UPDATE, OnEnUpdate)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_FILE_PRINT, CBaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CBaseView::OnFilePrintPreview)
	ON_MESSAGE(CBroadcast::WM_USER_REMOVE_ERR_MARK, OnRemoveErrMark)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LuaSrcView construction/destruction

LuaSrcView::LuaSrcView()
{
	actual_pointer_line_ = -1;
	actual_err_mark_line_ = -1;
}

LuaSrcView::~LuaSrcView()
{
}

BOOL LuaSrcView::PreCreateWindow(CREATESTRUCT& cs)
{
	bool pre_created = CBaseView::PreCreateWindow(cs);
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	return pre_created;
}

/////////////////////////////////////////////////////////////////////////////
// LuaSrcView printing

BOOL LuaSrcView::OnPreparePrinting(CPrintInfo* info)
{
	// default CBaseView preparation
	return CBaseView::OnPreparePrinting(info);
}

void LuaSrcView::OnBeginPrinting(CDC* dc, CPrintInfo* info)
{
	// Default CBaseView begin printing.
	CBaseView::OnBeginPrinting(dc, info);
}

void LuaSrcView::OnEndPrinting(CDC* dc, CPrintInfo* info)
{
	// Default CBaseView end printing
	CBaseView::OnEndPrinting(dc, info);
}

/////////////////////////////////////////////////////////////////////////////
// LuaSrcView diagnostics

#ifdef _DEBUG
void LuaSrcView::AssertValid() const
{
	CBaseView::AssertValid();
}

void LuaSrcView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}

LuaSrcDoc* LuaSrcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(LuaSrcDoc)));
	return (LuaSrcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// LuaSrcView message handlers

void LuaSrcView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();

	SelectEditFont();
}

const char LuaKeywords[]= "and break do else elseif end false for function if in local nil not or repeat return then true until while";

const char LuaFunctions[]=
"_G _VERSION assert collectgarbage dofile error getfenv getmetatable ipairs load loadfile loadstring module next pairs pcall "
"print rawequal rawget rawset require select setfenv setmetatable tonumber tostring type unpack xpcall gcinfo newproxy "

"coroutine.create coroutine.resume coroutine.running coroutine.status coroutine.wrap coroutine.yield "

"debug.debug debug.getfenv debug.gethook debug.getinfo debug.getlocal debug.getmetatable debug.getregistry "
"debug.getupvalue debug.setfenv debug.sethook debug.setlocal debug.setmetatable debug.setupvalue debug.traceback "

"io.close io.flush io.input io.lines io.open io.output io.popen io.read io.stderr io.stdin io.stdout io.tmpfile io.type io.write "

"math.abs math.acos math.asin math.atan math.atan2 math.ceil math.cos math.cosh math.deg math.exp math.floor math.fmod "
"math.frexp math.huge math.ldexp math.log math.log10 math.max math.min math.modf math.pi math.pow math.rad math.random "
"math.randomseed math.sin math.sinh math.sqrt math.tan math.tanh math.mod "

"os.clock os.date os.difftime os.execute os.exit os.getenv os.remove os.rename os.setlocale os.time os.tmpname "

"package.cpath package.loaded package.loaders package.loadlib package.path package.preload package.seeall package.config "

"string.byte string.char string.dump string.find string.format string.gmatch string.gsub string.len string.lower string.match "
"string.rep string.reverse string.sub string.upper string.gfind "

"table.concat table.insert table.maxn table.remove table.sort table.setn table.getn table.foreachi table.foreach "

"_LUA_VERSION";


int LuaSrcView::OnCreate(LPCREATESTRUCT create_struct)
{
	if (CBaseView::OnCreate(create_struct) == -1)
		return -1;

	CScintillaCtrl& ctrl= GetCtrl();

	ctrl.SetLexer(SCLEX_LUA);
	ctrl.StyleSetFont(STYLE_DEFAULT, "Verdana");
	ctrl.StyleSetSize(STYLE_DEFAULT, 10);
	ctrl.SetKeyWords(0, LuaKeywords);
	ctrl.SetKeyWords(1, LuaFunctions);

	COLORREF comment= RGB(0,128,128);
	COLORREF string= RGB(128,128,0);

	ctrl.StyleSetFore(SCE_LUA_COMMENT, comment);
	ctrl.StyleSetFore(SCE_LUA_COMMENTLINE, comment);
	ctrl.StyleSetFore(SCE_LUA_COMMENTDOC, comment);
	ctrl.StyleSetFore(SCE_LUA_NUMBER, RGB(0,0,255));
	ctrl.StyleSetFore(SCE_LUA_WORD, RGB(34,78,160));
	ctrl.StyleSetFore(SCE_LUA_STRING, string);
	ctrl.StyleSetFore(SCE_LUA_CHARACTER, string);
	ctrl.StyleSetFore(SCE_LUA_LITERALSTRING, string);
	ctrl.StyleSetFore(SCE_LUA_WORD2, RGB(53,113,202));

	ctrl.StyleSetFont(SCE_LUA_WORD, "Verdana");
	ctrl.StyleSetSize(SCE_LUA_WORD, 10);
	ctrl.StyleSetBold(SCE_LUA_WORD, true);

	//#define SCE_LUA_PREPROCESSOR 9
	//#define SCE_LUA_OPERATOR 10
	//#define SCE_LUA_IDENTIFIER 11
	//#define SCE_LUA_STRINGEOL 12
	//#define SCE_LUA_WORD2 13
	//#define SCE_LUA_WORD3 14
	//#define SCE_LUA_WORD4 15
	//#define SCE_LUA_WORD5 16
	//#define SCE_LUA_WORD6 17
	//#define SCE_LUA_WORD7 18
	//#define SCE_LUA_WORD8 19

	ctrl.Colourise(0, -1);

	ctrl.MarkerDefine(MARKER_POINTER, SC_MARK_ARROW);
	ctrl.MarkerSetBack(MARKER_POINTER, RGB(255,255,0));

	ctrl.MarkerDefine(MARKER_BREAKPOINT, SC_MARK_ROUNDRECT);
	ctrl.MarkerSetBack(MARKER_BREAKPOINT, RGB(0,0,255));

	ctrl.MarkerDefine(MARKER_ERROR, SC_MARK_ARROW);
	ctrl.MarkerSetBack(MARKER_ERROR, RGB(255,0,0));

	ctrl.SetMarginWidthN(1, 18);

	//ctrl.SetMarginWidthN(2, 10);
	//ctrl.SetProperty("fold", "1");

	return 0;
}


LRESULT (CALLBACK *LuaSrcView::pfn_old_proc_)(HWND,UINT,WPARAM,LPARAM) = NULL;



void LuaSrcView::disp_warning(int line, CString &msg)
{
	SetErrMark(line);		// mark line with syntax error
	CMainFrame* main = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	main->status_bar_wnd_.SetPaneText(0, msg);
}


//=============================================================================

int LuaSrcView::ScrollToLine(int line, int &height, bool scroll)
{
	ASSERT(line >= 0);

	GetCtrl().GotoLine(line);
	return 0;
}


// edit view info
//
void LuaSrcView::GetDispInfo(int& top_line, int& line_count, int& line_height)
{
	line_height = GetCtrl().TextHeight(0);
}

//-----------------------------------------------------------------------------


void LuaSrcView::SetPointer(int line, bool scroll)
{
	const int P= MARKER_POINTER;

	if (actual_pointer_line_ != -1)
	{
		int tmp_line= actual_pointer_line_;
		GetCtrl().MarkerDelete(actual_pointer_line_, P);
		actual_pointer_line_ = -1;
		//    EraseMark(tmp_line);	// zmazanie starej strza³ki
	}
	actual_pointer_line_ = line;
	if (line != -1)
	{
		int h;
		ScrollToLine(line,h,TRUE);
		GetCtrl().MarkerAdd(line, P);
	}
}


void LuaSrcView::SetErrMark(int line)
{
	if (actual_err_mark_line_ != -1)
	{
		GetCtrl().MarkerDelete(actual_err_mark_line_, MARKER_ERROR);
	}
	actual_err_mark_line_ = line;
	if (line != -1)
	{
		int h;
		ScrollToLine(line,h,TRUE);
		actual_err_mark_line_ = line;
		GetCtrl().MarkerAdd(line, MARKER_ERROR);
	}
}


void LuaSrcView::OnEnUpdate()
{
	if (actual_err_mark_line_ != -1)
	{
		SetErrMark(-1);
		CMainFrame* main= (CMainFrame*) AfxGetApp()->m_pMainWnd;
		main->status_bar_wnd_.SetPaneText(0, NULL);
	}
}


void LuaSrcView::SelectEditFont()
{
	GetCtrl().SetTabWidth(tab_step_);
}


int LuaSrcView::GetCurrLineNo()
{
	return GetCtrl().LineFromPosition(GetCtrl().GetCurrentPos());
}


void LuaSrcView::AddBreakpoint(int line, Defs::Breakpoint bp, bool draw)
{
	breakpoints_map_[line] = (BYTE)bp;
	GetCtrl().MarkerAdd(line, MARKER_BREAKPOINT);
}


void LuaSrcView::RemoveBreakpoint(int line, bool draw)
{
	breakpoints_map_.RemoveKey(line);
	GetCtrl().MarkerDelete(line, MARKER_BREAKPOINT);
}


void LuaSrcView::ClearAllBreakpoints(bool draw)
{
	breakpoints_map_.RemoveAll();
	GetCtrl().MarkerDeleteAll(MARKER_BREAKPOINT);
}


void LuaSrcView::RedrawMarks(int line/*= -1*/)
{
}


void LuaSrcView::EraseMark(int line)
{
	RedrawMarks(line);
}



void LuaSrcView::OnContextMenu(CWnd* wnd, CPoint point)
{
	CMenu menu;
	if (!menu.LoadMenu(IDR_POPUP_EDIT))
		return;
	CMenu *popup = menu.GetSubMenu(0);
	ASSERT(popup != NULL);

	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);

		point = rect.TopLeft();
		CPoint top_left(0, 0);
		ClientToScreen(&top_left);
		point.x = top_left.x + rect.Width() / 2;
		point.y = top_left.y + rect.Height() / 2;
	}

	popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
}


LRESULT LuaSrcView::OnRemoveErrMark(WPARAM wParam, LPARAM lParam)
{
	SetErrMark(-1);
	return 1;
}


// return breakpoint info for line 'line'
//
BYTE LuaSrcView::GetBreakpoint(int line) const
{
	BYTE bp= 0;
	breakpoints_map_.Lookup(line, bp);
	return bp;
}


void LuaSrcView::GetText(CString& text)
{
	GetCtrl().GetWindowText(text);
}


void LuaSrcView::OnUpdateUI(SCNotification* notification)
{
	long pos= GetCtrl().GetCurrentPos();
	int line= GetCtrl().LineFromPosition(pos);
	int col= GetCtrl().GetColumn(pos);

	CMainFrame* main = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	main->SetPositionText(line + 1, col + 1, !GetCtrl().GetOvertype());
}


void LuaSrcView::OnDestroy()
{
}
