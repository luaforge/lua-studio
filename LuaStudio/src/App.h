/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/
#pragma once


#include "Global.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


/////////////////////////////////////////////////////////////////////////////
// StudioApp:
//

class StudioApp : public CWinApp
{
  static const TCHAR REGISTRY_KEY[];
  static const TCHAR PROFILE_NAME[];
  HINSTANCE inst_res_;
  HMODULE rich_edit_;

public:
  static bool maximize_;	// maximize editor window at start-up
  static bool file_new_;	// open new empty doc at start-up
  CGlobal global_;
  bool do_not_add_to_recent_file_list_;

  StudioApp();

// Overrides
public:
  virtual BOOL InitInstance();
  virtual void AddToRecentFileList(LPCTSTR path_name);
  virtual int ExitInstance();

// Implementation

  afx_msg void OnAppAbout();
  DECLARE_MESSAGE_MAP()
};


extern StudioApp theApp;
