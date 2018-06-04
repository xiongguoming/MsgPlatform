package com.webservice;

//import java.rmi.RemoteException;
import java.util.ArrayList;

import com.pojo.AppInfo;
import com.pojo.UserInfo;

import javax.xml.rpc.ParameterMode;
import org.apache.axis.client.Call;  
import org.apache.axis.client.Service;  
import org.apache.axis.encoding.XMLType;

public class SmsMessage {
	
	//电话号码列表
	private ArrayList<String> recArray = new ArrayList<String>();
	private UserInfo senderUser;
	private AppInfo senderApp;
	private int msgType;//0:用户消息,1:应用消息,2:系统消息
	//设置接收列表
	public void SetReceiverList(ArrayList<String> recArray)
	{
		this.recArray = recArray;
	}
	//设置发送者
	public void SetSenderUser(UserInfo senderUser)
	{
		this.senderUser = senderUser;
	}
	public void SetSenderApp(AppInfo senderApp)
	{
		this.senderApp = senderApp;
	}
	
	public String MakeSmsMessage(String title,String content)
	{
		String msg = "";
		String phone = "";
		msg += "<message><appkey>mportal</appkey><password>mportal_ecjtu</password><mobile>";
		for(int nIndex=0; nIndex<recArray.size(); nIndex++)
		{
			phone = recArray.get(nIndex);
			//大概的判断一下
			if(phone.length()!=11 || !phone.startsWith("1"))
			{
				continue;
			}
			msg += phone;
			if(nIndex<recArray.size()-1)
			{
				msg += ",";
			}
		}
		msg += "</mobile><content>";
		
		msg += "【测试消息平台】";
		//<content>
		msg += title;
		msg += ":";
		msg += content;
		String senderInfo = "";
		switch(msgType)
		{
		case 0://用户消息
			senderInfo = "-来自好友【"+senderUser.getUserName()+"】的消息";
			break;
		case 1://应用消息
			senderInfo = "-来自应用【"+senderApp.getAppName()+"】的消息";
			break;
		case 2://系统消息
			senderInfo = "-来自"+"系统"+"的消息 ";
			break;
		}
		msg += senderInfo;
		//</content>
		msg += "</content></message>";
		
		return msg;
	}
	//发送短信(message:消息,recArray:接收列表)
	public void SendSms(String title,String content,int msgType)
	{
		
		if(recArray.size()==0)
		{
			return;
		}
		this.msgType = msgType;
		
		String message = MakeSmsMessage(title,content);
		
		try {  
			  
            String endpoint = "http://oa.ecjtu.jx.cn:81/smsgate/services/base.intercept?wsdl";  
  
            Service service = new Service();  
            Call call = (Call) service.createCall();  
            call.setTargetEndpointAddress(endpoint);  
            // WSDL里面描述的接口名称(要调用的方法)  
            call.setOperationName("sendMessage");  
            // 接口方法的参数名, 参数类型,参数模式  IN(输入), OUT(输出) or INOUT(输入输出)，可以设置多个参数
            call.addParameter("message", XMLType.XSD_STRING, ParameterMode.IN);
            //call.addParameter("companyFlag", XMLType.XSD_STRING, ParameterMode.IN);  
            // 设置被调用方法的返回值类型  
            call.setReturnType(XMLType.XSD_STRING);  
            //设置方法中参数的值 ，多个参数用逗号分隔 
            Object[] paramValues = new Object[] {message};  
            // 给方法传递参数，并且调用方法  
            String result = (String) call.invoke(paramValues);    
      
            System.out.println("result is " + result);  
        } 
		catch (Exception e) {  
            e.printStackTrace();  
        }  
	}
}
