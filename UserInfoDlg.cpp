// UserInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "UserInfoDlg.h"


// CUserInfoDlg 对话框

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialog)

CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
	, m_strUserID(_T(""))
	, m_strPassword(_T(""))
	, m_strName(_T(""))
	, m_nSex(0)
	, m_strTelphone(_T(""))
	, m_strEmail(_T(""))
	, m_strWeixin(_T(""))
{
	m_bModify = false;
}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Radio(pDX, IDC_RDO_SEX_1, m_nSex);
	DDX_Control(pDX, IDC_CMB_RIGHT, m_cmbRight);
	DDX_Text(pDX, IDC_EDIT_TELEPHONE, m_strTelphone);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_strEmail);
	DDX_Text(pDX, IDC_EDIT_WEIXIN, m_strWeixin);
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CUserInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CUserInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cmbRight.InsertString(0,"普通用户");
	m_cmbRight.InsertString(1,"单位管理员");
	m_cmbRight.InsertString(2,"系统管理员");
	m_cmbRight.SetCurSel(0);
	
	if (m_bModify)
	{
		GetDlgItem(IDC_EDIT_USERID)->EnableWindow(FALSE);
		m_strUserID = m_userInfo.UserID;
		m_strPassword = m_userInfo.PassWord;
		m_strName = m_userInfo.UserName;
		m_nSex = m_userInfo.nSex;
		m_strTelphone = m_userInfo.Telephone;
		m_strEmail = m_userInfo.Email;
		m_strWeixin = m_userInfo.Weixin;
		m_cmbRight.SetCurSel(m_userInfo.nRight);
		UpdateData(FALSE);
	}
	
	return TRUE;
}
void CUserInfoDlg::SetModifyFlag(bool bModify)
{
	m_bModify = bModify;
}
void CUserInfoDlg::SetUserInfo(sUserInfo* pUserInfo)
{
	if (pUserInfo!=NULL)
	{
		strncpy_s(m_userInfo.UserID,pUserInfo->UserID,LENGTH_20);
		strncpy_s(m_userInfo.PassWord,pUserInfo->PassWord,LENGTH_20);
		strncpy_s(m_userInfo.UserName,pUserInfo->UserName,LENGTH_20);

		m_userInfo.bOnlineStatus = pUserInfo->bOnlineStatus;
		m_userInfo.nSex = pUserInfo->nSex;
		m_userInfo.nRight = pUserInfo->nRight;

		strncpy_s(m_userInfo.Telephone,pUserInfo->Telephone,LENGTH_20);
		strncpy_s(m_userInfo.Email,pUserInfo->Email,LENGTH_20);
		strncpy_s(m_userInfo.Weixin,pUserInfo->Weixin,LENGTH_20);
	}
}
void CUserInfoDlg::GetUserInfo(sUserInfo* pUserInfo)
{
	if (pUserInfo!=NULL)
	{
		strncpy_s(pUserInfo->UserID,m_userInfo.UserID,LENGTH_20);
		strncpy_s(pUserInfo->PassWord,m_userInfo.PassWord,LENGTH_20);
		strncpy_s(pUserInfo->UserName,m_userInfo.UserName,LENGTH_20);
		
		pUserInfo->bOnlineStatus = m_userInfo.bOnlineStatus;
		pUserInfo->nSex = m_userInfo.nSex;
		pUserInfo->nRight = m_userInfo.nRight;

		strncpy_s(m_userInfo.Telephone,pUserInfo->Telephone,LENGTH_20);
		strncpy_s(m_userInfo.Email,pUserInfo->Email,LENGTH_20);
		strncpy_s(m_userInfo.Weixin,pUserInfo->Weixin,LENGTH_20);
	}
}

//添加用户或修改用户
void CUserInfoDlg::OnBnClickedOk()
{
	UpdateData();
	
	strncpy_s(m_userInfo.UserID,m_strUserID.GetBuffer(),LENGTH_20);
	strncpy_s(m_userInfo.PassWord,m_strPassword.GetBuffer(),LENGTH_20);
	strncpy_s(m_userInfo.UserName,m_strName.GetBuffer(),LENGTH_20);
	strncpy_s(m_userInfo.Telephone,m_strTelphone.GetBuffer(),LENGTH_20);
	strncpy_s(m_userInfo.Email,m_strEmail.GetBuffer(),LENGTH_20);
	strncpy_s(m_userInfo.Weixin,m_strWeixin.GetBuffer(),LENGTH_20);
	
	m_userInfo.nSex = (SEX)m_nSex;
	switch(m_cmbRight.GetCurSel())
	{
	case 0:
		m_userInfo.nRight = NORMAL_USER;
		break;
	case 1:
		m_userInfo.nRight = UNIT_MANGE;
		break;
	case 2:
		m_userInfo.nRight = SYS_MANAGE;
		break;
	default:
		m_userInfo.nRight = NORMAL_USER;
		break;
	}
	OnOK();
}