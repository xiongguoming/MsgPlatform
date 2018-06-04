package com.dbmanager;

import java.sql.*;
import com.pojo.SettingInfo;

public class SettingOperater  extends DBOperater
{
	private SettingInfo mySetting;
	
	public void setMySettingInfo(SettingInfo mySetting)
	{
		this.mySetting = mySetting;
	}
	public SettingInfo getMySettingInfo()
	{
		return this.mySetting;
	}
	//根据用户ID获取个人消息设置
	public SettingInfo readMySetting(String userID)
	{
		SettingInfo setting = new SettingInfo();
		
		String sqlString = "select * from user_msg_subscription where USER_ID='"+userID+"'";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return setting;
			}
			//ResultSetMetaData rsdata = rs.getMetaData();
			int rowCount = 0;
			while(rs.next())
			{
				//数据列索引从1开始
				setting.setUserID(rs.getString(2));
				setting.setIsReceiveAllMsg(rs.getBoolean(3));
				setting.setIsReceiveAppMsg(rs.getBoolean(4));
				setting.setIsReceiveUserMsg(rs.getBoolean(5));
				setting.setIsSetReceiveTime(rs.getBoolean(6));
				setting.setStartRecTime(rs.getString(7));
				setting.setEndRecTime(rs.getString(8));
				setting.setSysMsgPolicy(rs.getString(9));
				setting.setAppMsgPolicy(rs.getString(10));
				setting.setUserMsgPolicy(rs.getString(11));
				rowCount++;
				break;
			}
			if(rowCount==0)
			{
				return null;
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			//closeDB();
			return null;
		}
		return setting;
	}
	//保存用户设置
	public boolean saveMySetting()
	{
		boolean result;
		String sqlString = "";
		//记录存在-更新
		if(readMySetting(mySetting.getUserID())!=null)
		{
			sqlString = "update user_msg_subscription set RECEIVE_ALL_MSG="
					+mySetting.getIsReceiveAllMsg()+","+" RECEIVE_APP_MSG="+mySetting.getIsReceiveAppMsg()+","+
					" RECEIVE_USER_MSG="+mySetting.getIsReceiveUserMsg()+","+" SET_RECEIVE_TIME="+mySetting.getIsSetReceiveTime()+","+
					" START_REC_TIME="+"'"+mySetting.getStartRecTime()+"',"+" END_REC_TIME="+"'"+mySetting.getEndRecTime()+"',"+
					" SYS_MSG_POLICY="+"'"+mySetting.getSysMsgPolicy()+"',"+" APP_MSG_POLICY="+"'"+mySetting.getAppMsgPolicy()+"',"+
					" USER_MSG_POLICY="+"'"+mySetting.getUserMsgPolicy()+"'"+
					" where USER_ID="+"'"+mySetting.getUserID()+"'";
		}
		//否则-插入
		else
		{
			sqlString = "insert into user_msg_subscription(USER_ID,RECEIVE_ALL_MSG,RECEIVE_APP_MSG,RECEIVE_USER_MSG,SET_RECEIVE_TIME,"+
						"START_REC_TIME,END_REC_TIME,SYS_MSG_POLICY,APP_MSG_POLICY,USER_MSG_POLICY) values ("+
						"'"+mySetting.getUserID()+"',"+mySetting.getIsReceiveAllMsg()+","+mySetting.getIsReceiveAppMsg()+","+
						mySetting.getIsReceiveUserMsg()+","+mySetting.getIsSetReceiveTime()+",'"+mySetting.getStartRecTime()+"',"
						+"'"+mySetting.getEndRecTime()+"',"+"'"+mySetting.getSysMsgPolicy()+"',"+"'"+mySetting.getAppMsgPolicy()+"',"
						+"'"+mySetting.getUserMsgPolicy()+"')";
		}
			
		result = executUpdate(sqlString);
		return result;
	}
}
