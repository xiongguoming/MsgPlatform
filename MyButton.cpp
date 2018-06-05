#include "StdAfx.h"


CMyButton::CMyButton(void)
{
	m_nIDNormal = 0;
	m_nIDFocus = 0;
	m_nIDSelected = 0;
	m_nIDDisabled = 0;
	m_TextColor = RGB(0,0,0);
	m_bAlwaysSelect = false;
}

CMyButton::~CMyButton(void)
{
}

BEGIN_MESSAGE_MAP(CMyButton, CButton)
//	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CMyButton::SetCaption(LPCTSTR szText,COLORREF color)
{
	m_strText = szText;
	m_TextColor = color;
}

void CMyButton::LoadMyBitmap(UINT nIDNormal,UINT nIDFocus,UINT nIDSelected,UINT nIDDisabled)
{
	m_nIDNormal = nIDNormal;
	m_nIDFocus = (nIDFocus==0) ? nIDNormal:nIDFocus;
	m_nIDSelected = (nIDSelected==0) ? nIDNormal:nIDSelected;
	m_nIDDisabled = (nIDDisabled==0) ? nIDNormal:nIDDisabled;
}
//按钮适应图片尺寸
void CMyButton::SizeToPicture()
{
	CRect rect;
	CBitmap bmp;
	BITMAP bmpInfo;
	
	bmp.LoadBitmap(m_nIDNormal);
	bmp.GetBitmap(&bmpInfo);
	
	if (bmpInfo.bmWidth>0 && bmpInfo.bmHeight>0)
	{
		int nTitleHeight = 0;

		if (GetParent()!=NULL)
		{
			GetParent()->GetWindowRect(&rect);
			nTitleHeight = rect.Height();
			GetParent()->GetClientRect(&rect);
			nTitleHeight -= rect.Height();
		}
		
		GetWindowRect(&rect);
		
		rect.top -= nTitleHeight;
		rect.right = rect.left+bmpInfo.bmWidth;
		rect.bottom = rect.top+bmpInfo.bmHeight;
		MoveWindow(rect);
	}
}
//实现按钮自绘的代码
void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC;
	CRect rect;
	CDC memDC;
	BITMAP bmp;
	CBitmap bmpTrans;
	int nItemState;

	rect = lpDrawItemStruct->rcItem;			 //获取按钮控件大小
	nItemState = lpDrawItemStruct->itemState;	 //获取按钮的状态
	
	int nType = 0;
	if (nItemState&ODS_FOCUS)
	{
		nType = 1;
	}
	if (nItemState&ODS_SELECTED)
	{
		nType = 2;
	}
	if (nItemState&ODS_DISABLED)
	{
		nType = 3;
	}
	switch (nType)
	{
	case 1:
		bmpTrans.LoadBitmap(m_nIDFocus);
		break;
	case 2:
		bmpTrans.LoadBitmap(m_nIDSelected);
		break;
	case 3:
		bmpTrans.LoadBitmap(m_nIDDisabled);
		break;
	default:
		if(m_bAlwaysSelect)
		{
			bmpTrans.LoadBitmap(m_nIDFocus);
		}
		else
		{
			bmpTrans.LoadBitmap(m_nIDNormal);
		}
		break;
	}

	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);	//获取指向设备环境的指针
	memDC.CreateCompatibleDC(pDC);					//创建与内存设备环境相兼容的设备环境
	CBitmap* pOld = memDC.SelectObject(&bmpTrans);	//将位图对象选入到内存设备环境中

	bmpTrans.GetBitmap(&bmp);						//获取位图信息

	//将位图从内存设备环境拷贝到显示设备环境
	if (nItemState&ODS_SELECTED)
	{
		//实现按下简单效果
		if (m_nIDSelected==m_nIDNormal)
		{
			pDC->StretchBlt(rect.left,rect.top+1,rect.right,rect.bottom,&memDC,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		}
		else
		{
			pDC->StretchBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		}
	}
	else
	{
		pDC->StretchBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);		
	}

	memDC.SelectObject(pOld);						//删除刚才选入到内存设备环境的位图信息
	bmpTrans.DeleteObject();

	CFont* pOldFont = pDC->SelectObject(&m_Font);	
	pDC->SetBkMode(TRANSPARENT);

	if(nType != 3)
	{
		pDC->SetTextColor(m_TextColor);
	}
	else
	{
		pDC->SetTextColor(RGB(128,128,128));
	}
	
	pDC->DrawText(m_strText,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);	
	pDC->SelectObject(pOldFont);
}

void CMyButton::EnableSelectAlways(bool bEnable)
{
	m_bAlwaysSelect = bEnable;
}
bool CMyButton::IsSelectAlways()
{
	return m_bAlwaysSelect;
}

int CMyButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

//	CDC* pDC = GetDC();

	LOGFONT font;
	font.lfHeight = 12;								//字体高度
	font.lfWidth = 0;								//字体宽度
	font.lfWeight = FW_BOLD;						//线条宽度
	font.lfCharSet = GB2312_CHARSET;				//字符集
	font.lfClipPrecision = CLIP_CHARACTER_PRECIS;	//剪辑精度
	font.lfOutPrecision = OUT_DEFAULT_PRECIS;		//输出精度
	font.lfEscapement = 0;							//文本行相当于页面底端的角度(单位：0.1°)
	font.lfOrientation = 0;							//字符基线相当于页面底端的角度(单位：0.1°)
	font.lfPitchAndFamily = DEFAULT_PITCH|FF_MODERN;//字符间距和字符家族
	font.lfQuality = DEFAULT_QUALITY;				//字符质量			
	font.lfItalic = FALSE;							//正斜体(TRUE：斜体)
	font.lfStrikeOut = FALSE;						//删除线(TRUE：删除线)
	font.lfUnderline = FALSE;						//下划线(TRUE：下划线)	
	strcpy_s(font.lfFaceName,"宋体");					//字体

	//字体必须是全局的，否则只能看到光标改变，而字体无效	
	m_Font.CreateFontIndirect(&font);

	return 0;
}
