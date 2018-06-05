#pragma once
#include "mybutton.h"


// CLoadDlg �Ի���

class CLoadDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadDlg)

public:
	CLoadDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoadDlg();

// �Ի�������
	enum { IDD = IDD_DLG_LOAD };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	CMyButton m_btnOK;
	CMyButton m_btnCancel;
	CString m_strUserName;
	CString m_strPassword;
};
