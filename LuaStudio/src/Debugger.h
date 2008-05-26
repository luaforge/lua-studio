/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#ifndef _debugger_h_
#define _debugger_h_

//#include "OutputMem.h"
//#include "LogBuffer.h"
#include "Defs.h"
#include "Lua.h"


class Debugger
{
/*
	enum IOFunc			// funkcje kolejnych bajtów z obszaru we/wy symulatora
	{ 
		IO_NONE      = -1,
		TERMINAL_CLS = 0,
		TERMINAL_OUT,
		TERMINAL_OUT_CHR,
		TERMINAL_OUT_HEX,
		TERMINAL_IN,
		TERMINAL_GET_X_POS,
		TERMINAL_GET_Y_POS,
		TERMINAL_SET_X_POS,
		TERMINAL_SET_Y_POS,
		IO_LAST_FUNC= TERMINAL_SET_X_POS
	};
*/

private:
	//IOFunc io_func;
	CWnd* io_window();		// find terminal window
	CWnd* io_open_window();	// open terminal window
	Defs::SymStat fin_stat;

	//SymStat perform_cmd();
	//SymStat skip_cmd();		// ominiêcie bie¿¹cej instrukcji
	//SymStat step_over();
	//SymStat run_till_ret();
	//SymStat run(bool animate= false);
	//void interrupt(int& interrupt);	// interrupt requested: load pc
	//SymStat perform_step(bool animate);
	//SymStat perform_command();

	//void SetPointer(LuaSrcView* view, int line, bool scroll); // helper fn
	//void ResetPointer();			// schowanie strza³ki
	//LuaSrcView *FindDocView(FileUID fuid);	// odszukanie okna dokumentu
	//FileUID fuid_last_view_;			// zapamiêtanie okna, w którym narysowana jest strza³ka
	//HWND last_view_;				// j.w.
	//void AddBranchCycles(UINT8 arg);

	//SymStat io_function(UINT8 arg);
	//UINT8 io_function();

public:

	//void Update(SymStat stat, bool no_ok= false);
	//CString GetStatMsg(SymStat stat);
	CString GetLastStatMsg();
	//SymStat SkipInstr();
	//void SkipToAddr(UINT16 addr);
	//void set_addr_bus_width(UINT w)
	//{}

	Debugger(); //: eventRedraw(true,true)
//	{ init(); }

	void Restart();
	void SymStart(UINT16 org);

	Defs::SymStat StepInto();
	Defs::SymStat StepOver();
	Defs::SymStat StepOut();
	Defs::SymStat Run();


	Defs::Breakpoint ToggleBreakpoint(int line, const CString& path);

//	void OutputChar(int c);

	bool IsFinished() const;
	bool IsRunning() const;		// is Lua program running?
	void Break();				// break program execution
	void AbortProg();
	bool IsStopped() const;
	bool IsActive() const;

	int GetCurrentLine() const;

//	std::string GetCallStack() const;
//	bool GetLocalVars(std::vector<Lua::Var>& vars) const;
//	bool GetGlobalVars(std::vector<Lua::Field>& vars, bool deep) const;

	void SetNewContext(std::auto_ptr<Lua> lua);

	Lua* GetLua() const		{ return lua_.get(); }

private:
	void SimEvent(int event, int line);
	std::auto_ptr<Lua> lua_;
	int current_line_;

	void init();
};

#endif
