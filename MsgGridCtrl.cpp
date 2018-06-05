// MsgGridCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "MsgGridCtrl.h"


// CMsgGridCtrl

IMPLEMENT_DYNAMIC(CMsgGridCtrl, CBCGPReportCtrl)

inline int Rand (int nMax)
{
	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

CMsgGridCtrl::CMsgGridCtrl()
{
	m_pSelRow = NULL;
}

CMsgGridCtrl::~CMsgGridCtrl()
{

}


BEGIN_MESSAGE_MAP(CMsgGridCtrl, CBCGPReportCtrl)
	//{{AFX_MSG_MAP(CReportGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMsgGridCtrl ��Ϣ�������
int CMsgGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPReportCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	//------------------
	// Load grid images:
	//------------------
	CBitmap bmp;
	//bmp.LoadBitmap (IDB_EXIT_DOWN);

	m_Images.Create (16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
	m_Images.Add (&bmp, RGB (255, 0, 255));

	SetImageList (&m_Images);

	this->m_bVisualManagerStyle = TRUE;

	//----------------
	// Insert columns:
	//----------------
	InsertColumn (0, _T("���"), 60);
	InsertColumn (1, _T("���ͷ�"), 80);
	InsertColumn (2, _T("���շ�"), 80);
	InsertColumn (3, _T("��������"), 120);
	InsertColumn (4, _T("����ʱ��"), 150);
	InsertColumn (5, _T("��Ϣ����"), 100);
	InsertColumn (6, _T("����"), 150);
	InsertColumn (7, _T("����"), 250);
	InsertColumn (8, _T("״̬"), 80);
	InsertColumn (9, _T("���ȼ�"), 60);

	//-------------------
	// Set group columns:
	//-------------------
	InsertGroupColumn (0, 3 /* ����ʱ�� */);
	InsertGroupColumn (1, 1 /* ���ͷ� */);

	SetColumnVisible (1, FALSE);
	SetColumnVisible (3, FALSE);
	SetColumnVisible (9, FALSE);

	EnableHeader ();
	EnableColumnAutoSize (TRUE);

	SetWholeRowSel (TRUE);
	SetSingleSel (TRUE);
	EnableMarkSortedColumn (TRUE);
	EnableGroupByBox (TRUE);
	EnableInvertSelOnCtrl ();

	EnablePreviewRow (TRUE, FALSE);
	SetPreviewRowAutoLeftMargin ();

	AdjustLayout ();

	return 0;
}
//����һ�м�¼
void CMsgGridCtrl::AddMessage(int nRow,sTextMessage msg)
{
	CString str;
	sDateTime dTime;
	const int nColumns = GetColumnCount();
	CBCGPGridRow* pRootRow = CreateRow (nColumns);

	//��һ�У����
	str.Format("%d",nRow);
	pRootRow->GetItem (0)->SetValue (str.GetBuffer());

	//�ڶ��У����ͷ�
	pRootRow->GetItem (1)->SetValue (msg.senderID);

	//�����У����շ�
	pRootRow->GetItem (2)->SetValue (msg.receiverID);
	
	//�����У���������
	dTime = stamp_to_standard(msg.timeStap);
	pRootRow->GetItem (3)->SetValue (dTime.ToCString(true).GetBuffer());
	
	//�����У�����ʱ��
	dTime = stamp_to_standard(msg.timeStap+msg.expiration);
	pRootRow->GetItem (4)->SetValue (dTime.ToCString().GetBuffer());

	//�����У���Ϣ����
	pRootRow->GetItem (5)->SetValue (msg.msgType);
	
	//�����У�����
	pRootRow->GetItem (6)->SetValue (msg.title);

	//�ڰ��У�����	
	pRootRow->GetItem (7)->SetValue (msg.content);

	//�ھ��У�״̬
	str = msg.bIsRead?"δ��":"�Ѷ�";
	pRootRow->GetItem (8)->SetValue (str.GetBuffer());

	//��ʮ�У���ϢID�����أ�
	str.Format("%d",msg.nMsgID);
	pRootRow->GetItem (9)->SetValue (str.GetBuffer());

	//������
	AddRow (pRootRow,FALSE);
	
}
//�Ƴ�һ�м�¼
void CMsgGridCtrl::RemoveSelectMsg()
{
	CBCGPGridRow* pRow = NULL;
	CBCGPGridItem* pItem = NULL;
	CString str1,str2;
	if (m_pSelRow!=NULL)
	{
		pItem = m_pSelRow->GetItem(9);
		str2 = (LPCSTR)(_bstr_t)pItem->GetValue();

		for (int nIndex=0; nIndex<this->GetRowCount(); nIndex++)
		{
		    pRow = GetRow(nIndex);
			/*
			if(pRow == m_pSelRow)
			{
				this->RemoveRow(nIndex);
				break;
			}
			//����Ҳ�ǿ��Ե�
			*/
			if (pRow==NULL||pRow->IsGroup())
			{
				continue;
			}
			
			pItem = pRow->GetItem(9);
			str1 = (LPCSTR)(_bstr_t)pItem->GetValue();

			if (str1.Compare(str2)==0)
			{
				this->RemoveRow(nIndex);
				break;
			}
		}
	}
	else
	{
		AfxMessageBox("û��ѡ����Ϣ��¼��");
	}
}

void CMsgGridCtrl::GetSelectMsg(int& nMsgId)
{
	if (m_pSelRow==NULL)
	{
		nMsgId = -1;
	}
	else
	{
		CBCGPGridItem* pItem = NULL;
		pItem = m_pSelRow->GetItem(9);
		CString str = (LPCSTR)(_bstr_t)pItem->GetValue();
		nMsgId = atoi(str.GetBuffer());
	}
}

//��׼ʱ���ʽ���磺2016:08:02 12:12:30��ת����ʱ���
int CMsgGridCtrl::standard_to_stamp(char *str_time)  
{  
	struct tm stm;  
	int iY, iM, iD, iH, iMin, iS;  

	memset(&stm,0,sizeof(stm));  
	iY = atoi(str_time);  
	iM = atoi(str_time+5);  
	iD = atoi(str_time+8);  
	iH = atoi(str_time+11);  
	iMin = atoi(str_time+14);  
	iS = atoi(str_time+17);  

	stm.tm_year=iY-1900;  
	stm.tm_mon=iM-1;  
	stm.tm_mday=iD;  
	stm.tm_hour=iH;  
	stm.tm_min=iMin;  
	stm.tm_sec=iS;  

	return (int)mktime(&stm);  
}  

//ʱ���ת��Ϊ
sDateTime CMsgGridCtrl::stamp_to_standard(long stampTime)
{
	char s[100];
	sDateTime standard;
	struct tm *ttime; 
	
	time_t temp = stampTime;

	if (stampTime<0)
	{
		return  standard;
	}
	ttime = localtime(&temp);  
	strftime(s,sizeof(s),"%Y-%m-%d %H:%M:%S",ttime);


	standard.nYear = atoi(s);
	standard.nMonth = atoi(s+5);
	standard.nDay = atoi(s+8);
	standard.nHour = atoi(s+11);
	standard.nMinute = atoi(s+14);
	standard.nSecond = atoi(s+17);

	return standard;
}

void CMsgGridCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CBCGPGridRow* pRow = HitTest(point);

	if (pRow != NULL && !pRow->IsGroup()) 
	{
		m_pSelRow = pRow;
	}
	else
	{
		m_pSelRow = NULL;
	}

	CBCGPReportCtrl::OnLButtonDown(nFlags, point);
}

void CMsgGridCtrl::OnDestroy() 
{
	CBCGPReportCtrl::OnDestroy();
}

