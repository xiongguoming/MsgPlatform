#pragma once
#include "mybutton.h"


// CLoadDlg 对话框

class CLoadDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadDlg)

public:
	CLoadDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadDlg();

// 对话框数据
	enum { IDD = IDD_DLG_LOAD };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	CMyButton m_btnOK;
	CMyButton m_btnCancel;
	CString m_strUserName;
	CString m_strPassword;
};
