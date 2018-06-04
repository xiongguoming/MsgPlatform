package com.dbmanager;

import java.sql.*;
import java.util.*;

import com.pojo.MsgPolicy;
import com.pojo.UserInfo;

public class DBOperater
{
	//数据库用户名
	private static String userName="root";
	//数据库密码
	private static String password="45092209";
	//数据库的URL，包括连接数据库所使用的编码格式
	private static String url="jdbc:mysql://localhost:3306/msg_platform?useUnicode=true&characterEncoding=gb2312";
	//连接名
	private static String driverName = "com.mysql.jdbc.Driver";
	//定义一个连接对象
	private static Connection dbConn;
	//描述 错误号 0=无错误，-1有错误
	private int errNum;
	//错误信息串
	private String errDesc;
	//记录查询结果
	@SuppressWarnings("unused")
	private ArrayList<HashMap<String, String>> queryRS;
	//自增序列ID
	private int autoIncKey = 0;
	
	protected MsgPolicy policy = new MsgPolicy();

	//初始化操作
	public DBOperater()
	{
		if((dbConn=getConnection()) == null)
		{
			System.out.print("连接数据库失败!\n");
		}
		else
		{
			policy = ReadMsgPolicy();
			//System.out.print("当前数据库连接数："+String.valueOf(getConNum())+"\n");
		}
		errNum = 0;
		errDesc = "";
		queryRS = new ArrayList<HashMap<String, String>>();
	}
	protected void finalize()
	{
		closeDB();
	}
	//查看数据库连接数(出错)
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
	//连接数据库
   	public static Connection getConnection()
   	{
   		if(dbConn != null)
   		{
   			return dbConn;
   		}
   		try
	   	{ 
			//声明所用的类包
			Class.forName(driverName);
			//获得数据库的连接对象
			dbConn = DriverManager.getConnection(url,userName,password);
			//设置自动提交事务
			dbConn.setAutoCommit(true);
	   	}
	   	catch(Exception ex)
	   	{	   		
	   		dbConn = null;   		
	   	}
	   	return dbConn;
    }
	//执行sql 执行语句，主要是执行插入和删除的SQL语句
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

	//执行sql 查询语句    
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
    
	//返回自增序列ID
	public int getAutoIncKey()
	{
		return autoIncKey;
	}
    //关闭数据库链接
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
    //根据数据库表、字段名、传入值及类型、操作类型生成SQL
  	public String getSqlString(String tableName, HashMap<String,Object> filedValues,String optType)
  	{
  		String sqlString = "";
  		//insert
  		if(optType.equals("insert"))
  		{
  			sqlString = "insert into "+tableName;
  			//字段列表
  			String tempKeys = "(";
  			String tempValues = "";
  			Set set = filedValues.keySet();
  			for(Iterator ita = set.iterator(); ita.hasNext();)
  			{
  				String key = (String)ita.next();
  				tempKeys += key;
  				
  				Object value = (Object)filedValues.get(key);
  				//除字符串外，其它的都是数字型 
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
    //取得错误号码 
    public int getErrNum()
    {
        return errNum;
    }
    //取得错误信息
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
