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
		case "AppMessage":		//应用消息
			SendAppMessage(msg);
			break;
		case "SysMessage":	   //系统消息
			SendSysMessage(msg);
			break;
		case "UserMessage":	   //用户消息
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
		//每个人一个设置,存储所有的订阅信息
		ArrayList<SettingInfo> settingArray = new ArrayList<SettingInfo>();
		
		for(int nIndex=0; nIndex<userArray.getUserNum(); nIndex++)
		{
			SettingInfo setting =  settingdb.readMySetting(userArray.getUserInfo(nIndex).getUserID());
			settingArray.add(setting);
		}
		
		//发送方式-WEB:if(sendType.charAt(0)=='1')
		//发送方式-短信
		if(sendType.charAt(1)=='1')
		{
			ArrayList<String> recArray = new ArrayList<String>();
			
			for(int nIndex=0; nIndex<userArray.getUserNum(); nIndex++)
			{
				UserInfo user = userArray.getUserInfo(nIndex);
				
				for(int inct=0; inct<settingArray.size(); inct++)
				{
					//该用户不满足整体订阅条件
					if(!EntireSubscribe(settingArray.get(inct).getIsReceiveAllMsg(),
							settingArray.get(inct).getIsSetReceiveTime()))
					{
						break;
					}
					//找到某用户的App消息订阅设置
					if(settingArray.get(inct).getUserID().equals(user.getUserID()))
					{
						String policy = settingArray.get(inct).getAppMsgPolicy();
						//允许发送短信,将电话号码加入发送列表
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
		//发送方式-邮件
		if(sendType.charAt(2)=='1')
		{
			//是否设置了主接收邮箱
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
						//用户不满足整体订阅条件
						if(!EntireSubscribe(settingArray.get(inct).getIsReceiveAllMsg(),
								settingArray.get(inct).getIsSetReceiveTime()))
						{
							break;
						}
						//允许发送邮件,将电话号码加入发送列表
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
		//发送方式-微信
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
			//允许接收短信
			if(policy.charAt(1)=='1')
			{
				smsMsg.SetSenderUser(sender);
				smsMsg.SetReceiverList(recArray);
				smsMsg.SendSms(title, content, 0);
			}
			//允许发邮件
			if(policy.charAt(2)=='1')
			{
				emailMsg.setRecAccount(receiver.getEmail());
				emailMsg.sendEmail(title, content);
			}
			//允许发微信
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
		
		//msgType 统一都用SysMessage，通过title区分系统消息类型
		//String msgType = msg.getMsgType();
		
		//获取接收用户的订阅设置
		SettingInfo setting =  settingdb.readMySetting(receiver.getUserID());
		
		if(setting == null)
		{
			setting = new SettingInfo();
		}
		
		String policy = setting.getUserMsgPolicy();
		
		//获取消息内容
		String title = msg.getMsgTitle();
		String content = msg.getMsgString();
		
		if(EntireSubscribe(setting.getIsReceiveAppMsg(),setting.getIsSetReceiveTime()))
		{
			//添加好友
			if(title == "AddFriend")
			{
				title = sender.getUserName()+"请求加为好友";
				/*
				//允许接收短信
				if(policy.charAt(1)=='1')
				{
					smsMsg.SetSenderUser(sender);
					smsMsg.SetReceiverList(recArray);
				    smsMsg.SendSms(title, content, 2);
				}
				//允许发邮件
				if(policy.charAt(2)=='1')
				{
					emailMsg.setRecAccount(receiver.getEmail());
					emailMsg.sendEmail(title, content);
				}
				*/
			}
			//好友回复
			else if((title == "ReplyFriend"))
			{
				if(content == "agree")
				{
					title = sender.getUserName()+"通过好友申请";
				}
				else
				{
					title = sender.getUserName()+"未通过好友申请";
				}
			}
			//允许接收短信
			if(policy.charAt(1)=='1')
			{
				smsMsg.SetSenderUser(sender);
				smsMsg.SetReceiverList(recArray);
			    smsMsg.SendSms(title, content, 2);
			}
			//允许发邮件
			if(policy.charAt(2)=='1')
			{
				emailMsg.setRecAccount(receiver.getEmail());
				emailMsg.sendEmail(title, content);
			}
			//允许发微信
			if(policy.charAt(3)=='1')
			{
				
			}
		}
	}
	//整体订阅
	protected boolean EntireSubscribe(boolean IsRecMsg,boolean IsNightNoDisturb)
	{
		if(!IsRecMsg)
		{
			return false;
		}
		
		Calendar curTime = Calendar.getInstance();	//设置为当前时间
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
