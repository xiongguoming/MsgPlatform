#pragma once
#include "afxwin.h"


// CUserInfoDlg �Ի���

class CUserInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserInfoDlg();

// �Ի�������
	enum { IDD = IDD_DLG_USERINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public: 
	void SetUserInfo(sUserInfo* pUserInfo);
	void GetUserInfo(sUserInfo* pUserInfo);
	void SetModifyFlag(bool bModify=true);
public:
	CComboBox m_cmbRight;
	sUserInfo m_userInfo;
	CString m_strUserID;
	CString m_strPassword;
	CString m_strName;
	int m_nSex;
	bool m_bModify;
	CString m_strTelphone;
	CString m_strEmail;
	CString m_strWeixin;
};
