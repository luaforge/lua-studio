/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MainFrm.h"
#include "Options.h"
//#include "DialEditBrkp.h"
#include "AFXPRIV.H"	// LoadBarState()
#include "LuaView.h"
#include "LuaDoc.h"
#include "DockBarEx.h"
#include "Lua.h"
#include "App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#pragma warning (disable: 4407)

//-----------------------------------------------------------------------------

const HWND* /*const*/ CMainFrame::windows_[]= {0,0,0,0,0,0,0,0,0,0};

WNDPROC CMainFrame::pfn_old_proc_;
CBitmap CMainFrame::code_bmp_;		// obrazki w StatusBar
CBitmap CMainFrame::debug_bmp_;

Debugger& GetDebugger()
{
	return theApp.global_.GetDebugger();
}

//-----------------------------------------------------------------------------
//const TCHAR CMainFrame::REG_ENTRY_LAYOUT[]= _T("Bars\\Layout");
const char REG_ENTRY_CONTROL_BARS[]= _T("CtrlBars\\BarState");
const TCHAR CMainFrame::REG_ENTRY_MAINFRM[]= _T("MainFrame");
const TCHAR CMainFrame::REG_POSX[]= _T("XPos");
const TCHAR CMainFrame::REG_POSY[]= _T("YPos");
const TCHAR CMainFrame::REG_SIZX[]= _T("Width");
const TCHAR CMainFrame::REG_SIZY[]= _T("Height");
const TCHAR CMainFrame::REG_STATE[]= _T("Maximize");

void CMainFrame::ConfigSettings(bool load)
{
	static const LOGFONT LogFont=
	{
		-12,// LONG lfHeight;
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
		"Fixedsys"	// CHAR lfFaceName[LF_FACESIZE];
	};

	static const TCHAR ENTRY_SYM[]= _T("Simulator");
	static const TCHAR SYM_FIN[]= _T("Finish");
	static const TCHAR SYM_IO_ADDR[]= _T("IOAddress");
	static const TCHAR SYM_IO_ENABLED[]= _T("IOEnabled");
	static const TCHAR SYM_PROT_MEM[]= _T("ProtectMem");
	static const TCHAR SYM_PROT_MEM_FROM[]= _T("ProtectMemFrom");
	static const TCHAR SYM_PROT_MEM_TO[]= _T("ProtectMemTo");
	static const TCHAR SYM_WND_X[]= _T("TerminalXPos");
	static const TCHAR SYM_WND_Y[]= _T("TerminalYPos");
	static const TCHAR SYM_WND_W[]= _T("TerminalWidth");
	static const TCHAR SYM_WND_H[]= _T("TerminalHeight");

	static const TCHAR ENTRY_ASM[]= _T("Assembler");
	static const TCHAR ASM_CASE[]= _T("CaseSensitive");
	static const TCHAR ASM_GEN_LST[]= _T("GenerateListing");
	static const TCHAR ASM_LST_FILE[]= _T("ListingFile");
	static const TCHAR ASM_GEN_BYTE[]= _T("GenerateBRKExtraByte");
	static const TCHAR ASM_BRK_BYTE[]= _T("BRKExtraByte");

	static const TCHAR ENTRY_EDIT[]= _T("Editor");
	static const TCHAR EDIT_FONT[]= _T("Font");
	static const TCHAR EDIT_TAB_STEP[]= _T("TabStep");
	static const TCHAR EDIT_AUTO_INDENT[]= _T("AutoIndent");
	static const TCHAR EDIT_SYNTAX_CHECK[]= _T("SyntaxChecking");
	static const TCHAR EDIT_CAPITALS[]= _T("AutoUppercase");
	static const TCHAR EDIT_FILENEW[]= _T("FileNew");

	static const TCHAR ENTRY_DEASM[]= _T("Deassembler");
	static const TCHAR DEASM_ADDR_COLOR[]= _T("AddrColor");
	static const TCHAR DEASM_CODE_COLOR[]= _T("CodeColor");
	static const TCHAR DEASM_SHOW_CODE[]= _T("ShowCode");

	static const TCHAR ENTRY_GEN[]= _T("General");
	static const TCHAR GEN_PROC[]= _T("ProcType");
	static const TCHAR GEN_BUS_WIDTH[]= _T("BusWidth");
	static const TCHAR GEN_PTR[]= _T("PointerColor");
	static const TCHAR GEN_BRKP[]= _T("BreakpointColor");
	static const TCHAR GEN_ERR[]= _T("ErrorColor");

	static const TCHAR ENTRY_VIEW[]= _T("View");
	static const TCHAR VIEW_IDENTS_X[]= _T("IdentsXPos");
	static const TCHAR VIEW_IDENTS_Y[]= _T("IdentsYPos");
	static const TCHAR VIEW_IDENTS_W[]= _T("IdentsW");
	static const TCHAR VIEW_IDENTS_H[]= _T("IdentsH");
	static const TCHAR VIEW_MEMO_X[]= _T("MemoryXPos");
	static const TCHAR VIEW_MEMO_Y[]= _T("MemoryYPos");
	static const TCHAR VIEW_MEMO_W[]= _T("MemoryW");
	static const TCHAR VIEW_MEMO_H[]= _T("MemoryH");
	static const TCHAR VIEW_MEMO_HID[]= _T("MemoryWndHidden");
	static const TCHAR VIEW_ZMEM_X[]= _T("ZeroPageXPos");
	static const TCHAR VIEW_ZMEM_Y[]= _T("ZeroPageYPos");
	static const TCHAR VIEW_ZMEM_W[]= _T("ZeroPageW");
	static const TCHAR VIEW_ZMEM_H[]= _T("ZeroPageH");
	static const TCHAR VIEW_ZMEM_HID[]= _T("ZeroPageWndHidden");
	static const TCHAR VIEW_STACK_X[]= _T("StackXPos");
	static const TCHAR VIEW_STACK_Y[]= _T("StackYPos");
	static const TCHAR VIEW_STACK_W[]= _T("StackW");
	static const TCHAR VIEW_STACK_H[]= _T("StackH");
	static const TCHAR VIEW_STACK_HID[]= _T("StackWndHidden");
	static const TCHAR VIEW_LOG_X[]= _T("LogWndXPos");
	static const TCHAR VIEW_LOG_Y[]= _T("LogWndYPos");
	static const TCHAR VIEW_LOG_W[]= _T("LogWndW");
	static const TCHAR VIEW_LOG_H[]= _T("LogWndH");
	static const TCHAR VIEW_LOG_HID[]= _T("LogWndHidden");
	static const TCHAR VIEW_IO_HID[]= _T("IOWndHidden");
	static const TCHAR VIEW_REGS_HID[]= _T("RegsWndHidden");
	static const TCHAR VIEW_FONT_ED[]= _T("FontEditor");
	static const TCHAR VIEW_ED_TCOL[]= _T("EditorTextColor");
	static const TCHAR VIEW_ED_BCOL[]= _T("EditorBkgndColor");
	static const TCHAR VIEW_FONT_SYM[]= _T("FontIOSymWnd");
	static const TCHAR VIEW_SYM_TCOL[]= _T("IOSymWndTextColor");
	static const TCHAR VIEW_SYM_BCOL[]= _T("IOSymWndBkgndColor");
	static const TCHAR VIEW_FONT_DEASM[]= _T("FontDeasm");
	static const TCHAR VIEW_DEASM_TCOL[]= _T("DeasmInstrColor");
	static const TCHAR VIEW_DEASM_BCOL[]= _T("DeasmBkgndColor");
	static const TCHAR VIEW_FONT_MEMO[]= _T("FontMemory");
	static const TCHAR VIEW_MEMO_TCOL[]= _T("MemoryTextColor");
	static const TCHAR VIEW_MEMO_BCOL[]= _T("MemoryBkgndColor");
	static const TCHAR VIEW_FONT_ZERO[]= _T("FontZeroPage");
	static const TCHAR VIEW_ZERO_TCOL[]= _T("ZeroPageTextColor");
	static const TCHAR VIEW_ZERO_BCOL[]= _T("ZeroPageBkgndColor");
	static const TCHAR VIEW_FONT_STACK[]= _T("FontStack");
	static const TCHAR VIEW_STACK_TCOL[]= _T("StackTextColor");
	static const TCHAR VIEW_STACK_BCOL[]= _T("StackBkgndColor");

	static const TCHAR* const idents[]=
	{ VIEW_FONT_ED, VIEW_FONT_SYM, VIEW_FONT_DEASM, VIEW_FONT_MEMO, VIEW_FONT_ZERO, VIEW_FONT_STACK };
	static const TCHAR* const tcolors[]=
	{ VIEW_ED_TCOL, VIEW_SYM_TCOL, VIEW_DEASM_TCOL, VIEW_MEMO_TCOL, VIEW_ZERO_TCOL, VIEW_STACK_TCOL };
	static const TCHAR* const bcolors[]=
	{ VIEW_ED_BCOL, VIEW_SYM_BCOL, VIEW_DEASM_BCOL, VIEW_MEMO_BCOL, VIEW_ZERO_BCOL, VIEW_STACK_BCOL };
	static const TCHAR* const syntax_colors[]=
	{ _T("ColorInstruction"), _T("ColorDirective"), _T("ColorComment"), _T("ColorNumber"), _T("ColorString"), _T("ColorSelection"), 0 };
	static const TCHAR* const syntax_font[]=
	{ _T("FontInstruction"), _T("FontDirective"), _T("FontComment"), _T("FontNumber"), _T("FontString"), 0 };

	CWinApp* app = AfxGetApp();

	if (load)		// odczyt?
	{
		CPoint pos;
		pos.x = app->GetProfileInt(ENTRY_SYM, SYM_WND_X, 200);
		pos.y = app->GetProfileInt(ENTRY_SYM, SYM_WND_Y, 200);
		IO_window_.SetWndPos(pos);
		IO_window_.SetSize( app->GetProfileInt(ENTRY_SYM, SYM_WND_W, 40),
			app->GetProfileInt(ENTRY_SYM, SYM_WND_H, 12) );
		//    IO_window_.SetColors( (COLORREF)app->GetProfileInt(ENTRY_SYM, SYM_WND_TEXT_COL, int(RGB(0, 0, 0))),
		//      app->GetProfileInt(ENTRY_SYM, SYM_WND_BK_COL, int(RGB(255,255,255))) );

		//CDeasm6502View::rgb_address_   = COLORREF(app->GetProfileInt(ENTRY_DEASM, DEASM_ADDR_COLOR, (int)RGB(127,127,127)));
		//CDeasm6502View::rgb_code_      = COLORREF(app->GetProfileInt(ENTRY_DEASM, DEASM_CODE_COLOR, (int)RGB(191,191,191)));
		////    CDeasm6502View::rgb_instr_   = COLORREF(app->GetProfileInt(ENTRY_DEASM, DEASM_INSTR_COLOR, (int)RGB(0,0,0)));
		//CDeasm6502View::draw_code_    = app->GetProfileInt(ENTRY_DEASM, DEASM_SHOW_CODE, 1);

		//CMarks::rgb_pointer_           = COLORREF(app->GetProfileInt(ENTRY_GEN, GEN_PTR, (int)RGB(255,255,0)));
		//CMarks::rgb_breakpoint_        = COLORREF(app->GetProfileInt(ENTRY_GEN, GEN_BRKP, (int)RGB(0,0,160)));
		//CMarks::rgb_error_             = COLORREF(app->GetProfileInt(ENTRY_GEN, GEN_ERR, (int)RGB(255,0,0)));


		LuaSrcView::tab_step_       = app->GetProfileInt(ENTRY_EDIT, EDIT_TAB_STEP, 4);
		//		LuaSrcView::auto_indent_    = app->GetProfileInt(ENTRY_EDIT, EDIT_AUTO_INDENT, 1);
		LuaSrcView::auto_syntax_    = app->GetProfileInt(ENTRY_EDIT, EDIT_SYNTAX_CHECK, 1);
		LuaSrcView::auto_uppercase_ = app->GetProfileInt(ENTRY_EDIT, EDIT_CAPITALS, 1);
		//StudioApp::file_new_           = app->GetProfileInt(ENTRY_EDIT, EDIT_FILENEW, 0);



		CIOWindow::hidden_           = app->GetProfileInt(ENTRY_VIEW, VIEW_IO_HID, 0);
		//		CRegisterBar::hidden_        = app->GetProfileInt(ENTRY_VIEW, VIEW_REGS_HID, 0);

		//memory_.hidden_             = app->GetProfileInt(ENTRY_VIEW, VIEW_MEMO_HID, false) != 0;
		//zero_page_.hidden_           = app->GetProfileInt(ENTRY_VIEW, VIEW_ZMEM_HID, false) != 0;
		//stack_.hidden_              = app->GetProfileInt(ENTRY_VIEW, VIEW_STACK_HID, false) != 0;
		//log_wnd_.hidden_             = !!app->GetProfileInt(ENTRY_VIEW, VIEW_LOG_HID, false) != 0;

		//    CMemoryInfo::hidden_ = app->GetProfileInt(ENTRY_VIEW, VIEW_MEMO_HID, false) != 0;

		for (int i=0; fonts[i]; i++)	// odczyt info o fontach w programie
		{
			*fonts[i] = LogFont;	// domyœlny font
			LPBYTE ptr= NULL;
			UINT bytes= sizeof *fonts[i];
			app->GetProfileBinary(ENTRY_VIEW, idents[i], &ptr, &bytes);
			if (ptr)
			{
				if (bytes == sizeof *fonts[i])
					memcpy(fonts[i], ptr, sizeof *fonts[i]);
				delete [] ptr;
			}
			static const COLORREF defaults[]=	      // domyœlne kolory t³a dla okien
			{ // VIEW_ED_BCOL, VIEW_SYM_BCOL, VIEW_DEASM_BCOL, VIEW_MEMO_BCOL, VIEW_ZERO_BCOL
				RGB(255,255,255), RGB(255,255,224), RGB(255,255,255),
				RGB(240,255,240), RGB(255,240,240), RGB(255,255,255), RGB(240,240,240)
			};
			*text_color[i] = COLORREF(app->GetProfileInt(ENTRY_VIEW, tcolors[i], RGB(0,0,0)));
			*bkgnd_color[i] = COLORREF(app->GetProfileInt(ENTRY_VIEW, bcolors[i], defaults[i]));
		}

		for (int clr= 0; syntax_colors[clr]; ++clr)
			*color_syntax[clr] = app->GetProfileInt(ENTRY_VIEW, syntax_colors[clr], *color_syntax[clr]);

		for (int style= 0; syntax_font[style]; ++style)
			*syntax_font_style[style] = app->GetProfileInt(ENTRY_VIEW, syntax_font[style], *syntax_font_style[style]);

		//    app->GetProfileInt(ENTRY_ASM,ASM_CASE,1);

	}
	else			// zapis
	{
		CPoint pos= IO_window_.GetWndPos();
		app->WriteProfileInt(ENTRY_SYM, SYM_WND_X, pos.x);
		app->WriteProfileInt(ENTRY_SYM, SYM_WND_Y, pos.y);
		int w, h;
		IO_window_.GetSize(w, h);
		app->WriteProfileInt(ENTRY_SYM, SYM_WND_W, w);
		app->WriteProfileInt(ENTRY_SYM, SYM_WND_H, h);
		COLORREF txt, bk;
		IO_window_.GetColors(txt, bk);
		//    app->WriteProfileInt(ENTRY_SYM, SYM_WND_TEXT_COL, (int)txt);
		//    app->WriteProfileInt(ENTRY_SYM, SYM_WND_BK_COL, (int)bk);
		//    app->WriteProfileBinary(ENTRY_SYM, SYM_WND_FONT,  LPBYTE(&IO_window_.log_font_), UINT(sizeof IO_window_.log_font_));

		//app->WriteProfileInt(ENTRY_GEN, GEN_PTR, (int)CMarks::rgb_pointer_);
		//app->WriteProfileInt(ENTRY_GEN, GEN_BRKP, (int)CMarks::rgb_breakpoint_);
		//app->WriteProfileInt(ENTRY_GEN, GEN_ERR, (int)CMarks::rgb_error_);

		//    app->WriteProfileBinary(ENTRY_EDIT, EDIT_FONT,  LPBYTE(&LuaSrcView::log_font_), UINT(sizeof LuaSrcView::log_font_));
		app->WriteProfileInt(ENTRY_EDIT, EDIT_TAB_STEP, LuaSrcView::tab_step_);
		//		app->WriteProfileInt(ENTRY_EDIT, EDIT_AUTO_INDENT, LuaSrcView::auto_indent_);
		app->WriteProfileInt(ENTRY_EDIT, EDIT_SYNTAX_CHECK, LuaSrcView::auto_syntax_);
		app->WriteProfileInt(ENTRY_EDIT, EDIT_CAPITALS, LuaSrcView::auto_uppercase_);
		//app->WriteProfileInt(ENTRY_EDIT, EDIT_FILENEW, StudioApp::file_new_);

		app->WriteProfileInt(ENTRY_ASM, ASM_CASE, 1);

		app->WriteProfileInt(ENTRY_VIEW, VIEW_IO_HID,    CIOWindow::hidden_);

		for (int i= 0; fonts[i]; i++)
		{
			app->WriteProfileBinary(ENTRY_VIEW, idents[i], LPBYTE(fonts[i]), UINT(sizeof *fonts[i]));
			app->WriteProfileInt(ENTRY_VIEW, tcolors[i], int(*text_color[i]));
			app->WriteProfileInt(ENTRY_VIEW, bcolors[i], int(*bkgnd_color[i]));
		}

		for (int clr= 0; syntax_colors[clr]; ++clr)
			app->WriteProfileInt(ENTRY_VIEW, syntax_colors[clr], int(*color_syntax[clr]));

		for (int style= 0; syntax_font[style]; ++style)
			app->WriteProfileInt(ENTRY_VIEW, syntax_font[style], *syntax_font_style[style]);

		CSizingControlBar::GlobalSaveState(this, REG_ENTRY_CONTROL_BARS);
		SaveBarState(REG_ENTRY_CONTROL_BARS);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_SIM_ASSEMBLE, OnAssemble)
	ON_UPDATE_COMMAND_UI(ID_SIM_ASSEMBLE, OnUpdateAssemble)
	ON_UPDATE_COMMAND_UI(ID_SIM_DEBUG, OnUpdateSymDebug)
	ON_COMMAND(ID_SIM_DEBUG, OnSimDebug)
	ON_COMMAND(ID_SIM_STEP_INTO, OnSimStepInto)
	ON_UPDATE_COMMAND_UI(ID_SIM_STEP_INTO, OnUpdateSymStepInto)
	ON_COMMAND(ID_SIM_SKIP_INSTR, OnSimSkipInstr)
	ON_UPDATE_COMMAND_UI(ID_SIM_SKIP_INSTR, OnUpdateSymSkipInstr)
	ON_COMMAND(ID_SIM_BREAKPOINT, OnSimBreakpoint)
	ON_UPDATE_COMMAND_UI(ID_SIM_BREAKPOINT, OnUpdateSymBreakpoint)
	ON_COMMAND(ID_SIM_BREAK, OnSimBreak)
	ON_UPDATE_COMMAND_UI(ID_SIM_BREAK, OnUpdateSymBreak)
	ON_COMMAND(ID_SIM_GO, OnSimGo)
	ON_UPDATE_COMMAND_UI(ID_SIM_GO, OnUpdateSymGo)
	ON_COMMAND(ID_SIM_OPTIONS, OnOptions)
	ON_UPDATE_COMMAND_UI(ID_SIM_OPTIONS, OnUpdateOptions)
	ON_COMMAND(ID_SIM_GO_LINE, OnSimGoToLine)
	ON_UPDATE_COMMAND_UI(ID_SIM_GO_LINE, OnUpdateSymGoToLine)
	ON_COMMAND(ID_SIM_SKIP_TO_LINE, OnSimSkipToLine)
	ON_UPDATE_COMMAND_UI(ID_SIM_SKIP_TO_LINE, OnUpdateSymSkipToLine)
	ON_COMMAND(ID_SIM_STEP_OUT, OnSimStepOut)
	ON_UPDATE_COMMAND_UI(ID_SIM_STEP_OUT, OnUpdateSymStepOut)
	ON_COMMAND(ID_SIM_STEP_OVER, OnSimStepOver)
	ON_UPDATE_COMMAND_UI(ID_SIM_STEP_OVER, OnUpdateSymStepOver)
	ON_COMMAND(ID_SIM_EDIT_BREAKPOINT, OnSimEditBreakpoint)
	ON_UPDATE_COMMAND_UI(ID_SIM_EDIT_BREAKPOINT, OnUpdateSymEditBreakpoint)
	ON_COMMAND(ID_SIM_RESTART, OnSimRestart)
	ON_UPDATE_COMMAND_UI(ID_SIM_RESTART, OnUpdateSymRestart)
	//ON_COMMAND(ID_FILE_SAVE_CODE, OnFileSaveCode)
	//ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_CODE, OnUpdateFileSaveCode)
	ON_COMMAND(ID_VIEW_DEASM, OnViewDeasm)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DEASM, OnUpdateViewDeasm)
	ON_COMMAND(ID_VIEW_IDENT, OnViewIdents)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IDENT, OnUpdateViewIdents)
	ON_COMMAND(ID_VIEW_MEMORY, OnViewMemory)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MEMORY, OnUpdateViewMemory)
	ON_COMMAND(ID_EDITOR_OPT, OnEditorOpt)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_OPT, OnUpdateEditorOpt)
	ON_COMMAND(ID_VIEW_IO_WINDOW, OnViewIOWindow)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IO_WINDOW, OnUpdateViewIOWindow)
	ON_WM_DESTROY()
	//ON_COMMAND(ID_FILE_OPEN_CODE, OnFileLoadCode)
	//ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_CODE, OnUpdateFileLoadCode)
	ON_COMMAND(ID_DEASM_OPTIONS, OnDeasmOptions)
	ON_UPDATE_COMMAND_UI(ID_DEASM_OPTIONS, OnUpdateDeasmOptions)

	ON_COMMAND(ID_VIEW_REGISTERBAR, OnViewRegisterWnd)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REGISTERBAR, OnUpdateIdViewRegisterbar)

	ON_WM_SYSCOLORCHANGE()

	ON_UPDATE_COMMAND_UI(ID_MEMORY_OPTIONS, OnUpdateMemoryOptions)
	ON_COMMAND(ID_MEMORY_OPTIONS, OnMemoryOptions)
	ON_WM_TIMER()

	ON_COMMAND(ID_VIEW_STACK, OnViewStack)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STACK, OnUpdateViewStack)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOCAL_VARS, OnUpdateViewLocalVars)
	ON_COMMAND(ID_VIEW_LOCAL_VARS, OnViewLocalVars)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GLOBAL_VARS, OnUpdateViewGlobalVars)
	ON_COMMAND(ID_VIEW_GLOBAL_VARS, OnViewGlobalVars)

	ON_COMMAND(ID_VIEW_LOG, OnViewLog)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOG, OnUpdateViewLog)
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	//  ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
	//ON_MESSAGE(WM_USER+9998, OnUpdateState)
	ON_MESSAGE(CBroadcast::WM_USER_START_DEBUGGER, OnStartDebugger)
	ON_MESSAGE(CBroadcast::WM_USER_EXIT_DEBUGGER, OnExitDebugger)
	ON_MESSAGE(CBroadcast::WM_USER_PROG_MEM_CHANGED, OnChangeCode)

	ON_MESSAGE(CBroadcast::WM_USER_NEW_LINE, OnExecEvent)
END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	0,
	0,
	//#ifdef USE_CRYSTAL_EDIT
	ID_EDIT_INDICATOR_POSITION,
	ID_INDICATOR_OVR,
	//#endif
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	last_page_ = 0;	// ostatnio wywo³ana strona (zak³adka) w pude³ku opcji

	int i= 0;
	windows_[i++] = &m_hWnd;
	windows_[i++] = &IO_window_.m_hWnd;
	windows_[i++] = NULL;

	timer_ = 0;
}

CMainFrame::~CMainFrame()
{
	//  if (idents_)
	//    delete idents_;
}

//-----------------------------------------------------------------------------

const DWORD CMainFrame::dock_bar_map_ex[4][2] =
{
	{ AFX_IDW_DOCKBAR_TOP,      CBRS_TOP    },
	{ AFX_IDW_DOCKBAR_BOTTOM,   CBRS_BOTTOM },
	{ AFX_IDW_DOCKBAR_LEFT,     CBRS_LEFT   },
	{ AFX_IDW_DOCKBAR_RIGHT,    CBRS_RIGHT  },
};

void CMainFrame::EnableDockingEx(DWORD dock_style)
{
	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
	ASSERT((dock_style & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

	m_pFloatingFrameClass = RUNTIME_CLASS(CMiniDockFrameWnd);
	for (int i = 0; i < 4; i++)
	{
		if (dock_bar_map_ex[i][1] & dock_style & CBRS_ALIGN_ANY)
		{
			CDockBar* dock = (CDockBar*)GetControlBar(dock_bar_map_ex[i][0]);
			if (dock == NULL)
			{
				dock = new CDockBarEx;
				if (!dock->Create(this, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | dock_bar_map_ex[i][1],
					dock_bar_map_ex[i][0]))
				{
					AfxThrowResourceException();
				}
			}
		}
	}
}


int CMainFrame::OnCreate(LPCREATESTRUCT create_struct)
{
	if (CMDIFrameWnd::OnCreate(create_struct) == -1)
		return -1;

	m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);

	if (!tool_bar_wnd_.Create(this) ||
		!tool_bar_wnd_.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	CString name;
	name.LoadString(IDS_TOOLBAR);
	tool_bar_wnd_.SetWindowText(name);

	if (!status_bar_wnd_.Create(this) ||
		!status_bar_wnd_.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	{		// dodanie pola do wyœwietlania aktualnego wiersza i kolumny
		UINT id;
		UINT style;
		int width;
		CRect area_rect(0,0,0,0);

		if (format_.LoadString(IDS_ROW_COLUMN))
		{
			CString str;
			str.Format(format_,99999,999);
			status_bar_wnd_.GetPaneInfo(1, id, style, width);
			//#ifdef USE_CRYSTAL_EDIT
			status_bar_wnd_.SetPaneInfo(1, id, SBPS_NOBORDERS | SBPS_DISABLED, 1);
			//#else
			//			CClientDC dc(&status_bar_wnd_);
			//			dc.SelectObject(status_bar_wnd_.GetFont());
			//			dc.DrawText(str, -1, area_rect, DT_SINGLELINE | DT_CALCRECT);
			//			status_bar_wnd_.SetPaneInfo(1, id, style, area_rect.Width());
			//#endif
		}

		status_bar_wnd_.GetPaneInfo(2, id, style, width);
		status_bar_wnd_.SetPaneInfo(2, id, style, 16);	// szerokoœæ obrazka

		code_bmp_.LoadMappedBitmap(IDB_CODE);
		debug_bmp_.LoadMappedBitmap(IDB_DEBUG);

		pfn_old_proc_ = (WNDPROC)::SetWindowLong(status_bar_wnd_.m_hWnd,GWL_WNDPROC,(LONG)StatusBarWndProc);
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	tool_bar_wnd_.SetBarStyle(tool_bar_wnd_.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	//	EnableDockingEx(CBRS_ALIGN_ANY); //CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
	EnableDocking(CBRS_ALIGN_ANY);
#ifdef _SCB_REPLACE_MINIFRAME
	m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
#endif //_SCB_REPLACE_MINIFRAME

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	tool_bar_wnd_.EnableDocking(CBRS_ALIGN_ANY);
	//	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&tool_bar_wnd_);


	if (!local_vars_wnd_.Create("Local Variables", this, 1020))
		return -1;

	local_vars_wnd_.SetBarStyle(local_vars_wnd_.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	local_vars_wnd_.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&local_vars_wnd_, AFX_IDW_DOCKBAR_RIGHT);

	if (!global_vars_wnd_.Create("Global Variables", this, 1030))
		return -1;

	global_vars_wnd_.SetBarStyle(global_vars_wnd_.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	global_vars_wnd_.EnableDocking(CBRS_ALIGN_ANY);

	DockBelow(local_vars_wnd_, global_vars_wnd_);

	if (!call_stack_wnd_.Create("Call Stack", this, 1040))
		return -1;

	call_stack_wnd_.SetBarStyle(call_stack_wnd_.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	call_stack_wnd_.EnableDocking(CBRS_ALIGN_ANY);

	DockBelow(global_vars_wnd_, call_stack_wnd_);

	if (!value_stack_wnd_.Create("Value Stack", this, 1010))
		return -1;

	value_stack_wnd_.SetBarStyle(value_stack_wnd_.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	value_stack_wnd_.EnableDocking(CBRS_ALIGN_ANY);

	DockBelow(call_stack_wnd_, value_stack_wnd_);

	for (int i =0; cfonts[i]; i++)	// utworzenie fontów
	{
		//    cfonts[i]->DeleteObject();
		cfonts[i]->CreateFontIndirect(fonts[i]);
	}

	if (VerifyBarState(REG_ENTRY_CONTROL_BARS))
	{
		CSizingControlBar::GlobalLoadState(this, REG_ENTRY_CONTROL_BARS);
		LoadBarState(REG_ENTRY_CONTROL_BARS);
	}

	return 0;
}


void CMainFrame::DockBelow(CControlBar& first, CControlBar& second)
{
	RecalcLayout();
	CRect rect(0,0,0,0);
	first.GetWindowRect(rect);
	rect.OffsetRect(0, 1);
	DockControlBar(&second, AFX_IDW_DOCKBAR_RIGHT, rect);
}


// This function is Copyright (c) 2000, Cristi Posea.
// See www.datamekanix.com for more control bars tips&tricks.
BOOL CMainFrame::VerifyBarState(LPCTSTR profile_name)
{
	CDockState state;
	state.LoadState(profile_name);

	for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
	{
		CControlBarInfo* info = (CControlBarInfo*)state.m_arrBarInfo[i];
		ASSERT(info != NULL);
		int docked_count = info->m_arrBarID.GetSize();
		if (docked_count > 0)
		{
			// dockbar
			for (int j = 0; j < docked_count; j++)
			{
				UINT id = (UINT) info->m_arrBarID[j];
				if (id == 0) continue; // row separator
				if (id > 0xFFFF)
					id &= 0xFFFF; // placeholder - get the ID
				if (GetControlBar(id) == NULL)
					return FALSE;
			}
		}

		if (!info->m_bFloating) // floating dockbars can be created later
			if (GetControlBar(info->m_nBarID) == NULL)
				return FALSE; // invalid bar ID
	}

	return TRUE;
}

//-----------------------------------------------------------------------------

LRESULT CALLBACK CMainFrame::StatusBarWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CWnd* cwnd= FromHandlePermanent(wnd);

	switch (msg)
	{
	case WM_PAINT:
		{
			LRESULT ret= (*CMainFrame::pfn_old_proc_)(wnd,msg,wParam,lParam);
			if (ret == 0)
			{
				if (!GetDebugger().IsActive())
					return ret;

				// active program available?
				bool active= !GetDebugger().IsFinished();

				CRect rect;
				(*pfn_old_proc_)(wnd,SB_GETRECT,2,(LPARAM)(RECT*)rect);	// miejsce na obrazek - wymiary
				int borders[3];
				(*pfn_old_proc_)(wnd,SB_GETBORDERS,0,(LPARAM)borders);		// gruboœæ obwódki
				rect.DeflateRect(borders[0]+1,borders[1]-1);
				CClientDC dc(cwnd);
				if (dc)
				{
					CDC memDC;
					memDC.CreateCompatibleDC(&dc);
					if (memDC)
					{
						CBitmap* old_bmp= memDC.SelectObject(active ? &debug_bmp_ : &code_bmp_);
						dc.BitBlt(rect.left+2, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
						memDC.SelectObject(old_bmp);
					}
				}
			}
			return ret;
		}

	default:
		return (*CMainFrame::pfn_old_proc_)(wnd,msg,wParam,lParam);
	}
}

//-----------------------------------------------------------------------------

afx_msg LRESULT CMainFrame::OnStartDebugger(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	RECT rect;
	status_bar_wnd_.SendMessage(SB_GETRECT,2,(LPARAM)&rect);	// miejsce na obrazek - wymiary
	status_bar_wnd_.InvalidateRect(&rect);		// obrazek pch³y do przerysowania
	return 0;
}


afx_msg LRESULT CMainFrame::OnExitDebugger(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	RECT rect;
	status_bar_wnd_.SendMessage(SB_GETRECT,2,(LPARAM)&rect);	// miejsce na obrazek - wymiary
	status_bar_wnd_.InvalidateRect(&rect);		// obrazek pch³y do przerysowania
	return 0;
}


afx_msg LRESULT CMainFrame::OnChangeCode(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	RECT rect;
	status_bar_wnd_.SendMessage(SB_GETRECT,2,(LPARAM)&rect);	// miejsce na obrazek - wymiary
	status_bar_wnd_.InvalidateRect(&rect);		// obrazek pch³y do przerysowania
	return 0;
}


static void SetPointer(LuaSrcView* view, int line, bool scroll)
{
	if (view == 0)
		return;

	CDocument* doc= view->GetDocument();
	POSITION pos= doc->GetFirstViewPosition();
	while (pos != NULL)
	{
		if (LuaSrcView* src_view= dynamic_cast<LuaSrcView*>(doc->GetNextView(pos)))
			src_view->SetPointer(line, scroll && src_view == view);
	}
}


int ParseLine(const CString& path, const char* msg)
{
	if (strlen(msg) < static_cast<size_t>(path.GetLength()))
		return 0;

	const char* p= path;

	while (*msg++ == *p++)
		;

	if (msg[-1] == ':')
	{
		int line= atoi(msg);
		return line;
	}

	return 0;
}


LRESULT CMainFrame::OnExecEvent(WPARAM ev, LPARAM data)
{
	if (ev == Lua::Start)
	{
		if (LuaSrcView* view= GetCurrentView())
		{
			SetPointer(view, -1, false);	// hide pointer
			//			status_bar_wnd_.SetPaneText(0, "Ready to run");
		}
	}
	else if (ev == Lua::NewLine)
	{
		int cur_line= data;

		if (Lua* lua= GetDebugger().GetLua())
		{
			Lua::StackFrame top;
			if (cur_line > 0 && lua->GetCurrentSource(top))
			{
				const char* file_path= top.SourcePath();
				if (LuaSrcView* view= OpenView(file_path))
				{
					SetPointer(view, cur_line - 1, true);
				}
			}
		}
	}
	else if (ev == Lua::Finished)
	{
		if (LuaSrcView* view= GetCurrentView())
		{
			SetPointer(view, -1, false);	// hide pointer

			CString msg= GetDebugger().GetLastStatMsg();

			if (CDocument* doc= view->GetDocument())
			{
				const CString& path= doc->GetPathName();

				if (int line= ParseLine(path, msg))
					view->SetErrMark(line - 1);		// mark error line

				status_bar_wnd_.SetPaneText(0, msg);
			}
		}
	}
	else if (ev == Lua::Running)
	{
		if (LuaSrcView* view= GetCurrentView())
		{
			SetPointer(view, -1, false);	// hide pointer
			status_bar_wnd_.SetPaneText(0, "Run");
		}
	}

	if (Lua* lua= GetDebugger().GetLua())
	{
		value_stack_wnd_.Notify(ev, data, lua);
		local_vars_wnd_.Notify(ev, data, lua);
		global_vars_wnd_.Notify(ev, data, lua);
		call_stack_wnd_.Notify(ev, data, lua);
	}

	return 0;
}


//-----------------------------------------------------------------------------

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	CWinApp* app = AfxGetApp();

	CRect desk;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, desk, 0);

	cs.x = app->GetProfileInt(REG_ENTRY_MAINFRM, REG_POSX, 50);
	cs.y = app->GetProfileInt(REG_ENTRY_MAINFRM, REG_POSY, 50);
	cs.cx = app->GetProfileInt(REG_ENTRY_MAINFRM, REG_SIZX, desk.Width() - 100);
	cs.cy = app->GetProfileInt(REG_ENTRY_MAINFRM, REG_SIZY, desk.Height() - 100);

	// prevent from appearing outside desk area
	if (cs.x < desk.left)
		cs.x = desk.left;
	if (cs.y < desk.top)
		cs.y = desk.top;
	if (cs.x + cs.cx > desk.right)
		cs.x = desk.right - min(cs.cx, desk.Width());
	if (cs.y + cs.cy > desk.bottom)
		cs.y = desk.bottom - min(cs.cy, desk.Height());

	if (app->GetProfileInt(REG_ENTRY_MAINFRM, REG_STATE, 0))	// maximize?
		StudioApp::maximize_ = true;
	//  StudioApp::file_new_ = app->GetProfileInt(REG_ENTRY_MAINFRM,REG_FILENEW,1);	// new file
	ConfigSettings(true);		// odczyt ustawieñ

	return CMDIFrameWnd::PreCreateWindow(cs);
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose()
{
	if (GetDebugger().IsRunning())
	{
		if (IO_window_.IsWaiting())
		{
			IO_window_.ExitModalLoop();
			return;
		}
		if (AfxMessageBox(IDS_MAINFRM_PROG_RUNNING,MB_YESNO) == IDYES)
		{
			GetDebugger().AbortProg();
			if (IO_window_.m_hWnd != 0)
				IO_window_.SendMessage(CBroadcast::WM_USER_EXIT_DEBUGGER,0,0);
			//if (register_bar_wnd_.m_hWnd != 0)
			//	register_bar_wnd_.SendMessage(CBroadcast::WM_USER_EXIT_DEBUGGER,0,0);
			//if (idents_.m_hWnd != 0)
			//	idents_.SendMessage(CBroadcast::WM_USER_EXIT_DEBUGGER,0,0);
		}
		else
			return;
	}

	CWinApp* app = AfxGetApp();

	WINDOWPLACEMENT wp;
	if (GetWindowPlacement(&wp))
	{						   // zapisanie po³o¿enia okna g³ównego
		CRect wnd(wp.rcNormalPosition);
		app->WriteProfileInt(REG_ENTRY_MAINFRM,REG_POSX,wnd.left);
		app->WriteProfileInt(REG_ENTRY_MAINFRM,REG_POSY,wnd.top);
		app->WriteProfileInt(REG_ENTRY_MAINFRM,REG_SIZX,wnd.Width());
		app->WriteProfileInt(REG_ENTRY_MAINFRM,REG_SIZY,wnd.Height());
		app->WriteProfileInt(REG_ENTRY_MAINFRM,REG_STATE,wp.showCmd==SW_SHOWMAXIMIZED ? 1 : 0);
	}

	CMDIFrameWnd::OnClose();
}


void CMainFrame::OnDestroy() 
{
	if (timer_)
		KillTimer(timer_);
	ConfigSettings(false);		// save settings
	CMDIFrameWnd::OnDestroy();
}

//-----------------------------------------------------------------------------

void CMainFrame::StartDebuggerSession()
{
	SendMessageToViews(WM_USER_START_DEBUGGER);
	SendMessageToPopups(WM_USER_START_DEBUGGER);//, (WPARAM)restart);
}


void CMainFrame::ExitDebuggerSession()
{
	GetDebugger().AbortProg();
	SendMessageToViews(WM_USER_EXIT_DEBUGGER);
	SendMessageToPopups(WM_USER_EXIT_DEBUGGER);
}


void CMainFrame::OnAssemble()
{
	LuaSrcView* view= GetCurrentView();
	if (view == 0)
		return;

	if (IO_window_.IsWaiting())
	{
		IO_window_.SetFocus();
		return;
	}

	SendMessageToViews(WM_USER_REMOVE_ERR_MARK);

	//if (theApp.global_.IsDebugger())	// dzia³a debugger?
	//{
	//	if (AfxMessageBox(IDS_STOP_DEBUG,MB_OKCANCEL) != IDOK)
	//		return;
	//	ExitDebugMode();			// wyjœcie z trybu debuggera
	//}

	if (CDocument* doc= view->GetDocument())
	{
		if (!doc->SaveModified())
			return;

		if (doc->IsModified())
			return;

		// before assembly start set current dir to the document directory,
		// so include directive will find included files
		//
		const CString& path= doc->GetPathName();
		if (!path.IsEmpty())
		{
			CString dir= path.Left(path.ReverseFind('\\'));
			::SetCurrentDirectory(dir);

			std::auto_ptr<Lua> lua(new Lua());

			const char* msg= 0;
			if (lua->LoadFile(path, msg))
			{
				//ProgBuf p;
				//lua.Dump(p, true);
				//lua.Call();

				StartDebuggerSession();

				GetDebugger().SetNewContext(lua);

				theApp.global_.ClearOutput();

				SetPointer(view, -1, false);	// hide old pointer
				view->ClearAllBreakpoints();
			}
			else
			{
				if (int line= ParseLine(path, msg))
					view->SetErrMark(line - 1);		// mark error line

				status_bar_wnd_.SetPaneText(0, msg);
			}

		}
	}
}


void CMainFrame::OnUpdateAssemble(CCmdUI* cmd_ui) 
{
	cmd_ui->Enable(GetCurrentDocument() != NULL &&	// jest aktywny dokument?
		!IO_window_.IsWaiting());
}


LuaSrcDoc* CMainFrame::GetCurrentDocument()
{
	if (CMDIChildWnd* wnd= MDIGetActive())
		if (CDocument* doc= wnd->GetActiveDocument())
			if (doc->IsKindOf(RUNTIME_CLASS(LuaSrcDoc)))
				return static_cast<LuaSrcDoc*>(doc);

	return 0;
}


LuaSrcView* CMainFrame::OpenView(const char* file_path)
{
	if (file_path == 0)
		return 0;

	if (LuaSrcDoc* doc= GetCurrentDocument())
		if (doc->GetPathName() == file_path)
		{
			POSITION pos = doc->GetFirstViewPosition();
			if (pos != NULL)
				return dynamic_cast<LuaSrcView*>(doc->GetNextView(pos));
		}

		StudioApp* app= static_cast<StudioApp*>(AfxGetApp());

		app->do_not_add_to_recent_file_list_ = true;
		CDocument* doc= app->OpenDocumentFile(file_path);
		app->do_not_add_to_recent_file_list_ = false;

		if (LuaSrcDoc* src_doc= dynamic_cast<LuaSrcDoc*>(doc))
		{
			POSITION pos = src_doc->GetFirstViewPosition();
			if (pos != NULL)
				return dynamic_cast<LuaSrcView*>(src_doc->GetNextView(pos));
		}

		return 0;
}


LuaSrcView* CMainFrame::GetCurrentView()
{
	CMDIChildWnd* wnd= MDIGetActive();
	if (wnd==NULL)
		return NULL;

	CView* view= wnd->GetActiveView();	// aktywne okno 'view'
	if (view==NULL || !view->IsKindOf( RUNTIME_CLASS(LuaSrcView) ))
		return NULL;

	return static_cast<LuaSrcView*>(view);
}

//-----------------------------------------------------------------------------

void CMainFrame::OnUpdateSymDebug(CCmdUI* cmd_ui)
{
	//	cmd_ui->Enable(theApp.global_.IsCodePresent());	// jest zasemblowany program?
	cmd_ui->Enable();
	cmd_ui->SetCheck(GetDebugger().GetLua() != 0);
}

void CMainFrame::OnSimDebug()		// uruchomienie debuggera
{
	if (GetDebugger().IsActive())   // ju¿ uruchomiony?
	{
		OnSimDebugStop();
	}
	else
	{
		//		if (!theApp.global_.IsCodePresent())
		//			return;
		//		theApp.global_.StartDebug();
		//		tool_bar_wnd_.OnInitialUpdate();
		//		DelayedUpdateAll();
		//		StartIntGenerator();
	}
	/*
	if (theApp.global_.GetDebugger() == NULL)
	return;
	register_bar_wnd_.Update( theApp.global_.GetDebugger().GetContext(), theApp.global_.GetStatMsg() );

	if (IO_window_.m_hWnd != 0)
	{
	IO_window_.SendMessage(CBroadcast::WM_USER_START_DEBUGGER,0,0);
	IO_window_.SendMessage(CIOWindow::CMD_CLS);
	}
	if (register_bar_wnd_.m_hWnd != 0)
	register_bar_wnd_.PostMessage(CBroadcast::WM_USER_START_DEBUGGER,0,0);
	if (idents_.m_hWnd != 0)
	idents_.PostMessage(CBroadcast::WM_USER_START_DEBUGGER,0,0);
	*/
}

//-----------------------------------------------------------------------------
/*
void CMainFrame::ClearPositionText()
{
status_bar_wnd_.SetPaneText(1,NULL);
}
*/

void CMainFrame::SetPositionText(int row, int col, bool insert_mode)
{
	CString position;
	position.Format(format_, row, col);
	status_bar_wnd_.SetPaneText(3, position);
	status_bar_wnd_.SetPaneText(4, insert_mode ? "Ins" : "Ovr");
	status_bar_wnd_.UpdateWindow();
}

/*
void CMainFrame::SetRowColumn(CEdit &edit)
{
int idx= edit.LineIndex();
if (idx == -1)
return;
int row= edit.LineFromChar(idx);

SetPositionText(row+1,0);
}
*/

//-----------------------------------------------------------------------------

void CMainFrame::OnSimBreakpoint() 
{
	LuaSrcView* view= (LuaSrcView*)(GetActiveFrame()->GetActiveView());
	//  ASSERT(view==NULL || view->IsKindOf(RUNTIME_CLASS(LuaSrcView)));

	if (!GetDebugger().IsActive() || view==NULL)
		return;

	if (view->IsKindOf(RUNTIME_CLASS(LuaSrcView)))
	{
		int line= view->GetCurrLineNo();	// bie¿¹cy wiersz

		if (GetDebugger().ToggleBreakpoint(line, view->GetDocument()->GetPathName()))
			AddBreakpoint(view, line, Defs::BPT_EXECUTE);
		else
			view->RemoveBreakpoint(line);
		/*
		// ustawienie miejsca przerwania w kodzie wynikowym odpowiadaj¹cym bie¿¹cemu wierszowi
		Defs::Breakpoint bp= theApp.global_.SetBreakpoint( line, view->GetDocument()->GetPathName() );
		if (bp != Defs::BPT_NO_CODE)
		{
		if (bp != Defs::BPT_NONE)
		AddBreakpoint(view, line, bp);
		else
		RemoveBreakpoint(view, line);
		}
		else
		AfxMessageBox(IDS_SRC_NO_CODE); */
	}
	//else if (view->IsKindOf(RUNTIME_CLASS(CDeasm6502View)))
	//{
	//	;
	//}
	else
	{
		ASSERT(false);	// aktywne okno nierozpoznane
		return;
	}
}

void CMainFrame::OnUpdateSymBreakpoint(CCmdUI* cmd_ui) 
{  
	cmd_ui->Enable(GetDebugger().IsActive() && GetActiveFrame()->GetActiveView() != 0);
}


void CMainFrame::AddBreakpoint(LuaSrcView* view, int line, Defs::Breakpoint bp)
{
	if (view == 0)
		return;

	CDocument* doc= view->GetDocument();
	POSITION pos= doc->GetFirstViewPosition();
	while (pos != NULL)
		if (LuaSrcView* src_view= dynamic_cast<LuaSrcView*>(doc->GetNextView(pos)))
			src_view->AddBreakpoint(line, bp);
}

void CMainFrame::RemoveBreakpoint(LuaSrcView* view, int line)
{
	if (view == 0)
		return;

	CDocument* doc= view->GetDocument();
	POSITION pos= doc->GetFirstViewPosition();
	while (pos != NULL)
		if (LuaSrcView* src_view= dynamic_cast<LuaSrcView*>(doc->GetNextView(pos)))
			src_view->RemoveBreakpoint(line);
}


void CMainFrame::OnSimEditBreakpoint()
{
}

void CMainFrame::OnUpdateSymEditBreakpoint(CCmdUI* cmd_ui)
{
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimBreak()		// stop execution
{
	if (!GetDebugger().IsRunning())
		return;	

	GetDebugger().Break();		// przerwanie dzia³aj¹cego programu
	DelayedUpdateAll();

	AfxGetMainWnd()->SetFocus();		// restore focus (so it's not in i/o window)
}

void CMainFrame::OnUpdateSymBreak(CCmdUI* cmd_ui) 
{
	cmd_ui->Enable(GetDebugger().IsRunning());
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimSkipInstr()	// skip current line
{
}

void CMainFrame::OnUpdateSymSkipInstr(CCmdUI* cmd_ui) 
{
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimGo()		// run program
{
	if (GetDebugger().IsStopped())
		GetDebugger().Run();
}

void CMainFrame::OnUpdateSymGo(CCmdUI* cmd_ui) 
{
	cmd_ui->Enable(GetDebugger().IsStopped());
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimGoToLine()
{
	//LuaSrcView* view= (LuaSrcView *)( GetActiveFrame()->GetActiveView() );
	//ASSERT(view==NULL || view->IsKindOf(RUNTIME_CLASS(LuaSrcView)));

	//if (view==NULL || !theApp.global_.IsDebugger() || theApp.global_.IsProgramRunning() ||
	//	theApp.global_.IsProgramFinished() )
	//	return;

	//int line= view->GetCurrLineNo();
	//Defs::DbgFlag flg= theApp.global_.GetLineDebugFlags(line,view->GetDocument()->GetPathName());
	//if (flg == Defs::DBG_EMPTY || (flg & Defs::DBG_MACRO))	// wiersz bez kodu wynikowego?
	//{
	//	AfxMessageBox(IDS_SRC_NO_CODE2);
	//	return;
	//}
	//else if (flg & Defs::DBG_DATA)			// wiersz z danymi zamiast rozkazów?
	//{
	//	if (AfxMessageBox(IDS_SRC_DATA,MB_YESNO) != IDYES)
	//		return;
	//}

	//theApp.global_.SetTempExecBreakpoint(line,view->GetDocument()->GetPathName());
	//theApp.global_.GetDebugger().Run();	// uruchomienie po ustawieniu tymczasowego przerwania
}

void CMainFrame::OnUpdateSymGoToLine(CCmdUI* cmd_ui) 
{
	//cmd_ui->Enable( theApp.global_.IsDebugger() &&	// jest dzia³aj¹cy debugger
	//  !theApp.global_.IsProgramRunning() &&		// oraz zatrzymany
	//  !theApp.global_.IsProgramFinished() &&		// niezakoñczony program
	//  GetActiveFrame()->GetActiveView() &&		// i aktywny dokument?
	//  GetActiveFrame()->GetActiveView()->IsKindOf(RUNTIME_CLASS(LuaSrcView)) );
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimSkipToLine()
{
	//LuaSrcView*view= (LuaSrcView *)( GetActiveFrame()->GetActiveView() );
	//ASSERT(view==NULL || view->IsKindOf(RUNTIME_CLASS(LuaSrcView)));

	//if (view==NULL || !theApp.global_.IsDebugger() || theApp.global_.IsProgramRunning() ||
	//  theApp.global_.IsProgramFinished() )
	//  return;
	//int line= view->GetCurrLineNo();
	//Defs::DbgFlag flg= theApp.global_.GetLineDebugFlags(line,view->GetDocument()->GetPathName());
	//if (flg == Defs::DBG_EMPTY || (flg & Defs::DBG_MACRO))	// wiersz bez kodu wynikowego?
	//{
	//  AfxMessageBox(IDS_SRC_NO_CODE3);
	//  return;
	//}
	//else if (flg & Defs::DBG_DATA)			// wiersz z danymi zamiast rozkazów?
	//{
	//  if (AfxMessageBox(IDS_SRC_DATA,MB_YESNO) != IDYES)
	//    return;
	//}
	//UINT16 addr= theApp.global_.GetLineCodeAddr(line,view->GetDocument()->GetPathName());
	//theApp.global_.GetDebugger().SkipToAddr(addr);
}

void CMainFrame::OnUpdateSymSkipToLine(CCmdUI* cmd_ui) 
{
	//cmd_ui->Enable( theApp.global_.IsDebugger() &&	// jest dzia³aj¹cy debugger
	//  !theApp.global_.IsProgramRunning() &&		// oraz zatrzymany
	//  !theApp.global_.IsProgramFinished() &&		// niezakoñczony program
	//  GetActiveFrame()->GetActiveView() &&		// i aktywny dokument?
	//  GetActiveFrame()->GetActiveView()->IsKindOf(RUNTIME_CLASS(LuaSrcView)) );
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimStepOut()
{
	if (!GetDebugger().IsStopped())
		return;
	GetDebugger().StepOut();
}

void CMainFrame::OnUpdateSymStepOut(CCmdUI* cmd_ui) 
{
	cmd_ui->Enable(GetDebugger().IsStopped());
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimStepInto()	// wykonanie bie¿¹cej instrukcji
{
	if (!GetDebugger().IsStopped())
		return;
	GetDebugger().StepInto();
	//	DelayedUpdateAll();
}

void CMainFrame::OnUpdateSymStepInto(CCmdUI* cmd_ui)
{
	cmd_ui->Enable(GetDebugger().IsStopped());
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimStepOver()
{
	if (!GetDebugger().IsStopped())
		return;
	GetDebugger().StepOver();
}

void CMainFrame::OnUpdateSymStepOver(CCmdUI* cmd_ui)
{
	cmd_ui->Enable(GetDebugger().IsStopped());
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimRestart()
{
	//if (!theApp.global_.IsDebugger() || theApp.global_.IsProgramRunning() )
	//  return;
	//theApp.global_.RestartProgram();
	//DelayedUpdateAll();
}

void CMainFrame::OnUpdateSymRestart(CCmdUI* cmd_ui) 
{
	//cmd_ui->Enable( theApp.global_.IsDebugger() &&	// jest dzia³aj¹cy debugger
	//  !theApp.global_.IsProgramRunning() );		// oraz zatrzymany program?
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSimDebugStop()
{
	ExitDebuggerSession();
}

void CMainFrame::OnUpdateSymDebugStop(CCmdUI* cmd_ui)
{
	cmd_ui->Enable(GetDebugger().IsActive());
}

//=============================================================================


int CMainFrame::Options(int page)
{
	return -1;
}


void CMainFrame::OnOptions() 
{
	last_page_ = Options(last_page_);
}


void CMainFrame::OnUpdateOptions(CCmdUI* cmd_ui) 
{
	cmd_ui->Enable(true);
}


int CMainFrame::RedrawAllViews(int chgHint)	// 'Invalidate' wszystkich okien
{
	CWinApp* app= AfxGetApp();
	POSITION posTempl= app->GetFirstDocTemplatePosition();
	while (posTempl != NULL)
	{
		CDocTemplate* templ= app->GetNextDocTemplate(posTempl);
		POSITION posDoc= templ->GetFirstDocPosition();
		while (posDoc != NULL)
		{
			CDocument* doc= templ->GetNextDoc(posDoc);
			POSITION posView = doc->GetFirstViewPosition();
			while (posView != NULL)
			{
				CView* view = doc->GetNextView(posView);
				if (view->IsKindOf(RUNTIME_CLASS(LuaSrcView)))
				{
					LuaSrcView* src_view= static_cast<LuaSrcView*>(view);
#ifdef USE_CRYSTAL_EDIT
					src_view->SetTabSize(LuaSrcView::tab_step_);
					src_view->SetAutoIndent(LuaSrcView::auto_indent_);
#else
					int tab_step= LuaSrcView::tab_step_ * 1;
					src_view->GetCtrl().SetTabWidth(tab_step);
					//					src_view->GetEditCtrl().SetTabStops(tab_step);
#endif
					src_view->SelectEditFont();
				}
				view->Invalidate();
				//	view->UpdateWindow();
			}
		}
		//      GetNextDoc(posDoc)->UpdateAllViews(NULL);
	}
	return 0;
}

//-----------------------------------------------------------------------------

void CMainFrame::OnViewRegisterWnd()
{
	ShowControlBar(&value_stack_wnd_, !value_stack_wnd_.IsVisible(), false);
}

void CMainFrame::OnUpdateIdViewRegisterbar(CCmdUI* cmd_ui)
{
	cmd_ui->SetCheck(value_stack_wnd_.m_hWnd != 0 && value_stack_wnd_.IsVisible());
}

//-----------------------------------------------------------------------------

//void CMainFrame::OnFileSaveCode()
//{
//  CString filter;
//  filter.LoadString(IDS_SAVE_CODE);
//  CSaveCode dlg(_T("Binary Code"),filter,this);
//  if (dlg.DoModal() == IDOK)
//    dlg.SaveCode();
//}
//
//void CMainFrame::OnUpdateFileSaveCode(CCmdUI* cmd_ui)
//{
//  cmd_ui->Enable(theApp.global_.IsCodePresent());	// jest kod programu?
//}

//-----------------------------------------------------------------------------

void CMainFrame::OnViewDeasm() 
{
	//if (!theApp.global_.IsDebugger())	// nie ma dzia³aj¹cego debuggera?
	//  return;

	//theApp.global_.CreateDeasm();
}

void CMainFrame::OnUpdateViewDeasm(CCmdUI* cmd_ui) 
{
	//  cmd_ui->Enable( theApp.global_.IsDebugger() );	// jest dzia³aj¹cy debugger?
}

//-----------------------------------------------------------------------------

void CMainFrame::OnViewIdents() 
{
	//if (theApp.global_.IsDebugger()) //InfoPresent())	// jest zasemblowany program?
	//{
	//	if (idents_.m_hWnd != 0)	// jest ju¿ okno?
	//		idents_.ShowWindow((idents_.GetStyle() & WS_VISIBLE) ? SW_HIDE : SW_NORMAL);
	//	else
	//	{
	//		idents_.Create(theApp.global_.GetDebug());
	//		idents_.ShowWindow(SW_SHOWNA);
	//	}
	//}
	//else		// nie ma zasemblowanego programu
	//{
	//	if (idents_.m_hWnd != 0)
	//		idents_.ShowWindow(SW_HIDE);
	//}

	//	tool_bar_wnd_.OnInitialUpdate();
}

void CMainFrame::OnUpdateViewIdents(CCmdUI* cmd_ui) 
{
	//cmd_ui->Enable(theApp.global_.IsDebugger());	// jest zasemblowany program?
	//cmd_ui->SetCheck(/*idents_ != NULL &&*/ idents_.m_hWnd != 0 && (idents_.GetStyle() & WS_VISIBLE) != 0);
}

//-----------------------------------------------------------------------------

void CMainFrame::OnViewMemory() 
{
	//if (theApp.global_.IsCodePresent())		// jest program?
	//{
	//	if (memory_.m_hWnd != 0)	// jest ju¿ okno?
	//		memory_.ShowWindow((memory_.GetStyle() & WS_VISIBLE) ? SW_HIDE : SW_NORMAL);
	//	else
	//	{
	//		memory_.Create(theApp.global_.GetMem(), theApp.global_.GetStartAddr(), CMemoryInfo::VIEW_MEMORY);
	//		memory_.ShowWindow(SW_SHOWNA);
	//	}
	//}
	//else		// nie ma programu
	//	if (memory_.m_hWnd != 0)
	//		memory_.ShowWindow(SW_HIDE);

	//	tool_bar_wnd_.OnInitialUpdate();
}

void CMainFrame::OnUpdateViewMemory(CCmdUI* cmd_ui) 
{
	//cmd_ui->Enable(theApp.global_.IsCodePresent());	// jest program?
	//cmd_ui->SetCheck(memory_.m_hWnd != 0 && (memory_.GetStyle() & WS_VISIBLE) != 0);
}

//-----------------------------------------------------------------------------

void CMainFrame::OnEditorOpt() 
{
	last_page_ = Options(2);		// opcje edytora
}

void CMainFrame::OnUpdateEditorOpt(CCmdUI* cmd_ui) 
{
	cmd_ui->Enable(true);
}

//-----------------------------------------------------------------------------

void CMainFrame::OnViewIOWindow() 
{
	if (!GetDebugger().IsActive())
		return;

	if (!IO_window_.m_hWnd)	// nie ma okna?
	{
		IO_window_.Create();
		IO_window_.ShowWindow(SW_NORMAL);
	}
	else
		IO_window_.ShowWindow((IO_window_.GetStyle() & WS_VISIBLE) ? SW_HIDE : SW_NORMAL);

	//	tool_bar_wnd_.OnInitialUpdate();
}


void CMainFrame::OnUpdateViewIOWindow(CCmdUI* cmd_ui) 
{
	cmd_ui->Enable(GetDebugger().IsActive());
	//  cmd_ui->Enable( true );	// jest dzia³aj¹cy debugger?
	cmd_ui->SetCheck(IO_window_.m_hWnd != 0 && (IO_window_.GetStyle() & WS_VISIBLE) != 0);
}

//-----------------------------------------------------------------------------

//void CMainFrame::OnFileLoadCode()
//{
//  CString filter;
//  filter.LoadString(IDS_LOAD_CODE);
//  CLoadCode dlg(_T(""),filter,this);
//  if (dlg.DoModal() == IDOK)
//    dlg.LoadCode();
//}
//
//
//void CMainFrame::OnUpdateFileLoadCode(CCmdUI* cmd_ui)
//{
//  cmd_ui->Enable( true );
//}

//-----------------------------------------------------------------------------

//void CMainFrame::ExitDebugMode()
//{
//  if (theApp.global_.IsProgramRunning())
//  {
//    if (IO_window_.IsWaiting())
//      IO_window_.ExitModalLoop();
//    theApp.global_.GetDebugger().AbortProg();	// przerwanie dzia³aj¹cego programu
//  }
//  OnSimDebugStop();
//}

//-----------------------------------------------------------------------------

void CMainFrame::OnDeasmOptions()
{
	last_page_ = Options(3);		// opcje deasemblera
}

void CMainFrame::OnUpdateDeasmOptions(CCmdUI* cmd_ui)
{	
	cmd_ui->Enable(true);
}

//-----------------------------------------------------------------------------

void CMainFrame::OnSysColorChange()
{
	CMDIFrameWnd::OnSysColorChange();

	code_bmp_.DeleteObject();
	code_bmp_.LoadMappedBitmap(IDB_CODE);
	debug_bmp_.DeleteObject();
	debug_bmp_.LoadMappedBitmap(IDB_DEBUG);
}

//-----------------------------------------------------------------------------

void CMainFrame::OnUpdateViewLocalVars(CCmdUI* cmd_ui)
{
	cmd_ui->SetCheck(local_vars_wnd_.m_hWnd != 0 && local_vars_wnd_.IsVisible());
}

void CMainFrame::OnViewLocalVars()
{
	ShowControlBar(&local_vars_wnd_, !local_vars_wnd_.IsVisible(), false);
}

//-----------------------------------------------------------------------------

void CMainFrame::OnUpdateViewGlobalVars(CCmdUI* cmd_ui)
{
	cmd_ui->SetCheck(global_vars_wnd_.m_hWnd != 0 && global_vars_wnd_.IsVisible());
}

void CMainFrame::OnViewGlobalVars()
{
	ShowControlBar(&global_vars_wnd_, !global_vars_wnd_.IsVisible(), false);
}

//-----------------------------------------------------------------------------
void CMainFrame::OnViewLog()
{
	//if (theApp.global_.IsDebugger())		// is simulator present?
	//{
	//	if (log_wnd_.m_hWnd != 0) 	// jest ju¿ okno?
	//		log_wnd_.ShowWindow((log_wnd_.GetStyle() & WS_VISIBLE) ? SW_HIDE : SW_NORMAL);
	//	else
	//	{
	//		log_wnd_.Create();
	//		log_wnd_.ShowWindow(SW_SHOWNA);
	//	}
	//}
	//else		// nie ma programu
	//	if (log_wnd_.m_hWnd != 0)
	//		log_wnd_.ShowWindow(SW_HIDE);
}

void CMainFrame::OnUpdateViewLog(CCmdUI* cmd_ui)
{
	//	cmd_ui->Enable(theApp.global_.IsDebugger());	// is simulator present?
	//	cmd_ui->SetCheck(log_wnd_.m_hWnd != 0 && (log_wnd_.GetStyle() & WS_VISIBLE) != 0);
}

//-----------------------------------------------------------------------------

void CMainFrame::OnViewStack()
{
	ShowControlBar(&call_stack_wnd_, !call_stack_wnd_.IsVisible(), false);
}

void CMainFrame::OnUpdateViewStack(CCmdUI* cmd_ui)
{
	cmd_ui->SetCheck(call_stack_wnd_.m_hWnd != 0 && call_stack_wnd_.IsVisible());
}

//-----------------------------------------------------------------------------

void CMainFrame::OnUpdateMemoryOptions(CCmdUI* cmd_ui) 
{
	cmd_ui->Enable(true);
}

void CMainFrame::OnMemoryOptions() 
{
	last_page_ = Options(5);		// opcje wygl¹du okna pamiêci
}

//-----------------------------------------------------------------------------

BOOL CMainFrame::OnCmdMsg(UINT id, int code, void* extra, AFX_CMDHANDLERINFO* handler_info) 
{
	//if (stack_.OnCmdMsg(id, code, extra, handler_info))
	//  return true;
	//if (zero_page_.OnCmdMsg(id, code, extra, handler_info))
	//  return true;
	//if (memory_.OnCmdMsg(id, code, extra, handler_info))
	//  return true;
	if (IO_window_.OnCmdMsg(id, code, extra, handler_info))
		return true;

	// If the object(s) in the extended command route don't handle
	// the command, then let the base class OnCmdMsg handle it.
	return CMDIFrameWnd::OnCmdMsg(id, code, extra, handler_info);
}

//-----------------------------------------------------------------------------

void CMainFrame::UpdateAll()
{
	if (IO_window_.m_hWnd)
		IO_window_.InvalidateRect(NULL, false);
	//if (memory_.m_hWnd)
	//	memory_.Invalidate();
	//if (zero_page_.m_hWnd)
	//	zero_page_.Invalidate();
	//if (stack_.m_hWnd)
	//{
	//	if (CSym6502* simulator= theApp.global_.GetDebugger())
	//		stack_.InvalidateView(simulator->GetContext()->s + 0x100);
	//	else
	//		stack_.Invalidate();
	//}
	//if (log_wnd_.m_hWnd)
	//	if (CSym6502* simulator= theApp.global_.GetDebugger())
	//		log_wnd_.SetText(simulator->GetLog());
	//	else
	//		log_wnd_.Invalidate();
}

void CMainFrame::DelayedUpdateAll()
{
	//	if (timer_ == 0)
	timer_ = SetTimer(100, 200, NULL);

	if (timer_ == 0)
		UpdateAll();
}

void CMainFrame::OnTimer(UINT id_event)
{
	KillTimer(timer_);
	timer_ = 0;
	UpdateAll();
}


void CMainFrame::ShowDynamicHelp(const CString& line, int word_start, int word_end)
{
	//	help_bar_wnd_.DisplayHelp(line, word_start, word_end);
}
