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
	 * �����ĺ�������Ҫ��Բ������ƽ���ע�⣬����ͻ����޷���ȷ���øú���
	 * ע�������������ע�⣬����ֵע�⣬������ע��
	 * ���ܣ��ⲿӦ��ע�ᣬ����-appinfo,Ӧ����Ϣ
	 * ����ֵ��ע����
	 * */
    @WebMethod(operationName="registerApp")
	public @WebResult(name="result")String registerApp(@WebParam(name="appinfo")String appinfo)
	{
    	XmlAppInfo xmlApp = new XmlAppInfo();
    	AppInfo appInfo = xmlApp.parseRegInfoApp(appinfo);
    	AppOperater appdb = new AppOperater();
    	//���浽���ݿ�
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
	 * �����ĺ�������Ҫ��Բ������ƽ���ע�⣬����ͻ����޷���ȷ���øú���
	 * ע�������������ע�⣬����ֵע�⣬������ע��
	 * ���ܣ��ⲿӦ�÷�����Ϣ������-message,XML��ʽ��Ϣ
	 * ����ֵ��ע����
	 * */
    @WebMethod(operationName="sendMessage")
	public @WebResult(name="result")String sendMessage(@WebParam(name="message")String message)
	{
    	//message�ĸ�ʽΪ��Ӧ��ID(5�ֽ�)+���ͷ�ʽ��4�ֽڣ�+��������
    	//System.out.print("sendMessage��"+message+"\n");
    	String res = "����ʧ��";
    	String appId = message.substring(0, 5);
    	String sendType = message.substring(5, 9);
    	String title = "�����ⲿӦ�õ���Ϣ";
    	String content = message.substring(9);
    	
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
		
		//�������ݿ�
		AppMsgOperater appmsgdb = new AppMsgOperater();
		//��Ϣ�־û�
		int MessageID = appmsgdb.addMessage(txtMsg);
		
		if(MessageID>0)
		{
			txtMsg.setMessageID(MessageID);
			
			String remark = "";
			MsgLog log = new MsgLog();
			long occTime = new Date().getTime();
			
			//�ⲿӦ��
			log.addLog(appId, 6, occTime, remark);
			LogOperater dbLog = new LogOperater();
			dbLog.SaveLog(log);
			
			ImmediateMessage imdtMsg = new ImmediateMessage();
			imdtMsg.SendImmediateMessage(txtMsg);
			
			res = "���ͳɹ�";
		}
    	
		return res;
	}
	
	//ͨ��ע�⣬�÷��������⹫��
	@WebMethod(exclude=true)
	public void SaveRegisterInfo()
	{
		
	}
}
