// MsgManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "MsgManageDlg.h"


// CMsgManageDlg 对话框

IMPLEMENT_DYNAMIC(CMsgManageDlg, CDialog)

CMsgManageDlg::CMsgManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgManageDlg::IDD, pParent)
{
	m_pHisMsgArray = NULL;
	m_nHisMsgNum = 0;

	m_pSysMsgArray = NULL;
	m_nSysMsgNum = NULL;

	m_pAppMsgArray = NULL;
	m_nAppMsgNum = 0;

	m_pUserMsgArray = NULL;
	m_nUserMsgNum = 0;

	m_pDB = ((CMSG_PLATFORMApp*)AfxGetApp())->m_pDB;
}

CMsgManageDlg::~CMsgManageDlg()
{
	if (m_pHisMsgArray!=NULL)
	{
		delete[] m_pHisMsgArray;
		m_pHisMsgArray = NULL;
	}

	if (m_pSysMsgArray!=NULL)
	{
		delete[] m_pSysMsgArray;
		m_pSysMsgArray = NULL;
	}

	if (m_pAppMsgArray!=NULL)
	{
		delete[] m_pAppMsgArray;
		m_pAppMsgArray = NULL;
	}

	if (m_pUserMsgArray!=NULL)
	{
		delete[] m_pUserMsgArray;
		m_pUserMsgArray = NULL;
	}
}

void CMsgManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_VIEW, m_btnView);
	DDX_Control(pDX, IDC_BTN_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BTN_MSGDISPATCH, m_btnDispatch);
	DDX_Control(pDX, IDC_BTN_MSGHISTORY, m_btnHistory);

}


BEGIN_MESSAGE_MAP(CMsgManageDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_VIEW, &CMsgManageDlg::OnBnClickedBtnView)
	ON_BN_CLICKED(IDC_BTN_MSGDISPATCH, &CMsgManageDlg::OnBnClickedBtnMsgdispatch)
	ON_BN_CLICKED(IDC_BTN_MSGHISTORY, &CMsgManageDlg::OnBnClickedBtnMsghistory)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CMsgManageDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CMsgManageDlg 消息处理程序
BOOL CMsgManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitButtons();
	ReadAllMessage();

	return TRUE; 
}

void CMsgManageDlg::ReadAllMessage()
{
	//历史消息
	m_nHisMsgNum = m_pDB->ReadHistoryMsg(NULL);
	if(m_nHisMsgNum>0)
	{
		m_pHisMsgArray = new sTextMessage[m_nHisMsgNum];
		m_pDB->ReadHistoryMsg(m_pHisMsgArray);
	}
	
	//系统消息
	m_nSysMsgNum = m_pDB->ReadAllSysMsg(NULL);
	if(m_nSysMsgNum>0)
	{
		m_pSysMsgArray = new sTextMessage[m_nSysMsgNum];
		m_pDB->ReadAllSysMsg(m_pSysMsgArray);
	}

	//应用消息
	m_nAppMsgNum = m_pDB->ReadAllAppMsg(NULL);
	if(m_nAppMsgNum>0)
	{
		m_pAppMsgArray = new sTextMessage[m_nAppMsgNum];
		m_pDB->ReadAllAppMsg(m_pAppMsgArray);
	}

	//用户消息
	m_nUserMsgNum = m_pDB->ReadAllUserMsg(NULL);
	if(m_nUserMsgNum>0)
	{
		m_pUserMsgArray = new sTextMessage[m_nUserMsgNum];
		m_pDB->ReadAllUserMsg(m_pUserMsgArray);
	}

	SwitchMsgType(0);
}
//nType=0:调度消息，nType=1:历史消息
void CMsgManageDlg::SwitchMsgType(int nType)
{
	m_nMsgType = nType;
	int nSysCount=0,nAppCount=0,nUserCount=0;
	
	m_listSysMsg.RemoveAll();
	m_listAppMsg.RemoveAll();
	m_listUserMsg.RemoveAll();

	if (nType == 0)
	{
		for (int nIndex=0; nIndex<m_nSysMsgNum; nIndex++)
		{
			m_listSysMsg.AddMessage(nSysCount++,m_pSysMsgArray[nIndex]); 
		}

		for (int nIndex=0; nIndex<m_nAppMsgNum; nIndex++)
		{
			m_listAppMsg.AddMessage(nAppCount++,m_pAppMsgArray[nIndex]); 
		}

		for (int nIndex=0; nIndex<m_nUserMsgNum; nIndex++)
		{
			m_listUserMsg.AddMessage(nUserCount++,m_pUserMsgArray[nIndex]); 
		}
	}
	else
	{
		for (int nIndex=0; nIndex<m_nHisMsgNum; nIndex++)
		{
			switch(m_pHisMsgArray[nIndex].nType)
			{
				case 0:
					m_listSysMsg.AddMessage(nSysCount++,m_pHisMsgArray[nIndex]); 
					break;
				case 1:
					m_listAppMsg.AddMessage(nAppCount++,m_pHisMsgArray[nIndex]);
					break;
				case 2:
					m_listUserMsg.AddMessage(nUserCount++,m_pHisMsgArray[nIndex]);
					break;

			}
		}
		
	}
}

void CMsgManageDlg::InitButtons()
{
	m_btnDispatch.SetWindowText (_T("最近消息"));
	m_btnDispatch.SetFaceColor(RGB(135,206,235));
	m_btnDispatch.Invalidate ();
	m_btnDispatch.SetMouseCursorHand ();

	m_btnHistory.SetWindowText (_T("历史消息"));
	m_btnHistory.SetFaceColor(RGB(135,206,235));
	m_btnHistory.Invalidate ();
	m_btnHistory.SetMouseCursorHand ();

	m_btnView.SetWindowText (_T("查看内容"));
	m_btnView.SetFaceColor(RGB(135,206,235));
	m_btnView.Invalidate ();
	m_btnView.SetMouseCursorHand ();

	m_btnDelete.SetWindowText (_T("删除消息"));
	m_btnDelete.SetFaceColor(RGB(135,206,235));
	m_btnDelete.Invalidate ();
	m_btnDelete.SetMouseCursorHand ();
}

HBRUSH CMsgManageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	UINT nIDCtrl = pWnd->GetDlgCtrlID();

	switch (nIDCtrl)
	{
	case IDC_AREA_GRID:
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(200,234,249));
		break;
	}

	return hbr;
}


int CMsgManageDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_FLAT, rectDummy, this,1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;
	}

	const DWORD dwViewStyle =	
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/;

	if (!m_listUserMsg.Create (dwViewStyle, rectDummy, &m_wndTabs, 2) ||
		!m_listAppMsg.Create (dwViewStyle, rectDummy, &m_wndTabs, 3)||
		!m_listSysMsg.Create (dwViewStyle, rectDummy, &m_wndTabs, 4))
	{
		TRACE0("Failed to create output view\n");
		return -1;
	}

	m_wndTabs.AddTab (&m_listUserMsg, _T("用户消息"),IDB_MSG_APP);
	m_wndTabs.AddTab (&m_listAppMsg, _T("应用消息"), IDB_MSG_USER);
	m_wndTabs.AddTab (&m_listSysMsg, _T("系统消息"), IDB_MSG_SYS);

	m_wndTabs.SetTabBkColor(0,RGB(198,232,248));
	m_wndTabs.SetTabBkColor(1,RGB(198,232,248));
	return 0;
}

void CMsgManageDlg::OnPaint()
{
	CPaintDC dc(this); 
	
	CRect rect;
	CBitmap bmp;
	CDC memdc;
	CDC* pDC = GetDC();
	memdc.CreateCompatibleDC(pDC);
	bmp.LoadBitmap(IDB_HOMEPAGE_MSG);
	memdc.SelectObject(&bmp);

	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
	bmp.DeleteObject();
	memdc.DeleteDC();

//	rect.InflateRect (1,1);
//	dc.Draw3dRect (rect,::GetSysColor (COLOR_3DSHADOW),::GetSysColor (COLOR_3DSHADOW));
}

void CMsgManageDlg::OnSize(UINT nType, int cx, int cy)
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
//查看消息
void CMsgManageDlg::OnBnClickedBtnView()
{
	//0-用户消息,1-应用消息,2-系统消息
	int nCurSel =  m_wndTabs.GetActiveTab();

	int nMsgId = 0;

	//最新消息
	if (m_nMsgType==0)
	{
		switch(nCurSel)
		{
		case 0:
			m_listUserMsg.GetSelectMsg(nMsgId);
			break;
		case 1:
			m_listAppMsg.GetSelectMsg(nMsgId);
			break;
		case 2:
			m_listSysMsg.GetSelectMsg(nMsgId);
			break;

		}
	}
	//历史消息
	else
	{
		switch(nCurSel)
		{
		case 0:
			m_listUserMsg.GetSelectMsg(nMsgId);
			break;
		case 1:
			m_listAppMsg.GetSelectMsg(nMsgId);
			break;
		case 2:
			m_listSysMsg.GetSelectMsg(nMsgId);
			break;

		}
	}
	//从数据库里面查询消息
	sTextMessage* pMsg = QueryMsg(nMsgId,nCurSel,m_nMsgType);
	if (pMsg != NULL)
	{
		CString str = pMsg->title;
		str += "\r\n";
		str += pMsg->content;
		AfxMessageBox(str);
	}
}
//删除消息
void CMsgManageDlg::OnBnClickedBtnDelete()
{
	//0-用户消息,1-应用消息,2-系统消息
	int nCurSel =  m_wndTabs.GetActiveTab();
	int nMsgId = 0;
	//调度消息
	if (m_nMsgType==0)
	{
		switch(nCurSel)
		{
		case 0:
			m_listUserMsg.GetSelectMsg(nMsgId);

			if (nMsgId>=0 && m_pDB->RemoveUserMsg(nMsgId))
			{
				m_listUserMsg.RemoveSelectMsg();
			}
			break;
		case 1:
			m_listAppMsg.GetSelectMsg(nMsgId);
			
			if (nMsgId>=0 && m_pDB->RemoveAppMsg(nMsgId))
			{
				m_listAppMsg.RemoveSelectMsg();
			}
			break;
		case 2:
			m_listSysMsg.GetSelectMsg(nMsgId);
			
			if (nMsgId>=0 && m_pDB->RemoveSysMsg(nMsgId))
			{
				m_listSysMsg.RemoveSelectMsg();
			}
			break;

		}
	}
	//历史消息
	else
	{
		switch(nCurSel)
		{
		case 0:
			m_listUserMsg.GetSelectMsg(nMsgId);
			if (nMsgId>=0 && m_pDB->RemoveHistoryMsg(nMsgId))
			{
				m_listUserMsg.RemoveSelectMsg();
			}
			break;
		case 1:
			m_listAppMsg.GetSelectMsg(nMsgId);
			if (nMsgId>=0 && m_pDB->RemoveHistoryMsg(nMsgId))
			{
				m_listAppMsg.RemoveSelectMsg();
			}
			break;
		case 2:
			m_listSysMsg.GetSelectMsg(nMsgId);
			if (nMsgId>=0 && m_pDB->RemoveHistoryMsg(nMsgId))
			{
				m_listSysMsg.RemoveSelectMsg();
			}
			break;
		}
	}

	if (nMsgId<0)
	{
		AfxMessageBox("错误：没有选择记录！");
	}
}

void CMsgManageDlg::OnBnClickedBtnMsgdispatch()
{
	SwitchMsgType(0);
}

void CMsgManageDlg::OnBnClickedBtnMsghistory()
{
	SwitchMsgType(1);
}
//查询成功返回数据指针，查询失败返回NULL
sTextMessage* CMsgManageDlg::QueryMsg(int nMsgId,int nMsgType,int nType)
{
	sTextMessage*  pFindMsg = NULL;
	if (nMsgId<0)
	{
		return NULL;
	}
	if(nType == 0)
	{
		switch(nMsgType)
		{
		case 0:
			for (int nIndex=0; nIndex<m_nUserMsgNum; nIndex++)
			{
				if (m_pUserMsgArray[nIndex].nMsgID == nMsgId)
				{
					pFindMsg = &m_pUserMsgArray[nIndex];
					break;
				}
			}
			break;
		case 1:
			for (int nIndex=0; nIndex<m_nAppMsgNum; nIndex++)
			{
				if (m_pAppMsgArray[nIndex].nMsgID == nMsgId)
				{
					pFindMsg = &m_pAppMsgArray[nIndex];
					break;
				}
			}
			break;
		case 2:
			for (int nIndex=0; nIndex<m_nSysMsgNum; nIndex++)
			{
				if (m_pSysMsgArray[nIndex].nMsgID == nMsgId)
				{
					pFindMsg = &m_pSysMsgArray[nIndex];
					break;
				}
			}
			break;

		}
	}
	else
	{
		for (int nIndex=0; nIndex<m_nHisMsgNum; nIndex++)
		{
			if (m_pHisMsgArray[nIndex].nMsgID == nMsgId)
			{
				pFindMsg = &m_pHisMsgArray[nIndex];
				break;
			}
		}
	}
	return pFindMsg;
}

