// MSG_PLATFORM.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "MSG_PLATFORMDlg.h"
#include "LoadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSG_PLATFORMApp

BEGIN_MESSAGE_MAP(CMSG_PLATFORMApp, CWinApp)
	//{{AFX_MSG_MAP(CMSG_PLATFORMApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSG_PLATFORMApp construction

CMSG_PLATFORMApp::CMSG_PLATFORMApp()
{
	m_pDB = new PlatformDB;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMSG_PLATFORMApp object

CMSG_PLATFORMApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMSG_PLATFORMApp initialization

BOOL CMSG_PLATFORMApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	if (m_pDB!=NULL && m_pDB->Connect("localhost","root","45092209","msg_platform",3306))
	{
		m_pDB->CreateTables();
	}
	else
	{
		AfxMessageBox("数据库连接失败！");
	}
	
	CLoadDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		CMSG_PLATFORMDlg dlg;
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
	}

	return FALSE;
}

int CMSG_PLATFORMApp::ExitInstance() 
{
	if (m_pDB!=NULL)
	{
		delete m_pDB;
		m_pDB = NULL;
	}

	return CWinApp::ExitInstance();
}
