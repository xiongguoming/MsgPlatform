package com.system;

import java.io.IOException;
import java.util.Date;
import java.util.Map;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;

import com.dbmanager.AppOperater;
import com.dbmanager.LogOperater;
import com.dbmanager.SysMsgOperater;
import com.dbmanager.UserOperater;
import com.message.ImmediateMessage;
import com.message.TextMessage;
import com.pojo.AppInfo;
import com.pojo.MsgLog;
import com.pojo.UserInfo;

public class MessageFilter implements Filter {
	
	ImmediateMessage ImdMessage = new ImmediateMessage();
	SysMsgOperater msgdb = new SysMsgOperater();
	UserOperater userdb = new  UserOperater();
	AppOperater appdb = new AppOperater();
	@Override
	public void destroy() {

	}

	@Override
	public void doFilter(ServletRequest request, ServletResponse response,
			FilterChain chain) throws IOException, ServletException {
		
		String ipAddr = getRemoteHost((HttpServletRequest)request);
		String optType = request.getParameter("type");
		String title = "";
		String content = "";
		String senderId = "";
		
		//找到非法地址
		if(userdb.QueryBlackList("", ipAddr)||appdb.QueryBlackList("", ipAddr))
		{
			return;
		}
		if(optType == null)
		{
			chain.doFilter(request, response);
			return;
		}
		
	
		switch(optType)
		{
		case "requestfriend":	//系统消息-添加好友消息
			senderId = request.getParameter("senderid");
			String rqContent = request.getParameter("rqcontent");
			if(userdb.QueryBlackList(senderId,""))
			{
				return;
			}
			if(IsParamsLegal(rqContent))
			{
				chain.doFilter(request, response);
			}
			else
			{
				doIllegalMessage(ipAddr,senderId,optType);
			}
			break;
		case "usermsg":	    	//用户消息-发送消息
			senderId = request.getParameter("senderid");
			title = request.getParameter("title");
			content = request.getParameter("content");
			
			if(userdb.QueryBlackList(senderId,""))
			{
				return;
			}
			if(IsParamsLegal(title+content))
			{
				chain.doFilter(request, response);
			}
			else
			{
				doIllegalMessage(ipAddr,senderId,optType);
			}
			break;
		case "appmsg":  		//APP发送消息
			senderId = request.getParameter("appId");
			title = request.getParameter("title");
			content = request.getParameter("content");
			//查禁用用户
			if(appdb.QueryBlackList(senderId,""))
			{
				return;
			}
			if(IsParamsLegal(title+content))
			{
				chain.doFilter(request, response);
			}
			else
			{
				doIllegalMessage(ipAddr,senderId,optType);
			}
			break;
		default:
			chain.doFilter(request, response);
			break;
		}
	}
	//发送一次负面消息，扣6分，扣完后仍然继续发送的话继续扣，积分为正可以继续发消息
	//ippAddr:发送方IP地址，sendId:发送方Id,type:发送方消息类型
	public void doIllegalMessage(String ipAddr,String senderId,String type)
	{
		UserInfo user = null;
		AppInfo app = null;
		
		switch(type)
		{
		//用户积分扣减
		case "requestfriend":
		case "usermsg":
			user = userdb.getUserInfo();
			if(user != null)
			{
				user.setScore(user.getScore()-6);
				userdb.updateUserScore(senderId,user.getScore());
				//发送系统告警消息
				if(user.getScore()>0)
				{
					SendSysMessage("SysWarn","您发送的消息存在敏感字",senderId);
				}
				//发送系统告警信息，并将用户加入黑名单
				else
				{
					SendSysMessage("SysWarn","由于您多次违规发送消息，该账号已被禁用，请联系管理员",senderId);
					userdb.AddBlackList(senderId, ipAddr);
				}
			}
			break;
		//应用积分扣减	
		case "appmsg":
			app = appdb.readApp(senderId);
			if(app != null)
			{
				app.setScore(app.getScore()-6);
				appdb.updateAppScore(senderId,user.getScore());
				//发送系统告警消息
				if(user.getScore()>0)
				{
					//SendSysMessage("SysWarn","您发送的消息存在敏感字",senderId);
				}
				//发送系统告警信息，并将用户加入黑名单
				else
				{
					//SendSysMessage("SysWarn","由于您多次违规发送消息，该账号已被禁用，请联系管理员",senderId);
					appdb.AddBlackList(senderId, ipAddr);
				}
			}
			
			break;
		default:
			
			break;
		}
	}
	//title:SysWarn表示“警告”,其它类型包括“提醒”SysTip(RequestFriend,ReplyFriend),"消息"SysMsg等。
	public void SendSysMessage(String title,String content,String receiverId)
	{
		TextMessage msg = new TextMessage();
		msg.setSenderID("SYSTEM");
		msg.setReceiverID(receiverId);
		
		//出错
		msg.setTimeStap(System.currentTimeMillis());
		msg.setMsgType("SystemMessage");
		msg.setMsgTitle(title);			
		msg.setMsgString(content);	
		
		//消息存储系统消息
		msgdb.addMessage(msg);
		//系统消息-默认所有方式都发
		ImdMessage.SendImmediateMessage(msg);
		//记录日志
		AddOperaterLog(receiverId,2);
	}
	public boolean IsParamsLegal(String content)
	{
		if(content.contains("测试关键字"))
		{
			return false;
		}
		return true;
	}
	//获取正式IP地址
	public String getRemoteHost(HttpServletRequest request)
	{
	    String ip = request.getHeader("x-forwarded-for");
	    
	    if(ip == null || ip.length() == 0 || "unknown".equalsIgnoreCase(ip))
	    {
	        ip = request.getHeader("Proxy-Client-IP");
	    }
	    
	    if(ip == null || ip.length() == 0 || "unknown".equalsIgnoreCase(ip))
	    {
	        ip = request.getHeader("WL-Proxy-Client-IP");
	    }
	    
	    if(ip == null || ip.length() == 0 || "unknown".equalsIgnoreCase(ip))
	    {
	        ip = request.getRemoteAddr();
	    }
	    return ip.equals("0:0:0:0:0:0:0:1")?"127.0.0.1":ip;
	}
	
	@Override
	public void init(FilterConfig arg0) throws ServletException
	{

	}
	
	//增加操作日志
	public void AddOperaterLog(String userId,int nType)
	{
		String remark = "";
		MsgLog log = new MsgLog();
		long occTime = new Date().getTime();
		
		log.addLog(userId, nType, occTime, remark);
		LogOperater dbLog = new LogOperater();
		dbLog.SaveLog(log);
	}

}
