#pragma once
#include "mybutton.h"
#include "afxwin.h"
#include "PlatformDB.h"
#include "afxcmn.h"

// CAppManageDlg �Ի���

class CAppManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CAppManageDlg)

public:
	CAppManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAppManageDlg();

// �Ի�������
	enum { IDD = IDD_DLG_YYGL };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnAudit();
	afx_msg void OnBnClickedBtnForbit();
	afx_msg void OnBnClickedBtnPass();
	afx_msg void OnNMClickAppPass(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnReflash();
	afx_msg void OnBnClickedBtnDeleteapp();

	DECLARE_MESSAGE_MAP()

	void InitAppArray();
	void InitButtons();
	void UpdateAppStatus(sAppInfo appInfo);
	void RemoveAppFromVector(sAppInfo* pApp);
private:
	CBCGPTabWnd	m_wndTabs;
	CBCGPListCtrl	m_wndListSuccess;
	CBCGPListCtrl	m_wndListAudit;
	CBCGPListCtrl	m_wndListforbid;
	PlatformDB* m_pDB;
	CImageList m_ImageList;
	vector<sAppInfo> m_appArray;
	CBCGPButton m_btnPass;
	CBCGPButton m_btnForbit;
	CBCGPButton m_btnAudit;
	CBCGPButton m_btnDelApp;
	CBCGPButton m_btnReflash;
	int m_nIsPassed;
};
