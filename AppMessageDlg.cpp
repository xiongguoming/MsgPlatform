// AppMessageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "AppMessageDlg.h"


// CAppMessageDlg 对话框

IMPLEMENT_DYNAMIC(CAppMessageDlg, CDialog)

CAppMessageDlg::CAppMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppMessageDlg::IDD, pParent)
	, m_strTitle(_T(""))
	, m_strContent(_T(""))
{

}

CAppMessageDlg::~CAppMessageDlg()
{
}

void CAppMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
}


BEGIN_MESSAGE_MAP(CAppMessageDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAppMessageDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAppMessageDlg 消息处理程序

void CAppMessageDlg::OnBnClickedOk()
{
	UpdateData();

	OnOK();
}

//获取APP消息
void CAppMessageDlg::GetAppMessage(CString& title,CString& content)
{	
	title = m_strTitle;
	content = m_strContent;
}


