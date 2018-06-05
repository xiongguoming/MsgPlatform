#pragma once


// CMsgGridCtrl

class CMsgGridCtrl : public CBCGPReportCtrl
{
	DECLARE_DYNAMIC(CMsgGridCtrl)

public:
	CMsgGridCtrl();
	virtual ~CMsgGridCtrl();

public:
	enum IMPORTANCE
	{
		IMPORTANCE_NORMAL,
		IMPORTANCE_HIGH,
		IMPORTANCE_LOW
	};

	void AddMessage(int nRow,sTextMessage msg);
	void RemoveSelectMsg();
	void GetSelectMsg(int& nMsgId);

	int standard_to_stamp(char *str_time);
	sDateTime stamp_to_standard(long stampTime);
	

protected:
	DECLARE_MESSAGE_MAP()
	//{{AFX_MSG(CReportGridCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG


private:
	CImageList      m_Images;
	CBCGPGridRow*   m_pSelRow; 
};


