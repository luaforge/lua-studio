/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "stdafx.h"
#include "LuaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LuaSrcDoc

IMPLEMENT_DYNCREATE(LuaSrcDoc, CScintillaDoc)

BEGIN_MESSAGE_MAP(LuaSrcDoc, CScintillaDoc)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LuaSrcDoc construction/destruction

LuaSrcDoc::LuaSrcDoc()
{}

LuaSrcDoc::~LuaSrcDoc()
{}

BOOL LuaSrcDoc::OnNewDocument()
{
	if (!CScintillaDoc::OnNewDocument())
		return FALSE;

	static UINT no= 1;
	CString name;
	name.Format(_T("NewFile %u"), no++);
	SetPathName(name, false);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// LuaSrcDoc diagnostics

#ifdef _DEBUG
void LuaSrcDoc::AssertValid() const
{
	CScintillaDoc::AssertValid();
}

void LuaSrcDoc::Dump(CDumpContext& dc) const
{
	CScintillaDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

BOOL LuaSrcDoc::OnOpenDocument(LPCTSTR path_name)
{
	if (CDocument::OnOpenDocument(path_name))
	{
		GetView()->GetCtrl().Colourise(0, -1);
		return true;
	}

	return false;
}
