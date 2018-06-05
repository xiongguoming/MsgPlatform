#pragma once
#include "afxwin.h"
#include "resource.h"

class CMyButton :
	public CButton
{
public:
	CMyButton(void);
public:
	~CMyButton(void);
public:
	
	void EnableSelectAlways(bool bEnable);
	void SetCaption(LPCTSTR szText,COLORREF color=RGB(0,0,0));
	void LoadMyBitmap(UINT nIDNormal,UINT nIDFocus=0,UINT nIDSelected=0,UINT nIDDisabled=0);
	void SizeToPicture();
	bool IsSelectAlways();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	DECLARE_MESSAGE_MAP()
private:
	CString m_strText;	//∞¥≈•±ÍÃ‚
	UINT m_nIDNormal;
	UINT m_nIDFocus;
	UINT m_nIDSelected;
	UINT m_nIDDisabled;
	COLORREF m_TextColor;
	bool m_bAlwaysSelect;
	CFont m_Font;	
};
