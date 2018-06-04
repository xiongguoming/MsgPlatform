package com.webservice;

import java.util.Date;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;

import com.dbmanager.AppMsgOperater;
import com.dbmanager.AppOperater;
import com.dbmanager.LogOperater;
import com.message.ImmediateMessage;
import com.message.TextMessage;
import com.pojo.AppInfo;
import com.pojo.MsgLog;
import com.system.XmlAppInfo;


@WebService(serviceName="AppService",targetNamespace="http://appservice.com/")
public class AppService {
	
	/*
	 * 发布的函数至少要求对参数名称进行注解，否则客户端无法正确调用该函数
	 * 注解包括：函数名注解，返回值注解，参数名注解
	 * 功能：外部应用注册，参数-appinfo,应用信息
	 * 返回值：注册结果
	 * */
    @WebMethod(operationName="registerApp")
	public @WebResult(name="result")String registerApp(@WebParam(name="appinfo")String appinfo)
	{
    	XmlAppInfo xmlApp = new XmlAppInfo();
    	AppInfo appInfo = xmlApp.parseRegInfoApp(appinfo);
    	AppOperater appdb = new AppOperater();
    	//保存到数据库
    	if(appInfo != null)
    	{
    		if(appdb.saveApp(appInfo))
    		{
    			return "sucess";
    		}
    		else
    		{
    			return "error";
    		}
    	}
    	
    	return "error";
	}
    /*
	 * 发布的函数至少要求对参数名称进行注解，否则客户端无法正确调用该函数
	 * 注解包括：函数名注解，返回值注解，参数名注解
	 * 功能：外部应用发送消息，参数-message,XML格式消息
	 * 返回值：注册结果
	 * */
    @WebMethod(operationName="sendMessage")
	public @WebResult(name="result")String sendMessage(@WebParam(name="message")String message)
	{
    	//message的格式为：应用ID(5字节)+发送方式（4字节）+发送内容
    	//System.out.print("sendMessage："+message+"\n");
    	String res = "发送失败";
    	String appId = message.substring(0, 5);
    	String sendType = message.substring(5, 9);
    	String title = "来自外部应用的消息";
    	String content = message.substring(9);
    	
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
		
		//存入数据库
		AppMsgOperater appmsgdb = new AppMsgOperater();
		//消息持久化
		int MessageID = appmsgdb.addMessage(txtMsg);
		
		if(MessageID>0)
		{
			txtMsg.setMessageID(MessageID);
			
			String remark = "";
			MsgLog log = new MsgLog();
			long occTime = new Date().getTime();
			
			//外部应用
			log.addLog(appId, 6, occTime, remark);
			LogOperater dbLog = new LogOperater();
			dbLog.SaveLog(log);
			
			ImmediateMessage imdtMsg = new ImmediateMessage();
			imdtMsg.SendImmediateMessage(txtMsg);
			
			res = "发送成功";
		}
    	
		return res;
	}
	
	//通过注解，该方法不对外公布
	@WebMethod(exclude=true)
	public void SaveRegisterInfo()
	{
		
	}
}
