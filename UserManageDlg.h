#pragma once
#include "mybutton.h"
#include "afxcmn.h"


// CUserManageDlg 对话框
class CUserManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserManageDlg)

public:
	CUserManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserManageDlg();

// 对话框数据
	enum { IDD = IDD_DLG_YHGL };

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedBtnAddunit();
	afx_msg void OnBnClickedBtnAdduser();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnDelunit();
	afx_msg void OnBnClickedBtnModifyunit();
	afx_msg void OnTvnSelchangedTreeUnit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDeluser();
	afx_msg void OnBnClickedBtnModifyuser();
	void InitUserInfo();
	void InitUnitTree();
	void AddtoNode(HTREEITEM hParent);
	bool RemoveSubUnit(sUnitInfo* pSupUnit);
	void InitButtons();

protected:
	CBCGPButton m_btnAddUnit;
	CBCGPButton m_btnModifyUnit;
	CBCGPButton m_btnDelUnit;
	CBCGPButton m_btnAddUser;
	CBCGPButton m_btnModifyUser;
	CBCGPButton m_btnDelUser;
	CTreeCtrl m_treeUnit;
	PlatformDB* m_pDB;
	vector<sUnitInfo> m_totalUnits;
	vector<sUserInfo> m_totalUsers;
	HTREEITEM m_hRoot;
	CImageList m_ImageList;
	CListCtrl m_listUser;	
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
