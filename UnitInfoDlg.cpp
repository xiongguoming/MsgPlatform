// UnitInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "UnitInfoDlg.h"


// CUnitInfo 对话框

IMPLEMENT_DYNAMIC(CUnitInfoDlg, CDialog)

CUnitInfoDlg::CUnitInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitInfoDlg::IDD, pParent)
	, m_nUnitID(0)
	, m_strUnitName(_T(""))
	, m_nRank(0)
	, m_strManager(_T(""))
	, m_strSuperUnit(_T(""))
{
	m_pSuperUnit = NULL;
	m_bModify = false;
}

CUnitInfoDlg::~CUnitInfoDlg()
{
}

void CUnitInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UNITID, m_nUnitID);
	DDX_Text(pDX, IDC_EDIT_UNITNAME, m_strUnitName);
	DDX_Text(pDX, IDC_EDIT_RANK, m_nRank);
	DDX_Text(pDX, IDC_EDIT_MANAGER, m_strManager);
	DDX_Text(pDX, IDC_EDIT_SUPERNAME, m_strSuperUnit);
}


BEGIN_MESSAGE_MAP(CUnitInfoDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CUnitInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CUnitInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if(m_pSuperUnit!=NULL)
	{
		m_strSuperUnit = m_pSuperUnit->UnitName;
	}

	if (m_bModify)
	{
		GetDlgItem(IDC_EDIT_UNITID)->EnableWindow(FALSE);
		m_nUnitID = m_unitInfo.nUnitID;
		m_strUnitName = m_unitInfo.UnitName;
		m_nRank = m_unitInfo.nRank;
//		m_strManager = m_unitInfo.ManagerID;
	}

	UpdateData(FALSE);
	
	return TRUE;  
}

void CUnitInfoDlg::SetModifyFlag(bool bModify)
{
	m_bModify = bModify;
}
void CUnitInfoDlg::SetSuperUnit(sUnitInfo* pSuperUnit)
{
	if (pSuperUnit != NULL)
	{
		m_pSuperUnit = pSuperUnit;
	}
}
void CUnitInfoDlg::SetUnitInfo(sUnitInfo* pUnitInfo)
{
	if (pUnitInfo!=NULL)
	{
		strncpy_s(m_unitInfo.UnitName,pUnitInfo->UnitName,LENGTH_20);
		m_unitInfo.nUnitID = pUnitInfo->nUnitID;
		strncpy_s(m_unitInfo.ManagerID,pUnitInfo->ManagerID,LENGTH_20);
		m_unitInfo.nRank = pUnitInfo->nRank;
		m_unitInfo.nSuperID = pUnitInfo->nSuperID;
	}
}
void CUnitInfoDlg::GetUnitInfo(sUnitInfo* pUnitInfo)
{
	if (pUnitInfo!=NULL)
	{
		strncpy_s(pUnitInfo->UnitName,m_unitInfo.UnitName,LENGTH_20);
		pUnitInfo->nUnitID = m_unitInfo.nUnitID;
		strncpy_s(pUnitInfo->ManagerID,m_unitInfo.ManagerID,LENGTH_20);
		pUnitInfo->nRank = m_unitInfo.nRank;
		pUnitInfo->nSuperID = m_unitInfo.nSuperID;
	}
}


// CUnitInfoDlg 消息处理程序
void CUnitInfoDlg::OnBnClickedOk()
{
	UpdateData();

	strncpy_s(m_unitInfo.UnitName,m_strUnitName.GetBuffer(),LENGTH_20);
	m_unitInfo.nUnitID = m_nUnitID;
	m_unitInfo.nRank = m_nRank;
	
	if (m_pSuperUnit != NULL)
	{
		m_unitInfo.nSuperID = m_pSuperUnit->nUnitID;
	}
	else
	{
		m_unitInfo.nSuperID = -1;//一级单位
	}

	OnOK();
}
