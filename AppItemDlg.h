#pragma once


// CAppItemDlg 对话框

class CAppItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CAppItemDlg)

public:
	CAppItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAppItemDlg();

// 对话框数据
	enum { IDD = IDD_DLG_APPITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:	
	void SetAppInfo(sAppInfo* pApp);
	void SetAppItem(sAppItem* pApp);	
	void GetAppItem(sAppItem* pItem);
private:
	sAppInfo* m_pApp;
	sAppItem* m_pItem;

	CString m_strAppName;
	CString m_strItemName;
	CString m_strRemark;
	
};
