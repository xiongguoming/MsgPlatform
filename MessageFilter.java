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
		
		//�ҵ��Ƿ���ַ
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
		case "requestfriend":	//ϵͳ��Ϣ-��Ӻ�����Ϣ
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
		case "usermsg":	    	//�û���Ϣ-������Ϣ
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
		case "appmsg":  		//APP������Ϣ
			senderId = request.getParameter("appId");
			title = request.getParameter("title");
			content = request.getParameter("content");
			//������û�
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
	//����һ�θ�����Ϣ����6�֣��������Ȼ�������͵Ļ������ۣ�����Ϊ�����Լ�������Ϣ
	//ippAddr:���ͷ�IP��ַ��sendId:���ͷ�Id,type:���ͷ���Ϣ����
	public void doIllegalMessage(String ipAddr,String senderId,String type)
	{
		UserInfo user = null;
		AppInfo app = null;
		
		switch(type)
		{
		//�û����ֿۼ�
		case "requestfriend":
		case "usermsg":
			user = userdb.getUserInfo();
			if(user != null)
			{
				user.setScore(user.getScore()-6);
				userdb.updateUserScore(senderId,user.getScore());
				//����ϵͳ�澯��Ϣ
				if(user.getScore()>0)
				{
					SendSysMessage("SysWarn","�����͵���Ϣ����������",senderId);
				}
				//����ϵͳ�澯��Ϣ�������û����������
				else
				{
					SendSysMessage("SysWarn","���������Υ�淢����Ϣ�����˺��ѱ����ã�����ϵ����Ա",senderId);
					userdb.AddBlackList(senderId, ipAddr);
				}
			}
			break;
		//Ӧ�û��ֿۼ�	
		case "appmsg":
			app = appdb.readApp(senderId);
			if(app != null)
			{
				app.setScore(app.getScore()-6);
				appdb.updateAppScore(senderId,user.getScore());
				//����ϵͳ�澯��Ϣ
				if(user.getScore()>0)
				{
					//SendSysMessage("SysWarn","�����͵���Ϣ����������",senderId);
				}
				//����ϵͳ�澯��Ϣ�������û����������
				else
				{
					//SendSysMessage("SysWarn","���������Υ�淢����Ϣ�����˺��ѱ����ã�����ϵ����Ա",senderId);
					appdb.AddBlackList(senderId, ipAddr);
				}
			}
			
			break;
		default:
			
			break;
		}
	}
	//title:SysWarn��ʾ�����桱,�������Ͱ��������ѡ�SysTip(RequestFriend,ReplyFriend),"��Ϣ"SysMsg�ȡ�
	public void SendSysMessage(String title,String content,String receiverId)
	{
		TextMessage msg = new TextMessage();
		msg.setSenderID("SYSTEM");
		msg.setReceiverID(receiverId);
		
		//����
		msg.setTimeStap(System.currentTimeMillis());
		msg.setMsgType("SystemMessage");
		msg.setMsgTitle(title);			
		msg.setMsgString(content);	
		
		//��Ϣ�洢ϵͳ��Ϣ
		msgdb.addMessage(msg);
		//ϵͳ��Ϣ-Ĭ�����з�ʽ����
		ImdMessage.SendImmediateMessage(msg);
		//��¼��־
		AddOperaterLog(receiverId,2);
	}
	public boolean IsParamsLegal(String content)
	{
		if(content.contains("���Թؼ���"))
		{
			return false;
		}
		return true;
	}
	//��ȡ��ʽIP��ַ
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
	
	//���Ӳ�����־
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
