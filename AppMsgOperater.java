package com.dbmanager;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;

import com.message.TextMessage;

public class AppMsgOperater extends DBOperater
{
	public TextMessage getMessageById(String msgid)
	{
		String sqlString = "select * from msg_app_msg where ID="+msgid;
		TextMessage msg = new TextMessage();
		
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return msg;
			}
			
			while(rs.next())
			{
				msg.setMessageID(rs.getInt(1));
				msg.setSenderID(rs.getString(2));
				msg.setReceiverID(rs.getString(3));
				msg.setTimeStap(rs.getLong(4));
				msg.setExpiration(rs.getLong(5));
				msg.setPriority(rs.getInt(6));
				msg.setMsgType(rs.getString(7));
				msg.setMsgTitle(rs.getString(8));
				msg.setMsgString(rs.getString(9));
				msg.setStatus(rs.getBoolean(10));
				break;
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			return null;
		}
		return msg;
	}
	
	public ArrayList<TextMessage> getAppMessage()
	{
		String sqlString = "select * from msg_app_msg order by ID DESC";//ASC升序
		ArrayList<TextMessage> msgArray = new ArrayList<TextMessage> ();
		try
		{
			ResultSet rs = executQuery(sqlString);
			
			if(rs == null)
			{
				return msgArray;
			}
			 
			int rowCount = 0;
			while(rs.next())
			{
				TextMessage msg = new TextMessage();
				msg.setMessageID(rs.getInt(1));
				msg.setSenderID(rs.getString(2));
				msg.setReceiverID(rs.getString(3));
				msg.setTimeStap(rs.getLong(4));
				msg.setExpiration(rs.getLong(5));
				msg.setPriority(rs.getInt(6));
				msg.setMsgType(rs.getString(7));
				msg.setMsgTitle(rs.getString(8));
				msg.setMsgString(rs.getString(9));
				msg.setStatus(rs.getBoolean(10));
				msgArray.add(rowCount++,msg);
			}
			
			if(rowCount==0)
			{
				return null;
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			return null;
		}
		
		return msgArray;
	}
	//修改信息并保存
	public int addMessage(TextMessage msg)
	{
		int msgID = -1;
		String sqlString = "";
		//记录存在-更新
		HashMap<String,Object> filedValues = new HashMap<String, Object>();
		filedValues.put("SENDER_ID", msg.getSenderID());
		filedValues.put("RECEIVER_ID", msg.getReceiverID());	
		filedValues.put("TIMESTAP", msg.getTimeStap());
		filedValues.put("EXPIRATION", msg.getExpiration());
		filedValues.put("PRIORITY", msg.getPriority());
		filedValues.put("MSG_TYPE", msg.getMsgType());
		filedValues.put("MSG_TITLE", msg.getMsgTitle());
		filedValues.put("MSG_CONTENT", msg.getMsgString());
		filedValues.put("STATUS", msg.getStatus());
		
		sqlString = getSqlString("msg_app_msg", filedValues,"insert");
		
		if(executUpdate(sqlString))
		{
			msgID = this.getAutoIncKey();
			storageMessage(msg);
		}
		
		return msgID;
	}
	public void storageMessage(TextMessage msg)
	{
		String sqlString = "";
		//记录存在-更新
		HashMap<String,Object> filedValues = new HashMap<String, Object>();
		filedValues.put("SENDER_ID", msg.getSenderID());
		filedValues.put("RECEIVER_ID", msg.getReceiverID());	
		filedValues.put("TIMESTAP", msg.getTimeStap());
		filedValues.put("EXPIRATION", msg.getExpiration());
		filedValues.put("PRIORITY", msg.getPriority());
		filedValues.put("MSG_TYPE", msg.getMsgType());
		filedValues.put("MSG_TITLE", msg.getMsgTitle());
		filedValues.put("MSG_CONTENT", msg.getMsgString());
		filedValues.put("TYPE", 1);//消息类型：1-应用消息
		
		sqlString = getSqlString("msg_storage", filedValues,"insert");
		
		executUpdate(sqlString);
	}
	
	public ArrayList<TextMessage> getHistoryMessage(String receiverID)
	{
		String sqlString = "";
		ArrayList<TextMessage> msgArray = new ArrayList<TextMessage> ();
		//获得关注应用的历史消息
		sqlString = GetFocusApps(receiverID);
		String[] appIds = sqlString.split(",");
		
		for(int nIndex=0; nIndex<appIds.length; nIndex++)
		{
			ArrayList<TextMessage> appMsgs = getStorageMessage(appIds[nIndex]);
			if(appMsgs != null)
			{
				for(int nItem=0; nItem<appMsgs.size(); nItem++)
				{
					msgArray.add(appMsgs.get(nItem));
				}
			}
		}
		
		//该条sql将得到除应用消息之外的其它消息
		sqlString = "select * from msg_storage where RECEIVER_ID= '"+receiverID+"' order by ID DESC";//ASC升序	
		try
		{
			ResultSet rs = executQuery(sqlString);
			
			if(rs == null)
			{
				return msgArray;
			}
			 
			int rowCount = 0;
			while(rs.next())
			{
				TextMessage msg = new TextMessage();
				msg.setMessageID(rs.getInt(1));
				msg.setSenderID(rs.getString(2));
				msg.setReceiverID(rs.getString(3));
				msg.setTimeStap(rs.getLong(4));
				msg.setExpiration(rs.getLong(5));
				msg.setPriority(rs.getInt(6));
				msg.setMsgType(rs.getString(7));
				msg.setMsgTitle(rs.getString(8));
				msg.setMsgString(rs.getString(9));
				msgArray.add(rowCount++,msg);
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			return null;
		}
		
		return msgArray;
	}
	//获得关注应用
	public String GetFocusApps(String userId)
	{
		String sqlString = "select * from app_users_focus where USER_ID='"+userId+"'";
		String res = "";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs != null)
			{
				while(rs.next())
				{
					String appId = rs.getString(2);
					res += appId;
					res += ',';
				}
			}
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
		
		return res;
	}
	public ArrayList<TextMessage> getStorageMessage(String appId)
	{
		String sqlString = "select * from msg_storage where sender_Id="
					     +appId+ " and TYPE=1 " + " order by ID DESC";//ASC升序
		
		ArrayList<TextMessage> msgArray = new ArrayList<TextMessage> ();
		try
		{
			ResultSet rs = executQuery(sqlString);
			
			if(rs == null)
			{
				return msgArray;
			}
			 
			int rowCount = 0;
			while(rs.next())
			{
				TextMessage msg = new TextMessage();
				msg.setMessageID(rs.getInt(1));
				msg.setSenderID(rs.getString(2));
				msg.setReceiverID(rs.getString(3));
				msg.setTimeStap(rs.getLong(4));
				msg.setExpiration(rs.getLong(5));
				msg.setPriority(rs.getInt(6));
				msg.setMsgType(rs.getString(7));
				msg.setMsgTitle(rs.getString(8));
				msg.setMsgString(rs.getString(9));
				msgArray.add(rowCount++,msg);
			}
			
			if(rowCount==0)
			{
				return null;
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			return null;
		}
		
		return msgArray;
	}
	//删除一条消息
	public boolean deleteMessage(String msgID)
	{
		String sqlString = "delete from msg_app_msg where ID="+msgID;
		return executUpdate(sqlString);
	}
	//更新消息状态
	public boolean updateMsgStatus(String msgID) {
		
		String sqlString = "update msg_app_msg set STATUS=1 where ID="+msgID;
		return executUpdate(sqlString);
	}
}
