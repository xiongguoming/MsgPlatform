package com.message;

import java.util.ArrayList;

import com.dbmanager.AppMsgOperater;

public class AppMessageQueue {
	
	private String queueName = "AppMessage";
	private ArrayList<TextMessage> msgQueue = new ArrayList<TextMessage>();
	
	//=================================
	//队列基本操作
	//=================================
	public void SetQueueName(String queueName)
	{
		this.queueName = queueName;
	}
	public String getQueueName()
	{
		return this.queueName;
	}
	public ArrayList<TextMessage> getMessageQueue()
	{
		return this.msgQueue;
	}
	//消息加入消息队列
	public synchronized void addQueueMsg(TextMessage msg)
	{
		msgQueue.add(msg);
	}
	//从消息队列删除消息
	public synchronized TextMessage removeQueueMsg(TextMessage msg)
	{
		msgQueue.remove(msg);
		return msg;
	}
	//队列清空
	public void clearQueue()
	{
		msgQueue.clear();
	}
	
	//=================================
	//更新数据库
	//=================================
	
	//更新消息状态(已读、未读)
	public void updateMsgStatus(String msgID)
	{
		AppMsgOperater appdb = new AppMsgOperater();
		if(appdb.updateMsgStatus(msgID))
		{
			for(int nIndex=0; nIndex<msgQueue.size(); nIndex++)
			{
				String temp = String.valueOf(msgQueue.get(nIndex).getMessageID());
				if(msgID.equals(temp))
				{
					msgQueue.get(nIndex).setStatus(true);
					break;
				}
			}
		}
	}
	
	//删除消息
	public void deleteDBMessage(String msgID)
	{
		AppMsgOperater appdb = new AppMsgOperater();
		
		if(appdb.deleteMessage(msgID))
		{
			for(int nIndex=0; nIndex<msgQueue.size(); nIndex++)
			{
				String temp = String.valueOf(msgQueue.get(nIndex).getMessageID());
				if(msgID.equals(temp))
				{
					removeQueueMsg(msgQueue.get(nIndex));
					break;
				}
			}
		}
	}
}
