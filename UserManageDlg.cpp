// UserManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "UserManageDlg.h"
#include "UserInfoDlg.h"
#include "UnitInfoDlg.h"

// CUserManageDlg 对话框
IMPLEMENT_DYNAMIC(CUserManageDlg, CDialog)

CUserManageDlg::CUserManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManageDlg::IDD, pParent)
{
	m_pDB = ((CMSG_PLATFORMApp*)AfxGetApp())->m_pDB;
	m_hRoot = NULL;
}

CUserManageDlg::~CUserManageDlg()
{
	m_totalUnits.clear();
	m_totalUsers.clear();
}

void CUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADDUNIT, m_btnAddUnit);
	DDX_Control(pDX, IDC_BTN_MODIFYUNIT, m_btnModifyUnit);
	DDX_Control(pDX, IDC_BTN_DELUNIT, m_btnDelUnit);
	DDX_Control(pDX, IDC_BTN_ADDUSER, m_btnAddUser);
	DDX_Control(pDX, IDC_BTN_MODIFYUSER, m_btnModifyUser);
	DDX_Control(pDX, IDC_BTN_DELUSER, m_btnDelUser);
	DDX_Control(pDX, IDC_TREE_UNIT, m_treeUnit);
	DDX_Control(pDX, IDC_LIST_USER, m_listUser);
}


BEGIN_MESSAGE_MAP(CUserManageDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_ADDUNIT, &CUserManageDlg::OnBnClickedBtnAddunit)
	ON_BN_CLICKED(IDC_BTN_ADDUSER, &CUserManageDlg::OnBnClickedBtnAdduser)
	ON_BN_CLICKED(IDC_BTN_DELUNIT, &CUserManageDlg::OnBnClickedBtnDelunit)
	ON_BN_CLICKED(IDC_BTN_MODIFYUNIT, &CUserManageDlg::OnBnClickedBtnModifyunit)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_UNIT, &CUserManageDlg::OnTvnSelchangedTreeUnit)
	ON_BN_CLICKED(IDC_BTN_DELUSER, &CUserManageDlg::OnBnClickedBtnDeluser)
	ON_BN_CLICKED(IDC_BTN_MODIFYUSER, &CUserManageDlg::OnBnClickedBtnModifyuser)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CUserManageDlg 消息处理程序

BOOL CUserManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitButtons();

	HICON hIcon[5];
	m_ImageList.Create(32, 32,ILC_COLOR32|ILC_MASK, 3, 1);
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_TREE_ROOT);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_TREE_NODE);
	hIcon[2] = AfxGetApp()->LoadIcon(IDI_USER);
	for (int n=0; n<3; n++)
	{
		m_ImageList.Add(hIcon[n]);
	}

	m_treeUnit.SetImageList(&m_ImageList,LVSIL_NORMAL);
	m_listUser.SetImageList(&m_ImageList,LVSIL_NORMAL);

	m_listUser.InsertItem(0,"张三",2);
	m_listUser.InsertItem(1,"李四",2);

	m_hRoot = m_treeUnit.InsertItem("组织机构");

	InitUnitTree();
	InitUserInfo();
	
	return TRUE; 
}

void CUserManageDlg::InitButtons()
{
	m_btnAddUnit.SetWindowText (_T("增加单位"));
	m_btnAddUnit.SetFaceColor(RGB(135,206,235));
	m_btnAddUnit.Invalidate ();
	m_btnAddUnit.SetMouseCursorHand ();

	m_btnModifyUnit.SetWindowText (_T("修改单位"));
	m_btnModifyUnit.SetFaceColor(RGB(135,206,235));
	m_btnModifyUnit.Invalidate ();
	m_btnModifyUnit.SetMouseCursorHand ();

	m_btnDelUnit.SetWindowText (_T("删除单位"));
	m_btnDelUnit.SetFaceColor(RGB(135,206,235));
	m_btnDelUnit.Invalidate ();
	m_btnDelUnit.SetMouseCursorHand ();

	m_btnAddUser.SetWindowText (_T("增加用户"));
	m_btnAddUser.SetFaceColor(RGB(135,206,235));
	m_btnAddUser.Invalidate ();
	m_btnAddUser.SetMouseCursorHand ();

	m_btnModifyUser.SetWindowText (_T("修改用户"));
	m_btnModifyUser.SetFaceColor(RGB(135,206,235));
	m_btnModifyUser.Invalidate ();
	m_btnModifyUser.SetMouseCursorHand ();
	
	m_btnDelUser.SetWindowText (_T("删除用户"));
	m_btnDelUser.SetFaceColor(RGB(135,206,235));
	m_btnDelUser.Invalidate ();
	m_btnDelUser.SetMouseCursorHand ();
}

//初始化装备树
void CUserManageDlg::InitUnitTree()
{
	int nIndex = 0;
	
	sUnitInfo* pUnitArray = NULL;
	int nUnitNum = 0;

	nUnitNum = m_pDB->ReadAllUnits(NULL);

	if (nUnitNum>0)
	{
		pUnitArray = new sUnitInfo[nUnitNum];
		m_pDB->ReadAllUnits(pUnitArray);

		for (nIndex=0; nIndex<nUnitNum; nIndex++)
		{
			m_totalUnits.push_back(pUnitArray[nIndex]);
		}

		delete[] pUnitArray;
		pUnitArray = NULL;
	}

	//添加一级节点
	for (nIndex=0; nIndex<(int)m_totalUnits.size(); nIndex++)
	{
		
		//一级节点的上级ID小于0 
		if (m_totalUnits[nIndex].nSuperID<0)
		{
			HTREEITEM hItem = NULL;
			hItem = m_treeUnit.InsertItem(m_totalUnits[nIndex].UnitName,1,1,m_hRoot);
			
			m_treeUnit.SetItemData(hItem,(DWORD)&m_totalUnits[nIndex]);
			//添加所有下属节点
			AddtoNode(hItem);
		}
	}
	m_treeUnit.Expand(m_hRoot,TVE_EXPAND);
}

void CUserManageDlg::AddtoNode(HTREEITEM hParent)
{
	HTREEITEM hAddItem = NULL;
	sUnitInfo* pSupUnit = (sUnitInfo*)m_treeUnit.GetItemData(hParent);

	for (int nIndex=0; nIndex<(int)m_totalUnits.size(); nIndex++)
	{
		//找出所有子节点
		if (m_totalUnits[nIndex].nSuperID==pSupUnit->nUnitID)
		{
			HTREEITEM hItem = NULL;
			hItem = m_treeUnit.InsertItem(m_totalUnits[nIndex].UnitName,1,1,hParent);	
			m_treeUnit.SetItemData(hItem,(DWORD)&m_totalUnits[nIndex]);
			AddtoNode(hItem);
		}	
	}
}

//初始化用户信息
void CUserManageDlg::InitUserInfo()
{
	int nIndex = 0;

	sUserInfo* pUserArray = NULL;
	int nUserNum = 0;

	nUserNum = m_pDB->ReadAllUsers(pUserArray);

	if (nUserNum>0)
	{
		pUserArray = new sUserInfo[nUserNum];
		m_pDB->ReadAllUsers(pUserArray);
		
		
		for (nIndex=0; nIndex<nUserNum; nIndex++)
		{
			m_totalUsers.push_back(pUserArray[nIndex]);
		}
		
		delete[] pUserArray;
		pUserArray = NULL;
	}
	
	for (nIndex=0; nIndex<(int)m_totalUsers.size(); nIndex++)
	{
		m_listUser.InsertItem(nIndex,m_totalUsers[nIndex].UserName,2);
		m_listUser.SetItemData(nIndex,(DWORD)&m_totalUsers[nIndex]);
	}
}
void CUserManageDlg::OnPaint()
{
	CPaintDC dc(this); CRect rect;
	CBitmap bmp;
	CDC memdc;
	CDC* pDC = GetDC();
	memdc.CreateCompatibleDC(pDC);
	bmp.LoadBitmap(IDB_HOMEPAGE_USER);
	memdc.SelectObject(&bmp);

	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
	bmp.DeleteObject();
	memdc.DeleteDC();
}

//增加单位
void CUserManageDlg::OnBnClickedBtnAddunit()
{      
	UpdateData();

	CUnitInfoDlg dlg;
	sUnitInfo* pUnit = new sUnitInfo;
	HTREEITEM hSel = m_treeUnit.GetSelectedItem();
	HTREEITEM hNewNode = NULL;

	if (hSel==NULL)
	{
		MessageBox("错误，未选择要添加单位的上级单位","用户管理",MB_ICONERROR);
		return;
	}

	sUnitInfo* pSupUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSel);
	dlg.SetSuperUnit(pSupUnit);

	if (pSupUnit!=NULL && pSupUnit->nSuperID!=-1)
	{
		MessageBox("暂不支持4级部门！","用户管理",MB_ICONINFORMATION);
		return;
	}
	
	if (dlg.DoModal()==IDOK)
	{
		dlg.GetUnitInfo(pUnit);

		if (m_pDB->SaveUnit(pUnit))
		{
			hNewNode = m_treeUnit.InsertItem(pUnit->UnitName,1,1,hSel);
			MessageBox("添加单位成功！","用户管理");
			
			m_totalUnits.push_back(*pUnit);
			m_treeUnit.SetItemData(hNewNode,(DWORD)pUnit);
		}
		else
		{
			MessageBox("保存到数据库错误，单位编号可能重复！","用户管理",MB_ICONERROR);
		}
	}
	
// 	delete pUnit;
// 	pUnit = NULL;
}
//增加用户
void CUserManageDlg::OnBnClickedBtnAdduser()
{
	CUserInfoDlg dlg;
	sUserInfo* pUser = new sUserInfo;
	
	sUnitInfo* pUnit = NULL;
	HTREEITEM hSel = m_treeUnit.GetSelectedItem();
	
	if (hSel!=NULL)
	{
		pUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSel);
	}
	if (hSel==NULL||pUnit==NULL)
	{
		MessageBox("错误：未选择所属单位！","用户管理",MB_ICONERROR);
		return;
	}

	int nCount = m_listUser.GetItemCount();
	if (dlg.DoModal()==IDOK)
	{
		dlg.GetUserInfo(pUser);
		pUser->bOnlineStatus = 0;
		pUser->nUnitID = pUnit->nUnitID;

		if (m_pDB->SaveUser(pUser))
		{
			m_listUser.InsertItem(nCount,pUser->UserName,2);
			m_listUser.SetItemData(nCount,(DWORD)pUser);
			m_totalUsers.push_back(*pUser);
		}
		else
		{
			MessageBox("添加用户失败！","用户管理",MB_ICONERROR);
		}
	}

//	delete pUser;
//	pUser = NULL;
}

void CUserManageDlg::OnBnClickedBtnDelunit()
{
	if (MessageBox("确定要删除该单位及下属单位？","用户管理",MB_ICONQUESTION|MB_OKCANCEL)!=IDOK)
	{
		return;
	}

	HTREEITEM hSel = m_treeUnit.GetSelectedItem();
	sUnitInfo* pSelUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSel);
 
	if (hSel==NULL||pSelUnit==NULL)
	{
		MessageBox("错误，未选择要删除的单位！","用户管理",MB_ICONERROR);
		return;
	}
	
	//通过标识位删除
	for (vector<sUnitInfo>::iterator it=m_totalUnits.begin(); it!=m_totalUnits.end(); it++)
	{
		it->bDelFlag = false;
	}
	
	//删除下属单位
	if (!RemoveSubUnit(pSelUnit))
	{
		MessageBox("删除单位失败，该单位包含用户信息！","用户管理",MB_ICONERROR);
		return;
	}
	bool bContainUser = false;

	for (vector<sUnitInfo>::iterator it=m_totalUnits.begin(); it!=m_totalUnits.end(); it++)
	{
		if(it->nUnitID==pSelUnit->nUnitID)
		{
			if (m_pDB->RemoveUnit(pSelUnit))
			{
				m_treeUnit.DeleteItem(hSel);
				it->bDelFlag = true;
			}
			else
			{
				MessageBox("删除单位失败，该单位包含用户信息！","用户管理",MB_ICONERROR);
				bContainUser = true;
			}
			
			break;
		}
	}

	if (bContainUser)
	{
		return;
	}
	
	while(true)
	{
		bool bFind = false;

		//清除内存
		for (vector<sUnitInfo>::iterator it=m_totalUnits.begin(); it!=m_totalUnits.end(); it++)
		{
			if(it->bDelFlag)
			{
				bFind = true;
				m_totalUnits.erase(it);
				break;
			}
		}
		if (!bFind)
		{
			break;
		}
	}
	m_listUser.DeleteAllItems();
}

//删除下属单位
bool CUserManageDlg::RemoveSubUnit(sUnitInfo* pSupUnit)
{
	bool bResult = true;
	for (vector<sUnitInfo>::iterator it=m_totalUnits.begin(); it!=m_totalUnits.end(); it++)
	{
		sUnitInfo unit = *it;
		if(it->nSuperID == pSupUnit->nUnitID)
		{
			if (!RemoveSubUnit(&unit))
			{
				bResult = false;
				bResult;
			}
			if (m_pDB->RemoveUnit(&unit))
			{
				it->bDelFlag = true;	
				break;
			}
			else
			{
				bResult = false;
			}
		}
	}

	return bResult;
}
//修改单位
void CUserManageDlg::OnBnClickedBtnModifyunit()
{
	HTREEITEM hSel = m_treeUnit.GetSelectedItem();
	
	if (hSel == m_treeUnit.GetRootItem())
	{
		MessageBox("错误，根节点不能进行该操作！","用户管理",MB_ICONERROR);
		return;
	}
	
	sUnitInfo* pSelUnit = NULL;

	if(hSel != NULL)
	{
		pSelUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSel);
	}
	
	if (hSel==NULL||pSelUnit==NULL)
	{	
		MessageBox("错误，未选择单位！","用户管理",MB_ICONERROR);
		return;
	}
	
	HTREEITEM hSup = m_treeUnit.GetParentItem(hSel);
	sUnitInfo* pSupUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSup);


	CUnitInfoDlg dlg;
	dlg.SetSuperUnit(pSupUnit);
	dlg.SetUnitInfo(pSelUnit);
	dlg.SetModifyFlag();
	if (dlg.DoModal()==IDOK)
	{
		sUnitInfo newUnit;
		dlg.GetUnitInfo(&newUnit);

		if (m_pDB->SaveUnit(&newUnit,true))
		{
			m_treeUnit.SetItemText(hSel,newUnit.UnitName);
			for (vector<sUnitInfo>::iterator it=m_totalUnits.begin(); it!=m_totalUnits.end(); it++)
			{
				if (it->nUnitID == newUnit.nUnitID)
				{
					it->nRank = newUnit.nRank;
					strncpy_s(it->UnitName,newUnit.UnitName,LENGTH_100);
					strncpy_s(it->ManagerID,newUnit.ManagerID,LENGTH_20);
				}
			}
		}
	}
}

void CUserManageDlg::OnTvnSelchangedTreeUnit(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	if (pNMTreeView->itemNew.hItem == NULL)
	{
		return;	
	}
	
	HTREEITEM hSel = pNMTreeView->itemNew.hItem;
	m_listUser.DeleteAllItems();
	if (hSel == m_hRoot)
	{
		for (unsigned int nIndex=0; nIndex<m_totalUsers.size(); nIndex++)
		{
			m_listUser.InsertItem(nIndex,m_totalUsers[nIndex].UserName,2);
			m_listUser.SetItemData(nIndex,(DWORD)&m_totalUsers[nIndex]);
		}
	}
	else
	{
		sUnitInfo* pSelUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSel);
		if(hSel==NULL || pSelUnit==NULL)
		{
			return;
		}

		int nCount = 0;

		for (unsigned int nIndex=0; nIndex<m_totalUsers.size(); nIndex++)
		{
			if (m_totalUsers[nIndex].nUnitID == pSelUnit->nUnitID)
			{
				m_listUser.InsertItem(nCount,m_totalUsers[nIndex].UserName,2);
				m_listUser.SetItemData(nCount,(DWORD)&m_totalUsers[nIndex]);
				nCount++;
			}
		}
	}

	*pResult = 0;
}

//删除用户
void CUserManageDlg::OnBnClickedBtnDeluser()
{
	POSITION pos = m_listUser.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
	{
		MessageBox("错误：未选择用户！","用户管理",MB_ICONERROR);
		return;
	}
	int nSel = m_listUser.GetNextSelectedItem(pos);

	sUserInfo* pUser = (sUserInfo*)m_listUser.GetItemData(nSel);

	if (pUser == NULL)
	{
		MessageBox("错误：删除用户失败！","用户管理",MB_ICONERROR);
		return;
	}

	if (m_pDB->RemoveUser(pUser))
	{
		m_listUser.DeleteItem(nSel);
	}
}

void CUserManageDlg::OnBnClickedBtnModifyuser()
{
	POSITION pos = m_listUser.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		MessageBox("错误：未选择用户！","用户管理",MB_ICONERROR);
		return;
	}
	int nSel = m_listUser.GetNextSelectedItem(pos);

	sUserInfo* pUser = (sUserInfo*)m_listUser.GetItemData(nSel);

	if (pUser == NULL)
	{
		MessageBox("错误：修改用户失败！","用户管理",MB_ICONERROR);
		return;
	}

	CUserInfoDlg dlg;
	dlg.SetUserInfo(pUser);
	dlg.SetModifyFlag();
		
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetUserInfo(pUser);

		if (m_pDB->SaveUser(pUser,true))
		{
			m_listUser.SetItemText(nSel,0,pUser->UserName);
		}
	}
}

HBRUSH CUserManageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
