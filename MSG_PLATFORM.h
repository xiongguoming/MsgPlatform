// MSG_PLATFORM.h : main header file for the MSG_PLATFORM application
//

#if !defined(AFX_MSG_PLATFORM_H__B17ED457_B2D7_469A_91E6_83CE4D932610__INCLUDED_)
#define AFX_MSG_PLATFORM_H__B17ED457_B2D7_469A_91E6_83CE4D932610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSG_PLATFORMApp:
// See MSG_PLATFORM.cpp for the implementation of this class
//

class CMSG_PLATFORMApp : public CWinApp
{
public:
	CMSG_PLATFORMApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSG_PLATFORMApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMSG_PLATFORMApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	PlatformDB* m_pDB; 
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSG_PLATFORM_H__B17ED457_B2D7_469A_91E6_83CE4D932610__INCLUDED_)
