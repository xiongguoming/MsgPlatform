package com.message;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Date;
import javax.servlet.AsyncContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dbmanager.AppMsgOperater;
import com.dbmanager.AppOperater;
import com.dbmanager.LogOperater;
import com.dbmanager.SettingOperater;
import com.dbmanager.SysMsgOperater;
import com.dbmanager.UserMsgOperater;
import com.pojo.SettingInfo;
import com.system.JasonEncoding;

//消息调度
public class MsgDispatch extends Thread 
{
	//用户消息
	private AppMessageQueue appMsgQueue = null;
	//用户消息
	private UserMessageQueue userMsgQueue = null;
	//系统消息
	private SysMessageQueue sysMsgQueue = null;
	//请求客户端
	@SuppressWarnings("unused")
	private HttpServletRequest request = null;
	//响应客户端
	private HttpServletResponse response = null;
	//接收用户ID
	private String receiverID = "";
	//json编码类
	private JasonEncoding jasonOpt;
	//日志接口
	private LogOperater dbLog;
	//用户消息数据库接口
	private AppMsgOperater appmsgDB;
	//用户消息数据库接口
	private UserMsgOperater usermsgDB;
	//系统消息数据库接口
	private SysMsgOperater sysmsgDB;
	//servlet请求接口
	private AsyncContext act = null;
	//消息更新时间
	private long updateOccasion = 0;
	
	
	public MsgDispatch()
	{ 
		jasonOpt = new JasonEncoding();
		dbLog = new LogOperater();
		
		appmsgDB = new AppMsgOperater();
		appMsgQueue = new AppMessageQueue();
		appMsgQueue.SetQueueName("APP-MESSAGE");
		
		usermsgDB = new UserMsgOperater();
		userMsgQueue = new UserMessageQueue();
		userMsgQueue.SetQueueName("USER-MESSAGE");
		
		sysmsgDB = new SysMsgOperater();
		sysMsgQueue = new SysMessageQueue();
		sysMsgQueue.SetQueueName("SYS-MESSAGE");
		
		UpdateMsgQueue();
	}
	
	public void SetAsyncContext(AsyncContext act)
	{
		this.act = act;
		response = (HttpServletResponse) act.getResponse();
	}
	
	//更新消息队列
	public void UpdateMsgQueue()
	{
		if(receiverID.length()<1)
		{
			return;
		}
		
		//从数据库中读取所有用户消息
		if(IsSubscribeMsg(receiverID,0))
		{	
			ArrayList<TextMessage> userMsgArray = usermsgDB.getUserMessage();
			
			if(userMsgArray != null)
			{
				userMsgQueue.clearQueue();
				for(int nIndex=0; nIndex<userMsgArray.size(); nIndex++)
				{
					userMsgQueue.addQueueMsg(userMsgArray.get(nIndex));
				}
			}
			
		}
		
		//从数据库中读取所有应用消息
		if(IsSubscribeMsg(receiverID,1))
		{
			ArrayList<TextMessage> appMsgArray = appmsgDB.getAppMessage();
			
			if(appMsgArray != null)
			{
				appMsgQueue.clearQueue();
				for(int nIndex=0; nIndex<appMsgArray.size(); nIndex++)
				{
					appMsgQueue.addQueueMsg(appMsgArray.get(nIndex));
				}
			}
		}
		
		
		if(IsSubscribeMsg(receiverID,2))
		{
			//从数据库中读取所有系统消息
			ArrayList<TextMessage> sysMsgArray = sysmsgDB.getSysMessage();
			
			if(sysMsgArray != null)
			{
				sysMsgQueue.clearQueue();
				for(int nIndex=0; nIndex<sysMsgArray.size(); nIndex++)
				{
					sysMsgQueue.addQueueMsg(sysMsgArray.get(nIndex));
				}
			}
		}
		
		
		//当前消息更新时间
		updateOccasion = System.currentTimeMillis();
	}
	
	//根据receiveID提取消息
	public ArrayList<TextMessage> pickMessage()
	{
		ArrayList<TextMessage> msgArray = new ArrayList<TextMessage>();
		
		//用户消息
		if(userMsgQueue!=null)
		{
			ArrayList<TextMessage> userMsgArray = userMsgQueue.getMessageQueue();
			
			for(int nIndex=0; nIndex<userMsgArray.size(); nIndex++)
			{
				if(receiverID.equals(userMsgArray.get(nIndex).getReceiverID()))
				{
					msgArray.add(userMsgArray.get(nIndex));
				}
			}
		}
		
		//系统消息
		if(sysMsgQueue!=null)
		{
			ArrayList<TextMessage> sysMsgArray = sysMsgQueue.getMessageQueue();
			
			for(int nIndex=0; nIndex<sysMsgArray.size(); nIndex++)
			{
				if(receiverID.equals(sysMsgArray.get(nIndex).getReceiverID()))
				{
					msgArray.add(sysMsgArray.get(nIndex));
				}
			}
		}
		
		
		//应用消息
		if(appMsgQueue!=null)
		{
			ArrayList<TextMessage> appMsgArray = appMsgQueue.getMessageQueue();
			
			for(int nIndex=0; nIndex<appMsgArray.size(); nIndex++)
			{
				//是否关注了该应用
				if(IsFocusedApp(receiverID,appMsgArray.get(nIndex).getSenderID()))
				{
					msgArray.add(appMsgArray.get(nIndex));
				}
			}
		}
		
		return msgArray;
	}
	//网页消息订阅
	public boolean IsSubscribeMsg(String receiverId,int nType)
	{
		SettingOperater settingdb = new  SettingOperater();
		SettingInfo setting =  settingdb.readMySetting(receiverId);
		
		if(setting == null)
		{
			setting = new SettingInfo();
		}
		
		String policy = "";
		switch(nType)
		{
		case 0:
			policy = setting.getUserMsgPolicy();
			break;
		case 1:
			policy = setting.getAppMsgPolicy();
			break;	
		case 2:
			policy = setting.getSysMsgPolicy();
			break;
		}
	
		if(policy.charAt(0)=='1')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//执行消息调度
	@Override
	public void run() 
	{
		receiverID = act.getRequest().getParameter("receiveid");
		//是否有更新消息，如果用户取消订阅WEB消息，则不推送最新的WEB消息
		if(dbLog.IsMsgUpdated(updateOccasion))
		{
			UpdateMsgQueue();
			System.out.print("【线程ID-"+String.valueOf(getId())+"】更新当前消息队列：" + new Date() + ".\n");
		}
			
		String optType = act.getRequest().getParameter("type");
		
		if(optType == null)
		{
			return;
		}
		//客户端请求消息请求
		if(optType.equals("recroll"))
		{
			TransferMessage();
		}
	}
	
	//响应消息请求
	public void TransferMessage()
	{
		//根据接收ID提取消息
		ArrayList<TextMessage> msgArray = pickMessage();
		
		String jsonStr = jasonOpt.encodingUserMessage(msgArray);
		
		if(jsonStr==null||jsonStr.equals("")||response==null)
		{
			return;
		}
		//响应客户端
		response.setContentType("text/html");
		PrintWriter out = null;
		try 
		{
			out = response.getWriter();
			if(out != null)
			{
				out.println(jsonStr);               
				out.flush();
				out.close();	
			}
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	
	//用户是否关注了App
	public boolean IsFocusedApp(String userId,String appId)
	{
		if(userId==null||userId==""||appId==null||appId=="")
		{
			return false;
		}
		AppOperater appdb = new AppOperater();
		return appdb.IsFocusedApp(userId,appId);
	}
}
