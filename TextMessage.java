package com.message;

import java.util.Map;

public class TextMessage {
	//消息头
	private int messageID = 0;				//消息ID
	private String senderID="";				//发送ID
	private String receiverID="";			//接收ID(应用消息：网页0/1、短信0/1、邮件0/1、微信0/1)
	private long timeStap = 0;				//开始时间戳
	private long expiration = 259200000;	//过期时间(3天)
	private int priority = 0;				//优先级（可选）
	private String msgType;					//消息类型
	//消息体
	private String msgTitle="";				//消息标题（可选）
	private String msgString="";			//消息字符串
	private Map<String,String> content;		//消息内容（可选）
	private boolean status;					//消息状态(0:未读，1:已读)
	//消息ID
	public void setMessageID(int messageID)
	{
		this.messageID = messageID;	
	}
	public int getMessageID()
	{
		return this.messageID;	
	}
	
	//发送ID
	public void setSenderID(String senderID)
	{
		this.senderID = senderID;	
	}
	public String getSenderID()
	{
		return this.senderID;	
	}
	
	//发送ID
	public void setReceiverID(String receiverID)
	{
		this.receiverID = receiverID;	
	}
	public String getReceiverID()
	{
		return this.receiverID;	
	}
	
	//消息产生时间戳
	public void setTimeStap(long timeStap)
	{
		this.timeStap = timeStap;	
	}
	public long getTimeStap()
	{
		return this.timeStap;	
	}
	
	//消息过期时间
	public void setExpiration(long expiration)
	{
		this.expiration = expiration;	
	}
	public long getExpiration()
	{
		return this.expiration;	
	}
	
	//优先级
	public void setPriority(int priority)
	{
		this.priority = priority;	
	}
	public int getPriority()
	{
		return this.priority;	
	}
	
	//消息类型
	public void setMsgType(String msgType)
	{
		this.msgType = msgType;	
	}
	public String getMsgType()
	{
		return this.msgType;	
	}
	
	//消息标题
	public void setMsgTitle(String msgTitle)
	{
		this.msgTitle = msgTitle;	
	}
	public String getMsgTitle()
	{
		return this.msgTitle;	
	}
	
	//消息字符串
	public void setMsgString(String msgString)
	{
		this.msgString = msgString;	
	}
	public String getMsgString()
	{
		return this.msgString;	
	}
	
	//消息内容
	public void setContent(Map<String,String> content)
	{
		this.content = content;	
	}
	public Map<String,String> getContent()
	{
		return this.content;	
	}
	//消息状态true已读，false未读
	public void setStatus(boolean status)
	{
		this.status = status;	
	}
	public boolean getStatus()
	{
		return this.status;	
	}
}
