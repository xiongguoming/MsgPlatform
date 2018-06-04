package com.webservice;

import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;
import org.apache.axis.client.Call;  
import org.apache.axis.client.Service;  
import org.apache.axis.encoding.XMLType;

public class AppClientTest {

	//ע��
	public void Register(String xmlApp,String strIcon)
	{
		try {  
			  
            String endpoint = "http://localhost:8888/app/service?wsdl";  
  
            Service service = new Service();  
            Call call = (Call) service.createCall();  
            call.setTargetEndpointAddress(endpoint);
            //WSDL���������Ľӿ�����(Ҫ���õķ���),ָ�������ռ䣬�����Ҳ�������
            call.setOperationName(new QName("http://appservice.com/", "registerApp"));
            // �ӿڷ����Ĳ�����, ��������,����ģʽ  IN(����), OUT(���) or INOUT(�������)���������ö������
            call.addParameter("appinfo", XMLType.XSD_STRING, ParameterMode.IN);
            call.addParameter("iconpath", XMLType.XSD_STRING, ParameterMode.IN); 
            // ���ñ����÷����ķ���ֵ����  
            call.setReturnType(XMLType.XSD_STRING);  
            //���÷����в�����ֵ ����������ö��ŷָ� 
            Object[] paramValues = new Object[] {xmlApp,strIcon};  
            // ���������ݲ��������ҵ��÷���  
            String result = (String) call.invoke(paramValues);    
      
            System.out.println("result is " + result);  
        } 
		catch (Exception e) {  
            e.printStackTrace();  
        }  
	}
	//������Ϣ
	public void SendMessage(String xmlMsg)
	{		
		try {  
			  
            String endpoint = "http://localhost:8888/app/service?wsdl";
  
            Service service = new Service();  
            Call call = (Call) service.createCall();  
            call.setTargetEndpointAddress(endpoint); 
            //WSDL���������Ľӿ�����(Ҫ���õķ���),ָ�������ռ䣬�����Ҳ�������
            call.setOperationName(new QName("http://webservice.com/", "sendMessage")); 
            // �ӿڷ����Ĳ�����, ��������,����ģʽ  IN(����), OUT(���) or INOUT(�������)���������ö������
            call.addParameter("message", XMLType.XSD_STRING, ParameterMode.IN);
            //call.addParameter("companyFlag", XMLType.XSD_STRING, ParameterMode.IN);  
            // ���ñ����÷����ķ���ֵ����  
            call.setReturnType(XMLType.XSD_STRING);  
            //���÷����в�����ֵ ����������ö��ŷָ� 
            Object[] paramValues = new Object[] {xmlMsg};  
            // ���������ݲ��������ҵ��÷���  
            String result = (String) call.invoke(paramValues);    
      
            System.out.println("result is " + result);  
        } 
		catch (Exception e) {  
            e.printStackTrace();  
        }  
	}

}
