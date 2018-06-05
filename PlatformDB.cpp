// PlatformDB.cpp: implementation of the PlatformDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSG_PLATFORM.h"
#include "PlatformDB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PlatformDB::PlatformDB()
{

}

PlatformDB::~PlatformDB()
{

}

//创建数据库所有表
void PlatformDB::CreateTables()
{
	CString str;

	//char类型最大255，用text代替
	//1、用户-单位信息
	str = L"create table if not exists USER_UNIT(\
		   UNIT_ID int not null primary key,\
		   UNIT_NAME char(50) not null,\
		   SUPER_ID int not null,\
		   UNIT_RANK char(20),\
		   UNIT_MANAGE char(20))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	//2、用户-用户信息
	str = L"create table if not exists USER_INFO(\
		   USER_ID char(20) not null primary key,\
		   PASSWORD char(20) not null,\
		   USER_NAME char(20) not null,\
		   USER_RIGHT int,\
		   SEX int,\
		   UNIT_ID int,\
		   FRIEND_CIRCLE text,\
		   FOCUS_APP char(100),\
		   TELEPHONE char(20),\
		   EMAIL char(20),\
		   WEIXIN char(20),\
		   ONLINE_TYPE int,\
		   SCORE int,\
		   FOREIGN KEY(UNIT_ID) REFERENCES USER_UNIT(UNIT_ID))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	
	//3、用户-黑名单
	str = L"create table if not exists USER_BLACKLIST(\
		   ID int primary key auto_increment,\
		   USER_ID char(20) not null,\
		   IP_ADDR char(30),\
		   START_TIME char(50),\
		   END_TIME char(50),\
		   FOREIGN KEY(USER_ID) REFERENCES USER_INFO(USER_ID))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//4、用户-个人消息订阅
	str = L"create table if not exists USER_MSG_SUBSCRIPTION(\
		   ID int primary key auto_increment,\
		   USER_ID char(20) not null,\
		   RECEIVE_ALL_MSG int,\
		   RECEIVE_APP_MSG int,\
		   RECEIVE_USER_MSG int,\
		   SET_RECEIVE_TIME int,\
		   START_REC_TIME char(50),\
		   END_REC_TIME char(50),\
		   SYS_MSG_POLICY char(5),\
		   APP_MSG_POLICY char(5),\
		   USER_MSG_POLICY char(5),\
		   FORBID_APP char(255),\
		   FORBID_USER char(255),\
		   FOREIGN KEY(USER_ID) REFERENCES USER_INFO(USER_ID))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//5、应用-应用信息
	str = L"create table if not exists APP_INFO(\
		   APP_ID char(20) not null primary key,\
		   APP_NAME char(20) not null,\
		   PASSWORD char(20) not null,\
		   APP_TYPE int,\
		   ICON char(100),\
		   PHONE char(20),\
		   REGIST_TIME char(20),\
		   REMARK char(100),\
		   STATUS int not null,\
		   FOCUS_USER_LIST text,\
		   SCORE int)";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//6、用户-黑名单
	str = L"create table if not exists APP_BLACKLIST(\
		   ID int primary key auto_increment,\
		   APP_ID char(20) not null,\
		   IP_ADDR char(30),\
		   START_TIME char(50),\
		   END_TIME char(50),\
		   FOREIGN KEY(APP_ID) REFERENCES APP_INFO(APP_ID))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	
	//7、应用事项
	str = L"create table if not exists APP_ITEM(\
		   ITEM_ID int primary key auto_increment,\
		   APP_ID char(20) not null,\
		   ITEM_NAME char(50) not null,\
		   ITEM_TYPE int,\
		   REMARK char(100),\
		   FOREIGN KEY(APP_ID) REFERENCES APP_INFO(APP_ID))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	
	//8、应用事项流程
	str = L"create table if not exists APP_FLOW(\
		   FLOW_ID int primary key auto_increment,\
		   ITEM_ID int not null,\
		   FLOW_ORDER int not null,\
		   FLOW_NAME char(50) not null,\
		   PROMPT char(100),\
		   IS_AUTO_EXECUTE int not null,\
		   IS_SEND_MESSAGE int not null,\
		   MESSAGE char(100),\
		   SEND_TYPE char(4),\
		   FOREIGN KEY(ITEM_ID) REFERENCES APP_ITEM(ITEM_ID))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//9、应用-用户关注对应表
	str = L"create table if not exists APP_USERS_FOCUS(\
		   ID int primary key auto_increment,\
		   APP_ID char(20),\
		   USER_ID char(20),\
		   FOREIGN KEY(APP_ID) REFERENCES APP_INFO(APP_ID),\
		   FOREIGN KEY(USER_ID) REFERENCES USER_INFO(USER_ID))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//10、消息-消息调度
	str = L"create table if not exists MSG_DISPATCH(\
		   ID int primary key auto_increment,\
		   MSG_TYPE int not null,\
		   MSG_FORMAT int not null,\
		   SEND_POLICY char(50),\
		   MSG_PRIORITY int,\
		   MSG_TITLE char(250),\
		   MSG_CONTNET text,\
		   SAVE_PATH char(250),\
		   SURVIVAL_PERIOD int,\
		   ARRIVE_TIME char(50))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	
	//11、消息-存储(系统消息、应用消息、用户消息全部存储到该数据库)
	//TYPE=0:系统消息,TYPE=1:应用消息,TYPE=2:用户消息
	str = L"create table if not exists MSG_STORAGE(\
		   ID int primary key auto_increment,\
		   SENDER_ID char(20) not null,\
		   RECEIVER_ID char(20),\
		   TIMESTAP bigint,\
		   EXPIRATION bigint,\
		   PRIORITY int,\
		   MSG_TYPE char(20) not null,\
		   MSG_TITLE char(100),\
		   MSG_CONTENT text(1024),\
		   TYPE int not null)";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));


	//12、消息-应用消息
	str = L"create table if not exists MSG_APP_MSG(\
		   ID int primary key auto_increment,\
		   APP_ID char(20) not null,\
		   MSG_NAME char(100) not null,\
		   RECEIVER char(250),\
		   MSG_ID int,\
		   MSG_DISPATCH_ID int,\
		   MSG_STORAGE_ID int,\
		   STATUS int,\
		   FOREIGN KEY(APP_ID) REFERENCES APP_INFO(APP_ID))";
		   
	ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	
	//13、消息-用户消息
	str = L"create table if not exists MSG_USER_MSG(\
		   ID int primary key auto_increment,\
		   SENDER_ID char(20) not null,\
		   RECEIVER_ID char(20),\
		   TIMESTAP bigint,\
		   EXPIRATION bigint,\
		   PRIORITY int,\
		   MSG_TYPE char(20) not null,\
		   MSG_TITLE char(100),\
		   MSG_CONTENT text(1024),\
		   STATUS int,\
		   FOREIGN KEY(SENDER_ID) REFERENCES USER_INFO(USER_ID))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//14、消息-系统消息//PRIORITY：0-提醒，1-消息,2-告警
	str = L"create table if not exists MSG_SYS_MSG(\
		   ID int primary key auto_increment,\
		   SENDER_ID char(20) not null,\
		   RECEIVER_ID char(20),\
		   TIMESTAP bigint,\
		   EXPIRATION bigint,\
		   PRIORITY int,\
		   MSG_TYPE char(20) not null,\
		   MSG_TITLE char(100),\
		   MSG_CONTENT text(1024),\
		   STATUS int)";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//15、消息-应用消息
	str = L"create table if not exists MSG_APP_MSG(\
		   ID int primary key auto_increment,\
		   SENDER_ID char(20) not null,\
		   RECEIVER_ID char(1024) not null,\
		   TIMESTAP bigint,\
		   EXPIRATION bigint,\
		   PRIORITY int,\
		   MSG_TYPE char(20) not null,\
		   MSG_TITLE char(100),\
		   MSG_CONTENT text(1024),\
		   STATUS int)";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//16、消息-调度策略
	str = L"create table if not exists MSG_DISPATCH_POLICY(\
		   ID int primary key auto_increment,\
		   SYS_POLICY char(5),\
		   APP_POLICY char(5),\
		   USER_POLICY char(5),\
		   APP_MSG_LIMIT int,\
		   USER_MSG_LIMIT int,\
		   INIT_SCORE int,\
		   SUB_SCORE int)";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	
	//17、消息-日志，记录消息操作日志，也可用于消息调度时，检查消息队列是否有变化
	str = L"create table if not exists MSG_LOG(\
		   ID int primary key auto_increment,\
		   OPERATER_ID char(20),\
		   OPERATER_TYPE char(50),\
		   OCC_TIME char(50),\
		   REMARK char(200))";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//18、关键字
	str = L"create table if not exists KEYWORDS(KEYWORD char(100) primary key)";

	ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	//读取消息策略，备用
	ReadMsgPolicy(&m_policy);

//	CreateTriggers();

//	DropTables(NULL);//删除所有表
	
}

void PlatformDB::CreateTriggers()
{
	
	CString str;

	str = "DROP TRIGGER IF EXISTS t_after_insert_usermsg";

	bool val = ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	str = L"CREATE TRIGGER t_after_insert_usermsg \
		   AFTER INSERT ON MSG_USER_MSG \
		   FOR EACH ROW \
		   BEGIN \
		   insert into MSG_USER_MSGSTORAGE(\
		   SENDER_ID,RECEIVER_ID,TIMESTAP,EXPIRATION,PRIORITY,MSG_TYPE,MSG_TITLE,MSG_CONTENT,STATUS) \
		   values(new.SENDER_ID,new.RECEIVER_ID,new.TIMESTAP,new.EXPIRATION,new.PRIORITY,new.MSG_TYPE,\
		   new.MSG_TITLE,new.MSG_CONTENT,new.STATUS) \
		   END";

	val = ExecuteNoQuery(str.GetBuffer(str.GetLength()));
}


//删除指定表
bool PlatformDB::DropTables(char* tableName)
{
	CString str;
	//删除一张表
	if (tableName != NULL)
	{
		str.Format("drop table if exists '%s'",tableName);
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	}
	//删除所有表
	else
	{
		str = "drop table if exists USER_BLACKLIST";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists USER_MSG_SUBSCRIPTION";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists MSG_DISPATCH_POLICY";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists MSG_APP_MSG";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists MSG_USER_MSG";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists MSG_STORAGE";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists MSG_DISPATCH";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists USER_INFO";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists USER_UNIT";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));
		
		str = "drop table if exists APP_BLACKLIST";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));

		str = "drop table if exists APP_INFO";
		ExecuteNoQuery(str.GetBuffer(str.GetLength()));
		
	}
	
	return true;
}


//单位
bool PlatformDB::SaveUnit(sUnitInfo* pUnit,bool bModify)
{
	bool bResult = false;
	CString str = "";

	if (pUnit==NULL)
	{
		return bResult;
	}

	//保存新记录
	if (!bModify)
	{
		str.Format("insert into USER_UNIT(UNIT_ID,UNIT_NAME,SUPER_ID,UNIT_RANK,UNIT_MANAGE) values(%d,'%s',%d,%d,'%s')",
			pUnit->nUnitID,pUnit->UnitName,pUnit->nSuperID,pUnit->nRank,pUnit->ManagerID);
	}
	else
	{
		str.Format("update USER_UNIT set UNIT_NAME='%s',UNIT_RANK=%d,UNIT_MANAGE='%s' where UNIT_ID=%d",
			pUnit->UnitName,pUnit->nRank,pUnit->ManagerID,pUnit->nUnitID);
	}
	

	bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	return  bResult;
}

bool PlatformDB::RemoveUnit(sUnitInfo* pUnit)
{
	bool bResult =  false;
	CString str = "";

	if (pUnit != NULL)
	{
		str.Format("delete from USER_UNIT where UNIT_ID=%d",pUnit->nUnitID);
	}

	bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	return bResult;
}
int PlatformDB::ReadAllUnits(sUnitInfo* pUnitArray)
{
	CString str = "";
	int nRecordNum = 0;
	
	str.Format("select * from USER_UNIT");
	nRecordNum = ExecuteQuery(str.GetBuffer(str.GetLength()));

	if (pUnitArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		string str = "";
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{	
			//单位ID
			pUnitArray[nIndex].nUnitID = GetIntValue(nIndex,0);
			//单位名称
			str = GetStringValue(nIndex,1,&length);
			strncpy_s(pUnitArray[nIndex].UnitName,GetStringValue(nIndex,1,&length),LENGTH_100);
			//上级ID
			pUnitArray[nIndex].nSuperID = GetIntValue(nIndex,2);
			//单位排序
			pUnitArray[nIndex].nRank = GetIntValue(nIndex,3);
			//管理员ID
			strncpy_s(pUnitArray[nIndex].ManagerID,GetStringValue(nIndex,4,&length),LENGTH_20);
		}
	}
	return nRecordNum;
}
bool PlatformDB::RemoveAllUnits()
{
	bool bResult =  false;
	CString str = "";

	str.Format("delete from USER_UNIT");

	bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	return bResult;
}
//用户
bool PlatformDB::SaveUser(sUserInfo* pUser,bool bModify)
{
	bool bResult =  false;
	CString str = "";

	if (pUser==NULL)
	{
		return bResult;
	}
	//保存新记录
	if (!bModify)
	{
		pUser->nScore = m_policy.nInitScore;
		//初始状态：不在线，初始积分24
		str.Format("insert into USER_INFO(USER_ID,PASSWORD,USER_NAME,USER_RIGHT,SEX,UNIT_ID,TELEPHONE,EMAIL,WEIXIN,ONLINE_TYPE,SCORE)\
				   values('%s','%s','%s',%d,%d,%d,'%s','%s','%s',%d,%d)",pUser->UserID,pUser->PassWord,pUser->UserName,
				   pUser->nRight,pUser->nSex,pUser->nUnitID,pUser->Telephone,pUser->Email,pUser->Weixin,0,pUser->nScore);
		
	}
	else
	{
		str.Format("update USER_INFO set PASSWORD='%s',USER_NAME='%s',USER_RIGHT=%d,SEX=%d,UNIT_ID=%d, \
				   TELEPHONE='%s',EMAIL='%s',WEIXIN='%s' SCORE=%d where USER_ID='%s'",pUser->PassWord,pUser->UserName,
				   pUser->nRight,pUser->nSex,pUser->nUnitID,pUser->Telephone,pUser->Email,pUser->Weixin,pUser->nScore,pUser->UserID);
	}
	
	bResult = ExecuteNoQuery(str.GetBuffer());
	return  bResult;
}
bool PlatformDB::RemoveUser(sUserInfo* pUser)
{
	bool bResult =  false;
	CString str = "";

	if (pUser != NULL)
	{
		str.Format("delete from USER_INFO where USER_ID='%s'",pUser->UserID);
	}
	
	bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	
	return bResult;
}
int PlatformDB::ReadAllUsers(sUserInfo* pUserArray)
{
	CString str = "";
	int nRecordNum = 0;

	str.Format("select * from USER_INFO");
	nRecordNum = ExecuteQuery(str.GetBuffer());

	if (pUserArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{
			//用户ID
			strncpy_s(pUserArray[nIndex].UserID,GetStringValue(nIndex,0,&length),LENGTH_20);
			//密码
			strncpy_s(pUserArray[nIndex].PassWord,GetStringValue(nIndex,1,&length),LENGTH_20);
			//姓名
			strncpy_s(pUserArray[nIndex].UserName,GetStringValue(nIndex,2,&length),LENGTH_20);
			//权限
			pUserArray[nIndex].nRight = (RIGHT)GetIntValue(nIndex,3);
			//性别
			pUserArray[nIndex].nSex = (SEX)GetIntValue(nIndex,4);
			//单位ID
			pUserArray[nIndex].nUnitID = GetIntValue(nIndex,5);
			//朋友圈
			strncpy_s(pUserArray[nIndex].FriendCircle,GetStringValue(nIndex,6,&length),LENGTH_1024);
			//关注APP
			strncpy_s(pUserArray[nIndex].FocusApp,GetStringValue(nIndex,7,&length),LENGTH_1024);
			//电话
			strncpy_s(pUserArray[nIndex].Telephone,GetStringValue(nIndex,8,&length),LENGTH_20);
			//EMAIL
			strncpy_s(pUserArray[nIndex].Email,GetStringValue(nIndex,9,&length),LENGTH_20);
			//微信
			strncpy_s(pUserArray[nIndex].Weixin,GetStringValue(nIndex,10,&length),LENGTH_20);
			//在线状态
			pUserArray[nIndex].bOnlineStatus = GetBoolValue(nIndex,11);
			//积分
			pUserArray[nIndex].nScore = GetIntValue(nIndex,12);

		}
	}
	return nRecordNum;
}
bool PlatformDB::RemoveAllUsers()
{
	bool bResult =  false;
	CString str = "";

	str.Format("delete from USER_INFO");

	bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	return bResult;
}
//应用操作
bool PlatformDB::SaveApp(sAppInfo* pApp,bool bModify)
{
	bool bResult =  false;
	CString str = "";

	if (pApp==NULL)
	{
		return bResult;
	}
	
	//保存新记录
	if (!bModify)
	{
		if (IsAppExist(pApp))
		{
			return false;
		}
		//初始积分
		pApp->nScore = m_policy.nInitScore;

		str.Format("insert into APP_INFO(APP_ID,APP_NAME,PASSWORD,APP_TYPE,ICON,PHONE,REGIST_TIME,REMARK,STATUS,FOCUS_USER_LIST,SCORE)\
			   values('%s','%s','%s',%d,'%s','%s','%s','%s',%d,'%s',%d)",pApp->AppID,pApp->AppName,pApp->AppPassword,pApp->nAppType,pApp->IconPath,pApp->Phone,
			   pApp->RegTime.ToCString(),pApp->Remark,pApp->nStatus,pApp->FocusUserList,pApp->nScore);
	}
	else
	{
		str.Format("update APP_INFO set APP_NAME='%s',PASSWORD='%s',APP_TYPE=%d,REGIST_TIME='%s',PHONE='%s',REMARK='%s',\
				   STATUS=%d,FOCUS_USER_LIST='%s',SCORE=%d where APP_ID='%s'",pApp->AppName,pApp->AppPassword,pApp->nAppType,pApp->RegTime.ToCString(),
				   pApp->Phone,pApp->Remark,pApp->nStatus,pApp->FocusUserList,pApp->nScore,pApp->AppID);
	}
	
	bResult = ExecuteNoQuery(str.GetBuffer());
	return  bResult;
}

bool PlatformDB::IsAppExist(sAppInfo* pApp)
{
	CString str = "";

	if (pApp != NULL)
	{
		str.Format("select * from APP_INFO where APP_ID='%s'",pApp->AppID);
	}

	int num = ExecuteQuery(str.GetBuffer(str.GetLength()));

	if (num>0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PlatformDB::RemoveApp(sAppInfo* pApp)
{
	bool bResult =  false;
	CString str = "";

	if (pApp != NULL)
	{
		str.Format("delete from APP_INFO where APP_ID='%s'",pApp->AppID);
	}

	bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	return bResult;
}
int PlatformDB::ReadAllApps(sAppInfo* pAppArray)
{
	CString str = "";
	int nRecordNum = 0;

	str.Format("select * from APP_INFO");
	nRecordNum = ExecuteQuery(str.GetBuffer());

	if (pAppArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{
			//应用ID
			strncpy_s(pAppArray[nIndex].AppID,GetStringValue(nIndex,0,&length),LENGTH_20);
			//应用名
			strncpy_s(pAppArray[nIndex].AppName,GetStringValue(nIndex,1,&length),LENGTH_20);
			//密码
			strncpy_s(pAppArray[nIndex].AppPassword,GetStringValue(nIndex,2,&length),LENGTH_20);
			//应用类型
			pAppArray[nIndex].nAppType = GetIntValue(nIndex,3);
			//图标
			strncpy_s(pAppArray[nIndex].IconPath,GetStringValue(nIndex,4,&length),LENGTH_100);
			//电话
			strncpy_s(pAppArray[nIndex].Phone,GetStringValue(nIndex,5,&length),LENGTH_100);
			//注册日期
			pAppArray[nIndex].RegTime = Str2DateTime(GetStringValue(nIndex,6,&length));
			//应用简介
			strncpy_s(pAppArray[nIndex].Remark,GetStringValue(nIndex,7,&length),LENGTH_100);
			//在线状态
			pAppArray[nIndex].nStatus = GetIntValue(nIndex,8);
			//关注APP
			strncpy_s(pAppArray[nIndex].FocusUserList,GetStringValue(nIndex,9,&length),LENGTH_1024);
			//积分
			pAppArray[nIndex].nScore = GetIntValue(nIndex,10);
		}
	}
	return nRecordNum;
}
bool PlatformDB::ReadAppInfo(char* appId,sAppInfo* pAppInfo)
{
	CString str = "";
	int nRecordNum = 0;

	if(appId==NULL ||pAppInfo==NULL)
	{
		return false;
	}

	str.Format("select * from APP_INFO where APP_ID='%s'",appId);
	nRecordNum = ExecuteQuery(str.GetBuffer());

	if (nRecordNum <= 0)
	{
		;return false;	
	}

	int nIndex = 0;
	unsigned length = 0;

	//应用ID
	strncpy_s(pAppInfo->AppID,GetStringValue(nIndex,0,&length),LENGTH_20);
	//应用名
	strncpy_s(pAppInfo->AppName,GetStringValue(nIndex,1,&length),LENGTH_20);
	//密码
	strncpy_s(pAppInfo->AppPassword,GetStringValue(nIndex,2,&length),LENGTH_20);
	//应用类型
	pAppInfo->nAppType = GetIntValue(nIndex,3);
	//图标
	strncpy_s(pAppInfo->IconPath,GetStringValue(nIndex,4,&length),LENGTH_100);
	//电话
	strncpy_s(pAppInfo->Phone,GetStringValue(nIndex,5,&length),LENGTH_100);
	//注册日期
	pAppInfo->RegTime = Str2DateTime(GetStringValue(nIndex,6,&length));
	//应用简介
	strncpy_s(pAppInfo->Remark,GetStringValue(nIndex,7,&length),LENGTH_100);
	//在线状态
	pAppInfo->nStatus = GetIntValue(nIndex,8);
	//关注APP
	strncpy_s(pAppInfo->FocusUserList,GetStringValue(nIndex,9,&length),LENGTH_1024);

	return true;
}
bool PlatformDB::RemoveAllApps()
{
	bool bResult =  false;
	CString str = "";

	str.Format("delete from APP_INFO");

	bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));

	return bResult;
}
bool PlatformDB::updateAppStatus(sAppInfo* pApp)
{
	bool bResult =  false;
	CString str = "";

	if (pApp==NULL)
	{
		return bResult;
	}
	
	str.Format("update APP_INFO set STATUS=%d where ID='%d'",pApp->nStatus,pApp->AppID);

	bResult = ExecuteNoQuery(str.GetBuffer());
	return  bResult;
}

//应用-事项
bool PlatformDB::SaveItem(sAppItem* pItem,bool bModify)
{
	bool bResult =  false;
	CString str = "";

	if (pItem==NULL)
	{
		return bResult;
	}

	//保存新记录
	if (!bModify)
	{
		str.Format("insert into APP_ITEM(APP_ID,ITEM_NAME,ITEM_TYPE,REMARK) values ('%s','%s',%d,'%s')",
			pItem->AppID,pItem->ItemName,pItem->nItemType,pItem->Remark);
	}
	else
	{
		str.Format("update APP_ITEM set ITEM_NAME='%s',ITEM_TYPE=%d,REMARK='%s'",
			pItem->ItemName,pItem->nItemType,pItem->Remark);
	}

	bResult = ExecuteNoQuery(str.GetBuffer());
	return  bResult;
}
bool PlatformDB::RemoveItem(sAppItem* pItem)
{
	CString str = "";
	bool bResult =  false;

	if (pItem != NULL)
	{
		str.Format("delete from APP_FLOW where ITEM_ID=%d",pItem->nItemId);
		
		if(ExecuteNoQuery(str.GetBuffer(str.GetLength())))
		{
			str.Format("delete from APP_ITEM where ITEM_ID=%d",pItem->nItemId);

			bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));
		}
	}
	
	return bResult;
}
bool PlatformDB::ReadItemInfo(int nItemId,sAppItem* pItemInfo)
{
	CString str = "";
	int nRecordNum = 0;
	//获取全部的ITEM
	if (nItemId<0 || pItemInfo==0)
	{
		return false;
	}

	str.Format("select * from APP_ITEM where ITEM_ID=%d",nItemId);

	nRecordNum = ExecuteQuery(str.GetBuffer());
	
	if (nRecordNum >0)
	{
		int nIndex = 0;
		unsigned length = 0;

		//ITEM_ID
		pItemInfo->nItemId = GetIntValue(nIndex,0);
		//APP_ID
		strncpy_s(pItemInfo->AppID,GetStringValue(nIndex,1,&length),LENGTH_20);
		//ITEM_NAME
		strncpy_s(pItemInfo->ItemName,GetStringValue(nIndex,2,&length),LENGTH_50);
		//ITEM_TYPE
		pItemInfo->nItemType = GetIntValue(nIndex,3);
		//REMARK
		strncpy_s(pItemInfo->Remark,GetStringValue(nIndex,4,&length),LENGTH_100);
		return true;
	}
	return false;
}
int PlatformDB::ReadAppItems(char* appId,sAppItem* pItemArray)
{
	CString str = "";
	int nRecordNum = 0;

	//获取全部的ITEM
	if (appId == NULL||strlen(appId)==0)
	{
		str.Format("select * from APP_ITEM");
	}
	else
	{
		str.Format("select * from APP_ITEM where APP_ID='%s'",appId);
	}

	nRecordNum = ExecuteQuery(str.GetBuffer());

	if (pItemArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{
			//ITEM_ID
			pItemArray[nIndex].nItemId = GetIntValue(nIndex,0);
			//APP_ID
			strncpy_s(pItemArray[nIndex].AppID,GetStringValue(nIndex,1,&length),LENGTH_20);
			//ITEM_NAME
			strncpy_s(pItemArray[nIndex].ItemName,GetStringValue(nIndex,2,&length),LENGTH_50);
			//ITEM_TYPE
			pItemArray[nIndex].nItemType = GetIntValue(nIndex,3);
			//REMARK
			strncpy_s(pItemArray[nIndex].Remark,GetStringValue(nIndex,4,&length),LENGTH_100);
		}
	}
	return nRecordNum;
}
//应用-事项流程
bool PlatformDB::SaveFlow(sAppFlow* pFlow,bool bModify)
{
	bool bResult =  false;
	CString str = "";

	if (pFlow==NULL)
	{
		return bResult;
	}
	//保存新记录
	if (!bModify)
	{
		str.Format("insert into APP_FLOW(ITEM_ID,FLOW_ORDER,FLOW_NAME,PROMPT,IS_AUTO_EXECUTE,\
			IS_SEND_MESSAGE,MESSAGE,SEND_TYPE)values(%d,%d,'%s','%s',%d,%d,'%s','%s')",
			pFlow->nItemId,pFlow->nOrder,pFlow->FlowName,pFlow->Prompt,pFlow->IsAutoExecute,
			pFlow->IsSendMessage,pFlow->Message,pFlow->SendType);
	}
	else
	{
		str.Format("update APP_FLOW set FLOW_ORDER=%d, FLOW_NAME='%s',PROMPT='%s',IS_AUTO_EXECUTE=%d,\
				   IS_SEND_MESSAGE=%d,MESSAGE='%s',SEND_TYPE='%s' where FLOW_ID=%d",
				   pFlow->nOrder,pFlow->FlowName,pFlow->Prompt,pFlow->IsAutoExecute,pFlow->IsSendMessage,
				   pFlow->Message,pFlow->SendType,pFlow->nFlowId);
	}

	bResult = ExecuteNoQuery(str.GetBuffer());
	return  bResult;
}

bool PlatformDB::RemoveFlow(sAppFlow* pFlow)
{
	CString str = "";
	bool bResult =  false;

	if (pFlow != NULL)
	{
		str.Format("delete from APP_FLOW where FLOW_ID=%d",pFlow->nFlowId);

		bResult = ExecuteNoQuery(str.GetBuffer(str.GetLength()));
	}

	return bResult;
}

int PlatformDB::ReadItemFlows(int nItemId,sAppFlow* pFlowArray)
{
	CString str = "";
	int nRecordNum = 0;
	
	if (nItemId<=0)
	{
		str.Format("select * from APP_FLOW");
	}
	else
	{
		str.Format("select * from APP_FLOW where ITEM_ID=%d",nItemId);
	}
	
	nRecordNum = ExecuteQuery(str.GetBuffer());

	if (pFlowArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{
			//FLOW_ID
			pFlowArray[nIndex].nFlowId = GetIntValue(nIndex,0);
			//ITEM_ID
			pFlowArray[nIndex].nItemId = GetIntValue(nIndex,1);
			//FLOW_ORDER
			pFlowArray[nIndex].nOrder = GetIntValue(nIndex,2);
			//FLOW_NAME
			strncpy_s(pFlowArray[nIndex].FlowName,GetStringValue(nIndex,3,&length),LENGTH_50);
			//PROMPT
			strncpy_s(pFlowArray[nIndex].Prompt,GetStringValue(nIndex,4,&length),LENGTH_100);
			//IS_AUTO_EXECUTE
			pFlowArray[nIndex].IsAutoExecute = GetBoolValue(nIndex,5);
			//IS_SEND_MESSAGE
			pFlowArray[nIndex].IsSendMessage = GetBoolValue(nIndex,6);
			//MESSAGE
			strncpy_s(pFlowArray[nIndex].Message,GetStringValue(nIndex,7,&length),LENGTH_100);
			//SEND_TYPE
			strncpy_s(pFlowArray[nIndex].SendType,GetStringValue(nIndex,8,&length),4);
		}
	}

	return nRecordNum;
}

int PlatformDB::GetLastInsertId()
{
	CString str = "select @@IDENTITY";
	ExecuteQuery(str.GetBuffer());

	int nId = GetIntValue(0,0);
	
	return nId;
}
sDateTime PlatformDB::Str2DateTime(CString str)
{
	char dt[20];
	memset(dt,0,20);
	memcpy(dt,(LPCSTR)str,str.GetLength());

	sDateTime dTime;

	char temp[5];
	memset(temp,0,5);
	temp[0] = dt[0];
	temp[1] = dt[1];
	temp[2] = dt[2];
	temp[3] = dt[3];

	dTime.nYear = atoi(temp);

	memset(temp,0,5);
	temp[0] = dt[5];
	temp[1] = dt[6];
	dTime.nMonth = atoi(temp);
	
	memset(temp,0,5);
	temp[0] = dt[8];
	temp[1] = dt[9];
	dTime.nDay = atoi(temp);
	
	memset(temp,0,5);
	temp[0] = dt[11];
	temp[1] = dt[12];
	dTime.nHour = atoi(temp);

	memset(temp,0,5);
	temp[0] = dt[14];
	temp[1] = dt[15];
	dTime.nMinute = atoi(temp);

	memset(temp,0,5);
	temp[0] = dt[16];
	temp[1] = dt[17];
	dTime.nSecond = atoi(temp);

	return dTime;
}

bool PlatformDB::SaveMsgPolicy(sDispatchPolicy* pPolicy)
{
	bool bResult =  false;
	CString str = "";

	if(pPolicy == NULL)
	{
		return false;
	}
	str = "select * from MSG_DISPATCH_POLICY";

	int nRecordNum = ExecuteQuery(str.GetBuffer());
	
	//存在记录，查询记录ID（只取第一条记录）
	if (nRecordNum > 0)
	{
		pPolicy->nID = GetIntValue(0,0);

		str.Format("update MSG_DISPATCH_POLICY set SYS_POLICY='%s', APP_POLICY='%s',USER_POLICY='%s',APP_MSG_LIMIT=%d,\
				   USER_MSG_LIMIT=%d,INIT_SCORE=%d,SUB_SCORE=%d where ID=%d",
				   pPolicy->SysMsgPolicy,pPolicy->AppMsgPolicy,pPolicy->UserMsgPolicy,pPolicy->nAppMsgLimited,
				   pPolicy->nUserMsgLimited,pPolicy->nInitScore,pPolicy->nSubScore,pPolicy->nID);
	}
	else
	{
		str.Format("insert into MSG_DISPATCH_POLICY(SYS_POLICY,APP_POLICY,USER_POLICY,APP_MSG_LIMIT,USER_MSG_LIMIT,\
				   INIT_SCORE,SUB_SCORE)values('%s','%s','%s',%d,%d,%d,%d)",
				   pPolicy->SysMsgPolicy,pPolicy->AppMsgPolicy,pPolicy->UserMsgPolicy,pPolicy->nAppMsgLimited,
				   pPolicy->nUserMsgLimited,pPolicy->nInitScore,pPolicy->nSubScore);
	}


	bResult = ExecuteNoQuery(str.GetBuffer());
	return  bResult;
}

bool PlatformDB::ReadMsgPolicy(sDispatchPolicy* pPolicy)
{
	bool bResult =  false;
	CString str = "select * from MSG_DISPATCH_POLICY";

	if(pPolicy == NULL)
	{
		return false;
	}

	unsigned int length = 0;
	int nRecordNum = ExecuteQuery(str.GetBuffer());
	//取第一条记录
	if (nRecordNum>0)
	{
		pPolicy->nID = GetIntValue(0,0);
		strncpy_s(pPolicy->SysMsgPolicy,GetStringValue(0,1,&length),5);
		strncpy_s(pPolicy->AppMsgPolicy,GetStringValue(0,2,&length),5);
		strncpy_s(pPolicy->UserMsgPolicy,GetStringValue(0,3,&length),5);
		
		pPolicy->nAppMsgLimited = GetIntValue(0,4);
		pPolicy->nUserMsgLimited = GetIntValue(0,5);
		pPolicy->nInitScore = GetIntValue(0,6);
		pPolicy->nSubScore = GetIntValue(0,7);
		return true;
	}

	return false;
}

bool PlatformDB::SaveKeyword(CString keyword)
{
	CString str = "select * from KEYWORDS where KEYWORD="+keyword;

	int nRecordNum = ExecuteQuery(str.GetBuffer());

	if(nRecordNum>0)
	{
		return false;
	}
	else
	{
		str.Format("insert into KEYWORDS(KEYWORD) values ('%s')",keyword);
		return ExecuteNoQuery(str.GetBuffer());
	}
}
bool PlatformDB::DeleteKeyword(CString keyword)
{
	CString str = "delete from KEYWORDS where KEYWORD='"+keyword+"'";
	return ExecuteNoQuery(str.GetBuffer());
}
bool PlatformDB::ReadAllKeywords(vector<CString>& KeywordArray)
{
	unsigned int length = 0;
	CString str = "select * from KEYWORDS";
	int nRecordNum = ExecuteQuery(str.GetBuffer());

	KeywordArray.clear();

	for (int nIndex=0; nIndex<nRecordNum; nIndex++)
	{
		KeywordArray.push_back(GetStringValue(nIndex,0,&length));
	}

	return true;
}
//以下对消息进行管理
int PlatformDB::ReadAllUserMsg(sTextMessage* pMsgArray)
{
	CString str = "select * from MSG_USER_MSG";
	int nRecordNum = ExecuteQuery(str.GetBuffer());

	if (pMsgArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{
			//FLOW_ID
			pMsgArray[nIndex].nMsgID = GetIntValue(nIndex,0);
			strncpy_s(pMsgArray[nIndex].senderID,GetStringValue(nIndex,1,&length),LENGTH_20);
			strncpy_s(pMsgArray[nIndex].receiverID,GetStringValue(nIndex,2,&length),LENGTH_20);
			pMsgArray[nIndex].timeStap = GetLongValue(nIndex,3);
			pMsgArray[nIndex].expiration = GetLongValue(nIndex,4);
			pMsgArray[nIndex].priority = GetIntValue(nIndex,5);

			strncpy_s(pMsgArray[nIndex].msgType,GetStringValue(nIndex,6,&length),LENGTH_20);
			strncpy_s(pMsgArray[nIndex].title,GetStringValue(nIndex,7,&length),LENGTH_100);
			strncpy_s(pMsgArray[nIndex].content,GetStringValue(nIndex,8,&length),LENGTH_1024);
			pMsgArray[nIndex].bIsRead = GetBoolValue(nIndex,9);
			pMsgArray[nIndex].nType = 2;
		}
	}

	return nRecordNum;
}
int PlatformDB::ReadAllAppMsg(sTextMessage* pMsgArray)
{
	CString str = "select * from MSG_APP_MSG";
	int nRecordNum = ExecuteQuery(str.GetBuffer());

	if (pMsgArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{
			//FLOW_ID
			pMsgArray[nIndex].nMsgID = GetIntValue(nIndex,0);
			strncpy_s(pMsgArray[nIndex].senderID,GetStringValue(nIndex,1,&length),LENGTH_20);
			strncpy_s(pMsgArray[nIndex].receiverID,GetStringValue(nIndex,2,&length),LENGTH_20);
			pMsgArray[nIndex].timeStap = GetLongValue(nIndex,3);
			pMsgArray[nIndex].expiration = GetLongValue(nIndex,4);
			pMsgArray[nIndex].priority = GetIntValue(nIndex,5);

			strncpy_s(pMsgArray[nIndex].msgType,GetStringValue(nIndex,6,&length),LENGTH_20);
			strncpy_s(pMsgArray[nIndex].title,GetStringValue(nIndex,7,&length),LENGTH_100);
			strncpy_s(pMsgArray[nIndex].content,GetStringValue(nIndex,8,&length),LENGTH_1024);
			pMsgArray[nIndex].bIsRead = GetBoolValue(nIndex,9);
			pMsgArray[nIndex].nType = 1;
		}
	}

	return nRecordNum;
}
int PlatformDB::ReadAllSysMsg(sTextMessage* pMsgArray)
{
	CString str = "select * from MSG_SYS_MSG";
	int nRecordNum = ExecuteQuery(str.GetBuffer());

	if (pMsgArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{
			//FLOW_ID
			pMsgArray[nIndex].nMsgID = GetIntValue(nIndex,0);
			strncpy_s(pMsgArray[nIndex].senderID,GetStringValue(nIndex,1,&length),LENGTH_20);
			strncpy_s(pMsgArray[nIndex].receiverID,GetStringValue(nIndex,2,&length),LENGTH_20);
			pMsgArray[nIndex].timeStap = GetLongValue(nIndex,3);
			pMsgArray[nIndex].expiration = GetLongValue(nIndex,4);
			pMsgArray[nIndex].priority = GetIntValue(nIndex,5);

			strncpy_s(pMsgArray[nIndex].msgType,GetStringValue(nIndex,6,&length),LENGTH_20);
			strncpy_s(pMsgArray[nIndex].title,GetStringValue(nIndex,7,&length),LENGTH_100);
			strncpy_s(pMsgArray[nIndex].content,GetStringValue(nIndex,8,&length),LENGTH_1024);
			pMsgArray[nIndex].bIsRead = GetBoolValue(nIndex,9);
			pMsgArray[nIndex].nType = 0;
		}
	}

	return nRecordNum;
}
int PlatformDB::ReadHistoryMsg(sTextMessage* pMsgArray)
{
	CString str = "select * from MSG_STORAGE";
	int nRecordNum = ExecuteQuery(str.GetBuffer());

	if (pMsgArray == NULL)
	{
		return nRecordNum;	
	}
	else
	{
		unsigned length = 0;
		for (int nIndex=0; nIndex<nRecordNum; nIndex++)
		{
			//FLOW_ID
			pMsgArray[nIndex].nMsgID = GetIntValue(nIndex,0);
			strncpy_s(pMsgArray[nIndex].senderID,GetStringValue(nIndex,1,&length),LENGTH_20);
			strncpy_s(pMsgArray[nIndex].receiverID,GetStringValue(nIndex,2,&length),LENGTH_20);
			pMsgArray[nIndex].timeStap = GetLongValue(nIndex,3);
			pMsgArray[nIndex].expiration = GetLongValue(nIndex,4);
			pMsgArray[nIndex].priority = GetIntValue(nIndex,5);

			strncpy_s(pMsgArray[nIndex].msgType,GetStringValue(nIndex,6,&length),LENGTH_20);
			strncpy_s(pMsgArray[nIndex].title,GetStringValue(nIndex,7,&length),LENGTH_100);
			strncpy_s(pMsgArray[nIndex].content,GetStringValue(nIndex,8,&length),LENGTH_1024);
			pMsgArray[nIndex].nType = GetIntValue(nIndex,9);
		}
	}

	return nRecordNum;
}

bool PlatformDB::RemoveUserMsg(int nMsgID)
{
	CString str;
	str.Format("delete from MSG_USER_MSG where ID=%d",nMsgID);
	return ExecuteNoQuery(str.GetBuffer());
}

bool PlatformDB::RemoveAppMsg(int nMsgID)
{
	CString str;
	str.Format("delete from MSG_APP_MSG where ID=%d",nMsgID);
	return ExecuteNoQuery(str.GetBuffer());
}

bool PlatformDB::RemoveSysMsg(int nMsgID)
{
	CString str;
	str.Format("delete from MSG_SYS_MSG where ID=%d",nMsgID);
	return ExecuteNoQuery(str.GetBuffer());
}

bool PlatformDB::RemoveHistoryMsg(int nMsgID)
{
	CString str;
	str.Format("delete from MSG_STORAGE where ID=%d",nMsgID);
	return ExecuteNoQuery(str.GetBuffer());
}