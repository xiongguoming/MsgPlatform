package com.dbmanager;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;

import com.message.TextMessage;

public class SysMsgOperater extends DBOperater
{
	public TextMessage getMessageById(String msgid)
	{
		String sqlString = "select * from msg_sys_msg where ID="+msgid;
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
				msg.setSenderID(rs.getString(2));//系统消息
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
			//closeDB();
			return null;
		}
		return msg;
	}
	
	public ArrayList<TextMessage> getSysMessage()
	{
		String sqlString = "select * from msg_sys_msg order by ID DESC";//ASC升序
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
	
	public ArrayList<TextMessage> getStorageMessage(String receiverId)
	{
		String sqlString = "select * from msg_storage where RECEIVER_ID= "
						 + receiverId+" and TYPE=0 " + " order by ID DESC";//ASC升序
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
			//closeDB();
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
		filedValues.put("RECEIVER_ID", msg.getReceiverID());
		filedValues.put("SENDER_ID", "SYSTEM_"+msg.getSenderID());
		filedValues.put("TIMESTAP", msg.getTimeStap());
		filedValues.put("EXPIRATION", msg.getExpiration());
		filedValues.put("PRIORITY", msg.getPriority());
		filedValues.put("MSG_TYPE", msg.getMsgType());
		filedValues.put("MSG_TITLE", msg.getMsgTitle());
		filedValues.put("MSG_CONTENT", msg.getMsgString());
		filedValues.put("STATUS", msg.getStatus());
		
		sqlString = getSqlString("msg_sys_msg", filedValues,"insert");
		
		if(executUpdate(sqlString))
		{
			msgID = this.getAutoIncKey();
			storageMessage(msg);
		}
		
		return msgID;
	}
	//增加一条消息的时候同时存储一条到历史消息
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
		filedValues.put("TYPE", 0);//消息类型：1-系统消息
		
		sqlString = getSqlString("msg_storage", filedValues,"insert");
		
		executUpdate(sqlString);
	}
	//删除一条消息
	public boolean deleteMessage(String msgID)
	{
		String sqlString = "delete from msg_sys_msg where ID="+msgID;
		return executUpdate(sqlString);
	}
	//更改消息已读状态
	public boolean updateMsgStatus(String msgID)
	{
		String sqlString = "update msg_sys_msg set STATUS=1 where ID="+msgID;
		return executUpdate(sqlString);
	}
}
