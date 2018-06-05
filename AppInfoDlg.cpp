// AppInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "AppInfoDlg.h"


// CAppInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CAppInfoDlg, CDialog)

CAppInfoDlg::CAppInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppInfoDlg::IDD, pParent)
	, m_strAppName(_T(""))
	, m_strPassword(_T(""))
	, m_strIconPath(_T(""))
	, m_strRemark(_T(""))
	, m_strAppId(_T(""))
	, m_strPhone(_T(""))
{

}

CAppInfoDlg::~CAppInfoDlg()
{
}

void CAppInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_APPNAME, m_strAppName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Control(pDX, IDC_CMB_APPTYPE, m_cmbAppType);
	DDX_Text(pDX, IDC_EDIT_ICONPATH, m_strIconPath);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_strRemark);
	DDX_Text(pDX, IDC_EDIT_APPID, m_strAppId);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
}


BEGIN_MESSAGE_MAP(CAppInfoDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAppInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAppInfoDlg ��Ϣ�������
void CAppInfoDlg::SetAppInfo(sAppInfo* pAppinfo)
{
	if (pAppinfo == NULL)
	{
		return;
	}
	m_appinfo = *pAppinfo;
}
sAppInfo CAppInfoDlg::GetAppInfo()
{
	return m_appinfo;
}
void CAppInfoDlg::OnBnClickedOk()
{
	UpdateData();
	strncpy_s(m_appinfo.AppID,m_strAppId.GetBuffer(),LENGTH_20);
	strncpy_s(m_appinfo.AppName,m_strAppName.GetBuffer(),LENGTH_20);
	strncpy_s(m_appinfo.AppPassword,m_strAppName.GetBuffer(),LENGTH_20);
	strncpy_s(m_appinfo.IconPath,m_strIconPath.GetBuffer(),LENGTH_255);
	strncpy_s(m_appinfo.Phone,m_strPhone.GetBuffer(),LENGTH_20);

	m_appinfo.nAppType = m_cmbAppType.GetCurSel();
	strncpy_s(m_appinfo.Remark,m_strRemark.GetBuffer(),LENGTH_100);

	OnOK();
}

BOOL CAppInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cmbAppType.InsertString(0,"ƽ̨Ӧ��");
	m_cmbAppType.InsertString(1,"������Ӧ��(��Ϣ��)");
	m_cmbAppType.InsertString(2,"������Ӧ��(Ӧ����)");

	return TRUE;
}
