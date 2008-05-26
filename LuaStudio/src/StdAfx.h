/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define WINVER 0x0501 

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxtempl.h>
#include <AFXCVIEW.H>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxpriv.h>
#include <afxole.h>

#include <AFXMT.H>

#pragma warning(disable : 4800)

#include <Shlwapi.h>


#include <vector>
#include <string>
#include <map>
#include <memory>


//#define _SCB_REPLACE_MINIFRAME	1
#define _SCB_MINIFRAME_CAPTION		1
