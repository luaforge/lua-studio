/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "stdafx.h"
#include "App.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "LuaDoc.h"
#include "LuaView.h"
#include "CXMultiDocTemplate.h"
#include "winver.h"
#include "resource.h"
#include <io.h>
#include <fcntl.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const TCHAR StudioApp::REGISTRY_KEY[]= _T("MiKSoft");
const TCHAR StudioApp::PROFILE_NAME[]= _T("LuaIDE\\0.1");


BEGIN_MESSAGE_MAP(StudioApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

StudioApp::StudioApp()
{
	do_not_add_to_recent_file_list_ = false;
	inst_res_ = NULL;
	rich_edit_ = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only StudioApp object

StudioApp theApp;

/////////////////////////////////////////////////////////////////////////////
// StudioApp initialization

bool StudioApp::maximize_= false;
bool StudioApp::file_new_= true;

BOOL StudioApp::InitInstance()
{
	// read resources
	inst_res_ = LoadLibrary("Res.dll");
	if (inst_res_ == NULL)
	{
		AfxMessageBox("Can't find resource DLL 'Res.dll'.", MB_OK | MB_ICONERROR);
		return false;
	}
	AfxSetResourceHandle(inst_res_);

	HMODULE hmod = ::LoadLibrary("SciLexer.DLL");
	if (hmod == NULL)
	{
		AfxMessageBox("Can't find Scintilla DLL 'SciLexer.dll'.", MB_OK | MB_ICONERROR);
		return false;
	}

	rich_edit_ = ::LoadLibrary(_T("riched20.dll"));
	AfxInitRichEdit();

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	INITCOMMONCONTROLSEX init;
	init.dwSize = sizeof init;
	init.dwICC = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES | ICC_TAB_CLASSES | ICC_USEREX_CLASSES;
	::InitCommonControlsEx(&init);

	SetRegistryKey(REGISTRY_KEY);
	//First free the string allocated by MFC at CWinApp startup.
	//The string is allocated before InitInstance is called.
	free((void*)m_pszProfileName);
	//Change the name of the .INI file.
	//The CWinApp destructor will free the memory.
	m_pszProfileName = _tcsdup(PROFILE_NAME);
	//m_pszProfileName = PROFILE_NAME;

	LoadStdProfileSettings(_AFX_MRU_MAX_COUNT);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CXMultiDocTemplate* doc_template;
	doc_template = new CXMultiDocTemplate(
		IDR_LUA_SRC_TYPE,
		RUNTIME_CLASS(LuaSrcDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(LuaSrcView));

	AddDocTemplate(doc_template);

	// TODO: "disassembly" for Lua intermediate code
	//doc_template = new CXMultiDocTemplate(
	//	IDR_DEASM_TYPE,
	//	RUNTIME_CLASS(CDeasmDoc),
	//	RUNTIME_CLASS(CChildFrameDeAsm), // custom MDI child frame
	//	RUNTIME_CLASS(CDeasmView),
	//	false);

	//AddDocTemplate(doc_template);
	//doc_deasm_template_ = doc_template;

	// create main MDI Frame window
	CMainFrame* main_frame = new CMainFrame;
	if (!main_frame->LoadFrame(IDR_MAINFRAME))
		return false;
	m_pMainWnd = main_frame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(true);

	CXMultiDocTemplate::registration_ext_ = false;

	// Parse command line for standard shell commands, DDE, file open
	//  CCommandLineInfo cmdInfo;
	//  ParseCommandLine(cmdInfo);

	if (!file_new_ && cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return false;

	if (maximize_ && m_nCmdShow == SW_SHOWNORMAL)
		m_nCmdShow = SW_MAXIMIZE;

	// The main window has been initialized, so show and update it.
	main_frame->ShowWindow(m_nCmdShow);
	main_frame->UpdateWindow();
	main_frame->SetFocus();	// przywracamy fokus - zamiast na DialBar, do g³ównego okna

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// StudioApp commands

void StudioApp::AddToRecentFileList(LPCTSTR path_name)
{
	if (do_not_add_to_recent_file_list_)
		return;

	CWinApp::AddToRecentFileList(path_name);
}


#include "About.h"

// App command to run the dialog
void StudioApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


int StudioApp::ExitInstance() 
{
	if (inst_res_ != NULL)
		::FreeLibrary(inst_res_);

	if (rich_edit_)
		::FreeLibrary(rich_edit_);

	return CWinApp::ExitInstance();
}
