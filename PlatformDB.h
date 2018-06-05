// PlatformDB.h: interface for the PlatformDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLATFORMDB_H__364BD4E5_E4BD_47AA_9524_6AAE55CA2EE9__INCLUDED_)
#define AFX_PLATFORMDB_H__364BD4E5_E4BD_47AA_9524_6AAE55CA2EE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MySQLOperate.h"
#include "DataDefine.h"

class PlatformDB : public MySqlOperate 
{
public:
	PlatformDB();
	virtual ~PlatformDB();

	void CreateTables();
	bool DropTables(char* tableName);
	void CreateTriggers();

	bool SaveMsgPolicy(sDispatchPolicy* pPolicy);
	bool ReadMsgPolicy(sDispatchPolicy* pPolicy);

	//��λ
	bool SaveUnit(sUnitInfo* pUnit,bool bModify=false);
	bool RemoveUnit(sUnitInfo* pUnit);
	int ReadAllUnits(sUnitInfo* pUnitArray);
	bool RemoveAllUnits();
	//�û�
	bool SaveUser(sUserInfo* pUser,bool bModify=false);
	bool RemoveUser(sUserInfo* pUser);
	int ReadAllUsers(sUserInfo* pUserArray);
	bool RemoveAllUsers();

	//Ӧ��
	bool SaveApp(sAppInfo* pApp,bool bModify=false);
	bool RemoveApp(sAppInfo* pApp);
	bool ReadAppInfo(char* appId,sAppInfo* pAppInfo);
	int ReadAllApps(sAppInfo* pAppArray);
	bool RemoveAllApps();
	bool updateAppStatus(sAppInfo* pApp);
	bool IsAppExist(sAppInfo* pApp);

	//Ӧ��-����
	bool SaveItem(sAppItem* pItem,bool bModify=false);
	bool RemoveItem(sAppItem* pItem);
	int ReadAppItems(char* appId,sAppItem* pItemArray);
	bool ReadItemInfo(int nItemId,sAppItem* pItemInfo);

	//Ӧ��-��������
	bool SaveFlow(sAppFlow* pFlow,bool bModify=false);
	bool RemoveFlow(sAppFlow* pFlow);
	int ReadItemFlows(int nItemId,sAppFlow* pFlowArray);

	//��Ϣ����
	int ReadAllUserMsg(sTextMessage* pMsgArray);
	int ReadAllAppMsg(sTextMessage* pMsgArray);
	int ReadAllSysMsg(sTextMessage* pMsgArray);
	int ReadHistoryMsg(sTextMessage* pMsgArray);
	bool RemoveUserMsg(int nMsgID);
	bool RemoveAppMsg(int nMsgID);
	bool RemoveSysMsg(int nMsgID);
	bool RemoveHistoryMsg(int nMsgID);

	//��������
	sDateTime Str2DateTime(CString str);
	//�õ�����������ID
	int GetLastInsertId();
	//�ؼ���
	bool SaveKeyword(CString keyword);
	bool DeleteKeyword(CString keyword);
	bool ReadAllKeywords(vector<CString>& KeywordArray);

private:
	sDispatchPolicy m_policy;
	
};

#endif // !defined(AFX_PLATFORMDB_H__364BD4E5_E4BD_47AA_9524_6AAE55CA2EE9__INCLUDED_)
