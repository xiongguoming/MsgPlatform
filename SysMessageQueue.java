package com.message;

import java.util.ArrayList;

import com.dbmanager.SysMsgOperater;

public class SysMessageQueue {
	
	private String queueName = "";
	private ArrayList<TextMessage> msgQueue = new ArrayList<TextMessage>();
	
	//=================================
	//���л�������
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
	//��Ϣ������Ϣ����
	public synchronized void addQueueMsg(TextMessage msg)
	{
		msgQueue.add(msg);
	}
	//����Ϣ����ɾ����Ϣ
	public synchronized TextMessage removeQueueMsg(TextMessage msg)
	{
		msgQueue.remove(msg);
		return msg;
	}
	//�������
	public void clearQueue()
	{
		msgQueue.clear();
	}
	
	//=================================
	//�������ݿ�
	//=================================
	
	//������Ϣ״̬(�Ѷ���δ��)
	public void updateMsgStatus(String msgID)
	{
		SysMsgOperater sysdb = new SysMsgOperater();
		if(sysdb.updateMsgStatus(msgID))
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
	
	//ɾ����Ϣ
	public void deleteDBMessage(String msgID)
	{
		SysMsgOperater sysdb = new SysMsgOperater();
		
		if(sysdb.deleteMessage(msgID))
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
