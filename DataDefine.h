//数据结构定义


#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

#include <vector>

using namespace std;

//定义长度常量
const int LENGTH_1M = 1024*1024;
const int LENGTH_1024 = 1024;
const int LENGTH_512 = 512;
const int LENGTH_255 = 255;
const int LENGTH_100 = 100;
const int LENGTH_50 = 50;
const int LENGTH_20 = 20;

#define InitMemory(Destination,Length) memset((Destination),0,(Length*sizeof(TCHAR)))

//时间日期
typedef struct _DateTime
{
	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMinute;
	int nSecond;
	//初始化
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

//性别
enum SEX
{
	MALE,
	FEMALE
};
//权限
enum RIGHT
{
	NORMAL_USER,
	UNIT_MANGE,
	SYS_MANAGE
};

//用户信息
typedef struct _UserInfo
{
	char UserID[LENGTH_20];			//用户帐号
	char PassWord[LENGTH_20];		//密码
	char UserName[LENGTH_20];		//用户名
	RIGHT  nRight;					//权限
	SEX  nSex;						//性别
	int  nUnitID;					//单位ID
	char FriendCircle[LENGTH_1024];	//朋友圈
	char FocusApp[LENGTH_1024];		//关注应用
	bool bOnlineStatus;				//在线状态
	char Telephone[LENGTH_20];		//电话号码
	char Email[LENGTH_20];			//email
	char Weixin[LENGTH_20];			//微信号
	int nScore;						//初始积分(24分)，如果扣减到0则禁用

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

//单位信息
typedef struct _UnitInfo
{
	int  nUnitID;					//单位ID
	char UnitName[LENGTH_100];		//单位名称
	int  nSuperID;					//上级单位ID
	int  nRank;						//同级单位排名
	char ManagerID[LENGTH_20];		//管理员ID
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

//用户黑名单
typedef struct _UserBlackList
{
	int  nID;						//数据库中的主键
	char UserID[LENGTH_20];			//黑名单用户ID
	int  nForbitType;				//禁用类型（0：永久禁用，1：暂时禁用)
	sDateTime  StartTime;			//开始时间
	sDateTime  EndTime;				//结束时间
	_UserBlackList()
	{
		nID = 0;
		nForbitType = 0;
		InitMemory(UserID,LENGTH_20);
	}
} sUserBlackList;

//个人消息订阅
typedef struct _UserMsgSubscription
{
	int  nID;						 //数据库中的主键
	char UserID[LENGTH_20];			 //订阅用户ID
	bool bIsForbidAll;				 //是否禁用所有消息
	char ForbidFriends[LENGTH_1024]; //禁用好友消息
	char ForbidApps[LENGTH_1024];	 //禁用应用消息
	int  nForbidType;				 //禁用类型(0:全部、1、客户端、2：短信、3、微信)
	sDateTime  StartTime;			 //开始时间
	sDateTime  EndTime;				 //结束时间
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

//应用信息
typedef struct _AppInfo
{
	char AppID[LENGTH_20];			 //应用账号
	char AppName[LENGTH_20];		 //应用名称
	char AppPassword[LENGTH_20];	 //应用密码
	char IconPath[LENGTH_255];		 //应用图片
	int nAppType;					 //应用类型：0-平台应用，1-第三方应用-消息型，2-第三方应用-应用型
	char Phone[LENGTH_20];			 //联系电话
	int nStatus;					 //应用状态：0-未审核通过,1-审核通过,2-已被禁用
    sDateTime RegTime;				 //注册时间
	char Remark[LENGTH_100];		 //应用介绍				
	char FocusUserList[LENGTH_1024]; //关注应用列表
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

//应用事项
typedef struct _AppItem
{
	int  nItemId;					 //事项ID			
	char AppID[LENGTH_20];			 //应用账号(外键)
	char ItemName[LENGTH_50];		 //事项名称
	int  nItemType;					 //事项类型(备用)
	char Remark[LENGTH_100];		 //备注(备用)

	_AppItem()
	{
		nItemId = 0;
		nItemType = 0;
		InitMemory(AppID,LENGTH_20);
		InitMemory(ItemName,LENGTH_20);
		InitMemory(Remark,LENGTH_100);
	}
} sAppItem;

//应用事项流程
typedef struct _AppFlow
{
	int	 nFlowId;					 //流程ID
	int  nItemId;					 //事项ID(外键)
	int  nOrder;					 //流程排序
	char FlowName[LENGTH_50];		 //流程名称
	char Prompt[LENGTH_100];	     //流程内容提示
	bool IsAutoExecute;				 //是否自动执行
	bool IsSendMessage;				 //是否发送消息
	char Message[LENGTH_100];	     //消息内容
	char SendType[5];				 //0000四字符，0,1为其掩码位，分别代表微信、短信、邮件、站内					
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


//应用黑名单
typedef struct _AppBlackList
{
	int  nID;						 //数据库中的主键
	int  nAppID;					 //应用ID
	char IpAddr[LENGTH_20];			 //IP地址
	sDateTime  StartTime;			 //开始时间
	sDateTime  EndTime;				 //结束时间

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

//消息调度策略:消息策略只有一条
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

//消息调度
typedef struct _MsgDispatch
{
	int  nID;							 //数据库中的主键
	int  nMsgType;						 //消息类型
	int  nMsgFormat;					 //消息格式
	vector<sDispatchPolicy>  SendPolicy; //发送策略
	int  nMsgPriority;					 //消息优先级
	char Title[LENGTH_100];				 //消息标题
	char Content[LENGTH_1024];			 //消息内容
	char SavePath[LENGTH_255];			 //文件保存路径
	int  nSurvivalPeriod;				 //消息生存时间(毫秒)
	sDateTime  ArriveTime;				 //到达时间

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

//消息
typedef struct _TextMessage
{
	int  nMsgID;						    //数据库中的主键
	char senderID[LENGTH_20];				//发送ID
	char receiverID[LENGTH_20];				//接收ID(应用消息该字段无效)
	long timeStap;						    //开始时间戳
	long expiration;						//过期时间(3天)
	int priority;							//优先级（可选）

	char msgType[LENGTH_20];				//消息类型
	char title[LENGTH_100];					//消息标题
	char content[LENGTH_1024];				//消息正文
	bool bIsRead;							//消息状态(false:未读，true:已读)
	int nType;								//消息大类（0：系统，1：应用，2：用户）
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


//应用消息
typedef struct _AppMsg
{
	int  nID;						 //数据库中的主键
	sAppInfo  AppInfo;				 //应用信息
	char MsgName[LENGTH_50];		 //消息名称
	char Receiver[LENGTH_1024];		 //接收者列表
	bool bSendFlag;					 //消息发送标识(0:正在调度,1:已发送)
	sMsgDispatch  DispatchInfo;		 //消息分发信息

	_AppMsg()
	{
		nID = 0;
		InitMemory(MsgName,LENGTH_50);
		InitMemory(Receiver,LENGTH_1024);
		bSendFlag = false;
	}
} sAppMsg;


//用户消息
typedef struct _UserMsg
{
	int  nID;						 //数据库中的主键
	sUnitInfo Sender;				 //发送用户			
	vector<sUnitInfo>  Receivers;	 //接收用户
	int nSendType;					 //发送类型
	bool bSendFlag;					 //消息发送标识(0:正在调度,1:已发送)	
	sMsgDispatch  DispatchInfo;		 //消息分发信息

	_UserMsg()
	{
		nID = 0;
		nSendType = 0;
		bSendFlag = false;
	}
} sUserMsg;



#endif