/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/


#include "IOWindow.h"
#include "ConfigSettings.h"
#include "Broadcast.h"
#include "FlatBar.h"
//#include "LogWindow.h"
#include "DynamicHelp.h"
//#include "WatchBar.h"
#include "ValueStackWnd.h"
#include "LocalVarsWnd.h"
#include "GlobalVarsWnd.h"
#include "StackWnd.h"
#include "Defs.h"

class LuaSrcDoc;
class LuaSrcView;
class Debugger;


class CMainFrame : public CMDIFrameWnd, CBroadcast, CConfigSettings
{
	static const TCHAR REG_ENTRY_LAYOUT[];
	static const TCHAR REG_ENTRY_MAINFRM[];
	static const TCHAR REG_POSX[], REG_POSY[], REG_SIZX[], REG_SIZY[], REG_STATE[];

	static WNDPROC pfn_old_proc_;
	static LRESULT CALLBACK StatusBarWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static CBitmap code_bmp_;
	static CBitmap debug_bmp_;

	CString format_;	// status bar text format

	afx_msg LRESULT OnUpdateState(WPARAM wParam, LPARAM lParam);

	int RedrawAllViews(int chgHint= 0);
	int Options(int page);
	int last_page_;

	void ConfigSettings(bool load);
	void ExitDebugMode();

	DECLARE_DYNAMIC(CMainFrame)

	UINT timer_;
public:
	void SetPositionText(int row, int col, bool insert_mode);
	LuaSrcView *GetCurrentView();
	LuaSrcDoc *GetCurrentDocument();
	CMainFrame();

	LuaSrcView* OpenView(const char* file_path);

// Attributes
public:
	CIOWindow IO_window_;
//	CDynamicHelp help_bar_wnd_;
	ValueStackWnd value_stack_wnd_;
	LocalVarsWnd local_vars_wnd_;
	GlobalVarsWnd global_vars_wnd_;
	StackWnd call_stack_wnd_;

// Operations
public:
	static const HWND * /*const*/ windows_[];

	void UpdateAll();
	void DelayedUpdateAll();

	void ShowDynamicHelp(const CString& line, int word_start, int word_end);

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT id, int code, void* extra, AFX_CMDHANDLERINFO* handler_info);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CStatusBar status_bar_wnd_;
protected:
	CFlatToolBar tool_bar_wnd_;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT create_struct);
	afx_msg void OnClose();
	afx_msg void OnAssemble();
	afx_msg void OnUpdateAssemble(CCmdUI* cmd_ui);
	afx_msg void OnUpdateSymDebug(CCmdUI* cmd_ui);
	afx_msg void OnSimDebug();
	afx_msg void OnSimStepInto();
	afx_msg void OnUpdateSymStepInto(CCmdUI* cmd_ui);
	afx_msg void OnSimSkipInstr();
	afx_msg void OnUpdateSymSkipInstr(CCmdUI* cmd_ui);
	afx_msg void OnSimBreakpoint();
	afx_msg void OnUpdateSymBreakpoint(CCmdUI* cmd_ui);
	afx_msg void OnSimBreak();
	afx_msg void OnUpdateSymBreak(CCmdUI* cmd_ui);
	afx_msg void OnSimGo();
	afx_msg void OnUpdateSymGo(CCmdUI* cmd_ui);
	afx_msg void OnOptions();
	afx_msg void OnUpdateOptions(CCmdUI* cmd_ui);
	afx_msg void OnSimGoToLine();
	afx_msg void OnUpdateSymGoToLine(CCmdUI* cmd_ui);
	afx_msg void OnSimSkipToLine();
	afx_msg void OnUpdateSymSkipToLine(CCmdUI* cmd_ui);
	afx_msg void OnSimStepOut();
	afx_msg void OnUpdateSymStepOut(CCmdUI* cmd_ui);
	afx_msg void OnSimStepOver();
	afx_msg void OnUpdateSymStepOver(CCmdUI* cmd_ui);
	afx_msg void OnSimEditBreakpoint();
	afx_msg void OnUpdateSymEditBreakpoint(CCmdUI* cmd_ui);
	afx_msg void OnSimRestart();
	afx_msg void OnUpdateSymRestart(CCmdUI* cmd_ui);
	afx_msg void OnUpdateIdViewRegisterbar(CCmdUI* cmd_ui);
	//afx_msg void OnFileSaveCode();
	//afx_msg void OnUpdateFileSaveCode(CCmdUI* cmd_ui);
	afx_msg void OnViewDeasm();
	afx_msg void OnUpdateViewDeasm(CCmdUI* cmd_ui);
	afx_msg void OnViewIdents();
	afx_msg void OnUpdateViewIdents(CCmdUI* cmd_ui);
	afx_msg void OnViewMemory();
	afx_msg void OnUpdateViewMemory(CCmdUI* cmd_ui);
	afx_msg void OnEditorOpt();
	afx_msg void OnUpdateEditorOpt(CCmdUI* cmd_ui);
	afx_msg void OnViewIOWindow();
	afx_msg void OnUpdateViewIOWindow(CCmdUI* cmd_ui);
	afx_msg void OnDestroy();
	//afx_msg void OnFileLoadCode();
	//afx_msg void OnUpdateFileLoadCode(CCmdUI* cmd_ui);
	afx_msg void OnDeasmOptions();
	afx_msg void OnUpdateDeasmOptions(CCmdUI* cmd_ui);
	afx_msg void OnViewRegisterWnd();
	afx_msg void OnSysColorChange();
	afx_msg void OnUpdateViewGlobalVars(CCmdUI* cmd_ui);
	afx_msg void OnViewGlobalVars();
	afx_msg void OnUpdateViewLocalVars(CCmdUI* cmd_ui);
	afx_msg void OnViewLocalVars();
	afx_msg void OnUpdateMemoryOptions(CCmdUI* cmd_ui);
	afx_msg void OnMemoryOptions();
	afx_msg void OnTimer(UINT id_event);
	afx_msg void OnViewStack();
	afx_msg void OnUpdateViewStack(CCmdUI* cmd_ui);
	afx_msg void OnSimGenIRQ();
	afx_msg void OnUpdateSymGenIRG(CCmdUI* cmd_ui);
	afx_msg void OnSimGenNMI();
	afx_msg void OnUpdateSymGenNMI(CCmdUI* cmd_ui);
	afx_msg void OnSimGenReset();
	afx_msg void OnUpdateSymGenReset(CCmdUI* cmd_ui);
	afx_msg void OnSimGenIntDlg();
	afx_msg void OnUpdateSymGenIntDlg(CCmdUI* cmd_ui);
	afx_msg void OnViewLog();
	afx_msg void OnUpdateViewLog(CCmdUI* cmd_ui);
	afx_msg void OnSimDebugStop();
	void OnUpdateSymDebugStop(CCmdUI* cmd_ui);
	afx_msg LRESULT OnStartDebugger(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnExitDebugger(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangeCode(WPARAM wParam, LPARAM lParam);
	LRESULT OnExecEvent(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void EnableDockingEx(DWORD dock_style);
	static const DWORD dock_bar_map_ex[4][2];

	void AddBreakpoint(LuaSrcView* view, int line, Defs::Breakpoint bp);
	void RemoveBreakpoint(LuaSrcView* view, int line);

	BOOL VerifyBarState(LPCTSTR profile_name);

	void StartDebuggerSession();
	void ExitDebuggerSession();

	void DockBelow(CControlBar& first, CControlBar& second);
};

/////////////////////////////////////////////////////////////////////////////
