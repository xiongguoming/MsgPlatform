// MSG_PLATFORMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "MSG_PLATFORMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSG_PLATFORMDlg dialog

CMSG_PLATFORMDlg::CMSG_PLATFORMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMSG_PLATFORMDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMSG_PLATFORMDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMSG_PLATFORMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMSG_PLATFORMDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BTN_XXGL, m_btnXXGL);
	DDX_Control(pDX, IDC_BTN_YYGL, m_btnYYGL);
	DDX_Control(pDX, IDC_BTN_YHGL, m_btnYHGL);
	DDX_Control(pDX, IDC_BTN_XXCL, m_btnXXCL);
	DDX_Control(pDX, IDC_BTN_WBYY, m_btnWBYY);
}

BEGIN_MESSAGE_MAP(CMSG_PLATFORMDlg, CDialog)
	//{{AFX_MSG_MAP(CMSG_PLATFORMDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_XXGL, &CMSG_PLATFORMDlg::OnBnClickedBtnXxgl)
	ON_BN_CLICKED(IDC_BTN_YYGL, &CMSG_PLATFORMDlg::OnBnClickedBtnYygl)
	ON_BN_CLICKED(IDC_BTN_YHGL, &CMSG_PLATFORMDlg::OnBnClickedBtnYhgl)
	ON_BN_CLICKED(IDC_BTN_XXCL, &CMSG_PLATFORMDlg::OnBnClickedBtnXxcl)
	ON_BN_CLICKED(IDC_BTN_WBYY, &CMSG_PLATFORMDlg::OnBnClickedBtnWbyy)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSG_PLATFORMDlg message handlers

BOOL CMSG_PLATFORMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);
	
	InitBtnTool();

	m_nCurModel = 0;

	CBitmap bmp;  
	bmp.LoadBitmap(IDB_HOMEPAGE);
	m_bkBrush.CreatePatternBrush(&bmp);

	AdjustWindows(true);
	return TRUE;
}

void CMSG_PLATFORMDlg::InitBtnTool() 
{
	m_btnXXGL.SetImage (IDB_HOME_XXGL);
	m_btnXXGL.SetWindowText (_T("消息管理"));
	m_btnXXGL.SetFaceColor(RGB(135,206,235));
	m_btnXXGL.Invalidate ();
	m_btnXXGL.SetMouseCursorHand ();

	m_btnYYGL.SetImage (IDB_HOME_YYGL);
	m_btnYYGL.SetWindowText (_T("应用管理"));
	m_btnYYGL.SetFaceColor(RGB(135,206,235));
	m_btnYYGL.Invalidate ();
	m_btnYYGL.SetMouseCursorHand ();

	m_btnYHGL.SetImage (IDB_HOME_YHGL);
	m_btnYHGL.SetWindowText (_T("用户管理"));
	m_btnYHGL.SetFaceColor(RGB(135,206,235));
	m_btnYHGL.Invalidate ();
	m_btnYHGL.SetMouseCursorHand ();

	m_btnXXCL.SetImage (IDB_HOME_XXCL);
	m_btnXXCL.SetWindowText (_T("消息策略"));
	m_btnXXCL.SetFaceColor(RGB(135,206,235));
	m_btnXXCL.Invalidate ();
	m_btnXXCL.SetMouseCursorHand ();

	m_btnWBYY.SetImage (IDB_HOME_WBYY);
	m_btnWBYY.SetWindowText (_T("外部应用"));
	m_btnWBYY.SetFaceColor(RGB(135,206,235));
	m_btnWBYY.Invalidate ();
	m_btnWBYY.SetMouseCursorHand ();
}

void CMSG_PLATFORMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//禁止拖拉窗口
	if (nID == SC_MOVE || nID==0xF012)
	{
		return;
	}
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
	//拖拉窗口后重新刷新整个窗口
	if (nID == SC_MOVE || nID==0xF012)
	{
		RedrawWindow();
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMSG_PLATFORMDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMSG_PLATFORMDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CMSG_PLATFORMDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	if (m_msgDlg.Create(IDD_DLG_XXGL,this) == -1)
	{
		return -1;
	}

	if (m_appDlg.Create(IDD_DLG_YYGL,this) == -1)
	{
		return -1;
	}
	
	if (m_userDlg.Create(IDD_DLG_YHGL,this) == -1)
	{
		return -1;
	}
	if (m_policyDlg.Create(IDD_DLG_XXCL,this) == -1)
	{
		return -1;
	}
	
	if (m_extAppDlg.Create(IDD_DLG_WBYY,this) == -1)
	{
		return -1;
	}

	return 0;
}

//消息管理
void CMSG_PLATFORMDlg::OnBnClickedBtnXxgl()
{
	m_nCurModel = 0;
	AdjustWindows();
}

//应用管理
void CMSG_PLATFORMDlg::OnBnClickedBtnYygl()
{
	m_nCurModel = 1;
	AdjustWindows();
	
}
//用户管理
void CMSG_PLATFORMDlg::OnBnClickedBtnYhgl()
{
	m_nCurModel = 2;
	AdjustWindows();

}
//消息策略
void CMSG_PLATFORMDlg::OnBnClickedBtnXxcl()
{
	m_nCurModel = 3;
	AdjustWindows();
	
}
//外部应用模拟
void CMSG_PLATFORMDlg::OnBnClickedBtnWbyy()
{
	m_nCurModel = 4;
	AdjustWindows();
}

void CMSG_PLATFORMDlg::AdjustWindows(bool bInitFlag)
{
	static CRect rect = CRect(0,0,0,0);
	CWnd* pShowArea = GetDlgItem(IDC_SHOW_AREA);
	
	if (pShowArea != NULL)
	{
		if (bInitFlag)
		{
			pShowArea->GetWindowRect(&rect);
			ScreenToClient(&rect);
			pShowArea->ShowWindow(SW_HIDE);

			m_msgDlg.MoveWindow(rect);
			m_appDlg.MoveWindow(rect);
			m_userDlg.MoveWindow(rect);
			m_policyDlg.MoveWindow(rect);
			m_extAppDlg.MoveWindow(rect);
		}
		
		
		m_msgDlg.ShowWindow(SW_HIDE);
		m_appDlg.ShowWindow(SW_HIDE);
		m_userDlg.ShowWindow(SW_HIDE);
		m_policyDlg.ShowWindow(SW_HIDE);
		m_extAppDlg.ShowWindow(SW_HIDE);

		switch(m_nCurModel)
		{
		case 0:
			m_msgDlg.ShowWindow(SW_SHOW);
			break;
		case 1:
			m_appDlg.ShowWindow(SW_SHOW);
			break;
		case 2:
			m_userDlg.ShowWindow(SW_SHOW);
			break;
		case 3:
			m_policyDlg.ShowWindow(SW_SHOW);
			break;
		case 4:
			m_extAppDlg.ShowWindow(SW_SHOW);
			break;
		
		}
	}
	//比Invalidate()要快
	RedrawWindow(FALSE);
	
}
HBRUSH CMSG_PLATFORMDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	return (HBRUSH)m_bkBrush;
}
