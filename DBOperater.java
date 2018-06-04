package com.dbmanager;

import java.sql.*;
import java.util.*;

import com.pojo.MsgPolicy;
import com.pojo.UserInfo;

public class DBOperater
{
	//���ݿ��û���
	private static String userName="root";
	//���ݿ�����
	private static String password="45092209";
	//���ݿ��URL�������������ݿ���ʹ�õı����ʽ
	private static String url="jdbc:mysql://localhost:3306/msg_platform?useUnicode=true&characterEncoding=gb2312";
	//������
	private static String driverName = "com.mysql.jdbc.Driver";
	//����һ�����Ӷ���
	private static Connection dbConn;
	//���� ����� 0=�޴���-1�д���
	private int errNum;
	//������Ϣ��
	private String errDesc;
	//��¼��ѯ���
	@SuppressWarnings("unused")
	private ArrayList<HashMap<String, String>> queryRS;
	//��������ID
	private int autoIncKey = 0;
	
	protected MsgPolicy policy = new MsgPolicy();

	//��ʼ������
	public DBOperater()
	{
		if((dbConn=getConnection()) == null)
		{
			System.out.print("�������ݿ�ʧ��!\n");
		}
		else
		{
			policy = ReadMsgPolicy();
			//System.out.print("��ǰ���ݿ���������"+String.valueOf(getConNum())+"\n");
		}
		errNum = 0;
		errDesc = "";
		queryRS = new ArrayList<HashMap<String, String>>();
	}
	protected void finalize()
	{
		closeDB();
	}
	//�鿴���ݿ�������(����)
	public int getConNum()
	{
		int num = -1;
		String sqlString = "select count(*) from v$session";
		
		try 
		{
			ResultSet rs = executQuery(sqlString);
			num = rs.getInt(1);
			rs.close();
			return num; 
		} catch (SQLException e) {
			e.printStackTrace();
			return num;
		}
	}
	//�������ݿ�
   	public static Connection getConnection()
   	{
   		if(dbConn != null)
   		{
   			return dbConn;
   		}
   		try
	   	{ 
			//�������õ����
			Class.forName(driverName);
			//������ݿ�����Ӷ���
			dbConn = DriverManager.getConnection(url,userName,password);
			//�����Զ��ύ����
			dbConn.setAutoCommit(true);
	   	}
	   	catch(Exception ex)
	   	{	   		
	   		dbConn = null;   		
	   	}
	   	return dbConn;
    }
	//ִ��sql ִ����䣬��Ҫ��ִ�в����ɾ����SQL���
	public boolean executUpdate(String strSql)
	{
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try 
        {
            pstmt = dbConn.prepareStatement(strSql);
            
            int result = pstmt.executeUpdate();
            if(result <0)
            {
            	pstmt.close();
            	return false;
            }
            
            autoIncKey = -1;  
		    rs = pstmt.executeQuery("SELECT LAST_INSERT_ID()");             
		    if (rs.next()) 
		    {  
		    	autoIncKey = rs.getInt(1);  
		    }  
		    rs.close();
		    pstmt.close();
            return true;
        } 
        catch (Exception e) 
        {
        	this.errNum = -1;
			this.errDesc = e.toString();
            e.printStackTrace();
            return false;
        }
	}

	//ִ��sql ��ѯ���    
    public ResultSet executQuery(String strSql) throws SQLException
	{
    	PreparedStatement pstmt = null;
        ResultSet rs = null;
		try
		{
			pstmt=dbConn.prepareStatement(strSql);
			rs =pstmt.executeQuery();			            
		}
		catch(Exception ex)
		{
            this.errNum = -1;
            this.errDesc = ex.toString();
		}
		 return rs;
	}
    
	//������������ID
	public int getAutoIncKey()
	{
		return autoIncKey;
	}
    //�ر����ݿ�����
    public void closeDB()
    {  
    	try
    	{
    		dbConn.close();
    		dbConn = null;
    	}
    	catch(SQLException e)
        {  
            e.printStackTrace();  
        }  
    }
    //�������ݿ���ֶ���������ֵ�����͡�������������SQL
  	public String getSqlString(String tableName, HashMap<String,Object> filedValues,String optType)
  	{
  		String sqlString = "";
  		//insert
  		if(optType.equals("insert"))
  		{
  			sqlString = "insert into "+tableName;
  			//�ֶ��б�
  			String tempKeys = "(";
  			String tempValues = "";
  			Set set = filedValues.keySet();
  			for(Iterator ita = set.iterator(); ita.hasNext();)
  			{
  				String key = (String)ita.next();
  				tempKeys += key;
  				
  				Object value = (Object)filedValues.get(key);
  				//���ַ����⣬�����Ķ��������� 
  				if (value instanceof String) 
  				{
  					tempValues += "'"+value.toString()+"'";
  				}
  				else
  				{
  					tempValues += value.toString();
  				}
  				if(ita.hasNext())
  				{
  					tempKeys += ",";
  					tempValues += ",";
  				}
  			}
  			tempKeys += ")";
  			tempValues += ")";
  			
  			sqlString += tempKeys;
  			sqlString += " values (";
  			sqlString += tempValues;
  		}
  		
  		return sqlString;
  	}
    //ȡ�ô������ 
    public int getErrNum()
    {
        return errNum;
    }
    //ȡ�ô�����Ϣ
    public String getErrDesc()
    {
        return errDesc;
    }
    public MsgPolicy ReadMsgPolicy()
    {
    	MsgPolicy policy = new MsgPolicy();
		String sqlString = "select * from MSG_DISPATCH_POLICY";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs != null && rs.next())
			{
				policy.setSysMsgPolicy(rs.getString(2));
				policy.setAppMsgPolicy(rs.getString(3));
				policy.setUserMsgPolicy(rs.getString(4));
				policy.setAppMsgLimit(rs.getInt(5));
				policy.setUserMsgLimit(rs.getInt(6));	
				policy.setInitScore(rs.getInt(7));
				policy.setSubScore(rs.getInt(8));
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
		}
		return policy;
    }
}
