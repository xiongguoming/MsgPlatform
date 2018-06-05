#pragma once
#include "bcgpbutton.h"
#include "afxwin.h"


// CMsgPolicyDlg �Ի���

class CMsgPolicyDlg : public CDialog
{
	DECLARE_DYNAMIC(CMsgPolicyDlg)

public:
	CMsgPolicyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMsgPolicyDlg();

// �Ի�������
	enum { IDD = IDD_DLG_XXCL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAddkeyw();
	afx_msg void OnBnClickedBtnDelkeyw();
	afx_msg void OnBnClickedBtnModify();

	void InitButtons();
	void ReadPolicy();

private:
	CString m_strKeyWord;
	CListBox m_listKeyWords;
	CBCGPButton m_btnModify;
	CBCGPButton m_btnAddKeyword;
	CBCGPButton m_btnDelKeyword;
	CComboBox m_cmbInitScore;
	CComboBox m_cmbSubScore;
	sDispatchPolicy m_policy;
	UINT m_nAppLimit;
	UINT m_nUserLimit;
	PlatformDB* m_pDB;
};
