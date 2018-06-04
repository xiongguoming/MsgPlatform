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


//维护消息队列，通过监听数据库（轮询），分析监听结果并发送到客户端
public class MessageSender extends HttpServlet{

	private static final long serialVersionUID = 1L;
	
	private MsgDispatch msgTrans = null;
	
	public MessageSender() {
		super();
	}

	public void destroy() {
		super.destroy();
	}
	//通过异步处理消息调度
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		//历史消息不进调度
		String optType = request.getParameter("type");
		//获取
		if(optType.equals("history"))
		{
			//接收消息类型
			String msgType = request.getParameter("msgtype");
			//消息接收者id
			String receiverID = request.getParameter("receiverid");
			//读取历史消息
			ArrayList<TextMessage> msgArray = ReadHistoryMessage(msgType,receiverID);
			//组织json字符串
			JasonEncoding jasonOpt = new JasonEncoding();
			String jsonStr = jasonOpt.encodingUserMessage(msgArray);
			
			if(jsonStr.equals(""))
			{
				return;
			}
			//响应客户端
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
	//读取数据库中存储的消息
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
			//receiverID为appId
			msgArray = umdb.getStorageMessage(receiverID);
			break;
		case "appmsg":
			//receiverID为userId
			msgArray = appdb.getStorageMessage(receiverID);
			break;
		case "sysmsg":
			//receiverID为userId
			msgArray = sysdb.getStorageMessage(receiverID);
			break;
		case "allmsg":
			//借助APP数据库接口直接获取所有历史消息
			msgArray = appdb.getHistoryMessage(receiverID);
			break;
		}
		
		return msgArray;
	}
}
