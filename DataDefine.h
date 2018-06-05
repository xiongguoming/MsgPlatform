//���ݽṹ����


#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

#include <vector>

using namespace std;

//���峤�ȳ���
const int LENGTH_1M = 1024*1024;
const int LENGTH_1024 = 1024;
const int LENGTH_512 = 512;
const int LENGTH_255 = 255;
const int LENGTH_100 = 100;
const int LENGTH_50 = 50;
const int LENGTH_20 = 20;

#define InitMemory(Destination,Length) memset((Destination),0,(Length*sizeof(TCHAR)))

//ʱ������
typedef struct _DateTime
{
	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMinute;
	int nSecond;
	//��ʼ��
	_DateTime()
	{
		nYear = 2017;
		nMonth = 1;
		nDay = 1;
		nHour = 0;
		nMinute = 0;
		nSecond = 0;
	}
	inline CString ToCString(bool bShort=false)
	{
		CString str;
		if (!bShort)
		{
			str.Format("%04d-%02d-%02d %02d:%02d:%02d",nYear,nMonth,nDay,nHour,nMinute,nSecond);
		}
		else
		{
			str.Format("%04d-%02d-%02d",nYear,nMonth,nDay);
		}
		
		return str;
	}
} sDateTime;

//�Ա�
enum SEX
{
	MALE,
	FEMALE
};
//Ȩ��
enum RIGHT
{
	NORMAL_USER,
	UNIT_MANGE,
	SYS_MANAGE
};

//�û���Ϣ
typedef struct _UserInfo
{
	char UserID[LENGTH_20];			//�û��ʺ�
	char PassWord[LENGTH_20];		//����
	char UserName[LENGTH_20];		//�û���
	RIGHT  nRight;					//Ȩ��
	SEX  nSex;						//�Ա�
	int  nUnitID;					//��λID
	char FriendCircle[LENGTH_1024];	//����Ȧ
	char FocusApp[LENGTH_1024];		//��עӦ��
	bool bOnlineStatus;				//����״̬
	char Telephone[LENGTH_20];		//�绰����
	char Email[LENGTH_20];			//email
	char Weixin[LENGTH_20];			//΢�ź�
	int nScore;						//��ʼ����(24��)������ۼ���0�����

	_UserInfo()
	{
		InitMemory(UserID,LENGTH_20);
		InitMemory(UserName,LENGTH_20);
		InitMemory(PassWord,LENGTH_20);
		InitMemory(FriendCircle,LENGTH_1024);
		InitMemory(FocusApp,LENGTH_1024);
		InitMemory(Telephone,LENGTH_20);
		InitMemory(Email,LENGTH_20);
		InitMemory(Weixin,LENGTH_20);
		bOnlineStatus = false;
		nUnitID = 0;
		nRight = NORMAL_USER;
		nSex = MALE;
		nScore = 24;
	}
} sUserInfo;

//��λ��Ϣ
typedef struct _UnitInfo
{
	int  nUnitID;					//��λID
	char UnitName[LENGTH_100];		//��λ����
	int  nSuperID;					//�ϼ���λID
	int  nRank;						//ͬ����λ����
	char ManagerID[LENGTH_20];		//����ԱID
	bool bDelFlag;
	_UnitInfo()
	{
		InitMemory(UnitName,LENGTH_100);
		nUnitID = 0;
		nSuperID = -1;
		nRank = 0;
		InitMemory(ManagerID,LENGTH_20);
		bDelFlag = false;
	}
} sUnitInfo;

//�û�������
typedef struct _UserBlackList
{
	int  nID;						//���ݿ��е�����
	char UserID[LENGTH_20];			//�������û�ID
	int  nForbitType;				//�������ͣ�0�����ý��ã�1����ʱ����)
	sDateTime  StartTime;			//��ʼʱ��
	sDateTime  EndTime;				//����ʱ��
	_UserBlackList()
	{
		nID = 0;
		nForbitType = 0;
		InitMemory(UserID,LENGTH_20);
	}
} sUserBlackList;

//������Ϣ����
typedef struct _UserMsgSubscription
{
	int  nID;						 //���ݿ��е�����
	char UserID[LENGTH_20];			 //�����û�ID
	bool bIsForbidAll;				 //�Ƿ����������Ϣ
	char ForbidFriends[LENGTH_1024]; //���ú�����Ϣ
	char ForbidApps[LENGTH_1024];	 //����Ӧ����Ϣ
	int  nForbidType;				 //��������(0:ȫ����1���ͻ��ˡ�2�����š�3��΢��)
	sDateTime  StartTime;			 //��ʼʱ��
	sDateTime  EndTime;				 //����ʱ��
	_UserMsgSubscription()
	{
		nID = 0;
		InitMemory(UserID,LENGTH_20);
		bIsForbidAll = false;
		InitMemory(ForbidFriends,LENGTH_1024);
		InitMemory(ForbidApps,LENGTH_1024);
		nForbidType = 0;
	}
} sUserMsgSubscription;

//Ӧ����Ϣ
typedef struct _AppInfo
{
	char AppID[LENGTH_20];			 //Ӧ���˺�
	char AppName[LENGTH_20];		 //Ӧ������
	char AppPassword[LENGTH_20];	 //Ӧ������
	char IconPath[LENGTH_255];		 //Ӧ��ͼƬ
	int nAppType;					 //Ӧ�����ͣ�0-ƽ̨Ӧ�ã�1-������Ӧ��-��Ϣ�ͣ�2-������Ӧ��-Ӧ����
	char Phone[LENGTH_20];			 //��ϵ�绰
	int nStatus;					 //Ӧ��״̬��0-δ���ͨ��,1-���ͨ��,2-�ѱ�����
    sDateTime RegTime;				 //ע��ʱ��
	char Remark[LENGTH_100];		 //Ӧ�ý���				
	char FocusUserList[LENGTH_1024]; //��עӦ���б�
	int nScore;
	
	_AppInfo()
	{
		InitMemory(AppID,LENGTH_20);
		InitMemory(AppName,LENGTH_20);
		InitMemory(AppPassword,LENGTH_20);
		InitMemory(IconPath,LENGTH_255);
		nAppType = 0;
		InitMemory(Phone,LENGTH_20);
		InitMemory(FocusUserList,LENGTH_1024);
		nStatus = 0;
		InitMemory(Remark,LENGTH_100);
		nScore = 24;
	}
} sAppInfo;

//Ӧ������
typedef struct _AppItem
{
	int  nItemId;					 //����ID			
	char AppID[LENGTH_20];			 //Ӧ���˺�(���)
	char ItemName[LENGTH_50];		 //��������
	int  nItemType;					 //��������(����)
	char Remark[LENGTH_100];		 //��ע(����)

	_AppItem()
	{
		nItemId = 0;
		nItemType = 0;
		InitMemory(AppID,LENGTH_20);
		InitMemory(ItemName,LENGTH_20);
		InitMemory(Remark,LENGTH_100);
	}
} sAppItem;

//Ӧ����������
typedef struct _AppFlow
{
	int	 nFlowId;					 //����ID
	int  nItemId;					 //����ID(���)
	int  nOrder;					 //��������
	char FlowName[LENGTH_50];		 //��������
	char Prompt[LENGTH_100];	     //����������ʾ
	bool IsAutoExecute;				 //�Ƿ��Զ�ִ��
	bool IsSendMessage;				 //�Ƿ�����Ϣ
	char Message[LENGTH_100];	     //��Ϣ����
	char SendType[5];				 //0000���ַ���0,1Ϊ������λ���ֱ����΢�š����š��ʼ���վ��					
	_AppFlow()
	{
		nFlowId = 0;
		nItemId = 0;
		nOrder = 0;
		InitMemory(FlowName,LENGTH_50);
		InitMemory(Prompt,LENGTH_100);
		IsAutoExecute = true;
		IsSendMessage = true;
		InitMemory(Message,LENGTH_100);
		InitMemory(SendType,5);
	}
} sAppFlow;


//Ӧ�ú�����
typedef struct _AppBlackList
{
	int  nID;						 //���ݿ��е�����
	int  nAppID;					 //Ӧ��ID
	char IpAddr[LENGTH_20];			 //IP��ַ
	sDateTime  StartTime;			 //��ʼʱ��
	sDateTime  EndTime;				 //����ʱ��

	_AppBlackList()
	{
		nID = 0;
		nAppID = 0;
		InitMemory(IpAddr,LENGTH_20);
	}
} sAppBlackList;

typedef struct _Keyword
{
	int nID;
	char Keyword[LENGTH_20];
	_Keyword()
	{
		nID = 0;
		InitMemory(Keyword,LENGTH_20);
	}	

}sKeyword;

//��Ϣ���Ȳ���:��Ϣ����ֻ��һ��
typedef struct _DispatchPolicy
{
	int  nID;
	char SysMsgPolicy[5];
	char AppMsgPolicy[5];			
	char UserMsgPolicy[5];

	int nAppMsgLimited;
	int nUserMsgLimited;
	int nInitScore;
	int nSubScore;

	_DispatchPolicy()
	{
		nID = 0;

		InitMemory(SysMsgPolicy,5);
		InitMemory(AppMsgPolicy,5);
		InitMemory(UserMsgPolicy,5);
		
		nAppMsgLimited = 100;
		nUserMsgLimited = 100;
		nInitScore = 24;
		nSubScore = 6;
	}
} sDispatchPolicy;

//��Ϣ����
typedef struct _MsgDispatch
{
	int  nID;							 //���ݿ��е�����
	int  nMsgType;						 //��Ϣ����
	int  nMsgFormat;					 //��Ϣ��ʽ
	vector<sDispatchPolicy>  SendPolicy; //���Ͳ���
	int  nMsgPriority;					 //��Ϣ���ȼ�
	char Title[LENGTH_100];				 //��Ϣ����
	char Content[LENGTH_1024];			 //��Ϣ����
	char SavePath[LENGTH_255];			 //�ļ�����·��
	int  nSurvivalPeriod;				 //��Ϣ����ʱ��(����)
	sDateTime  ArriveTime;				 //����ʱ��

	_MsgDispatch()
	{
		nID = 0;
		nMsgType = 0;
		nMsgFormat = 0;
		nMsgPriority = 0;
		InitMemory(Title,LENGTH_100);
		InitMemory(Content,LENGTH_1024);
		InitMemory(SavePath,LENGTH_255);
		nSurvivalPeriod = 0;
	}
} sMsgDispatch;

//��Ϣ
typedef struct _TextMessage
{
	int  nMsgID;						    //���ݿ��е�����
	char senderID[LENGTH_20];				//����ID
	char receiverID[LENGTH_20];				//����ID(Ӧ����Ϣ���ֶ���Ч)
	long timeStap;						    //��ʼʱ���
	long expiration;						//����ʱ��(3��)
	int priority;							//���ȼ�����ѡ��

	char msgType[LENGTH_20];				//��Ϣ����
	char title[LENGTH_100];					//��Ϣ����
	char content[LENGTH_1024];				//��Ϣ����
	bool bIsRead;							//��Ϣ״̬(false:δ����true:�Ѷ�)
	int nType;								//��Ϣ���ࣨ0��ϵͳ��1��Ӧ�ã�2���û���
	_TextMessage()
	{
		nMsgID = 0;
		InitMemory(senderID,LENGTH_20);
		InitMemory(receiverID,LENGTH_20);
		timeStap = 0;
		expiration = 259200;
		priority = 0;
		InitMemory(msgType,LENGTH_20);
		InitMemory(title,LENGTH_100);
		InitMemory(content,LENGTH_1024);
		bIsRead = false;
		nType = 0;
	}
} sTextMessage;


//Ӧ����Ϣ
typedef struct _AppMsg
{
	int  nID;						 //���ݿ��е�����
	sAppInfo  AppInfo;				 //Ӧ����Ϣ
	char MsgName[LENGTH_50];		 //��Ϣ����
	char Receiver[LENGTH_1024];		 //�������б�
	bool bSendFlag;					 //��Ϣ���ͱ�ʶ(0:���ڵ���,1:�ѷ���)
	sMsgDispatch  DispatchInfo;		 //��Ϣ�ַ���Ϣ

	_AppMsg()
	{
		nID = 0;
		InitMemory(MsgName,LENGTH_50);
		InitMemory(Receiver,LENGTH_1024);
		bSendFlag = false;
	}
} sAppMsg;


//�û���Ϣ
typedef struct _UserMsg
{
	int  nID;						 //���ݿ��е�����
	sUnitInfo Sender;				 //�����û�			
	vector<sUnitInfo>  Receivers;	 //�����û�
	int nSendType;					 //��������
	bool bSendFlag;					 //��Ϣ���ͱ�ʶ(0:���ڵ���,1:�ѷ���)	
	sMsgDispatch  DispatchInfo;		 //��Ϣ�ַ���Ϣ

	_UserMsg()
	{
		nID = 0;
		nSendType = 0;
		bSendFlag = false;
	}
} sUserMsg;



#endif