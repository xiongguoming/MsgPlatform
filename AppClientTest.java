package com.webservice;

import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;
import org.apache.axis.client.Call;  
import org.apache.axis.client.Service;  
import org.apache.axis.encoding.XMLType;

public class AppClientTest {

	//注册
	public void Register(String xmlApp,String strIcon)
	{
		try {  
			  
            String endpoint = "http://localhost:8888/app/service?wsdl";  
  
            Service service = new Service();  
            Call call = (Call) service.createCall();  
            call.setTargetEndpointAddress(endpoint);
            //WSDL里面描述的接口名称(要调用的方法),指定命名空间，否则找不到函数
            call.setOperationName(new QName("http://appservice.com/", "registerApp"));
            // 接口方法的参数名, 参数类型,参数模式  IN(输入), OUT(输出) or INOUT(输入输出)，可以设置多个参数
            call.addParameter("appinfo", XMLType.XSD_STRING, ParameterMode.IN);
            call.addParameter("iconpath", XMLType.XSD_STRING, ParameterMode.IN); 
            // 设置被调用方法的返回值类型  
            call.setReturnType(XMLType.XSD_STRING);  
            //设置方法中参数的值 ，多个参数用逗号分隔 
            Object[] paramValues = new Object[] {xmlApp,strIcon};  
            // 给方法传递参数，并且调用方法  
            String result = (String) call.invoke(paramValues);    
      
            System.out.println("result is " + result);  
        } 
		catch (Exception e) {  
            e.printStackTrace();  
        }  
	}
	//发送消息
	public void SendMessage(String xmlMsg)
	{		
		try {  
			  
            String endpoint = "http://localhost:8888/app/service?wsdl";
  
            Service service = new Service();  
            Call call = (Call) service.createCall();  
            call.setTargetEndpointAddress(endpoint); 
            //WSDL里面描述的接口名称(要调用的方法),指定命名空间，否则找不到函数
            call.setOperationName(new QName("http://webservice.com/", "sendMessage")); 
            // 接口方法的参数名, 参数类型,参数模式  IN(输入), OUT(输出) or INOUT(输入输出)，可以设置多个参数
            call.addParameter("message", XMLType.XSD_STRING, ParameterMode.IN);
            //call.addParameter("companyFlag", XMLType.XSD_STRING, ParameterMode.IN);  
            // 设置被调用方法的返回值类型  
            call.setReturnType(XMLType.XSD_STRING);  
            //设置方法中参数的值 ，多个参数用逗号分隔 
            Object[] paramValues = new Object[] {xmlMsg};  
            // 给方法传递参数，并且调用方法  
            String result = (String) call.invoke(paramValues);    
      
            System.out.println("result is " + result);  
        } 
		catch (Exception e) {  
            e.printStackTrace();  
        }  
	}

}
