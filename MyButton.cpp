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
//��ť��ӦͼƬ�ߴ�
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
//ʵ�ְ�ť�Ի�Ĵ���
void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC;
	CRect rect;
	CDC memDC;
	BITMAP bmp;
	CBitmap bmpTrans;
	int nItemState;

	rect = lpDrawItemStruct->rcItem;			 //��ȡ��ť�ؼ���С
	nItemState = lpDrawItemStruct->itemState;	 //��ȡ��ť��״̬
	
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

	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);	//��ȡָ���豸������ָ��
	memDC.CreateCompatibleDC(pDC);					//�������ڴ��豸��������ݵ��豸����
	CBitmap* pOld = memDC.SelectObject(&bmpTrans);	//��λͼ����ѡ�뵽�ڴ��豸������

	bmpTrans.GetBitmap(&bmp);						//��ȡλͼ��Ϣ

	//��λͼ���ڴ��豸������������ʾ�豸����
	if (nItemState&ODS_SELECTED)
	{
		//ʵ�ְ��¼�Ч��
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

	memDC.SelectObject(pOld);						//ɾ���ղ�ѡ�뵽�ڴ��豸������λͼ��Ϣ
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
	font.lfHeight = 12;								//����߶�
	font.lfWidth = 0;								//������
	font.lfWeight = FW_BOLD;						//�������
	font.lfCharSet = GB2312_CHARSET;				//�ַ���
	font.lfClipPrecision = CLIP_CHARACTER_PRECIS;	//��������
	font.lfOutPrecision = OUT_DEFAULT_PRECIS;		//�������
	font.lfEscapement = 0;							//�ı����൱��ҳ��׶˵ĽǶ�(��λ��0.1��)
	font.lfOrientation = 0;							//�ַ������൱��ҳ��׶˵ĽǶ�(��λ��0.1��)
	font.lfPitchAndFamily = DEFAULT_PITCH|FF_MODERN;//�ַ������ַ�����
	font.lfQuality = DEFAULT_QUALITY;				//�ַ�����			
	font.lfItalic = FALSE;							//��б��(TRUE��б��)
	font.lfStrikeOut = FALSE;						//ɾ����(TRUE��ɾ����)
	font.lfUnderline = FALSE;						//�»���(TRUE���»���)	
	strcpy_s(font.lfFaceName,"����");					//����

	//���������ȫ�ֵģ�����ֻ�ܿ������ı䣬��������Ч	
	m_Font.CreateFontIndirect(&font);

	return 0;
}
