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
			case "registerapp"://注册应用
				RegisterApp(request,response);
				break;
			case "sendmessage"://发送应用消息
				SendAppMessage(request,response);
				break;
			case "totalapp"://获取所有应用
				GetTotalApp(request,response);
				break;
			case "focusapp"://用户关注应用
				UserFocusApp(request,response);
				break;
			case "totalfocus"://当前用户已关注应用
				GetFocusApps(request,response);
				break;
			case "cancelfocus"://取消关注用户
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
            //WSDL里面描述的接口名称(要调用的方法),指定命名空间，否则找不到函数
            call.setOperationName(new QName("http://appservice.com/", "registerApp"));
            // 接口方法的参数名, 参数类型,参数模式  IN(输入), OUT(输出) or INOUT(输入输出)，可以设置多个参数
            call.addParameter("appinfo", XMLType.XSD_STRING, ParameterMode.IN);
            // 设置被调用方法的返回值类型  
            call.setReturnType(XMLType.XSD_STRING);  
            //设置方法中参数的值 ，多个参数用逗号分隔 
            Object[] paramValues = new Object[] {regsterInfo};  
            // 给方法传递参数，并且调用方法  
            String result = (String) call.invoke(paramValues);    
      
            System.out.println("result is " + result);  
        } 
		catch (Exception e) 
		{  
            e.printStackTrace();  
        } 
	}
	//发送应用消息
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
