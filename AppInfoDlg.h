#pragma once
#include "afxwin.h"


// CAppInfoDlg �Ի���

class CAppInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CAppInfoDlg)

public:
	CAppInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAppInfoDlg();

// �Ի�������
	enum { IDD = IDD_DLG_APPINFO };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
public:
	void SetAppInfo(sAppInfo* pAppinfo);
	sAppInfo GetAppInfo();
private:
	sAppInfo m_appinfo;	
	CString m_strAppName;
	CString m_strPassword;
	CComboBox m_cmbAppType;
	CString m_strIconPath;
	CString m_strRemark;
	CString m_strAppId;
	CString m_strPhone;
};
