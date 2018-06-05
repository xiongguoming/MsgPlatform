// AppItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "AppItemDlg.h"


// CAppItemDlg 对话框

IMPLEMENT_DYNAMIC(CAppItemDlg, CDialog)

CAppItemDlg::CAppItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppItemDlg::IDD, pParent)
	, m_strAppName(_T(""))
	, m_strItemName(_T(""))
	, m_strRemark(_T(""))
{
	m_pApp = NULL;
	m_pItem = NULL;
}

CAppItemDlg::~CAppItemDlg()
{
	if (m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}

	if (m_pApp != NULL)
	{
		delete m_pApp;
		m_pApp = NULL;
	}
}

void CAppItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_APPNAME, m_strAppName);
	DDX_Text(pDX, IDC_EDIT_ITEMNAME, m_strItemName);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_strRemark);
}


BEGIN_MESSAGE_MAP(CAppItemDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAppItemDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAppItemDlg 消息处理程序
void CAppItemDlg::SetAppInfo(sAppInfo* pApp)
{	
	if (pApp == NULL)
	{
		return;
	}
	if (m_pApp == NULL)
	{
		m_pApp = new sAppInfo;
	}
	*m_pApp = *pApp;
}

void CAppItemDlg::SetAppItem(sAppItem* pItem)
{
	if (pItem == NULL)
	{
		return;
	}
	if (pItem == NULL)
	{
		m_pItem = new sAppItem;
	}
	*m_pItem = *pItem;
}

BOOL CAppItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_pApp == NULL)
	{
		MessageBox("错误：未选择应用","流程对话框",MB_ICONERROR|MB_OK);
		return FALSE;
	}

	CEdit* pEditName = (CEdit*)GetDlgItem(IDC_EDIT_ITEMNAME);
	pEditName->SetLimitText(20);
	CEdit* pRemark = (CEdit*)GetDlgItem(IDC_EDIT_REMARK);
	pRemark->SetLimitText(100);

	m_strAppName = m_pApp->AppName;
	
	//修改
	if(m_pItem != NULL)
	{
		m_strItemName = m_pItem->ItemName;
		m_strRemark = m_pItem->Remark;
	}
	
	UpdateData(FALSE);

	return TRUE;
}
void CAppItemDlg::GetAppItem(sAppItem* pItem)
{
	if(m_pItem==NULL || pItem==NULL)
	{
		return;
	}

	*pItem = *m_pItem;
}
void CAppItemDlg::OnBnClickedOk()
{
	UpdateData();
	if(m_pItem == NULL)
	{
		m_pItem = new sAppItem;
	}

	strcpy_s(m_pItem->AppID,m_pApp->AppID);
	strcpy_s(m_pItem->ItemName,(LPCTSTR)m_strItemName);
	strcpy_s(m_pItem->Remark,(LPCTSTR)m_strRemark);

	OnOK();
}
