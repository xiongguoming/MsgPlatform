package com.sevlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;

import org.apache.axis.client.Call;
import org.apache.axis.client.Service;
import org.apache.axis.encoding.XMLType;

import com.dbmanager.AppOperater;
import com.pojo.AppArray;
import com.pojo.AppInfo;
import com.system.JasonEncoding;
import com.system.XmlAppInfo;

public class AppServiceEx extends HttpServlet {

	private static final long serialVersionUID = 1L;

	public AppServiceEx() {
		super();
	}

	public void destroy() {
		super.destroy();
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		String optType = request.getParameter("type");
		switch(optType)
		{
			case "registerapp"://ע��Ӧ��
				RegisterApp(request,response);
				break;
			case "sendmessage"://����Ӧ����Ϣ
				SendAppMessage(request,response);
				break;
			case "totalapp"://��ȡ����Ӧ��
				GetTotalApp(request,response);
				break;
			case "focusapp"://�û���עӦ��
				UserFocusApp(request,response);
				break;
			case "totalfocus"://��ǰ�û��ѹ�עӦ��
				GetFocusApps(request,response);
				break;
			case "cancelfocus"://ȡ����ע�û�
				CancelFocusApp(request,response);
				break;
				
		}
	}
	public void CancelFocusApp(HttpServletRequest request, HttpServletResponse response)
	{
		String appId = request.getParameter("appid");
		String userId = request.getParameter("userid");
		
		AppOperater dbApp = new AppOperater();
		
		boolean res = dbApp.CancelFocusApp(userId,appId);
		
		try
		{
			response.setContentType("text/html");
			PrintWriter out = response.getWriter();
			if(res)
			{
				out.println("success");
			}
			else
			{
				out.println("failed");
			}
			out.flush();
			out.close();
		}
		catch(Exception e) 
		{
			e.printStackTrace();
		}	
	}
	public void GetFocusApps(HttpServletRequest request, HttpServletResponse response)
	{
		AppOperater dbApp = new AppOperater();
		String userId = request.getParameter("userid");
		String focusApps = dbApp.GetFocusApps(userId);
		
		try
		{
			response.setContentType("text/html");
			PrintWriter out = response.getWriter();
			out.println(focusApps);
			out.flush();
			out.close();
		}
		catch(Exception e) 
		{
			e.printStackTrace();
		}
	}
	public void UserFocusApp(HttpServletRequest request, HttpServletResponse response)
	{
		String appId = request.getParameter("appid");
		String userId = request.getParameter("userid");
		
		AppOperater dbApp = new AppOperater();
		
		int resId = dbApp.UserFocusApp(userId,appId);
		
		try
		{
			response.setContentType("text/html");
			PrintWriter out = response.getWriter();
			
			if(resId>=0)
			{
				out.println("success");
			}
			else
			{
				out.println("failed");
			}
			out.flush();
			out.close();
		}
		catch(Exception e) 
		{
			e.printStackTrace();
		}	
	}
	public void GetTotalApp(HttpServletRequest request, HttpServletResponse response)
	{
		String strJson = "";
		AppOperater dbApp = new AppOperater();
		AppArray appArray = new AppArray();
		appArray = dbApp.readAllApps();
		
		if(appArray != null)
		{
			JasonEncoding jsonObj = new JasonEncoding();
			strJson = jsonObj.encodingApps(appArray);
		}
		try
		{
			response.setContentType("text/html");
			PrintWriter out = response.getWriter();
			
			out.println(strJson);
			out.flush();
			out.close();
		}
		catch(Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	public void RegisterApp(HttpServletRequest request, HttpServletResponse response)
	{
		String appId = request.getParameter("appId");
		String appName = request.getParameter("appName");
		String password = request.getParameter("password");
		String appType = request.getParameter("appType");
		String phone = request.getParameter("phone");
		String icon = request.getParameter("icon");
		String remark = request.getParameter("remark");
		
		AppInfo app = new AppInfo();
		app.setAppId(appId);
		app.setAppName(appName);
		app.setPassword(password);
		app.setAppType(Integer.parseInt(appType));
		app.setPhone(phone);
		app.setIcon(icon);
		app.setRemark(remark);
		
		XmlAppInfo xmlApp = new XmlAppInfo();
		String regsterInfo = xmlApp.parseRegInfoXml(app);
		
		try {  
            String endpoint = "http://localhost:8888/app/service?wsdl";  
 
            Service service = new Service();  
            Call call = (Call) service.createCall();  
            call.setTargetEndpointAddress(endpoint);
            //WSDL���������Ľӿ�����(Ҫ���õķ���),ָ�������ռ䣬�����Ҳ�������
            call.setOperationName(new QName("http://appservice.com/", "registerApp"));
            // �ӿڷ����Ĳ�����, ��������,����ģʽ  IN(����), OUT(���) or INOUT(�������)���������ö������
            call.addParameter("appinfo", XMLType.XSD_STRING, ParameterMode.IN);
            // ���ñ����÷����ķ���ֵ����  
            call.setReturnType(XMLType.XSD_STRING);  
            //���÷����в�����ֵ ����������ö��ŷָ� 
            Object[] paramValues = new Object[] {regsterInfo};  
            // ���������ݲ��������ҵ��÷���  
            String result = (String) call.invoke(paramValues);    
      
            System.out.println("result is " + result);  
        } 
		catch (Exception e) 
		{  
            e.printStackTrace();  
        } 
	}
	//����Ӧ����Ϣ
	public void SendAppMessage(HttpServletRequest request, HttpServletResponse response)
	{
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doGet(request,response);
	}

	public void init() throws ServletException {
		// Put your code here
	}

}
