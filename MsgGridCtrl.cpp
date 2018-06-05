// MsgGridCtrl.cpp : 实现文件
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



// CMsgGridCtrl 消息处理程序
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
	InsertColumn (0, _T("序号"), 60);
	InsertColumn (1, _T("发送方"), 80);
	InsertColumn (2, _T("接收方"), 80);
	InsertColumn (3, _T("发送日期"), 120);
	InsertColumn (4, _T("到期时间"), 150);
	InsertColumn (5, _T("消息类型"), 100);
	InsertColumn (6, _T("主题"), 150);
	InsertColumn (7, _T("正文"), 250);
	InsertColumn (8, _T("状态"), 80);
	InsertColumn (9, _T("优先级"), 60);

	//-------------------
	// Set group columns:
	//-------------------
	InsertGroupColumn (0, 3 /* 发送时间 */);
	InsertGroupColumn (1, 1 /* 发送方 */);

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
//增加一行记录
void CMsgGridCtrl::AddMessage(int nRow,sTextMessage msg)
{
	CString str;
	sDateTime dTime;
	const int nColumns = GetColumnCount();
	CBCGPGridRow* pRootRow = CreateRow (nColumns);

	//第一列：序号
	str.Format("%d",nRow);
	pRootRow->GetItem (0)->SetValue (str.GetBuffer());

	//第二列：发送方
	pRootRow->GetItem (1)->SetValue (msg.senderID);

	//第三列：接收方
	pRootRow->GetItem (2)->SetValue (msg.receiverID);
	
	//第四列：发送日期
	dTime = stamp_to_standard(msg.timeStap);
	pRootRow->GetItem (3)->SetValue (dTime.ToCString(true).GetBuffer());
	
	//第五列：到期时间
	dTime = stamp_to_standard(msg.timeStap+msg.expiration);
	pRootRow->GetItem (4)->SetValue (dTime.ToCString().GetBuffer());

	//第六列：消息类型
	pRootRow->GetItem (5)->SetValue (msg.msgType);
	
	//第七列：主题
	pRootRow->GetItem (6)->SetValue (msg.title);

	//第八列：正文	
	pRootRow->GetItem (7)->SetValue (msg.content);

	//第九列：状态
	str = msg.bIsRead?"未读":"已读";
	pRootRow->GetItem (8)->SetValue (str.GetBuffer());

	//第十列：消息ID（隐藏）
	str.Format("%d",msg.nMsgID);
	pRootRow->GetItem (9)->SetValue (str.GetBuffer());

	//增加行
	AddRow (pRootRow,FALSE);
	
}
//移除一行记录
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
			//这样也是可以的
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
		AfxMessageBox("没有选择消息记录！");
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

//标准时间格式例如：2016:08:02 12:12:30，转换成时间戳
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

//时间戳转换为
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

