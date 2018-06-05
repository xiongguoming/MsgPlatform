#include "mysql.h"
#include <Afxmt.h>
#include <afxsock.h>

/*
#pragma comment(lib,"Debug\\lib\\libmysql.lib")
#pragma comment(lib,"Debug\\lib\\mysqlclient.lib")
#pragma comment(lib,"Debug\\lib\\mysys-max.lib")
#pragma comment(lib,"Debug\\lib\\mysys-nt.lib")
#pragma comment(lib,"Debug\\lib\\regex.lib")
#pragma comment(lib,"Debug\\lib\\strings.lib")
#pragma comment(lib,"Debug\\lib\\zlib.lib")
*/
#define DEFAULT_FIELD        32  //����Ҫ�����Ŀ��У����ݱ�������ֶ�����
#define DEFAULT_FIELD_SIZE   32  //ÿ���ֶ����Ƶ�����ֽ���

class MySqlOperate
{
public:
	MySqlOperate();
	~MySqlOperate();

	//����MySql������,
	bool Connect(char * host,char * name,char *pwd,char * db,unsigned port);

	//ִ�зǲ�ѯ���,���سɹ���ʧ��
	bool ExecuteNoQuery(char ** sqlArray,int count);
	bool ExecuteNoQuery(char* sql);
	//ִ�в�ѯ��䣬���ز�ѯ��������������������Ҫ����FreeResult�ͷŽ��
	//���������FreeResult�������´β�ѯʱ�Զ��ͷ��ϴεĽ����
	unsigned ExecuteQuery(char * sql);
	//�ͷŲ�ѯ�Ľ����
	void FreeResult();
     
	//�ı��û���ʹ��ȱʡdb�����dbΪ�գ���ʹ��
	bool ChangeUser(char * name,char *pwd,char *db);

	//�Ե�ǰ�û�����ݣ������������ݿ�
	bool SelectDB(char * db);

	//�ر�����
	void Close();

	//ִ�д������ķ�SELECT SQL���
	//�����ĸ������޷���4.1���µİ汾��ʹ��
	bool ExecutePrepare(char * sql);
	bool BindParam(MYSQL_BIND * bind);
    unsigned Execute();
	bool ClosePrepare();


	//���ָ���к�ָ���е�����ֵ
	//���ж���0��ʼ���
    // row     ���к�
    // fd_name ��������
    // fd_num  �����ֶκ�
    // ע��    ��Get**Valueϵ�к����Ĳ���Ҫȷ����ȷ�����򲻱�֤����ֵ����ȷ
	int GetIntValue(int row, char * fd_name);
	int GetIntValue(int row, int fd_num);
	//������
	long GetLongValue(int row, char * fd_name);
	long GetLongValue(int row, int fd_num);

	//��÷�����ֵ
	//��0��ʼ���
	float GetFloatValue(int row,char * fd_name);
	float GetFloatValue(int row,int fd_num);

	//��ø߾��ȷ�����ֵ
	//��0��ʼ���
	double GetDoubleValue(int row,char * fd_name);
	double GetDoubleValue(int row,int fd_num);

	//��ò�����ֵ
	//��0��ʼ���
	bool GetBoolValue(int row,char * fd_name);
	bool GetBoolValue(int row,int fd_num);

	//����ַ���ֵ�������ַ�������
	//��0��ʼ���
	char * GetStringValue(int row,char * fd_name, unsigned * len);
    char * GetStringValue(int row,int fd_num,unsigned * len);

	//�������ʱ�������ݣ����ַ�����ʽ��ʾ
	//��0��ʼ���
	//��ʽ���£�0000-00-00 00:00:00
	char * GetDataTimeValue(int row,char * fd_name);
	char * GetDataTimeValue(int row, int fd_num);

	//��ö��������ݵĻ�����
	//��0��ʼ��ţ������ݸ�pBuf==NULLʱ����û���������
	int GetBinaryValue(int row,char * fd_name,char * pBuf);
	int GetBinaryValue(int row,int fd_num,char * pBuf);

private:
	//MySql�����Ӿ��
	MYSQL ConMySQL;
	//MySqlԤ������
	MYSQL_STMT *myStmt;
	//MySql�Ľ����
	MYSQL_RES *result;
	//�洢��ѯ�������HashTable
	CMapWordToPtr res;
	//����
	char m_pwd[32];
public:
	char m_host[32];
	char m_name[32];
	unsigned m_port;
};