#pragma once


// CAppFlowDlg 对话框

class CAppFlowDlg : public CDialog
{
	DECLARE_DYNAMIC(CAppFlowDlg)

public:
	CAppFlowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAppFlowDlg();

// 对话框数据
	enum { IDD = IDD_DLG_APPFLOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:	
	void SetAppItem(sAppItem* pItem);	
	void SetAppFlow(sAppFlow* pFlow);	
	void GetAppFlow(sAppFlow* pFlow);
	
public:
	CString m_strItemName;
	CString m_strFlowName;
	int m_nOrder;
	CString m_strPrompt;
	BOOL m_bIsAutoExecuted;
	BOOL m_bIsSendMsg;
	CString m_strMessage;
	BOOL m_bMsgPlatform;
	BOOL m_bEmail;
	BOOL m_bSMS;
	BOOL m_bWeiXin;
	sAppFlow* m_pFlow;
	sAppItem* m_pItem;
};
