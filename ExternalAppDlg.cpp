// ExternalAppDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "ExternalAppDlg.h"
#include <shellapi.h>
#include "AppItemDlg.h"
#include "AppFlowDlg.h"


// CExternalAppDlg 对话框
IMPLEMENT_DYNAMIC(CExternalAppDlg, CDialog)

CExternalAppDlg::CExternalAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExternalAppDlg::IDD, pParent)
{
	m_pDB = ((CMSG_PLATFORMApp*)AfxGetApp())->m_pDB;
}

CExternalAppDlg::~CExternalAppDlg()
{
}

void CExternalAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MNSENDMSG, m_btnSendAppMsg);
	DDX_Control(pDX, IDC_LIST_ITEM, m_listItems);
	DDX_Control(pDX, IDC_LIST_FLOW, m_listFlows);
	DDX_Control(pDX, IDC_BTN_ADDITEM, m_btnAddItem);
	DDX_Control(pDX, IDC_BTN_DELITEM, m_btnDelItem);
	DDX_Control(pDX, IDC_BTN_ADDFLOW, m_btnAddFlow);
	DDX_Control(pDX, IDC_BTN_DELFLOW, m_btnDelFlow);
	DDX_Control(pDX, IDC_LIST_EXTAPP, m_listApps);
}


BEGIN_MESSAGE_MAP(CExternalAppDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_MNSENDMSG, OnBnClickedBtnMnsendmsg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_ADDITEM, &CExternalAppDlg::OnBnClickedBtnAdditem)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EXTAPP, &CExternalAppDlg::OnLvnItemchangedListExtapp)
	ON_BN_CLICKED(IDC_BTN_DELITEM, &CExternalAppDlg::OnBnClickedBtnDelitem)
	ON_BN_CLICKED(IDC_BTN_ADDFLOW, &CExternalAppDlg::OnBnClickedBtnAddflow)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FLOW, &CExternalAppDlg::OnLvnItemchangedListFlow)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ITEM, &CExternalAppDlg::OnLvnItemchangedListItem)
	ON_BN_CLICKED(IDC_BTN_DELFLOW, &CExternalAppDlg::OnBnClickedBtnDelflow)
END_MESSAGE_MAP()



BOOL CExternalAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
 
	m_font.CreatePointFont(120,_T("宋体")); 
	m_listApps.SetFont(&m_font,true);
	m_listItems.SetFont(&m_font,true);
	m_listFlows.SetFont(&m_font,true);

	DWORD dwStyle = m_listFlows.GetStyle();
	dwStyle = dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listFlows.SetExtendedStyle(dwStyle);

	HICON hIcon[3];
	m_ImageList.Create(24, 24,ILC_COLOR32|ILC_MASK, 2, 1);
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_LIST_APP);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_LIST_APP);
	for (int n=0; n<2; n++)
	{
		m_ImageList.Add(hIcon[n]);
	}
	m_listApps.SetImageList(&m_ImageList,LVSIL_SMALL);
	m_listFlows.SetImageList(&m_ImageList,LVSIL_SMALL);


	m_ImageList2.Create(32, 32,ILC_COLOR32|ILC_MASK, 2, 1);
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_LIST_ITEM);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_LIST_ITEM);
	for (int n=0; n<2; n++)
	{
		m_ImageList2.Add(hIcon[n]);
	}
	m_listItems.SetImageList(&m_ImageList2,LVSIL_NORMAL);
	
	m_listFlows.InsertColumn(0,"序号",LVCFMT_CENTER,50);
	m_listFlows.InsertColumn(1,"流程名称",LVCFMT_LEFT,180);
	m_listFlows.InsertColumn(2,"自动执行",LVCFMT_CENTER,98);
	m_listFlows.InsertColumn(3,"发送消息",LVCFMT_CENTER,98);
	m_listFlows.InsertColumn(4,"消息内容",LVCFMT_LEFT,180);
	m_listFlows.InsertColumn(5,"接收终端",LVCFMT_CENTER,120);
	
	InitButtons();

	InitAppData();

	return TRUE; 
}

void CExternalAppDlg::InitButtons()
{
	m_btnSendAppMsg.SetWindowText (_T("模拟消息"));
	m_btnSendAppMsg.SetFaceColor(RGB(135,206,235));
	m_btnSendAppMsg.Invalidate ();
	m_btnSendAppMsg.SetMouseCursorHand ();

	m_btnAddItem.SetWindowText (_T("添加事项"));
	m_btnAddItem.SetFaceColor(RGB(135,206,235));
	m_btnAddItem.Invalidate ();
	m_btnAddItem.SetMouseCursorHand ();

	m_btnDelItem.SetWindowText (_T("删除"));
	m_btnDelItem.SetFaceColor(RGB(135,206,235));
	m_btnDelItem.Invalidate ();
	m_btnDelItem.SetMouseCursorHand ();

	m_btnAddFlow.SetWindowText (_T("添加流程"));
	m_btnAddFlow.SetFaceColor(RGB(135,206,235));
	m_btnAddFlow.Invalidate ();
	m_btnAddFlow.SetMouseCursorHand ();

	m_btnDelFlow.SetWindowText (_T("删除"));
	m_btnDelFlow.SetFaceColor(RGB(135,206,235));
	m_btnDelFlow.Invalidate ();
	m_btnDelFlow.SetMouseCursorHand ();
}

void CExternalAppDlg::InitAppData()
{
	m_nAppNum = m_pDB->ReadAllApps(NULL);
	
	if (m_nAppNum>0)
	{
		m_pAppArray = new sAppInfo[m_nAppNum];
		m_pDB->ReadAllApps(m_pAppArray);
	}
	
	//应用添加到列表
	int nCount = 0;
	for (int nIndex=0; nIndex<m_nAppNum; nIndex++)
	{
		//审核通过的应用
		if (m_pAppArray[nIndex].nStatus == 1)
		{
			m_listApps.InsertItem(nCount,m_pAppArray[nIndex].AppName,0);
			m_listApps.SetItemData(nCount,(DWORD)(&m_pAppArray[nIndex]));
			nCount++;
		}
	}
	//获取所有ITEM数据
	int nItemNum = m_pDB->ReadAppItems(NULL,NULL);
	
	if(nItemNum>0 && nItemNum<1000)
	{
		sAppItem* pItemArray = new sAppItem[nItemNum];
		m_pDB->ReadAppItems(NULL,pItemArray);

		for (int nIndex=0; nIndex<nItemNum; nIndex++)
		{
			m_ItemArray.push_back(pItemArray[nIndex]);
		}
		delete[] pItemArray;
		pItemArray = NULL;
	}

	int nFlowNum = m_pDB->ReadItemFlows(-1,NULL);

	if(nFlowNum>0 && nFlowNum<2000)
	{
		sAppFlow* pFlowArray = new sAppFlow[nFlowNum];
		m_pDB->ReadItemFlows(-1,pFlowArray);

		for (int nIndex=0; nIndex<nFlowNum; nIndex++)
		{
			m_FlowArray.push_back(pFlowArray[nIndex]);
		}
		delete[] pFlowArray;
		pFlowArray = NULL;
	}
}

// CExternalAppDlg 消息处理程序
void CExternalAppDlg::OnPaint()
{
	CPaintDC dc(this); 

	CRect rect;
	CBitmap bmp;
	CDC memdc;
	CDC* pDC = GetDC();
	memdc.CreateCompatibleDC(pDC);
	bmp.LoadBitmap(IDB_HOMEPAGE_EXTAPP);
	memdc.SelectObject(&bmp);

	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
	bmp.DeleteObject();
	memdc.DeleteDC();
}

//模拟第三方应用发消息
void CExternalAppDlg::OnBnClickedBtnMnsendmsg()
{
	POSITION pos = m_listItems.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox("错误：未选择事项！","外部应用",MB_ICONERROR|MB_OK);
		return;
	}

	int nCurSel = m_listItems.GetNextSelectedItem(pos);
	int nItemId = m_listItems.GetItemData(nCurSel);


	CString str;
	str.Format("%d",nItemId);
	HINSTANCE dwRet = ShellExecute(m_hWnd,"open","ExternalApp.exe",str,".\\Debug",SW_SHOWNORMAL);
	if ((DWORD)dwRet < 32)
	{
		MessageBox("打开失败!");
	}
}


HBRUSH CExternalAppDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd == this)
	{
		hbr = CreateSolidBrush(RGB(51,153,204));
	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(198,232,248));
	}

	return hbr;
}

void CExternalAppDlg::OnLvnItemchangedListExtapp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	POSITION pos = m_listApps.GetFirstSelectedItemPosition();
	if (pos ==NULL)
	{
		return;
	}

	m_listItems.DeleteAllItems();

	int nCurSel = m_listApps.GetNextSelectedItem(pos);
	sAppInfo *pApp = (sAppInfo*)m_listApps.GetItemData(nCurSel);

	int nCount = 0;
	for (vector<sAppItem>::iterator it=m_ItemArray.begin(); it!=m_ItemArray.end(); it++)
	{
		if (strcmp(pApp->AppID,it->AppID) == 0)
		{
			m_listItems.InsertItem(nCount,it->ItemName,1);
			m_listItems.SetItemData(nCount,(DWORD)it->nItemId);
			nCount++;
		}
	}

	*pResult = 0;
}

//增加事项
void CExternalAppDlg::OnBnClickedBtnAdditem()
{
	//获取选中的应用
	POSITION pos = m_listApps.GetFirstSelectedItemPosition();
	if (pos ==NULL)
	{
		MessageBox("错误：未选择应用！","外部应用",MB_ICONERROR|MB_OK);
		return;
	}

	int nCurSel = m_listApps.GetNextSelectedItem(pos);
	sAppInfo *pApp = (sAppInfo*)m_listApps.GetItemData(nCurSel);
	
	//打开编辑对话框
	CAppItemDlg itemDlg;
	sAppItem *pItemInfo = new sAppItem;
	itemDlg.SetAppInfo(pApp);
	if (itemDlg.DoModal() == IDOK)
	{
		itemDlg.GetAppItem(pItemInfo);
		//保存成功
		if (m_pDB->SaveItem(pItemInfo))
		{
			pItemInfo->nItemId = m_pDB->GetLastInsertId();
			int nCount = m_listItems.GetItemCount();
			m_listItems.InsertItem(nCount,pItemInfo->ItemName,0);
			m_listItems.SetItemData(nCount,(DWORD)pItemInfo->nItemId);
			m_ItemArray.push_back(*pItemInfo);
		}
		else
		{
			MessageBox("错误：保存失败！","外部应用",MB_ICONERROR|MB_OK);
		}
	}
	delete pItemInfo;
	pItemInfo = NULL;
}

//删除事项
void CExternalAppDlg::OnBnClickedBtnDelitem()
{
	//获取选中的应用
	POSITION pos = m_listItems.GetFirstSelectedItemPosition();
	if (pos ==NULL)
	{
		MessageBox("错误：未选择事项！","外部应用",MB_ICONERROR|MB_OK);
		return;
	}

	int nCurSel = m_listItems.GetNextSelectedItem(pos);
	int nItemId = m_listItems.GetItemData(nCurSel);
	bool bSuccess = false;

	for (vector<sAppItem>::iterator it=m_ItemArray.begin(); it!=m_ItemArray.end(); it++)
	{
		if (it->nItemId == nItemId)
		{
			if (m_pDB->RemoveItem(&(*it)))
			{
				m_ItemArray.erase(it);
				m_listItems.DeleteItem(nCurSel);
				bSuccess = true;
			}
			else
			{
				MessageBox("删除失败！","外部应用",MB_ICONERROR|MB_OK);
			}
			break;
		}
	}
	//此处出现一个vector错误
	if (bSuccess)
	{
		for (vector<sAppFlow>::iterator it=m_FlowArray.begin(); it!=m_FlowArray.end(); it++)
		{
			if (nItemId == it->nItemId)
			{
				m_FlowArray.erase(it);
			}
		}
		m_listFlows.DeleteAllItems();
	}
}

void CExternalAppDlg::OnLvnItemchangedListItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	m_listFlows.DeleteAllItems();

	POSITION pos = m_listItems.GetFirstSelectedItemPosition();
	if (pos ==NULL)
	{
		return;
	}

	int nCurSel = m_listItems.GetNextSelectedItem(pos);
	int nItemId = m_listItems.GetItemData(nCurSel);

	int nCount = 0;
	for (vector<sAppFlow>::iterator it=m_FlowArray.begin(); it!=m_FlowArray.end(); it++)
	{
		if (nItemId == it->nItemId)
		{
			InsertFlowList(nCount++,&(*it));
		}
	}

	*pResult = 0;
}

//添加流程
void CExternalAppDlg::OnBnClickedBtnAddflow()
{
	//获取选中的应用
	POSITION pos = m_listItems.GetFirstSelectedItemPosition();
	if (pos ==NULL)
	{
		MessageBox("错误：未选择事项！","外部应用",MB_ICONERROR|MB_OK);
		return;
	}

	int nCurSel = m_listItems.GetNextSelectedItem(pos);
	int nItemId = m_listItems.GetItemData(nCurSel);
	
	sAppItem itemins;

	for (vector<sAppItem>::iterator it=m_ItemArray.begin(); it!=m_ItemArray.end(); it++)
	{
		if (it->nItemId == nItemId)
		{
			itemins = *it;
			break;
		}
	}


	//打开编辑对话框
	CString str;
	CAppFlowDlg flowDlg;
	sAppFlow *pFlowInfo = new sAppFlow;
	flowDlg.SetAppItem(&itemins);

	if (flowDlg.DoModal() == IDOK)
	{
		flowDlg.GetAppFlow(pFlowInfo);
		//保存成功
		if (m_pDB->SaveFlow(pFlowInfo))
		{
			pFlowInfo->nFlowId = m_pDB->GetLastInsertId();
			m_FlowArray.push_back(*pFlowInfo);

			InsertFlowList(m_listFlows.GetItemCount(),pFlowInfo);
		}
		else
		{
			MessageBox("错误：保存失败！","外部应用",MB_ICONERROR|MB_OK);
		}
	}
	delete pFlowInfo;
	pFlowInfo = NULL;
}


void CExternalAppDlg::InsertFlowList(int nCount,sAppFlow* pFlowInfo)
{
	CString str;
	if (nCount<0 || pFlowInfo==NULL)
	{
		return;
	}

	str.Format("%d",pFlowInfo->nOrder); 
	m_listFlows.InsertItem(nCount,str,1);
	m_listFlows.SetItemData(nCount,(DWORD)pFlowInfo->nFlowId);

	m_listFlows.SetItemText(nCount,1,pFlowInfo->FlowName);

	if (pFlowInfo->IsAutoExecute)
	{
		m_listFlows.SetItemText(nCount,2,"是");
	}
	else
	{
		m_listFlows.SetItemText(nCount,2,"否");
	}

	if (pFlowInfo->IsSendMessage)
	{
		m_listFlows.SetItemText(nCount,3,"是");
	}
	else
	{
		m_listFlows.SetItemText(nCount,3,"否");
	}

	m_listFlows.SetItemText(nCount,4,pFlowInfo->Message);
	//发送方式
	str = "";
	str += (pFlowInfo->SendType[0]=='1'?"消息平台/":"");
	str += (pFlowInfo->SendType[1]=='1'?"邮件/":"");
	str += (pFlowInfo->SendType[2]=='1'?"短信/":"");
	str += (pFlowInfo->SendType[3]=='1'?"微信/":"");
	m_listFlows.SetItemText(nCount,5,str);
}

void CExternalAppDlg::OnBnClickedBtnDelflow()
{
	POSITION pos = m_listFlows.GetFirstSelectedItemPosition();
	if (pos ==NULL)
	{
		MessageBox("错误：未选择流程！","外部应用",MB_ICONERROR|MB_OK);
		return;
	}

	int nCurSel = m_listFlows.GetNextSelectedItem(pos);
	int nFlowId = m_listFlows.GetItemData(nCurSel);

	for (vector<sAppFlow>::iterator it=m_FlowArray.begin(); it!=m_FlowArray.end(); it++)
	{
		if (it->nFlowId == nFlowId)
		{
			if (m_pDB->RemoveFlow(&(*it)))
			{
				m_FlowArray.erase(it);
				m_listFlows.DeleteItem(nCurSel);
			}
			else
			{
				MessageBox("删除失败！","外部应用",MB_ICONERROR|MB_OK);
			}
			break;
		}
	}
}
void CExternalAppDlg::OnLvnItemchangedListFlow(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);


	*pResult = 0;
}




