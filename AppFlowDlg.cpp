// AppFlowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "AppFlowDlg.h"


// CAppFlowDlg 对话框

IMPLEMENT_DYNAMIC(CAppFlowDlg, CDialog)

CAppFlowDlg::CAppFlowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppFlowDlg::IDD, pParent)
	, m_strItemName(_T(""))
	, m_strFlowName(_T(""))
	, m_nOrder(0)
	, m_strPrompt(_T(""))
	, m_bIsAutoExecuted(FALSE)
	, m_bIsSendMsg(FALSE)
	, m_strMessage(_T(""))
	, m_bMsgPlatform(FALSE)
	, m_bEmail(FALSE)
	, m_bSMS(FALSE)
	, m_bWeiXin(FALSE)
{
	m_pFlow = NULL;
	m_pItem = NULL;
}

CAppFlowDlg::~CAppFlowDlg()
{
	if(m_pFlow!=NULL)
	{	
		delete m_pFlow;
		m_pFlow = NULL;
	}

	if(m_pItem!=NULL)
	{	
		delete m_pItem;
		m_pItem = NULL;
	}	
}

void CAppFlowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ITEMNAME, m_strItemName);
	DDX_Text(pDX, IDC_EDIT_FLOWNAME, m_strFlowName);
	DDX_Text(pDX, IDC_EDIT_ORDER, m_nOrder);
	DDX_Text(pDX, IDC_EDIT_PROMPT, m_strPrompt);
	DDX_Radio(pDX, IDC_RDO_AUTOEXECUTE1, m_bIsAutoExecuted);
	DDX_Radio(pDX, IDC_RDO_SENDMSG1, m_bIsSendMsg);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_strMessage);
	DDX_Check(pDX, IDC_CHK_SENDTYPE1, m_bMsgPlatform);
	DDX_Check(pDX, IDC_CHK_SENDTYPE2, m_bEmail);
	DDX_Check(pDX, IDC_CHK_SENDTYPE3, m_bSMS);
	DDX_Check(pDX, IDC_CHK_SENDTYPE4, m_bWeiXin);
}


BEGIN_MESSAGE_MAP(CAppFlowDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAppFlowDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAppFlowDlg 消息处理程序
BOOL CAppFlowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_pItem == NULL)
	{
		MessageBox("错误：未选择应用事项","流程对话框",MB_ICONERROR|MB_OK);
		return FALSE;
	}
	
	CEdit* pFlowName = (CEdit*)GetDlgItem(IDC_EDIT_FLOWNAME);
	pFlowName->SetLimitText(50);
	
	CEdit* pPrompt = (CEdit*)GetDlgItem(IDC_EDIT_PROMPT);
	pPrompt->SetLimitText(100);

	CEdit* pMessage = (CEdit*)GetDlgItem(IDC_EDIT_MESSAGE);
	pMessage->SetLimitText(100);

	m_strItemName = m_pItem->ItemName;

	//修改
	if(m_pFlow != NULL)
	{
		m_strFlowName = m_pFlow->FlowName;
		m_nOrder = m_pFlow->nOrder;
		m_strPrompt = m_pFlow->Prompt;
		m_bIsAutoExecuted = !m_pFlow->IsAutoExecute;
		m_bIsSendMsg = !m_pFlow->IsSendMessage;
		m_strMessage = m_pFlow->Message;

		m_bMsgPlatform = m_pFlow->SendType[0]=='0' ? FALSE:TRUE;
		m_bEmail = m_pFlow->SendType[1]=='0' ? FALSE:TRUE;
		m_bSMS = m_pFlow->SendType[2]=='0' ? FALSE:TRUE;
		m_bWeiXin = m_pFlow->SendType[3]=='0' ? FALSE:TRUE;
	}

	UpdateData(FALSE);

	return TRUE; 
}



void CAppFlowDlg::SetAppItem(sAppItem* pItem)
{
	if (pItem == NULL)
	{
		return;
	}
	if (m_pItem == NULL)
	{
		m_pItem = new sAppItem;
	}
	*m_pItem = *pItem;
}

void CAppFlowDlg::SetAppFlow(sAppFlow* pFlow)
{
	if (pFlow == NULL)
	{
		return;
	}
	if (m_pFlow == NULL)
	{
		m_pFlow = new sAppFlow;
	}
	*m_pFlow = *pFlow;
}

void CAppFlowDlg::GetAppFlow(sAppFlow* pFlow)
{
	if (pFlow==NULL || m_pFlow==NULL)
	{
		return;
	}
	*pFlow = *m_pFlow;
}

void CAppFlowDlg::OnBnClickedOk()
{
	UpdateData();

	if (m_pFlow == NULL)
	{
		m_pFlow = new sAppFlow;
	}

	m_pFlow->nItemId = m_pItem->nItemId;

	strcpy_s(m_pFlow->FlowName,(LPCTSTR)m_strFlowName);
	
	m_pFlow->nOrder = m_nOrder;
	
	strcpy_s(m_pFlow->Prompt,(LPCTSTR)m_strPrompt);

	m_pFlow->IsAutoExecute = !m_bIsAutoExecuted;
	m_pFlow->IsSendMessage = !m_bIsSendMsg;

	strcpy_s(m_pFlow->Message,(LPCTSTR)m_strMessage);

	m_pFlow->SendType[0] = m_bMsgPlatform ? '1':'0';
	m_pFlow->SendType[1] = m_bEmail ? '1':'0';
	m_pFlow->SendType[2] = m_bSMS ? '1':'0';
	m_pFlow->SendType[3] = m_bWeiXin ? '1':'0';

	OnOK();
}
