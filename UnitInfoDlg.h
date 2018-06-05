#pragma once


// CUnitInfoDlg �Ի���

class CUnitInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CUnitInfoDlg)

public:
	CUnitInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUnitInfoDlg();

// �Ի�������
	enum { IDD = IDD_DLG_UNITINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	void SetSuperUnit(sUnitInfo* pSuperUnit);
	void SetUnitInfo(sUnitInfo* pUnitInfo);
	void GetUnitInfo(sUnitInfo* pUnitInfo);
	void SetModifyFlag(bool bModify=true);
public:
	sUnitInfo m_unitInfo;
	sUnitInfo* m_pSuperUnit;
	UINT m_nUnitID;
	CString m_strUnitName;
	UINT m_nRank;
	CString m_strManager;
	CString m_strSuperUnit;
	bool m_bModify;
};
