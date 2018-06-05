// LoadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "LoadDlg.h"


// CLoadDlg �Ի���

IMPLEMENT_DYNAMIC(CLoadDlg, CDialog)

CLoadDlg::CLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadDlg::IDD, pParent)
	, m_strUserName(_T("admin"))
	, m_strPassword(_T("123456"))
{

}

CLoadDlg::~CLoadDlg()
{
}

void CLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CLoadDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CLoadDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoadDlg ��Ϣ�������
BOOL CLoadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnOK.LoadMyBitmap(IDB_BTN_MENU_NORMAL,IDB_BTN_MENU_FOCUS,IDB_BTN_MENU_DOWN,IDB_BTN_MENU_DISABLE);
	m_btnOK.SetCaption("��¼",RGB(255,255,255));

	m_btnCancel.LoadMyBitmap(IDB_BTN_MENU_NORMAL,IDB_BTN_MENU_FOCUS,IDB_BTN_MENU_DOWN,IDB_BTN_MENU_DISABLE);
	m_btnCancel.SetCaption("�˳�",RGB(255,255,255));

	//ShowWindow(SW_MAXIMIZE);

	return TRUE; 
}
void CLoadDlg::OnPaint()
{
	CPaintDC dc(this); 
	
	CBitmap bmp;
	CDC memdc;
	CDC* pDC = GetDC();
	memdc.CreateCompatibleDC(pDC);
	bmp.LoadBitmap(IDB_BMP_LOAD);
	memdc.SelectObject(&bmp);

	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
	bmp.DeleteObject();
	memdc.DeleteDC();
}

void CLoadDlg::OnBnClickedOk()
{
	UpdateData();
	if (m_strUserName.Compare("admin")!=0||
		m_strPassword.Compare("123456")!=0)
	{
		MessageBox("�˺Ż�����������������룡","����Ա��¼",MB_ICONERROR);
		m_strUserName = "";
		m_strPassword = "";
		UpdateData(FALSE);	
	}
	else
	{
		OnOK();
	}
}
