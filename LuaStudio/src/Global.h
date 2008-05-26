/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/
#pragma once

#include "Broadcast.h"
#include "Debugger.h"
#include "MarkArea.h"
#include "Defs.h"


class CGlobal
{
	bool code_present_;
	int stdout_fds_[2];				// redirected stdout
public:

	CGlobal();

	~CGlobal();

	Debugger& GetDebugger() const;

	Defs::Breakpoint SetBreakpoint(int line, CString doc_title);
	Defs::Breakpoint GetBreakpoint(int line, CString doc_title);
	Defs::Breakpoint ModifyBreakpoint(int line, CString doc_title, Defs::Breakpoint bp);
	void ClrBreakpoint(int line, CString doc_title);

	UINT16 GetLineCodeAddr(int line, CString doc_title);
	bool SetTempExecBreakpoint(int line, CString doc_title);

	//---------------------------------------------------------------------------

	bool CreateDeasm();

	void GetOutput(std::vector<char>& out);

	void ClearOutput();

private:
	static UINT AFX_CDECL ReadStdoutText(LPVOID self);
	void BufferOutput(const char* buf, int len);
	std::vector<char> output_;
	size_t output_position_;
	CCriticalSection lock_output_;
	std::auto_ptr<Debugger> debugger_;
	CWinThread* thread_;
};
