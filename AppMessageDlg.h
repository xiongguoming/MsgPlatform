#pragma once


// CAppMessageDlg 对话框

class CAppMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CAppMessageDlg)

public:
	CAppMessageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAppMessageDlg();

// 对话框数据
	enum { IDD = IDD_DLG_APPMESSAGE };
	void GetAppMessage(CString& title,CString& content);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
private:
	CString m_strTitle;
	CString m_strContent;
};
