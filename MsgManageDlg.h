#pragma once
#include "afxcmn.h"
#include "MsgGridCtrl.h"
#include "bcgpmenubutton.h"
#include "bcgpbutton.h"
#include "mybutton.h"


// CMsgManageDlg 对话框

class CMsgManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CMsgManageDlg)

public:
	CMsgManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMsgManageDlg();

// 对话框数据
	enum { IDD = IDD_DLG_XXGL };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnView();
	afx_msg void OnBnClickedBtnMsgdispatch();
	afx_msg void OnBnClickedBtnMsghistory();
	afx_msg void OnBnClickedBtnDelete();
	DECLARE_MESSAGE_MAP()
	
	void InitButtons();
	void ReadAllMessage();
	void SwitchMsgType(int nType);
	sTextMessage* QueryMsg(int nMsgId,int nMsgType,int nType);
public:
	CBCGPTabWnd	m_wndTabs;
	CMsgGridCtrl m_listUserMsg;
	CMsgGridCtrl m_listAppMsg;
	CMsgGridCtrl m_listSysMsg;

	CBCGPButton m_btnView;
	CBCGPButton m_btnDelete;
	CBCGPButton m_btnHistory;
	CBCGPButton m_btnDispatch;

	sTextMessage* m_pHisMsgArray;
	int m_nHisMsgNum;
	sTextMessage* m_pSysMsgArray;
	int m_nSysMsgNum;
	sTextMessage* m_pAppMsgArray;
	int m_nAppMsgNum;
	sTextMessage* m_pUserMsgArray;
	int m_nUserMsgNum;

	PlatformDB* m_pDB;
	int m_nMsgType;

};
