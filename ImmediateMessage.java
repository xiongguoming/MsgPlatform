package com.message;

import java.util.ArrayList;
import java.util.Calendar;

import com.dbmanager.AppOperater;
import com.dbmanager.SettingOperater;
import com.dbmanager.UserOperater;
import com.pojo.AppInfo;
import com.pojo.SettingInfo;
import com.pojo.UserArray;
import com.pojo.UserInfo;
import com.webservice.EmailMessage;
import com.webservice.SmsMessage;

public class ImmediateMessage {
	
	private UserOperater userdb = new UserOperater();
	private AppOperater appdb = new AppOperater();
	private SmsMessage smsMsg = new SmsMessage();
	private EmailMessage emailMsg = new EmailMessage();
	private SettingOperater settingdb = new SettingOperater();
	
	public void SendImmediateMessage(TextMessage msg)
	{
		String msgType = msg.getMsgType();
		
		switch(msgType)
		{
		case "AppMessage":		//Ӧ����Ϣ
			SendAppMessage(msg);
			break;
		case "SysMessage":	   //ϵͳ��Ϣ
			SendSysMessage(msg);
			break;
		case "UserMessage":	   //�û���Ϣ
			SendUserMessage(msg);
			break;
		}
	}
	
	protected void SendAppMessage(TextMessage msg)
	{
		AppInfo app = appdb.readApp(msg.getSenderID());
		
		String sendType = msg.getReceiverID();
		String title = msg.getMsgTitle();
		String content = msg.getMsgString();
		
		UserArray userArray = appdb.GetFocusUsers(app.getAppId());
		if(userArray == null)
		{
			return;
		}
		//ÿ����һ������,�洢���еĶ�����Ϣ
		ArrayList<SettingInfo> settingArray = new ArrayList<SettingInfo>();
		
		for(int nIndex=0; nIndex<userArray.getUserNum(); nIndex++)
		{
			SettingInfo setting =  settingdb.readMySetting(userArray.getUserInfo(nIndex).getUserID());
			settingArray.add(setting);
		}
		
		//���ͷ�ʽ-WEB:if(sendType.charAt(0)=='1')
		//���ͷ�ʽ-����
		if(sendType.charAt(1)=='1')
		{
			ArrayList<String> recArray = new ArrayList<String>();
			
			for(int nIndex=0; nIndex<userArray.getUserNum(); nIndex++)
			{
				UserInfo user = userArray.getUserInfo(nIndex);
				
				for(int inct=0; inct<settingArray.size(); inct++)
				{
					//���û����������嶩������
					if(!EntireSubscribe(settingArray.get(inct).getIsReceiveAllMsg(),
							settingArray.get(inct).getIsSetReceiveTime()))
					{
						break;
					}
					//�ҵ�ĳ�û���App��Ϣ��������
					if(settingArray.get(inct).getUserID().equals(user.getUserID()))
					{
						String policy = settingArray.get(inct).getAppMsgPolicy();
						//�����Ͷ���,���绰������뷢���б�
						if(policy.charAt(1) == '1')
						{
							recArray.add(user.getTelephone());
						}
						break;
					}
				}
			}
			smsMsg.SetSenderApp(app);
			smsMsg.SetReceiverList(recArray);
			smsMsg.SendSms(title, content, 1);
		}
		//���ͷ�ʽ-�ʼ�
		if(sendType.charAt(2)=='1')
		{
			//�Ƿ�����������������
			boolean IsSetRecAccount = false;	
			
			ArrayList<String> ccEmailArray = new ArrayList<String>();
			
			for(int nIndex=0; nIndex<userArray.getUserNum(); nIndex++)
			{
				UserInfo user = userArray.getUserInfo(nIndex);
				
				for(int inct=0; inct<settingArray.size(); inct++)
				{
					if(settingArray.get(inct).getUserID().equals(user.getUserID()))
					{
						String policy = settingArray.get(inct).getAppMsgPolicy();
						//�û����������嶩������
						if(!EntireSubscribe(settingArray.get(inct).getIsReceiveAllMsg(),
								settingArray.get(inct).getIsSetReceiveTime()))
						{
							break;
						}
						//�������ʼ�,���绰������뷢���б�
						if(policy.charAt(2) == '1')
						{
							if(!IsSetRecAccount)
							{
								emailMsg.setRecAccount(user.getEmail());
								IsSetRecAccount = true;
							}
							else
							{
								ccEmailArray.add(user.getEmail());
							}
						}
						break;
					}
				}
			}
			emailMsg.setCCAccounts(ccEmailArray);
			emailMsg.sendEmail(title, content);
		}
		//���ͷ�ʽ-΢��
		if(sendType.charAt(3)=='1')
		{
			
		}
	}
	protected void SendUserMessage(TextMessage msg)
	{
		UserInfo sender = GetUserInfo(msg.getSenderID());
		UserInfo receiver = GetUserInfo(msg.getReceiverID());
		
		ArrayList<String> recArray = new ArrayList<String>();
		recArray.add(receiver.getTelephone());
		
		String title = msg.getMsgTitle();
		String content = msg.getMsgString();
		
		SettingInfo setting =  settingdb.readMySetting(receiver.getUserID());
		String policy = setting.getUserMsgPolicy();
		
		if(EntireSubscribe(setting.getIsReceiveAppMsg(),setting.getIsSetReceiveTime()))
		{
			//������ն���
			if(policy.charAt(1)=='1')
			{
				smsMsg.SetSenderUser(sender);
				smsMsg.SetReceiverList(recArray);
				smsMsg.SendSms(title, content, 0);
			}
			//�����ʼ�
			if(policy.charAt(2)=='1')
			{
				emailMsg.setRecAccount(receiver.getEmail());
				emailMsg.sendEmail(title, content);
			}
			//����΢��
			if(policy.charAt(3)=='1')
			{
				
			}
		}
	}
	protected void SendSysMessage(TextMessage msg)
	{
		UserInfo sender = GetUserInfo(msg.getSenderID());
		UserInfo receiver = GetUserInfo(msg.getReceiverID());
		
		ArrayList<String> recArray = new ArrayList<String>();
		recArray.add(receiver.getTelephone());
		
		//msgType ͳһ����SysMessage��ͨ��title����ϵͳ��Ϣ����
		//String msgType = msg.getMsgType();
		
		//��ȡ�����û��Ķ�������
		SettingInfo setting =  settingdb.readMySetting(receiver.getUserID());
		
		if(setting == null)
		{
			setting = new SettingInfo();
		}
		
		String policy = setting.getUserMsgPolicy();
		
		//��ȡ��Ϣ����
		String title = msg.getMsgTitle();
		String content = msg.getMsgString();
		
		if(EntireSubscribe(setting.getIsReceiveAppMsg(),setting.getIsSetReceiveTime()))
		{
			//��Ӻ���
			if(title == "AddFriend")
			{
				title = sender.getUserName()+"�����Ϊ����";
				/*
				//������ն���
				if(policy.charAt(1)=='1')
				{
					smsMsg.SetSenderUser(sender);
					smsMsg.SetReceiverList(recArray);
				    smsMsg.SendSms(title, content, 2);
				}
				//�����ʼ�
				if(policy.charAt(2)=='1')
				{
					emailMsg.setRecAccount(receiver.getEmail());
					emailMsg.sendEmail(title, content);
				}
				*/
			}
			//���ѻظ�
			else if((title == "ReplyFriend"))
			{
				if(content == "agree")
				{
					title = sender.getUserName()+"ͨ����������";
				}
				else
				{
					title = sender.getUserName()+"δͨ����������";
				}
			}
			//������ն���
			if(policy.charAt(1)=='1')
			{
				smsMsg.SetSenderUser(sender);
				smsMsg.SetReceiverList(recArray);
			    smsMsg.SendSms(title, content, 2);
			}
			//�����ʼ�
			if(policy.charAt(2)=='1')
			{
				emailMsg.setRecAccount(receiver.getEmail());
				emailMsg.sendEmail(title, content);
			}
			//����΢��
			if(policy.charAt(3)=='1')
			{
				
			}
		}
	}
	//���嶩��
	protected boolean EntireSubscribe(boolean IsRecMsg,boolean IsNightNoDisturb)
	{
		if(!IsRecMsg)
		{
			return false;
		}
		
		Calendar curTime = Calendar.getInstance();	//����Ϊ��ǰʱ��
		Calendar startTime = Calendar.getInstance();
		Calendar endTime = Calendar.getInstance();
		
		startTime.set(Calendar.HOUR, 22);
		startTime.set(Calendar.MINUTE, 0);
		startTime.set(Calendar.SECOND, 0);
		
		endTime.set(Calendar.HOUR, 8);
		endTime.set(Calendar.MINUTE, 0);
		endTime.set(Calendar.SECOND, 0);
		
		if(curTime.before(startTime)||curTime.after(endTime))
		{
			return false;
		}
		
		return true;
	}
	protected UserInfo GetUserInfo(String userId)
	{
		UserInfo userinfo = new UserInfo();
		
		userinfo = userdb.readUser(userId);
		
		return userinfo;
	}
}
