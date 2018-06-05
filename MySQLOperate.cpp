// MySql.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "MySql.h"

//һ���ֶνṹ
typedef struct _FIELDS
{
	char field_name[DEFAULT_FIELD_SIZE];//�ֶ���
	void * filed_value;					//�ֶ�ֵ��ָ��
	unsigned value_len;					//�ֶεĳ��ȣ�ֻ�������ַ�������
}FIELDS,*PFIELDS;

//һ�����ݵĽṹ����
typedef struct _ROWS{
    FIELDS fields[DEFAULT_FIELD];		//�ֶ�,���ݲ�ͬ��Ӧ�ó�������޸Ĵ�ֵ
	int cnt;							//���ٸ��ֶΣ�ָʾfield��Ԫ�ص���Ч����
}ROWS,*PROWS;


MySqlOperate::MySqlOperate()
{
	result=NULL;
	memset(m_host,0,32);
	memset(m_name,0,32);
	memset(m_pwd,0,32);
	m_port=0;
	mysql_init(&ConMySQL);

	//�������ӳ�ʱ
	unsigned timeout=5*60;
	mysql_options(&ConMySQL, MYSQL_OPT_CONNECT_TIMEOUT, (char *)&timeout);
	
	//����������
	my_bool reconnect=TRUE;
    mysql_options(&ConMySQL, MYSQL_OPT_RECONNECT, (char *)&reconnect);

	//��ʼ��HashTable��СΪ100
	res.InitHashTable(100);
}

MySqlOperate::~MySqlOperate()
{
	Close();
}

//����MySql������
bool MySqlOperate::Connect(char* host,char* name,char* pwd,char* db,unsigned port)
{
	bool bRet=true;
	strncpy_s(m_host,host,32);
	strncpy_s(m_name,name,32);
	strncpy_s(m_pwd,pwd,32);
	m_port=port;

	do
	{
		//���ӷ�����
		if(mysql_real_connect(&ConMySQL,host,name,pwd,db,port,NULL,0)==NULL)
		{
			bRet=false;
			break;
		}
		
		//���������ַ�����Ĭ��Ϊgb2312
		if(mysql_set_character_set(&ConMySQL, "gb2312"))
		{
			bRet=false;
			Close();
			break;
		}

		//������������֧��
		mysql_set_server_option(&ConMySQL, MYSQL_OPTION_MULTI_STATEMENTS_ON);

	}while(0);

	return bRet;
}

//ִ�зǲ�ѯ���(�������)
bool MySqlOperate::ExecuteNoQuery(char** sqlArray,int count)
{
	bool uRet=true;
	
	//�����Զ��ύģʽ
    mysql_autocommit(&ConMySQL, 0); 

	for(int i=0;i<count;i++)
	{
		mysql_query(&ConMySQL,sqlArray[i]);
	}

	//���û�гɹ�
	if(mysql_commit(&ConMySQL))
	{
		mysql_rollback(&ConMySQL);
		uRet=false;
	}

	//�ָ��Զ��ύģʽ
	mysql_autocommit(&ConMySQL, 1); 
	return uRet;
}

//ִ�зǲ�ѯ���(һ�����)
bool MySqlOperate::ExecuteNoQuery(char* sql)
{
	bool uRet=true;

	//�����Զ��ύģʽ
	mysql_autocommit(&ConMySQL, 0); 
	//ִ��sql���
	int nRes = mysql_query(&ConMySQL,sql);
	
	//���û�гɹ�
	if(nRes!=0||mysql_commit(&ConMySQL))
	{
		mysql_rollback(&ConMySQL);
		uRet=false;
	}

	//�ָ��Զ��ύģʽ
	mysql_autocommit(&ConMySQL, 1); 
	return uRet;
}

//ִ�в�ѯ���
unsigned MySqlOperate::ExecuteQuery(char* sql)
{
	unsigned uLine = 0;
	unsigned uField = 0;
	PROWS rows = NULL;
	MYSQL_ROW row = NULL;
	MYSQL_FIELD *pField = NULL;

    //�ͷ�ǰһ�εĽ����
	FreeResult();

    int nRes = mysql_query(&ConMySQL,sql);
    result=mysql_store_result(&ConMySQL);

    if(nRes!=0||result==NULL)
	{
		return 0;
	}

    //�������
    uLine = (unsigned)mysql_num_rows(result);
    //����ֶ���
    uField = (unsigned)mysql_num_fields(result);
	
	if (uLine==0||uField==0)
	{
		return 0;
	}

   //�������
   for(int i=0; i<(int)uLine; i++)
   {
		rows = (PROWS)malloc(sizeof(ROWS));
		rows->cnt = uField;
		
		//��ȡһ������
		row = mysql_fetch_row(result);

		for(int j=0; j<(int)uField; j++)
		{
			//��ø��е������Ϣ
			pField = mysql_fetch_field_direct(result, j);

			strncpy_s(rows->fields[j].field_name,pField->name,32);
			rows->fields[j].filed_value = row[j];
			rows->fields[j].value_len = pField->max_length;
		}

		//��һ�����ݴ洢��HashTable��
		res.SetAt(i,(void*)(rows));
   }

   //��������
   return uLine;
}

//�ͷŲ�ѯ�Ľ����
void MySqlOperate::FreeResult()
{
	int len = 0;
	PROWS rows = NULL;
	len = res.GetCount();
	
	//�ͷŽ�������ڴ�
	for(int i=0;i<len;i++)
	{
		rows = (PROWS)res[i];
		if(rows!=NULL)
		{
			free(rows); 
			rows = NULL;
		}
	}

	//���HashTable
	res.RemoveAll();
	//�ͷ�result
	if(result != NULL)
	{
		mysql_free_result(result);
	}
	result = NULL;
}

//ִ�д�������SQL��亯��
bool MySqlOperate::ExecutePrepare(char* sql)
{
	bool bRet=true;
	do
	{
		//��ʼ�����
		myStmt=mysql_stmt_init(&ConMySQL);
		if (!myStmt)
		{
			bRet=false;
			break;
		}
		//׼��SQL
		if (mysql_stmt_prepare(myStmt, sql, strlen(sql)))
		{
			bRet=false;
			break;
		}
	}while(0);
	return bRet;
}

bool MySqlOperate::BindParam(MYSQL_BIND* bind)
{
	bool bRet=true;
	if (mysql_stmt_bind_param(myStmt, bind))
	{
       bRet=false;
	}
	return bRet;

}

unsigned MySqlOperate::Execute()
{
	unsigned uRet=0;
	do
	{
		if (mysql_stmt_execute(myStmt))
		{
			uRet=0;
			break;
		}

		//�����Ӱ������� 
		uRet=(unsigned)mysql_stmt_affected_rows(myStmt);

	}while(0);

	return uRet;
}

bool MySqlOperate::ClosePrepare()
{
	bool bRet=true;

	//�رվ��
	if (mysql_stmt_close(myStmt))
	{
       bRet=false;
	}
	return bRet;
}

//�ı��û�
bool MySqlOperate::ChangeUser(char* name,char* pwd,char* db)
{
	bool bRet=true;

	//���ʧ�ܣ�����FALSE
	if(mysql_change_user(&ConMySQL, name, pwd, db) )
	{
		bRet=false;
	}
	return bRet;
}

//ѡ�����ݿ�
bool MySqlOperate::SelectDB(char* db)
{
	bool bRet=true;
	if(mysql_select_db(&ConMySQL, db))
	{
		bRet=false;
	}
	return bRet;
}


//�ر�
void MySqlOperate::Close()
{
    FreeResult();
	mysql_close(&ConMySQL);
}


//��ȡ��ѯ��ֵ
int MySqlOperate::GetIntValue(int row, char* fd_name)
{
	PROWS rows=NULL;
	int len=0;
	int iRet=0;
	char * tmp=NULL;

	len = res.GetCount();
	if(row>=len || fd_name==NULL)
	{
		return 0;
	}
	rows = (PROWS)res[row];
	if(rows == NULL)
	{
		return 0;
	}
	//������
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
			//������ݵ��ַ�����ʾ
			tmp=(char *)rows->fields[i].filed_value;
			//ת��������
			if (tmp == NULL)
			{
				iRet=atoi(tmp);
			}
			else
			{
				iRet = 0;
			}
			break;
		}
	}
	return iRet;
}


int MySqlOperate::GetIntValue(int row, int fd_num)
{
    PROWS rows=NULL;
	int len=0,iRet=0;
	char * tmp=NULL;

	len = res.GetCount();
	if(row>=len)
	{
		return 0;
	}
	rows = (PROWS)res[row];
	if (rows == NULL)
	{
		return 0;
	}

    //������ֵ��ַ�����ʾ
	tmp = (char*)rows->fields[fd_num].filed_value;
	
	if (tmp == NULL)
	{
		iRet = 0;
	}
	else
	{
		iRet = atoi(tmp);
	}
	return iRet;
}

long MySqlOperate::GetLongValue(int row, char* fd_name)
{
	PROWS rows=NULL;
	int len=0;
	long iRet=0;
	char * tmp=NULL;

	len = res.GetCount();
	if(row>=len || fd_name==NULL)
	{
		return 0;
	}
	rows = (PROWS)res[row];
	if(rows == NULL)
	{
		return 0;
	}
	//������
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
			//������ݵ��ַ�����ʾ
			tmp=(char *)rows->fields[i].filed_value;
			//ת��������
			if (tmp == NULL)
			{
				iRet=atol(tmp);
			}
			else
			{
				iRet = 0;
			}
			break;
		}
	}
	return iRet;
}


long MySqlOperate::GetLongValue(int row, int fd_num)
{
	PROWS rows=NULL;
	int len=0;
	long iRet=0;
	char * tmp=NULL;

	len = res.GetCount();
	if(row>=len)
	{
		return 0;
	}
	rows = (PROWS)res[row];
	if (rows == NULL)
	{
		return 0;
	}

	//������ֵ��ַ�����ʾ
	tmp = (char*)rows->fields[fd_num].filed_value;

	if (tmp == NULL)
	{
		iRet = 0;
	}
	else
	{
		iRet = atol(tmp);
	}
	return iRet;
}

//��ø߾��ȷ�����ֵ
double MySqlOperate::GetDoubleValue(int row,char * fd_name)
{
	PROWS rows=NULL;
	int len=0;
	char * tmp=NULL;
	double iRet=0.0;
	len=res.GetCount();
	
	if(row>=len)
	{
		return 0;
	}
	rows = (PROWS)res[row];
	if (rows == NULL)
	{
		return 0;
	}

	//������
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
			tmp=(char *)rows->fields[i].filed_value;
			if (tmp == NULL)
			{
				iRet = 0;
			}
			else
			{
				iRet=atof(tmp);
			}
			break;
		}
	}
	return iRet;
}

double MySqlOperate::GetDoubleValue(int row,int fd_num)
{
	PROWS rows=NULL;
	int len=0;
	char * tmp=NULL;
	double iRet=0.0;

	len=res.GetCount();
	if(row>=len)
	{
		return 0;
	}

	rows = (PROWS)res[row];
	if (rows == NULL)
	{
		return 0;
	}

	tmp=(char *)rows->fields[fd_num].filed_value;
	if (tmp==NULL)
	{
		iRet = 0;
	}
	else
	{
		iRet=atof(tmp);
	}
	
	return iRet;
}

//��ò�����ֵ
bool MySqlOperate::GetBoolValue(int row,char * fd_name)
{
   	PROWS rows=NULL;
	int len=0;
	char * tmp=NULL;
	bool iRet=0;

	len=res.GetCount();
	if(row>=len)
	{
		return 0;
	}
	rows=(PROWS)res[row];
	//������
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
			tmp = (char *)rows->fields[i].filed_value;
			if (tmp == NULL || strcmp(tmp,"0")==0)
			{
				iRet = false;
			}
			else
			{

				iRet = true;//(bool)atoi(tmp);
			}
			break;
		}
	}
	return iRet;
}
bool MySqlOperate::GetBoolValue(int row,int fd_num)
{
	PROWS rows=NULL;
	int len=0;
	bool iRet=0;
	char * tmp=NULL;

	len=res.GetCount();
	if(row>=len)
	{	
		return false;
	}
	rows=(PROWS)res[row];

	if (rows==NULL)
	{
		return false;
	}

	tmp=(char *)rows->fields[fd_num].filed_value;
	
	if (tmp==NULL|| strcmp(tmp,"0")==0)
	{
		iRet= false;
	}
	else
	{
		iRet = true;//(bool)atoi(tmp);
	}
	
	return iRet;
}

char* MySqlOperate::GetStringValue(int row,char * fd_name,unsigned * length)
{
	PROWS rows=NULL;
	int len=0;
	char *p_Tmp=NULL;

	len = res.GetCount();
	if(row>=len || fd_name==NULL || length==NULL)
	{
		return "";
	}

	rows=(PROWS)res[row];
	if (rows == NULL)
	{
		return "";
	}
	//������
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
			*length=(unsigned)(rows->fields[i].value_len);
			p_Tmp=(char *)(rows->fields[i].filed_value);
			break;
		}
	}
	if (p_Tmp!=NULL)
	{
		return p_Tmp;	
	}
	else
	{
		return "";
	}
}
char* MySqlOperate::GetStringValue(int row,int fd_num, unsigned * length)
{
	PROWS rows=NULL;
	int len=0;
	char * p_Tmp=NULL;

	len = res.GetCount();
	if(row>=len || length==NULL)
	{
		return "";
	}

	rows=(PROWS)res[row];

	if(rows == NULL)
	{
		return "";
	}

	//����г���
	*length=(unsigned)rows->fields[fd_num].value_len;
	//ֱ�ӷ��ش��е�ֵ
	p_Tmp=(char *)(rows->fields[fd_num].filed_value);
	if (p_Tmp!=NULL)
	{
		return p_Tmp;	
	}
	else
	{
		return "";
	}
}

//�������ʱ��������
char* MySqlOperate::GetDataTimeValue(int row,char * fd_name)
{
	PROWS rows=NULL;
	int len=0;
	char * pTime=NULL;

	len = res.GetCount();
	if(row>=len || fd_name==NULL)
	{
		return "2010-01-01 00:00:00";
	}
	rows=(PROWS)res[row];
	if (rows == NULL)
	{
		return "2010-01-01 00:00:00";
	}
	//������
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
			pTime=(char *)(rows->fields[i].filed_value);
			break;
		}
	}
	if (pTime!=NULL)
	{
		return pTime;	
	}
	else
	{
		return "2010-01-01 00:00:00";
	}
}
char* MySqlOperate::GetDataTimeValue(int row, int fd_num)
{
   	PROWS rows=NULL;
	int len=0;
	len=res.GetCount();
	if(row>=len)
	{
		return "2010-01-01 00:00:00";
	}

	rows = (PROWS)res[row];
	
	if (rows==NULL)
	{
		return "2010-01-01 00:00:00";
	}

	char* pTime = (char *)(rows->fields[fd_num].filed_value);

	if (pTime!=NULL)
	{
		return pTime;	
	}
	else
	{
		return "2010-01-01 00:00:00";
	}
}

//��ö��������ݵĻ�����
int MySqlOperate::GetBinaryValue(int row,char * fd_name,char * pBuf)
{
	PROWS rows=NULL;
	int len=0;
	char* p=NULL;

	len = res.GetCount();
	if(row>=len || fd_name==NULL || pBuf==NULL)
	{
		return 0;
	}

	rows = (PROWS)res[row];
	if (rows == NULL)
	{
		return 0;
	}

	//������
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
		    len=(int)rows->fields[i].value_len;
			if(pBuf==NULL)
				break;
			p=(char *)(rows->fields[i].filed_value);
			memcpy(pBuf,p,len);
			break;
		}
	}
	return len;
}

int MySqlOperate::GetBinaryValue(int row,int fd_num,char * pBuf)
{
	PROWS rows=NULL;
	int len=0;
	char * p=NULL;
	len=res.GetCount();
	
	if(row>=len||pBuf==NULL)
	{
		return 0;
	}
	rows=(PROWS)res[row];
	if (rows == NULL)
	{
		return 0;
	}

	len=rows->fields[fd_num].value_len;

	if(pBuf==NULL)
	{
		return len;
	}
	//ֱ�ӷ��ش��е�ֵ
	 p=(char *)(rows->fields[fd_num].filed_value);
	 memcpy(pBuf,p,len);
	 return len;
}
