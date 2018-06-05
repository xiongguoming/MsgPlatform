#pragma once
#include "bcgpbutton.h"
#include "afxcmn.h"


// CExternalAppDlg 对话框

class CExternalAppDlg : public CDialog
{
	DECLARE_DYNAMIC(CExternalAppDlg)

public:
	CExternalAppDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExternalAppDlg();

// 对话框数据
	enum { IDD = IDD_DLG_WBYY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnMnsendmsg();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnAdditem();
	afx_msg void OnLvnItemchangedListExtapp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDelitem();
	afx_msg void OnBnClickedBtnAddflow();
	afx_msg void OnLvnItemchangedListFlow(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDelflow();
	void InitButtons();
	void InitAppData();

	void InsertFlowList(int nCount,sAppFlow* pFlowInfo);
protected:
	CListCtrl m_listApps;
	CListCtrl m_listItems;
	CListCtrl m_listFlows;
	CBCGPButton m_btnSendAppMsg;
	CBCGPButton m_btnAddItem;
	CBCGPButton m_btnDelItem;
	CBCGPButton m_btnAddFlow;
	CBCGPButton m_btnDelFlow;
	PlatformDB* m_pDB;
	CImageList m_ImageList;
	CImageList m_ImageList2;
	CFont m_font;

	sAppInfo* m_pAppArray;
	int m_nAppNum;
	//动态队列
	vector<sAppItem> m_ItemArray;
	vector<sAppFlow> m_FlowArray;
};
