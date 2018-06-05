// UserManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "UserManageDlg.h"
#include "UserInfoDlg.h"
#include "UnitInfoDlg.h"

// CUserManageDlg �Ի���
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


// CUserManageDlg ��Ϣ�������

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

	m_listUser.InsertItem(0,"����",2);
	m_listUser.InsertItem(1,"����",2);

	m_hRoot = m_treeUnit.InsertItem("��֯����");

	InitUnitTree();
	InitUserInfo();
	
	return TRUE; 
}

void CUserManageDlg::InitButtons()
{
	m_btnAddUnit.SetWindowText (_T("���ӵ�λ"));
	m_btnAddUnit.SetFaceColor(RGB(135,206,235));
	m_btnAddUnit.Invalidate ();
	m_btnAddUnit.SetMouseCursorHand ();

	m_btnModifyUnit.SetWindowText (_T("�޸ĵ�λ"));
	m_btnModifyUnit.SetFaceColor(RGB(135,206,235));
	m_btnModifyUnit.Invalidate ();
	m_btnModifyUnit.SetMouseCursorHand ();

	m_btnDelUnit.SetWindowText (_T("ɾ����λ"));
	m_btnDelUnit.SetFaceColor(RGB(135,206,235));
	m_btnDelUnit.Invalidate ();
	m_btnDelUnit.SetMouseCursorHand ();

	m_btnAddUser.SetWindowText (_T("�����û�"));
	m_btnAddUser.SetFaceColor(RGB(135,206,235));
	m_btnAddUser.Invalidate ();
	m_btnAddUser.SetMouseCursorHand ();

	m_btnModifyUser.SetWindowText (_T("�޸��û�"));
	m_btnModifyUser.SetFaceColor(RGB(135,206,235));
	m_btnModifyUser.Invalidate ();
	m_btnModifyUser.SetMouseCursorHand ();
	
	m_btnDelUser.SetWindowText (_T("ɾ���û�"));
	m_btnDelUser.SetFaceColor(RGB(135,206,235));
	m_btnDelUser.Invalidate ();
	m_btnDelUser.SetMouseCursorHand ();
}

//��ʼ��װ����
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

	//���һ���ڵ�
	for (nIndex=0; nIndex<(int)m_totalUnits.size(); nIndex++)
	{
		
		//һ���ڵ���ϼ�IDС��0 
		if (m_totalUnits[nIndex].nSuperID<0)
		{
			HTREEITEM hItem = NULL;
			hItem = m_treeUnit.InsertItem(m_totalUnits[nIndex].UnitName,1,1,m_hRoot);
			
			m_treeUnit.SetItemData(hItem,(DWORD)&m_totalUnits[nIndex]);
			//������������ڵ�
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
		//�ҳ������ӽڵ�
		if (m_totalUnits[nIndex].nSuperID==pSupUnit->nUnitID)
		{
			HTREEITEM hItem = NULL;
			hItem = m_treeUnit.InsertItem(m_totalUnits[nIndex].UnitName,1,1,hParent);	
			m_treeUnit.SetItemData(hItem,(DWORD)&m_totalUnits[nIndex]);
			AddtoNode(hItem);
		}	
	}
}

//��ʼ���û���Ϣ
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

//���ӵ�λ
void CUserManageDlg::OnBnClickedBtnAddunit()
{      
	UpdateData();

	CUnitInfoDlg dlg;
	sUnitInfo* pUnit = new sUnitInfo;
	HTREEITEM hSel = m_treeUnit.GetSelectedItem();
	HTREEITEM hNewNode = NULL;

	if (hSel==NULL)
	{
		MessageBox("����δѡ��Ҫ��ӵ�λ���ϼ���λ","�û�����",MB_ICONERROR);
		return;
	}

	sUnitInfo* pSupUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSel);
	dlg.SetSuperUnit(pSupUnit);

	if (pSupUnit!=NULL && pSupUnit->nSuperID!=-1)
	{
		MessageBox("�ݲ�֧��4�����ţ�","�û�����",MB_ICONINFORMATION);
		return;
	}
	
	if (dlg.DoModal()==IDOK)
	{
		dlg.GetUnitInfo(pUnit);

		if (m_pDB->SaveUnit(pUnit))
		{
			hNewNode = m_treeUnit.InsertItem(pUnit->UnitName,1,1,hSel);
			MessageBox("��ӵ�λ�ɹ���","�û�����");
			
			m_totalUnits.push_back(*pUnit);
			m_treeUnit.SetItemData(hNewNode,(DWORD)pUnit);
		}
		else
		{
			MessageBox("���浽���ݿ���󣬵�λ��ſ����ظ���","�û�����",MB_ICONERROR);
		}
	}
	
// 	delete pUnit;
// 	pUnit = NULL;
}
//�����û�
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
		MessageBox("����δѡ��������λ��","�û�����",MB_ICONERROR);
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
			MessageBox("����û�ʧ�ܣ�","�û�����",MB_ICONERROR);
		}
	}

//	delete pUser;
//	pUser = NULL;
}

void CUserManageDlg::OnBnClickedBtnDelunit()
{
	if (MessageBox("ȷ��Ҫɾ���õ�λ��������λ��","�û�����",MB_ICONQUESTION|MB_OKCANCEL)!=IDOK)
	{
		return;
	}

	HTREEITEM hSel = m_treeUnit.GetSelectedItem();
	sUnitInfo* pSelUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSel);
 
	if (hSel==NULL||pSelUnit==NULL)
	{
		MessageBox("����δѡ��Ҫɾ���ĵ�λ��","�û�����",MB_ICONERROR);
		return;
	}
	
	//ͨ����ʶλɾ��
	for (vector<sUnitInfo>::iterator it=m_totalUnits.begin(); it!=m_totalUnits.end(); it++)
	{
		it->bDelFlag = false;
	}
	
	//ɾ��������λ
	if (!RemoveSubUnit(pSelUnit))
	{
		MessageBox("ɾ����λʧ�ܣ��õ�λ�����û���Ϣ��","�û�����",MB_ICONERROR);
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
				MessageBox("ɾ����λʧ�ܣ��õ�λ�����û���Ϣ��","�û�����",MB_ICONERROR);
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

		//����ڴ�
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

//ɾ��������λ
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
//�޸ĵ�λ
void CUserManageDlg::OnBnClickedBtnModifyunit()
{
	HTREEITEM hSel = m_treeUnit.GetSelectedItem();
	
	if (hSel == m_treeUnit.GetRootItem())
	{
		MessageBox("���󣬸��ڵ㲻�ܽ��иò�����","�û�����",MB_ICONERROR);
		return;
	}
	
	sUnitInfo* pSelUnit = NULL;

	if(hSel != NULL)
	{
		pSelUnit = (sUnitInfo*)m_treeUnit.GetItemData(hSel);
	}
	
	if (hSel==NULL||pSelUnit==NULL)
	{	
		MessageBox("����δѡ��λ��","�û�����",MB_ICONERROR);
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

//ɾ���û�
void CUserManageDlg::OnBnClickedBtnDeluser()
{
	POSITION pos = m_listUser.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
	{
		MessageBox("����δѡ���û���","�û�����",MB_ICONERROR);
		return;
	}
	int nSel = m_listUser.GetNextSelectedItem(pos);

	sUserInfo* pUser = (sUserInfo*)m_listUser.GetItemData(nSel);

	if (pUser == NULL)
	{
		MessageBox("����ɾ���û�ʧ�ܣ�","�û�����",MB_ICONERROR);
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
		MessageBox("����δѡ���û���","�û�����",MB_ICONERROR);
		return;
	}
	int nSel = m_listUser.GetNextSelectedItem(pos);

	sUserInfo* pUser = (sUserInfo*)m_listUser.GetItemData(nSel);

	if (pUser == NULL)
	{
		MessageBox("�����޸��û�ʧ�ܣ�","�û�����",MB_ICONERROR);
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
