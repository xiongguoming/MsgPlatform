package com.message;

import java.util.Map;

public class TextMessage {
	//��Ϣͷ
	private int messageID = 0;				//��ϢID
	private String senderID="";				//����ID
	private String receiverID="";			//����ID(Ӧ����Ϣ����ҳ0/1������0/1���ʼ�0/1��΢��0/1)
	private long timeStap = 0;				//��ʼʱ���
	private long expiration = 259200000;	//����ʱ��(3��)
	private int priority = 0;				//���ȼ�����ѡ��
	private String msgType;					//��Ϣ����
	//��Ϣ��
	private String msgTitle="";				//��Ϣ���⣨��ѡ��
	private String msgString="";			//��Ϣ�ַ���
	private Map<String,String> content;		//��Ϣ���ݣ���ѡ��
	private boolean status;					//��Ϣ״̬(0:δ����1:�Ѷ�)
	//��ϢID
	public void setMessageID(int messageID)
	{
		this.messageID = messageID;	
	}
	public int getMessageID()
	{
		return this.messageID;	
	}
	
	//����ID
	public void setSenderID(String senderID)
	{
		this.senderID = senderID;	
	}
	public String getSenderID()
	{
		return this.senderID;	
	}
	
	//����ID
	public void setReceiverID(String receiverID)
	{
		this.receiverID = receiverID;	
	}
	public String getReceiverID()
	{
		return this.receiverID;	
	}
	
	//��Ϣ����ʱ���
	public void setTimeStap(long timeStap)
	{
		this.timeStap = timeStap;	
	}
	public long getTimeStap()
	{
		return this.timeStap;	
	}
	
	//��Ϣ����ʱ��
	public void setExpiration(long expiration)
	{
		this.expiration = expiration;	
	}
	public long getExpiration()
	{
		return this.expiration;	
	}
	
	//���ȼ�
	public void setPriority(int priority)
	{
		this.priority = priority;	
	}
	public int getPriority()
	{
		return this.priority;	
	}
	
	//��Ϣ����
	public void setMsgType(String msgType)
	{
		this.msgType = msgType;	
	}
	public String getMsgType()
	{
		return this.msgType;	
	}
	
	//��Ϣ����
	public void setMsgTitle(String msgTitle)
	{
		this.msgTitle = msgTitle;	
	}
	public String getMsgTitle()
	{
		return this.msgTitle;	
	}
	
	//��Ϣ�ַ���
	public void setMsgString(String msgString)
	{
		this.msgString = msgString;	
	}
	public String getMsgString()
	{
		return this.msgString;	
	}
	
	//��Ϣ����
	public void setContent(Map<String,String> content)
	{
		this.content = content;	
	}
	public Map<String,String> getContent()
	{
		return this.content;	
	}
	//��Ϣ״̬true�Ѷ���falseδ��
	public void setStatus(boolean status)
	{
		this.status = status;	
	}
	public boolean getStatus()
	{
		return this.status;	
	}
}
