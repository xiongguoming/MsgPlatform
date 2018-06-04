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
//��Ҫִ����Ϣ�����־û�����ϢͶ�ݹ���
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
		case "requestfriend":	//ϵͳ��Ϣ-��Ӻ�����Ϣ
			RequestFriend(request,response);
			break;
		case "replyfriend":		//ϵͳ��Ϣ-��Ӻ��ѻظ���Ϣ
			ReplyFriend(request,response);
			break;
		case "usermsg":	    	//�û���Ϣ-������Ϣ
			SendUserMessage(request,response);
			break;
		case "readmsg":			//�޸���Ϣ���Ѷ�״̬
			ReadMessage(request,response);
			break;
		case "deletemsg":		//ɾ����Ϣ
			DeleteMessage(request,response);
			break;
		case "appmsg":  		//APP������Ϣ
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

	//�����û���Ϣ,type=0
	public void SendUserMessage(HttpServletRequest request, HttpServletResponse response)
	{
		String receiverID = request.getParameter("receiverid");
		String senderID = request.getParameter("senderid");
		String title = request.getParameter("title");
		String content = request.getParameter("content");
		
		TextMessage txtMsg = new TextMessage();
		
		//��Ϣͷ
		txtMsg.setSenderID(senderID);
		txtMsg.setReceiverID(receiverID);
		//����
		txtMsg.setTimeStap(System.currentTimeMillis());
		txtMsg.setMsgType("UserMessage");   //��Ϣ����
		txtMsg.setMsgTitle(title);			//��Ϣ����(������)
		txtMsg.setMsgString(content);		//��Ϣ����(������Ϣ)
		
		//�������ݿ�
		UserMsgOperater msgdb = new UserMsgOperater();
		//��Ϣ�־û�
		int MessageID = msgdb.addMessage(txtMsg);
		
		if(MessageID>0)
		{
			txtMsg.setMessageID(MessageID);
			AddOperaterLog(senderID,0);
			
			//������û���Ϣ�������Ǽ�ʱ��Ϣ
			ImdMessage.SendImmediateMessage(txtMsg);
		}	
	}
	
	//������Ӻ���,type=1
	public void RequestFriend(HttpServletRequest request, HttpServletResponse response) {
		
		String senderID = request.getParameter("senderid");
		String receiverID = request.getParameter("receiverid");
		String rqContent = request.getParameter("rqcontent");
			
		TextMessage txtMsg = new TextMessage();
		//��Ϣͷ
		txtMsg.setSenderID(senderID);
		txtMsg.setReceiverID(receiverID);
		txtMsg.setTimeStap(System.currentTimeMillis());
		txtMsg.setMsgType("SysMessage");    //��Ϣ����
		txtMsg.setMsgTitle("AddFriend");	//��Ϣ����(ϵͳ��Ϣ-������)
		txtMsg.setMsgString(rqContent);		//��Ϣ����(������Ϣ)
		
		//������Ϣ
		SysMsgOperater msgdb = new SysMsgOperater();
		msgdb.addMessage(txtMsg);
		//ϵͳ��Ϣ-Ĭ�����з�ʽ���������û�������ԣ�
		ImdMessage.SendImmediateMessage(txtMsg);
		
		AddOperaterLog(senderID,1);
	}
	//���Ժ��ѵĻظ�(��Ӻ���),type=2
	public void ReplyFriend(HttpServletRequest request, HttpServletResponse response)
	{
		String reply = request.getParameter("reply");//agree/disagree
		String msgid = request.getParameter("msgid");
		
		if(reply==null || msgid==null)
		{
			return;
		}	
		
		//��ȡԴ��Ϣ
		if(msgid.contains("SYS"))
		{
			msgid = msgid.substring(3);
		}
		
		SysMsgOperater msgdb = new SysMsgOperater();
		TextMessage origmsg = msgdb.getMessageById(msgid);
		
		//����ͨ���������շ����û��ĺ����б�
		if(reply.equals("agree"))
		{
			UserOperater userdb = new UserOperater();
			userdb.MakeFriend(origmsg.getSenderID().substring(7),origmsg.getReceiverID());
			
			//�����ѻظ�����Ϣ�ķ�ʽ֪ͨ�Է�
			TextMessage newmsg = new TextMessage();
			
			//��Ϣͷ
			newmsg.setSenderID(origmsg.getReceiverID());
			newmsg.setReceiverID(origmsg.getSenderID().substring(7));
			//����
			newmsg.setTimeStap(System.currentTimeMillis());
			newmsg.setMsgType("SysMessage");    //��Ϣ����
			newmsg.setMsgTitle("ReplyFriend");	//��Ϣ����(ϵͳ��Ϣ-������)
			newmsg.setMsgString(reply);			//��Ϣ����(agree/disagree)
			//��Ϣ�洢ϵͳ��Ϣ
			msgdb.addMessage(newmsg);
			//ϵͳ��Ϣ-Ĭ�����з�ʽ���������û�������ԣ�
			ImdMessage.SendImmediateMessage(newmsg);
			AddOperaterLog(origmsg.getSenderID(),2);
		}
	}
	
	//��Ϣ�Ѷ�,type=3
	public void ReadMessage(HttpServletRequest request, HttpServletResponse response)
	{
		//��ǰ�˷���������ID��ʽΪ��USER(APP/SYS)+ID����USER123
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
	
	//ɾ����Ϣ,type=4
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
	//����Ӧ����Ϣ,type=5
	public void SendAppMessage(HttpServletRequest request, HttpServletResponse response)
	{
		String appId = request.getParameter("appId");
		String title = request.getParameter("title");
		String content = request.getParameter("content");
		String sendType = request.getParameter("sendType");
		
		//�ı�����Ϣ
		TextMessage txtMsg = new TextMessage();
		
		//��Ϣͷ
		txtMsg.setSenderID(appId);
		//Ӧ����Ϣ��ϵͳ�Զ����͵���ע�û�,�˴��洢��Ϣ�����ն�
		txtMsg.setReceiverID(sendType);
		
		txtMsg.setTimeStap(System.currentTimeMillis());
		txtMsg.setMsgType("AppMessage");    //��Ϣ����
		txtMsg.setMsgTitle(title);			//��Ϣ����(������)
		txtMsg.setMsgString(content);		//��Ϣ����(������Ϣ)
		//txtMsg.setMsgType(msgType).setSendType(sendType);		//�������	
		//�������ݿ�
		AppMsgOperater appmsgdb = new AppMsgOperater();
		//��Ϣ�־û�
		int MessageID = appmsgdb.addMessage(txtMsg);
		
		if(MessageID>0)
		{
			txtMsg.setMessageID(MessageID);
			AddOperaterLog(appId,5);
			//�����Ӧ����Ϣ�������Ǽ�ʱ��Ϣ
			ImdMessage.SendImmediateMessage(txtMsg);
		}
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
