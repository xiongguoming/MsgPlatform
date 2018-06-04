package com.sevlet;

import java.io.IOException;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.ws.Endpoint;

import com.dbmanager.AppMsgOperater;
import com.dbmanager.LogOperater;
import com.dbmanager.SysMsgOperater;
import com.dbmanager.UserMsgOperater;
import com.dbmanager.UserOperater;
import com.message.*;
//主要执行消息处理、持久化、消息投递功能
import com.pojo.MsgLog;
import com.webservice.AppService;

public class MessageReceiver extends HttpServlet {

	private static final long serialVersionUID = 1L;
	
	ImmediateMessage ImdMessage;
	
	public MessageReceiver() {
		super();
	}
	
	public void destroy() {
		super.destroy(); 
	}
	
	public void init() throws ServletException {
		Endpoint.publish("http://localhost:8888/app/service", new AppService());
		
		ImdMessage = new ImmediateMessage();
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		String optType = request.getParameter("type");
		
		switch(optType)
		{
		case "requestfriend":	//系统消息-添加好友消息
			RequestFriend(request,response);
			break;
		case "replyfriend":		//系统消息-添加好友回复消息
			ReplyFriend(request,response);
			break;
		case "usermsg":	    	//用户消息-发送消息
			SendUserMessage(request,response);
			break;
		case "readmsg":			//修改消息的已读状态
			ReadMessage(request,response);
			break;
		case "deletemsg":		//删除消息
			DeleteMessage(request,response);
			break;
		case "appmsg":  		//APP发送消息
			SendAppMessage(request,response);
			break;
		default:
			break;
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
			doGet(request,response);	
	}

	//发送用户消息,type=0
	public void SendUserMessage(HttpServletRequest request, HttpServletResponse response)
	{
		String receiverID = request.getParameter("receiverid");
		String senderID = request.getParameter("senderid");
		String title = request.getParameter("title");
		String content = request.getParameter("content");
		
		TextMessage txtMsg = new TextMessage();
		
		//消息头
		txtMsg.setSenderID(senderID);
		txtMsg.setReceiverID(receiverID);
		//出错
		txtMsg.setTimeStap(System.currentTimeMillis());
		txtMsg.setMsgType("UserMessage");   //消息类型
		txtMsg.setMsgTitle(title);			//消息标题(子类型)
		txtMsg.setMsgString(content);		//消息内容(请求信息)
		
		//存入数据库
		UserMsgOperater msgdb = new UserMsgOperater();
		//消息持久化
		int MessageID = msgdb.addMessage(txtMsg);
		
		if(MessageID>0)
		{
			txtMsg.setMessageID(MessageID);
			AddOperaterLog(senderID,0);
			
			//如果是用户消息，可能是即时消息
			ImdMessage.SendImmediateMessage(txtMsg);
		}	
	}
	
	//请求添加好友,type=1
	public void RequestFriend(HttpServletRequest request, HttpServletResponse response) {
		
		String senderID = request.getParameter("senderid");
		String receiverID = request.getParameter("receiverid");
		String rqContent = request.getParameter("rqcontent");
			
		TextMessage txtMsg = new TextMessage();
		//消息头
		txtMsg.setSenderID(senderID);
		txtMsg.setReceiverID(receiverID);
		txtMsg.setTimeStap(System.currentTimeMillis());
		txtMsg.setMsgType("SysMessage");    //消息类型
		txtMsg.setMsgTitle("AddFriend");	//消息标题(系统消息-子类型)
		txtMsg.setMsgString(rqContent);		//消息内容(请求信息)
		
		//保存消息
		SysMsgOperater msgdb = new SysMsgOperater();
		msgdb.addMessage(txtMsg);
		//系统消息-默认所有方式都发（由用户定义策略）
		ImdMessage.SendImmediateMessage(txtMsg);
		
		AddOperaterLog(senderID,1);
	}
	//来自好友的回复(添加好友),type=2
	public void ReplyFriend(HttpServletRequest request, HttpServletResponse response)
	{
		String reply = request.getParameter("reply");//agree/disagree
		String msgid = request.getParameter("msgid");
		
		if(reply==null || msgid==null)
		{
			return;
		}	
		
		//获取源消息
		if(msgid.contains("SYS"))
		{
			msgid = msgid.substring(3);
		}
		
		SysMsgOperater msgdb = new SysMsgOperater();
		TextMessage origmsg = msgdb.getMessageById(msgid);
		
		//好友通过，更新收发放用户的好友列表
		if(reply.equals("agree"))
		{
			UserOperater userdb = new UserOperater();
			userdb.MakeFriend(origmsg.getSenderID().substring(7),origmsg.getReceiverID());
			
			//将好友回复以消息的方式通知对方
			TextMessage newmsg = new TextMessage();
			
			//消息头
			newmsg.setSenderID(origmsg.getReceiverID());
			newmsg.setReceiverID(origmsg.getSenderID().substring(7));
			//出错
			newmsg.setTimeStap(System.currentTimeMillis());
			newmsg.setMsgType("SysMessage");    //消息类型
			newmsg.setMsgTitle("ReplyFriend");	//消息标题(系统消息-子类型)
			newmsg.setMsgString(reply);			//消息内容(agree/disagree)
			//消息存储系统消息
			msgdb.addMessage(newmsg);
			//系统消息-默认所有方式都发（由用户定义策略）
			ImdMessage.SendImmediateMessage(newmsg);
			AddOperaterLog(origmsg.getSenderID(),2);
		}
	}
	
	//消息已读,type=3
	public void ReadMessage(HttpServletRequest request, HttpServletResponse response)
	{
		//从前端反馈过来的ID格式为：USER(APP/SYS)+ID，如USER123
		String msgID = request.getParameter("msgid");
		UserMsgOperater umdb = new UserMsgOperater();
		SysMsgOperater smdp = new SysMsgOperater();
		AppMsgOperater appdb = new AppMsgOperater();
		
		if(msgID.startsWith("USER"))
		{
			msgID = msgID.substring(4);
			umdb.updateMsgStatus(msgID);
			TextMessage msg = umdb.getMessageById(msgID);
			AddOperaterLog(msg.getReceiverID(),3);
		}
		if(msgID.startsWith("SYS"))
		{
			msgID = msgID.substring(3);
			smdp.updateMsgStatus(msgID);
			TextMessage msg = umdb.getMessageById(msgID);
			AddOperaterLog(msg.getReceiverID(),3);
		}
		if(msgID.startsWith("APP"))
		{
			msgID = msgID.substring(3);
			appdb.updateMsgStatus(msgID);
			TextMessage msg = appdb.getMessageById(msgID);
			AddOperaterLog(msg.getSenderID(),3);
		}
	}
	
	//删除消息,type=4
	public void DeleteMessage(HttpServletRequest request, HttpServletResponse response)
	{
		TextMessage msg = null;
		
		String msgID = request.getParameter("msgid");
		if(msgID.startsWith("USER"))
		{
			UserMsgOperater umdb = new UserMsgOperater();
			msgID = msgID.substring(4);
			msg = umdb.getMessageById(msgID);
			umdb.deleteMessage(msgID);
			AddOperaterLog(msg.getReceiverID(),4);
		}
		else if(msgID.startsWith("SYS"))
		{
			SysMsgOperater sysdb = new SysMsgOperater();
			msgID = msgID.substring(3);
			msg = sysdb.getMessageById(msgID);
			sysdb.deleteMessage(msgID);
			AddOperaterLog(msg.getReceiverID(),4);
		}
		else if(msgID.startsWith("APP"))
		{
			AppMsgOperater appdb = new AppMsgOperater();
			msgID = msgID.substring(3);
			msg = appdb.getMessageById(msgID);
			appdb.deleteMessage(msgID);
			AddOperaterLog(msg.getSenderID(),4);
		}
	}
	//发送应用消息,type=5
	public void SendAppMessage(HttpServletRequest request, HttpServletResponse response)
	{
		String appId = request.getParameter("appId");
		String title = request.getParameter("title");
		String content = request.getParameter("content");
		String sendType = request.getParameter("sendType");
		
		//文本类消息
		TextMessage txtMsg = new TextMessage();
		
		//消息头
		txtMsg.setSenderID(appId);
		//应用消息，系统自动推送到关注用户,此处存储消息接收终端
		txtMsg.setReceiverID(sendType);
		
		txtMsg.setTimeStap(System.currentTimeMillis());
		txtMsg.setMsgType("AppMessage");    //消息类型
		txtMsg.setMsgTitle(title);			//消息标题(子类型)
		txtMsg.setMsgString(content);		//消息内容(请求信息)
		//txtMsg.setMsgType(msgType).setSendType(sendType);		//发送类别	
		//存入数据库
		AppMsgOperater appmsgdb = new AppMsgOperater();
		//消息持久化
		int MessageID = appmsgdb.addMessage(txtMsg);
		
		if(MessageID>0)
		{
			txtMsg.setMessageID(MessageID);
			AddOperaterLog(appId,5);
			//如果是应用消息，可能是即时消息
			ImdMessage.SendImmediateMessage(txtMsg);
		}
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
