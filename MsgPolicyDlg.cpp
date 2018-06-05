// MsgPolicyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "MsgPolicyDlg.h"


// CMsgPolicyDlg 对话框

IMPLEMENT_DYNAMIC(CMsgPolicyDlg, CDialog)

CMsgPolicyDlg::CMsgPolicyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgPolicyDlg::IDD, pParent)
	, m_strKeyWord(_T(""))
	, m_nAppLimit(0)
	, m_nUserLimit(0)
{
	m_pDB = ((CMSG_PLATFORMApp*)AfxGetApp())->m_pDB;
}

CMsgPolicyDlg::~CMsgPolicyDlg()
{
	
}

void CMsgPolicyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADDKEYW, m_btnAddKeyword);
	DDX_Control(pDX, IDC_BTN_DELKEYW, m_btnDelKeyword);
	DDX_Control(pDX, IDC_BTN_MODIFY, m_btnModify);
	DDX_Text(pDX, IDC_EDIT_KEYWORD, m_strKeyWord);
	DDX_Control(pDX, IDC_LIST_KEYWORD, m_listKeyWords);
	DDX_Control(pDX, IDC_CMD_INITSCORE, m_cmbInitScore);
	DDX_Control(pDX, IDC_CMB_SUBSCORE, m_cmbSubScore);
	DDX_Text(pDX, IDC_EDIT_APPLIMIT, m_nAppLimit);
	DDV_MinMaxUInt(pDX, m_nAppLimit, 0, 999);
	DDX_Text(pDX, IDC_EDIT_USERLIMIT, m_nUserLimit);
	DDV_MinMaxUInt(pDX, m_nUserLimit, 0, 999);
}


BEGIN_MESSAGE_MAP(CMsgPolicyDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CMsgPolicyDlg::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_ADDKEYW, &CMsgPolicyDlg::OnBnClickedBtnAddkeyw)
	ON_BN_CLICKED(IDC_BTN_DELKEYW, &CMsgPolicyDlg::OnBnClickedBtnDelkeyw)
END_MESSAGE_MAP()


// CMsgPolicyDlg 消息处理程序

void CMsgPolicyDlg::OnPaint()
{
	CPaintDC dc(this); 
	CRect rect;
	CBitmap bmp;
	CDC memdc;
	CDC* pDC = GetDC();
	memdc.CreateCompatibleDC(pDC);
	bmp.LoadBitmap(IDB_HOMEPAGE_POLICY);
	memdc.SelectObject(&bmp);

	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
	bmp.DeleteObject();
	memdc.DeleteDC();
}

BOOL CMsgPolicyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitButtons();

	m_cmbInitScore.InsertString(0,"36");
	m_cmbInitScore.InsertString(1,"24");
	m_cmbInitScore.InsertString(2,"12");
	m_cmbInitScore.SetCurSel(1);

	m_cmbSubScore.InsertString(0,"6");
	m_cmbSubScore.InsertString(1,"3");
	m_cmbSubScore.InsertString(2,"2");
	m_cmbSubScore.InsertString(3,"1");
	m_cmbSubScore.SetCurSel(0);

	ReadPolicy();

	vector<CString> Keywords;
	m_pDB->ReadAllKeywords(Keywords);

	for(unsigned int nIndex=0; nIndex<Keywords.size(); nIndex++)
	{
		m_listKeyWords.InsertString(nIndex,Keywords[nIndex]);
	}
	Keywords.clear();

	return TRUE;
}

//读取消息策略
void CMsgPolicyDlg::ReadPolicy()
{
	m_pDB->ReadMsgPolicy(&m_policy);

	CButton* pChk = NULL;
	
	pChk = (CButton*)GetDlgItem(IDC_CHK_SYSMSG1);
	if (pChk!=NULL && m_policy.SysMsgPolicy[0]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_SYSMSG2);
	if (pChk!=NULL && m_policy.SysMsgPolicy[1]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_SYSMSG3);
	if (pChk!=NULL && m_policy.SysMsgPolicy[2]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_SYSMSG4);
	if (pChk!=NULL && m_policy.SysMsgPolicy[3]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_APPMSG1);
	if (pChk!=NULL && m_policy.AppMsgPolicy[0]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_APPMSG2);
	if (pChk!=NULL && m_policy.AppMsgPolicy[1]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_APPMSG3);
	if (pChk!=NULL && m_policy.AppMsgPolicy[2]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_APPMSG4);
	if (pChk!=NULL && m_policy.AppMsgPolicy[3]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_USERMSG1);
	if (pChk!=NULL && m_policy.UserMsgPolicy[0]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_USERMSG2);
	if (pChk!=NULL && m_policy.UserMsgPolicy[1]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_USERMSG3);
	if (pChk!=NULL && m_policy.UserMsgPolicy[2]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_USERMSG4);
	if (pChk!=NULL && m_policy.UserMsgPolicy[3]=='1')
	{
		pChk->SetCheck(TRUE);
	}
	else
	{
		pChk->SetCheck(FALSE);
	}

	m_nAppLimit = m_policy.nAppMsgLimited;
	m_nUserLimit = m_policy.nUserMsgLimited;
	
	CString str,cursel;
	str.Format("%d",m_policy.nInitScore);

	for (int nIndex=0; nIndex<m_cmbInitScore.GetCount(); nIndex++)
	{
		m_cmbInitScore.GetLBText(nIndex,cursel);
		if (str.Compare(cursel) == 0)
		{
			m_cmbInitScore.SetCurSel(nIndex);
			break;
		}
	}

	str.Format("%d",m_policy.nSubScore);
	for (int nIndex=0; nIndex<m_cmbSubScore.GetCount(); nIndex++)
	{
		m_cmbSubScore.GetLBText(nIndex,cursel);
		if (str.Compare(cursel) == 0)
		{
			m_cmbSubScore.SetCurSel(nIndex);
			break;
		}
	}
	
	UpdateData(FALSE);
}
void CMsgPolicyDlg::InitButtons()
{
	m_btnModify.SetWindowText (_T("修改消息策略"));
	m_btnModify.SetFaceColor(RGB(135,206,235));
	m_btnModify.Invalidate ();
	m_btnModify.SetMouseCursorHand ();

	m_btnAddKeyword.SetWindowText (_T("+"));
	m_btnAddKeyword.SetFaceColor(RGB(135,206,235));
	m_btnAddKeyword.Invalidate ();
	m_btnAddKeyword.SetMouseCursorHand ();

	m_btnDelKeyword.SetWindowText (_T("-"));
	m_btnDelKeyword.SetFaceColor(RGB(135,206,235));
	m_btnDelKeyword.Invalidate ();
	m_btnDelKeyword.SetMouseCursorHand ();
}

HBRUSH CMsgPolicyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CMsgPolicyDlg::OnBnClickedBtnModify()
{
	UpdateData();
	CButton* pChk = NULL;
	
	memset(&m_policy,0,sizeof(sDispatchPolicy));
	strcpy_s(m_policy.SysMsgPolicy,"0000");
	strcpy_s(m_policy.AppMsgPolicy,"0000");
	strcpy_s(m_policy.UserMsgPolicy,"0000");
	//系统消息策略
	pChk = (CButton*)GetDlgItem(IDC_CHK_SYSMSG1);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.SysMsgPolicy[0] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_SYSMSG2);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.SysMsgPolicy[1] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_SYSMSG3);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.SysMsgPolicy[2] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_SYSMSG4);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.SysMsgPolicy[3] = '1';
	}
	//应用消息策略
	pChk = (CButton*)GetDlgItem(IDC_CHK_APPMSG1);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.AppMsgPolicy[0] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_APPMSG2);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.AppMsgPolicy[1] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_APPMSG3);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.AppMsgPolicy[2] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_APPMSG4);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.AppMsgPolicy[3] = '1';
	}
	//用户消息策略
	pChk = (CButton*)GetDlgItem(IDC_CHK_USERMSG1);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.UserMsgPolicy[0] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_USERMSG2);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.UserMsgPolicy[1] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_USERMSG3);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.UserMsgPolicy[2] = '1';
	}

	pChk = (CButton*)GetDlgItem(IDC_CHK_USERMSG4);
	if (pChk!=NULL && pChk->GetCheck())
	{
		m_policy.UserMsgPolicy[3] = '1';
	}

	m_policy.nAppMsgLimited = m_nAppLimit;
	m_policy.nUserMsgLimited = m_nUserLimit;
	
	CString str;
	m_cmbInitScore.GetWindowText(str);
	m_policy.nInitScore = atoi(str.GetBuffer());
	
	m_cmbSubScore.GetWindowText(str);
	m_policy.nSubScore = atoi(str.GetBuffer());

	if (m_pDB->SaveMsgPolicy(&m_policy))
	{
		AfxMessageBox("保存成功！");
	}
}


void CMsgPolicyDlg::OnBnClickedBtnAddkeyw()
{
	UpdateData();
	int nCount = m_listKeyWords.GetCount();
	if (m_pDB->SaveKeyword(m_strKeyWord))
	{
		m_listKeyWords.InsertString(nCount,m_strKeyWord);
	}
	else
	{
		AfxMessageBox("添加失败！");
	}
}

void CMsgPolicyDlg::OnBnClickedBtnDelkeyw()
{
	CString keyword;
	int nCurSel = m_listKeyWords.GetCurSel();
	
	if (nCurSel>=0)
	{
		m_listKeyWords.GetText(nCurSel,keyword);

		if (m_pDB->DeleteKeyword(keyword))
		{
			m_listKeyWords.DeleteString(nCurSel);
		}
		else
		{
			AfxMessageBox("删除失败！");
		}

	}
	
}
