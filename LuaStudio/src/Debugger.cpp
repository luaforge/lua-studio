/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "stdafx.h"
#include "resource.h"
//#include "MainFrm.h"
//#include "Deasm6502Doc.h"
//#include "6502View.h"
#include "Debugger.h"
#include "Broadcast.h"
#include "IOWindow.h"

#include <boost/bind.hpp>

//-----------------------------------------------------------------------------

using namespace Defs;

//UINT16 Debugger::io_addr= 0xE000;		// pocz¹tek obszaru we/wy symulatora
//bool Debugger::io_enabled= true;
//int Debugger::bus_width= 16;
//static const int SIM_THREAD_PRIORITY= THREAD_PRIORITY_BELOW_NORMAL; // priorytet (oprócz animate)
//bool Debugger::write_protect_area_= false;
//UINT16 Debugger::protect_from_addr_= 0xc000;
//UINT16 Debugger::protect_to_addr_= 0xcfff;



Debugger::Debugger()
{
	init();
}

//-----------------------------------------------------------------------------


Defs::Breakpoint Debugger::ToggleBreakpoint(int line, const CString& path)
{
	if (lua_.get() == 0)
		return BPT_NO_CODE;

	return lua_->ToggleBreakpoint(line + 1) ? BPT_EXECUTE : BPT_NONE;
}



void Debugger::SimEvent(int event, int data)
{
	if (event == Lua::NewLine)
		current_line_ = data;

//	CBroadcast::SendMessageToPopups(CBroadcast::WM_USER_NEW_LINE, event, data);
	AfxGetMainWnd()->PostMessage(CBroadcast::WM_USER_NEW_LINE, event, data);

	fin_stat = event == Lua::Finished ? SYM_FIN : SYM_RUN;
}


void Debugger::SetNewContext(std::auto_ptr<Lua> lua)
{
	lua_ = lua;
	current_line_ = 0;
//	fin_stat = SYM_STOP;
	fin_stat = SYM_OK;
//	log_.Clear();

//	theApp.global_.ClearOutput();

	if (CWnd* terminal= io_window())
		terminal->SendMessage(CIOWindow::CMD_CLS);

	if (lua_.get())
		lua_->SetCallback(boost::bind(&Debugger::SimEvent, this, _1, _2));
}


int Debugger::GetCurrentLine() const
{
	return current_line_;
}


Defs::SymStat Debugger::StepInto()
{
	if (lua_.get() == 0)
		return SYM_FIN;

	lua_->StepInto();
	return SYM_OK;
}

//-----------------------------------------------------------------------------

Defs::SymStat Debugger::StepOver()
{
	if (lua_.get() == 0)
		return SYM_FIN;

	lua_->StepOver();
	return SYM_OK;
}


//-----------------------------------------------------------------------------

Defs::SymStat Debugger::StepOut()
{
	if (lua_.get() == 0)
		return SYM_FIN;

	lua_->StepOut();
	return SYM_OK;
}


//-----------------------------------------------------------------------------

Defs::SymStat Debugger::Run()
{
	if (lua_.get() == 0)
		return SYM_FIN;

	lua_->Run();
	return SYM_OK;
}

//-----------------------------------------------------------------------------

//void Debugger::SkipToAddr(UINT16 addr)
//{
//}
//
//
//Defs::SymStat Debugger::SkipInstr()
//{
//	return SYM_OK;
//}

//-----------------------------------------------------------------------------


//void Debugger::ExitSym()
//{
//	//ASSERT(running == false);
//	//ResetPointer();               // schowanie strza³ki
//	//CMainFrame* main = (CMainFrame*) AfxGetApp()->main_wnd_;
//	//  main->ShowRegisterBar(false);
//}

//-----------------------------------------------------------------------------

CString Debugger::GetLastStatMsg()
{
	if (lua_.get())
		return lua_->Status().c_str();

	return "Inactive";
}


//CString Debugger::GetStatMsg(SymStat stat)
//{
//	CString msg;
	//switch (stat)
	//{
	//case SYM_OK:
	//case SYM_BPT_TEMP:
	//	msg.LoadString(IDS_SYM_STAT_OK);
	//	break;
	//case SYM_BPT_EXECUTE:
	//	msg.LoadString(IDS_SYM_STAT_BPX);
	//	break;
	//case SYM_BPT_READ:
	//	msg.LoadString(IDS_SYM_STAT_BPR);
	//	break;
	//case SYM_BPT_WRITE:
	//	msg.LoadString(IDS_SYM_STAT_BPW);
	//	break;
	//case SYM_ILLEGAL_CODE:
	//	msg.LoadString(IDS_SYM_STAT_ILL);
	//	break;
	//case SYM_STOP:
	//	msg.LoadString(IDS_SYM_STAT_STOP);
	//	break;
	//case SYM_FIN:
	//	msg.LoadString(IDS_SYM_STAT_FIN);
	//	break;
	//case SYM_RUN:
	//	msg.LoadString(IDS_SYM_STAT_RUN);
	//	break;
	//case SYM_INP_WAIT:
	//	msg.LoadString(IDS_SYM_STAT_INP_WAIT);
	//	break;
	//case SYM_ILL_WRITE:
	//	msg.LoadString(IDS_SYM_ILL_WRITE);
	//	break;
	//default:
	//	ASSERT(false);
	//}
//	return msg;
//}

//-----------------------------------------------------------------------------


//void Debugger::Restart(const COutputMem &mem)
//{
//	//ctx.Reset(mem);
//	//old = ctx;
//	//fin_stat = SYM_OK;
//	//log_.Clear();
//}


//void Debugger::SymStart(UINT16 org)
//{
//	//ctx.pc = org;
//	//ctx.s = 0xFF;
//	//if (debug)
//	//{
//	//	CDebugLine dl;
//	//	debug->GetLine(dl,org);
//	//	//    ASSERT(dl.flags != Defs::DBG_EMPTY);      // brak wiersza odp. pocz¹tkowi programu
//	//	SetPointer(dl.line,org);    // ustawienie strza³ki (->) przed aktualnym wierszem
//	//}
//}


//void Debugger::SetPointer(const CLine &line, UINT16 addr) // ustawienie strza³ki (->) przed aktualnym wierszem
//{
	//POSITION posDoc= theApp.doc_deasm_template_->GetFirstDocPosition();
	//while (posDoc != NULL)        // s¹ okna z deasemblera?
	//{
	//	CDocument *doc= theApp.doc_deasm_template_->GetNextDoc(posDoc);
	//	ASSERT(doc->IsKindOf(RUNTIME_CLASS(CDeasm6502Doc)));
	//	((CDeasm6502Doc*)doc)->SetPointer(addr,true);
	//}

	//LuaSrcView* view= FindDocView(line.file);  // odszukanie okna dokumentu
	//if (fuid_last_view_ != line.file && ::IsWindow(last_view_))        // zmiana okna?
	//{
	//	if (LuaSrcView* view= dynamic_cast<LuaSrcView*>(CWnd::FromHandlePermanent(last_view_)))
	//		SetPointer(view, -1, false);              // ukrycie strza³ki
	//	last_view_ = 0;
	//}
	//if (!view && debug)
	//{
	//	if (const TCHAR* path= debug->GetFilePath(line.file))
	//	{                                           // próba otwarcia dokumentu...
	//		StudioApp* app= static_cast<StudioApp*>( AfxGetApp() );
	//		app->do_not_add_to_recent_file_list_ = true;
	//		CDocument* doc= app->OpenDocumentFile(path);
	//		app->do_not_add_to_recent_file_list_ = false;
	//		if (LuaSrcDoc* src_doc= dynamic_cast<LuaSrcDoc*>(doc))
	//		{
	//			POSITION pos = src_doc->GetFirstViewPosition();
	//			if (pos != NULL)
	//				view = dynamic_cast<LuaSrcView*>(src_doc->GetNextView(pos));
	//		}
	//	}
	//}
	//if (!view)
	//{
	//	//    ResetPointer();   // schowanie strza³ki, jeœli by³a
	//	return;             // nie ma okna dokumentu zawieraj¹cego aktualny wiersz
	//}

	//SetPointer(view, line.ln, true);  // wymuszenie przesuniêcia zawartoœci okna, jeœli potrzeba
	//fuid_last_view_ = line.file;
	//last_view_ = view->m_hWnd;
//}

//void Debugger::SetPointer(LuaSrcView* view, int line, bool scroll)
//{
	//if (view == 0)
	//	return;

	//CDocument* doc= view->GetDocument();
	//POSITION pos= doc->GetFirstViewPosition();
	//while (pos != NULL)
	//{
	//	if (LuaSrcView* src_view= dynamic_cast<LuaSrcView*>(doc->GetNextView(pos)))
	//		src_view->SetPointer(line, scroll && src_view == view);
	//}
//}


//void Debugger::ResetPointer()   // schowanie strza³ki
//{
	//POSITION posDoc= theApp.doc_deasm_template_->GetFirstDocPosition();
	//while (posDoc != NULL)        // s¹ okna z deasemblera?
	//{
	//	if (CDeasm6502Doc* doc= dynamic_cast<CDeasm6502Doc*>( theApp.doc_deasm_template_->GetNextDoc(posDoc) ))
	//		doc->SetPointer(-1,true);
	//}

	//if (fuid_last_view_)
	//{
	//	if (LuaSrcView* view= FindDocView(fuid_last_view_))
	//		SetPointer(view, -1, false);    // zmazanie strza³ki
	//}
	//fuid_last_view_ = 0;
//}


//LuaSrcView *Debugger::FindDocView(FileUID fuid)
//{
	//if (debug == NULL)
	//	return NULL;
	//if (CFrameWnd* frame= dynamic_cast<CFrameWnd*>(AfxGetMainWnd()))
	//	if (CFrameWnd* active= frame->GetActiveFrame())
	//		if (LuaSrcView* view= dynamic_cast<LuaSrcView*>(active->GetActiveView()))
	//			if (debug->GetFileUID(view->GetDocument()->GetPathName()) == fuid)
	//				return view;

//	return 0;
//}


//=============================================================================

CWnd *Debugger::io_open_window()  // otwarcie okna terminala
{
	AfxGetMainWnd()->SendMessage(WM_COMMAND,ID_VIEW_IO_WINDOW);
	return io_window();
}


CWnd *Debugger::io_window()     // odszukanie okna terminala
{
	static CString name;
	static bool loaded= false;
	if (!loaded)
	{
		name.LoadString(IDS_IO_WINDOW);
		loaded = true;
	}
	return CWnd::FindWindow(NULL,name);
}

#if 0

UINT8 Debugger::io_function()
{
	CWnd *terminal= io_window();
	if (terminal == NULL)
		terminal = io_open_window();
	if (terminal == 0 || !::IsWindow(terminal->m_hWnd))
	{
		io_func = IO_NONE;
		return 0;
	}

	int arg= 0;

	if (io_func == TERMINAL_IN)
	{
		arg = terminal->SendMessage(CIOWindow::CMD_IN);
	}
	else
	{
		if (io_func == TERMINAL_GET_X_POS || io_func == TERMINAL_GET_Y_POS)
			arg = terminal->SendMessage(CIOWindow::CMD_POSITION, io_func == TERMINAL_GET_X_POS ? 0x3 : 0x2);
		else
			arg = 0;
	}

	io_func = IO_NONE;

	if (arg == -1)  // break?
	{
		Break();
		return 0;
	}

	return UINT8(arg);
}

Defs::SymStat Debugger::io_function(UINT8 arg)
{
	CWnd *terminal= io_window();
	if (terminal == NULL)
		terminal = io_open_window();

	switch (io_func)
	{
	case TERMINAL_OUT:
		if (terminal)
			terminal->SendMessage(CIOWindow::CMD_PUTC, arg, 0);
		break;

	case TERMINAL_OUT_CHR:
		if (terminal)
			terminal->SendMessage(CIOWindow::CMD_PUTC, arg, 1);
		break;

	case TERMINAL_OUT_HEX:
		if (terminal)
			terminal->SendMessage(CIOWindow::CMD_PUTC, arg, 2);
		break;

	case TERMINAL_CLS:
		if (terminal)
			terminal->SendMessage(CIOWindow::CMD_CLS);
		break;

	case TERMINAL_IN:
		ASSERT(false);
		/*		if (terminal)
		arg = UINT8(terminal->SendMessage(CIOWindow::CMD_IN));
		else
		arg = 0; */
		break;

	case TERMINAL_SET_X_POS:
	case TERMINAL_SET_Y_POS:
		if (terminal)
			terminal->SendMessage(CIOWindow::CMD_POSITION, io_func == TERMINAL_SET_X_POS ? 0x1 : 0x0, arg);
		break;

	default:
		ASSERT(false);            // nierozpoznana funkcja
	}

	io_func = IO_NONE;
	return SYM_OK;
}


//void Debugger::OutputChar(int c)
//{
//	CWnd* terminal= io_window();
//	if (terminal == NULL)
//		terminal = io_open_window();
//
//	if (terminal)
//		terminal->SendMessage(CIOWindow::CMD_PUTC, c, 0);
//}
#endif


///////////////////////////////////////////////////////////////////////////////

void Debugger::init()
{
//	running = false;
//	fuid_last_view_ = 0;
	fin_stat = SYM_OK;
//	thread = 0;
//    io_enabled = false;
//    io_addr = 0xE000;
//	io_func = IO_NONE;
	current_line_ = 0;
}


void Debugger::Break()
{
	if (lua_.get())
		lua_->Break();
}


void Debugger::AbortProg()
{
	lua_.reset();
}


bool Debugger::IsRunning() const
{
	if (lua_.get())
		return lua_->IsRunning();
	else
		return false;
}


bool Debugger::IsStopped() const
{
	if (lua_.get())
		return lua_->IsStopped();
	else
		return false;	// it's not stopped, because it is gone
}


bool Debugger::IsFinished() const
{
	if (lua_.get())
		return lua_->IsFinished();
	else
		return true;
}


bool Debugger::IsActive() const
{
	return lua_.get() != 0;
}



//std::string Debugger::GetCallStack() const
//{
//	if (lua_.get())
//		return lua_->GetCallStack();
//	else
//		return std::string();
//}


//bool Debugger::GetGlobalVars(std::vector<Lua::Field>& vars, bool deep) const
//{
//	if (lua_.get())
//		return lua_->GetGlobalVars(vars, deep);
//	return false;
//}
//
//
//bool Debugger::GetLocalVars(std::vector<Lua::Var>& vars) const
//{
//	if (lua_.get())
//		return lua_->GetLocalVars(vars);
//	return false;
//}
