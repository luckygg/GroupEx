
// FTech_GroupEx.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFTech_GroupExApp:
// See FTech_GroupEx.cpp for the implementation of this class
//

class CFTech_GroupExApp : public CWinApp
{
public:
	CFTech_GroupExApp();

	ULONG_PTR m_gdiplusToken;
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFTech_GroupExApp theApp;