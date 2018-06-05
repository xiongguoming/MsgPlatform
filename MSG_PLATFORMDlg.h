// MSG_PLATFORMDlg.h : header file
//

#include "mybutton.h"
#if !defined(AFX_MSG_PLATFORMDLG_H__31D4E124_DAE1_4DB4_92A4_63EFB698DACA__INCLUDED_)
#define AFX_MSG_PLATFORMDLG_H__31D4E124_DAE1_4DB4_92A4_63EFB698DACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MsgManageDlg.h"
#include "MsgPolicyDlg.h"
#include "AppManageDlg.h"
#include "UserManageDlg.h"
#include "ExternalAppDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CMSG_PLATFORMDlg dialog

class CMSG_PLATFORMDlg : public CDialog
{
// Construction
public:
	CMSG_PLATFORMDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMSG_PLATFORMDlg)
	enum { IDD = IDD_DLG_PLATFORM};
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSG_PLATFORMDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CMSG_PLATFORMDlg)
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedBtnXxgl();
	afx_msg void OnBnClickedBtnYygl();
	afx_msg void OnBnClickedBtnYhgl();
	afx_msg void OnBnClickedBtnXxcl();
	afx_msg void OnBnClickedBtnWbyy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void InitBtnTool();
	void AdjustWindows(bool bInitFlag=false);
private:
	CBCGPButton m_btnXXGL;
	CBCGPButton m_btnYYGL;
	CBCGPButton m_btnYHGL;
	CBCGPButton m_btnXXCL;
	CBCGPButton m_btnWBYY;
	CMsgManageDlg m_msgDlg;
	CAppManageDlg m_appDlg;
	CUserManageDlg m_userDlg;
	CMsgPolicyDlg m_policyDlg;
	CExternalAppDlg m_extAppDlg;
	CBrush m_bkBrush;
	int m_nCurModel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSG_PLATFORMDLG_H__31D4E124_DAE1_4DB4_92A4_63EFB698DACA__INCLUDED_)
