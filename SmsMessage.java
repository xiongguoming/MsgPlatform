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
	
	//�绰�����б�
	private ArrayList<String> recArray = new ArrayList<String>();
	private UserInfo senderUser;
	private AppInfo senderApp;
	private int msgType;//0:�û���Ϣ,1:Ӧ����Ϣ,2:ϵͳ��Ϣ
	//���ý����б�
	public void SetReceiverList(ArrayList<String> recArray)
	{
		this.recArray = recArray;
	}
	//���÷�����
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
			//��ŵ��ж�һ��
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
		
		msg += "��������Ϣƽ̨��";
		//<content>
		msg += title;
		msg += ":";
		msg += content;
		String senderInfo = "";
		switch(msgType)
		{
		case 0://�û���Ϣ
			senderInfo = "-���Ժ��ѡ�"+senderUser.getUserName()+"������Ϣ";
			break;
		case 1://Ӧ����Ϣ
			senderInfo = "-����Ӧ�á�"+senderApp.getAppName()+"������Ϣ";
			break;
		case 2://ϵͳ��Ϣ
			senderInfo = "-����"+"ϵͳ"+"����Ϣ ";
			break;
		}
		msg += senderInfo;
		//</content>
		msg += "</content></message>";
		
		return msg;
	}
	//���Ͷ���(message:��Ϣ,recArray:�����б�)
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
            // WSDL���������Ľӿ�����(Ҫ���õķ���)  
            call.setOperationName("sendMessage");  
            // �ӿڷ����Ĳ�����, ��������,����ģʽ  IN(����), OUT(���) or INOUT(�������)���������ö������
            call.addParameter("message", XMLType.XSD_STRING, ParameterMode.IN);
            //call.addParameter("companyFlag", XMLType.XSD_STRING, ParameterMode.IN);  
            // ���ñ����÷����ķ���ֵ����  
            call.setReturnType(XMLType.XSD_STRING);  
            //���÷����в�����ֵ ����������ö��ŷָ� 
            Object[] paramValues = new Object[] {message};  
            // ���������ݲ��������ҵ��÷���  
            String result = (String) call.invoke(paramValues);    
      
            System.out.println("result is " + result);  
        } 
		catch (Exception e) {  
            e.printStackTrace();  
        }  
	}
}