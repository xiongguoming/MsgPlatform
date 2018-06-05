// AppManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "AppManageDlg.h"
#include "AppInfoDlg.h"
#include "AppMessageDlg.h"

//using namespace System;
//typedef System::String^ SysString;
//using namespace System::Runtime::InteropServices;

// CAppManageDlg 对话框
IMPLEMENT_DYNAMIC(CAppManageDlg, CDialog)

CAppManageDlg::CAppManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppManageDlg::IDD, pParent)
	, m_nIsPassed(0)
{
	
}

CAppManageDlg::~CAppManageDlg()
{
	m_appArray.clear();
}

void CAppManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_AUDIT, m_btnAudit);
	DDX_Control(pDX, IDC_BTN_FORBIT, m_btnForbit);
	DDX_Control(pDX, IDC_BTN_PASS, m_btnPass);
	DDX_Radio(pDX, IDC_RAD_PASS, m_nIsPassed);
	DDX_Control(pDX, IDC_APP_PASS, m_wndListSuccess);
	DDX_Control(pDX, IDC_APP_AUDIT, m_wndListAudit);
	DDX_Control(pDX, IDC_APP_FORBID, m_wndListforbid);
	DDX_Control(pDX, IDC_BTN_DELETEAPP, m_btnDelApp);
	DDX_Control(pDX, IDC_BTN_REFLASH, m_btnReflash);
}


BEGIN_MESSAGE_MAP(CAppManageDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_AUDIT, &CAppManageDlg::OnBnClickedBtnAudit)
	ON_BN_CLICKED(IDC_BTN_FORBIT, &CAppManageDlg::OnBnClickedBtnForbit)
	ON_BN_CLICKED(IDC_BTN_PASS, &CAppManageDlg::OnBnClickedBtnPass)
	ON_NOTIFY(NM_CLICK,IDC_APP_PASS,&CAppManageDlg::OnNMClickAppPass) 
	ON_BN_CLICKED(IDC_BTN_REFLASH, &CAppManageDlg::OnBnClickedBtnReflash)
	ON_BN_CLICKED(IDC_BTN_DELETEAPP, &CAppManageDlg::OnBnClickedBtnDeleteapp)
END_MESSAGE_MAP()


// CAppManageDlg 消息处理程序
BOOL CAppManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitButtons();
	m_pDB = ((CMSG_PLATFORMApp*)AfxGetApp())->m_pDB;

	HICON hIcon[3];
	m_ImageList.Create(32, 32,ILC_COLOR32|ILC_MASK, 3, 1);
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_SYS_APP);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_EXT_APP);

	for (int n=0; n<2; n++)
	{
		m_ImageList.Add(hIcon[n]);
	}

	m_wndListSuccess.SetImageList(&m_ImageList,LVSIL_NORMAL);
	m_wndListAudit.SetImageList(&m_ImageList,LVSIL_NORMAL);
	m_wndListforbid.SetImageList(&m_ImageList,LVSIL_NORMAL);

	InitAppArray();
	
	int nItemNum = 0;
	for (unsigned int nIndex=0; nIndex<m_appArray.size(); nIndex++)
	{
		//审核未通过
		if (m_appArray[nIndex].nStatus == 0)
		{
			nItemNum = m_wndListAudit.GetItemCount();
			m_wndListAudit.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListAudit.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}	
		//审核通过
		else if(m_appArray[nIndex].nStatus == 1)
		{
			nItemNum = m_wndListSuccess.GetItemCount();
			m_wndListSuccess.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListSuccess.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}
		//被禁用
		else
		{
			nItemNum = m_wndListforbid.GetItemCount();
			m_wndListforbid.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListforbid.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}
	}
	
	return TRUE; 
}

void CAppManageDlg::InitButtons()
{
	m_btnAudit.SetWindowText (_T("确定"));
	m_btnAudit.SetFaceColor(RGB(135,206,235));
	m_btnAudit.Invalidate ();
	m_btnAudit.SetMouseCursorHand ();

	m_btnForbit.SetWindowText (_T("禁用"));
	m_btnForbit.SetFaceColor(RGB(135,206,235));
	m_btnForbit.Invalidate ();
	m_btnForbit.SetMouseCursorHand ();

	m_btnPass.SetWindowText (_T("激活"));
	m_btnPass.SetFaceColor(RGB(135,206,235));
	m_btnPass.Invalidate ();
	m_btnPass.SetMouseCursorHand ();

	m_btnDelApp.SetWindowText (_T("删除"));
	m_btnDelApp.SetFaceColor(RGB(135,206,235));
	m_btnDelApp.Invalidate ();
	m_btnDelApp.SetMouseCursorHand ();
	
	m_btnReflash.SetWindowText (_T("刷新"));
	m_btnReflash.SetFaceColor(RGB(135,206,235));
	m_btnReflash.Invalidate ();
	m_btnReflash.SetMouseCursorHand ();
}

void CAppManageDlg::InitAppArray()
{
	sAppInfo* pAppArray = NULL;
	int nNum = m_pDB->ReadAllApps(NULL);
	if(nNum>0)
	{
		pAppArray = new sAppInfo[nNum];
		m_pDB->ReadAllApps(pAppArray);
		
		m_appArray.clear();

		for (int nIndex=0; nIndex<nNum; nIndex++)
		{
			m_appArray.push_back(pAppArray[nIndex]);
		}

		//delete[] pAppArray;
		//pAppArray = NULL;
	}
}

void CAppManageDlg::OnBnClickedBtnReflash()
{
	InitAppArray();

	m_wndListAudit.DeleteAllItems();
	m_wndListSuccess.DeleteAllItems();
	m_wndListforbid.DeleteAllItems();

	int nItemNum = 0;
	for (unsigned int nIndex=0; nIndex<m_appArray.size(); nIndex++)
	{
		//审核未通过
		if (m_appArray[nIndex].nStatus == 0)
		{
			nItemNum = m_wndListAudit.GetItemCount();
			m_wndListAudit.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListAudit.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}	
		//审核通过
		else if(m_appArray[nIndex].nStatus == 1)
		{
			nItemNum = m_wndListSuccess.GetItemCount();
			m_wndListSuccess.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListSuccess.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}
		//被禁用
		else
		{
			nItemNum = m_wndListforbid.GetItemCount();
			m_wndListforbid.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListforbid.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}
	}
}
void CAppManageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	CBitmap bmp;
	CDC memdc;
	CDC* pDC = GetDC();
	memdc.CreateCompatibleDC(pDC);
	bmp.LoadBitmap(IDB_HOMEPAGE_APP);
	memdc.SelectObject(&bmp);

	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
	bmp.DeleteObject();
	memdc.DeleteDC();
}

int CAppManageDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;
	}

	const DWORD dwViewStyle =	
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	m_wndListSuccess.m_bVisualManagerStyle = TRUE;
	m_wndListAudit.m_bVisualManagerStyle = TRUE;
	m_wndListforbid.m_bVisualManagerStyle = TRUE;

	if (!m_wndListSuccess.Create (dwViewStyle, rectDummy, &m_wndTabs, IDC_APP_PASS) ||
		!m_wndListAudit.Create (dwViewStyle, rectDummy, &m_wndTabs, IDC_APP_AUDIT)||
		!m_wndListforbid.Create (dwViewStyle, rectDummy, &m_wndTabs, IDC_APP_FORBID))
	{
		TRACE0("Failed to create output view\n");
		return -1;
	}

	m_wndTabs.AddTab (&m_wndListSuccess, _T("已审核"), -1);
	m_wndTabs.AddTab (&m_wndListAudit, _T("待审核"), -1);
	m_wndTabs.AddTab (&m_wndListforbid, _T("已禁止"), -1);
	
	m_wndTabs.SetTabBkColor(0,RGB(198,232,248));
	m_wndTabs.SetTabBkColor(1,RGB(198,232,248));

	return 0;
}

void CAppManageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (GetDlgItem(IDC_AREA_GRID)!=NULL)
	{
		CRect rect;

		CWnd* pArea = GetDlgItem(IDC_AREA_GRID);
		pArea->GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_wndTabs.MoveWindow(rect);
		pArea->ShowWindow(SW_HIDE);
	}
}


HBRUSH CAppManageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd == this)
	{
		hbr = CreateSolidBrush(RGB(51,153,204));
	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetTextColor(RGB(255,255,255));
		hbr = CreateSolidBrush(RGB(51,153,204));
	}

	return hbr;
}

void CAppManageDlg::OnBnClickedBtnAudit()
{
	UpdateData();
	
	POSITION pos = m_wndListAudit.GetFirstSelectedItemPosition();

	if (m_wndTabs.GetActiveTab()!=1 || pos==NULL)
	{
		MessageBox("没有选择应用！","应用管理",MB_ICONERROR);
		return;
	}

	int nCulSel = m_wndListAudit.GetNextSelectedItem(pos);

	sAppInfo *pAppinfo = (sAppInfo*)m_wndListAudit.GetItemData(nCulSel);
	
	//通过
	if(m_nIsPassed == 0)
	{
		pAppinfo->nStatus = 1;
	}
	//不通过=禁用
	else
	{
		pAppinfo->nStatus = 2;
	}
	
	if (m_pDB->SaveApp(pAppinfo,true))
	{
		UpdateAppStatus(*pAppinfo);
	}
	else
	{
		MessageBox("更新失败！","应用管理",MB_ICONERROR);
	}
}

//禁用应用
void CAppManageDlg::OnBnClickedBtnForbit()
{
	POSITION pos = m_wndListSuccess.GetFirstSelectedItemPosition();

	if (m_wndTabs.GetActiveTab() != 0 || pos==NULL)
	{
		MessageBox("没有选择应用！","应用管理",MB_ICONERROR);
		return;
	}

	int nCulSel = m_wndListSuccess.GetNextSelectedItem(pos);

	sAppInfo *pAppinfo = (sAppInfo*)m_wndListSuccess.GetItemData(nCulSel);
	//设置禁用
	pAppinfo->nStatus = 2;
	
	if (m_pDB->SaveApp(pAppinfo,true))
	{
		UpdateAppStatus(*pAppinfo);
	}
	else
	{
		MessageBox("更新失败！","应用管理",MB_ICONERROR);
	}
}

//解除禁用
void CAppManageDlg::OnBnClickedBtnPass()
{
	POSITION pos = m_wndListforbid.GetFirstSelectedItemPosition();

	if (m_wndTabs.GetActiveTab()!=2 || pos==NULL)
	{
		MessageBox("没有选择应用！","应用管理",MB_ICONERROR);
		return;
	}

	int nCulSel = m_wndListforbid.GetNextSelectedItem(pos);
	
	sAppInfo* pAppinfo = (sAppInfo*)m_wndListforbid.GetItemData(nCulSel);
	
	if (pAppinfo==NULL)
	{
		return;
	}

	//设置允许
	pAppinfo->nStatus = 1;

	if (m_pDB->SaveApp(pAppinfo,true))
	{
		UpdateAppStatus(*pAppinfo);
	}
	else
	{
		MessageBox("更新失败！","应用管理",MB_ICONERROR);
	}
}

void CAppManageDlg::OnBnClickedBtnDeleteapp()
{
	int nCurSel = -1;
	POSITION pos = NULL;
	int nCurAppType = m_wndTabs.GetActiveTab();
	
	switch(nCurAppType)
	{
	case 0:	//已通过
		pos = m_wndListSuccess.GetFirstSelectedItemPosition();
		if(pos != NULL)
		{
			nCurSel = m_wndListSuccess.GetNextSelectedItem(pos);
			sAppInfo* pAppinfo = (sAppInfo*)m_wndListSuccess.GetItemData(nCurSel);

			if(m_pDB->RemoveApp(pAppinfo))
			{
				m_wndListSuccess.DeleteItem(nCurSel);
				RemoveAppFromVector(pAppinfo);
			}
		}
		break;
	case 1: //待审核
		pos = m_wndListAudit.GetFirstSelectedItemPosition();
		if(pos != NULL)
		{
			nCurSel = m_wndListAudit.GetNextSelectedItem(pos);
			sAppInfo* pAppinfo = (sAppInfo*)m_wndListAudit.GetItemData(nCurSel);

			if(m_pDB->RemoveApp(pAppinfo))
			{
				m_wndListAudit.DeleteItem(nCurSel);
				RemoveAppFromVector(pAppinfo);
			}
		}
		break;
	case 2: //被禁止
		pos = m_wndListforbid.GetFirstSelectedItemPosition();
		if(pos != NULL)
		{
			nCurSel = m_wndListforbid.GetNextSelectedItem(pos);
			sAppInfo* pAppinfo = (sAppInfo*)m_wndListforbid.GetItemData(nCurSel);

			if(m_pDB->RemoveApp(pAppinfo))
			{
				m_wndListforbid.DeleteItem(nCurSel);
				RemoveAppFromVector(pAppinfo);
			}
		}
		break;
	}

	if (nCurSel<0)
	{
		MessageBox("没有选择应用！","应用管理",MB_ICONERROR);
	}
}

//更新APP的状态
void CAppManageDlg::UpdateAppStatus(sAppInfo appInfo)
{
	for (unsigned int nIndex=0; nIndex<m_appArray.size(); nIndex++)
	{
		if(strcmp(m_appArray[nIndex].AppID,appInfo.AppID) == 0)
		{
			m_appArray[nIndex].nStatus = appInfo.nStatus;
			break;
		}
	}

	m_wndListSuccess.DeleteAllItems();
	m_wndListAudit.DeleteAllItems();
	m_wndListforbid.DeleteAllItems();

	int nItemNum = 0;
	for (unsigned int nIndex=0; nIndex<m_appArray.size(); nIndex++)
	{
		//审核未通过
		if (m_appArray[nIndex].nStatus == 0)
		{
			nItemNum = m_wndListAudit.GetItemCount();
			m_wndListAudit.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListSuccess.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}	
		//审核通过
		else if(m_appArray[nIndex].nStatus == 1)
		{
			nItemNum = m_wndListSuccess.GetItemCount();
			m_wndListSuccess.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListSuccess.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}
		//被禁用
		else
		{
			nItemNum = m_wndListforbid.GetItemCount();
			m_wndListforbid.InsertItem(nItemNum,m_appArray[nIndex].AppName,1);
			m_wndListSuccess.SetItemData(nItemNum,(DWORD)(&m_appArray[nIndex]));
		}
	}
}

void CAppManageDlg::OnNMClickAppPass(NMHDR* pNMHDR, LRESULT* pResult)
{
	//NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	AfxMessageBox("ok");
	*pResult = 0;
}

void CAppManageDlg::RemoveAppFromVector(sAppInfo* pApp)
{
	if (pApp == NULL)
	{
		return;
	}
	for (vector<sAppInfo>::iterator it=m_appArray.begin(); it!=m_appArray.end(); it++)
	{
		if (strcmp(it->AppID,pApp->AppID)==0)
		{
			m_appArray.erase(it);
			break;
		}
	}
}

