// MySql.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "MySql.h"

//一个字段结构
typedef struct _FIELDS
{
	char field_name[DEFAULT_FIELD_SIZE];//字段名
	void * filed_value;					//字段值的指针
	unsigned value_len;					//字段的长度，只适用于字符串类型
}FIELDS,*PFIELDS;

//一行数据的结构数组
typedef struct _ROWS{
    FIELDS fields[DEFAULT_FIELD];		//字段,根据不同的应用程序可以修改此值
	int cnt;							//多少个字段，指示field中元素的有效个数
}ROWS,*PROWS;


MySqlOperate::MySqlOperate()
{
	result=NULL;
	memset(m_host,0,32);
	memset(m_name,0,32);
	memset(m_pwd,0,32);
	m_port=0;
	mysql_init(&ConMySQL);

	//设置连接超时
	unsigned timeout=5*60;
	mysql_options(&ConMySQL, MYSQL_OPT_CONNECT_TIMEOUT, (char *)&timeout);
	
	//启动再连接
	my_bool reconnect=TRUE;
    mysql_options(&ConMySQL, MYSQL_OPT_RECONNECT, (char *)&reconnect);

	//初始化HashTable大小为100
	res.InitHashTable(100);
}

MySqlOperate::~MySqlOperate()
{
	Close();
}

//连接MySql服务器
bool MySqlOperate::Connect(char* host,char* name,char* pwd,char* db,unsigned port)
{
	bool bRet=true;
	strncpy_s(m_host,host,32);
	strncpy_s(m_name,name,32);
	strncpy_s(m_pwd,pwd,32);
	m_port=port;

	do
	{
		//连接服务器
		if(mysql_real_connect(&ConMySQL,host,name,pwd,db,port,NULL,0)==NULL)
		{
			bRet=false;
			break;
		}
		
		//设置连接字符集，默认为gb2312
		if(mysql_set_character_set(&ConMySQL, "gb2312"))
		{
			bRet=false;
			Close();
			break;
		}

		//设置允许多语句支持
		mysql_set_server_option(&ConMySQL, MYSQL_OPTION_MULTI_STATEMENTS_ON);

	}while(0);

	return bRet;
}

//执行非查询语句(多条语句)
bool MySqlOperate::ExecuteNoQuery(char** sqlArray,int count)
{
	bool uRet=true;
	
	//撤消自动提交模式
    mysql_autocommit(&ConMySQL, 0); 

	for(int i=0;i<count;i++)
	{
		mysql_query(&ConMySQL,sqlArray[i]);
	}

	//如果没有成功
	if(mysql_commit(&ConMySQL))
	{
		mysql_rollback(&ConMySQL);
		uRet=false;
	}

	//恢复自动提交模式
	mysql_autocommit(&ConMySQL, 1); 
	return uRet;
}

//执行非查询语句(一条语句)
bool MySqlOperate::ExecuteNoQuery(char* sql)
{
	bool uRet=true;

	//撤消自动提交模式
	mysql_autocommit(&ConMySQL, 0); 
	//执行sql语句
	int nRes = mysql_query(&ConMySQL,sql);
	
	//如果没有成功
	if(nRes!=0||mysql_commit(&ConMySQL))
	{
		mysql_rollback(&ConMySQL);
		uRet=false;
	}

	//恢复自动提交模式
	mysql_autocommit(&ConMySQL, 1); 
	return uRet;
}

//执行查询语句
unsigned MySqlOperate::ExecuteQuery(char* sql)
{
	unsigned uLine = 0;
	unsigned uField = 0;
	PROWS rows = NULL;
	MYSQL_ROW row = NULL;
	MYSQL_FIELD *pField = NULL;

    //释放前一次的结果集
	FreeResult();

    int nRes = mysql_query(&ConMySQL,sql);
    result=mysql_store_result(&ConMySQL);

    if(nRes!=0||result==NULL)
	{
		return 0;
	}

    //获得行数
    uLine = (unsigned)mysql_num_rows(result);
    //获得字段数
    uField = (unsigned)mysql_num_fields(result);
	
	if (uLine==0||uField==0)
	{
		return 0;
	}

   //填充结果集
   for(int i=0; i<(int)uLine; i++)
   {
		rows = (PROWS)malloc(sizeof(ROWS));
		rows->cnt = uField;
		
		//获取一行数据
		row = mysql_fetch_row(result);

		for(int j=0; j<(int)uField; j++)
		{
			//获得该列的相关信息
			pField = mysql_fetch_field_direct(result, j);

			strncpy_s(rows->fields[j].field_name,pField->name,32);
			rows->fields[j].filed_value = row[j];
			rows->fields[j].value_len = pField->max_length;
		}

		//将一行数据存储到HashTable中
		res.SetAt(i,(void*)(rows));
   }

   //返回行数
   return uLine;
}

//释放查询的结果集
void MySqlOperate::FreeResult()
{
	int len = 0;
	PROWS rows = NULL;
	len = res.GetCount();
	
	//释放结果集的内存
	for(int i=0;i<len;i++)
	{
		rows = (PROWS)res[i];
		if(rows!=NULL)
		{
			free(rows); 
			rows = NULL;
		}
	}

	//清空HashTable
	res.RemoveAll();
	//释放result
	if(result != NULL)
	{
		mysql_free_result(result);
	}
	result = NULL;
}

//执行带参数的SQL语句函数
bool MySqlOperate::ExecutePrepare(char* sql)
{
	bool bRet=true;
	do
	{
		//初始化句柄
		myStmt=mysql_stmt_init(&ConMySQL);
		if (!myStmt)
		{
			bRet=false;
			break;
		}
		//准备SQL
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

		//获得受影响的行数 
		uRet=(unsigned)mysql_stmt_affected_rows(myStmt);

	}while(0);

	return uRet;
}

bool MySqlOperate::ClosePrepare()
{
	bool bRet=true;

	//关闭句柄
	if (mysql_stmt_close(myStmt))
	{
       bRet=false;
	}
	return bRet;
}

//改变用户
bool MySqlOperate::ChangeUser(char* name,char* pwd,char* db)
{
	bool bRet=true;

	//如果失败，返回FALSE
	if(mysql_change_user(&ConMySQL, name, pwd, db) )
	{
		bRet=false;
	}
	return bRet;
}

//选择数据库
bool MySqlOperate::SelectDB(char* db)
{
	bool bRet=true;
	if(mysql_select_db(&ConMySQL, db))
	{
		bRet=false;
	}
	return bRet;
}


//关闭
void MySqlOperate::Close()
{
    FreeResult();
	mysql_close(&ConMySQL);
}


//获取查询的值
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
	//查找列
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
			//获得数据的字符串表示
			tmp=(char *)rows->fields[i].filed_value;
			//转换成数字
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

    //获得数字的字符串表示
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
	//查找列
	for(int i=0;i<rows->cnt;i++)
	{
		if(!strcmp(rows->fields[i].field_name,fd_name))
		{
			//获得数据的字符串表示
			tmp=(char *)rows->fields[i].filed_value;
			//转换成数字
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

	//获得数字的字符串表示
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

//获得高精度符点型值
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

	//查找列
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

//获得布尔型值
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
	//查找列
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
	//查找列
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

	//获得列长度
	*length=(unsigned)rows->fields[fd_num].value_len;
	//直接返回此列的值
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

//获得日期时间型数据
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
	//查找列
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

//获得二进制数据的缓冲区
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

	//查找列
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
	//直接返回此列的值
	 p=(char *)(rows->fields[fd_num].filed_value);
	 memcpy(pBuf,p,len);
	 return len;
}
