#pragma once


// CAppMessageDlg �Ի���

class CAppMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CAppMessageDlg)

public:
	CAppMessageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAppMessageDlg();

// �Ի�������
	enum { IDD = IDD_DLG_APPMESSAGE };
	void GetAppMessage(CString& title,CString& content);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
private:
	CString m_strTitle;
	CString m_strContent;
};
