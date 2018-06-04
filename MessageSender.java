package com.sevlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.AsyncContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dbmanager.AppMsgOperater;
import com.dbmanager.SysMsgOperater;
import com.dbmanager.UserMsgOperater;
import com.message.MsgDispatch;
import com.message.TextMessage;
import com.system.JasonEncoding;


//ά����Ϣ���У�ͨ���������ݿ⣨��ѯ��������������������͵��ͻ���
public class MessageSender extends HttpServlet{

	private static final long serialVersionUID = 1L;
	
	private MsgDispatch msgTrans = null;
	
	public MessageSender() {
		super();
	}

	public void destroy() {
		super.destroy();
	}
	//ͨ���첽������Ϣ����
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		//��ʷ��Ϣ��������
		String optType = request.getParameter("type");
		//��ȡ
		if(optType.equals("history"))
		{
			//������Ϣ����
			String msgType = request.getParameter("msgtype");
			//��Ϣ������id
			String receiverID = request.getParameter("receiverid");
			//��ȡ��ʷ��Ϣ
			ArrayList<TextMessage> msgArray = ReadHistoryMessage(msgType,receiverID);
			//��֯json�ַ���
			JasonEncoding jasonOpt = new JasonEncoding();
			String jsonStr = jasonOpt.encodingUserMessage(msgArray);
			
			if(jsonStr.equals(""))
			{
				return;
			}
			//��Ӧ�ͻ���
			response.setContentType("text/html");
			PrintWriter out = null;
			try 
			{
				out = response.getWriter();
				out.println(jsonStr);               
				out.flush();
				out.close();
			} 
			catch (IOException e) 
			{
				e.printStackTrace();
			}
		}
		else
		{
			if(msgTrans != null)
			{
				AsyncContext act = request.startAsync();
				msgTrans.SetAsyncContext(act);
				
				Thread tasktd = new Thread(msgTrans);
				tasktd.start();
			}	
		}
		
	}
	
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		doGet(request,response);
	}
	public void init() throws ServletException {
		
		msgTrans = new MsgDispatch();
	}
	//��ȡ���ݿ��д洢����Ϣ
	public ArrayList<TextMessage> ReadHistoryMessage(String msgType,String receiverID)
	{
		if(msgType==null||receiverID==null)
		{
			return null;
		}
		UserMsgOperater umdb = new UserMsgOperater();
		AppMsgOperater appdb = new AppMsgOperater();
		SysMsgOperater sysdb = new SysMsgOperater();
		
		ArrayList<TextMessage> msgArray = new ArrayList<TextMessage>();
		
		switch(msgType)
		{
		case "usermsg":
			//receiverIDΪappId
			msgArray = umdb.getStorageMessage(receiverID);
			break;
		case "appmsg":
			//receiverIDΪuserId
			msgArray = appdb.getStorageMessage(receiverID);
			break;
		case "sysmsg":
			//receiverIDΪuserId
			msgArray = sysdb.getStorageMessage(receiverID);
			break;
		case "allmsg":
			//����APP���ݿ�ӿ�ֱ�ӻ�ȡ������ʷ��Ϣ
			msgArray = appdb.getHistoryMessage(receiverID);
			break;
		}
		
		return msgArray;
	}
}
