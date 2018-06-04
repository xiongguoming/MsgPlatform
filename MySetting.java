package com.sevlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.dbmanager.SettingOperater;
import com.dbmanager.UserOperater;
import com.system.*;
import com.pojo.SettingInfo;
import com.pojo.UserInfo;

public class MySetting extends HttpServlet {
	
	private static final long serialVersionUID = 1L;

	public MySetting() {
		super();
	}

	public void destroy() {
		super.destroy();
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		//��������
		String optType = request.getParameter("type");
		//׼�����
		response.setCharacterEncoding("UTF-8");
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		
		//�������
		String str = "error";
		boolean bResult = false;
		JasonEncoding jason = new JasonEncoding();
		
		switch(optType)
		{
		case "readuser":
			UserInfo user = ReadUser(request,response);
			if(user != null)
			{
				str = jason.encodingOnlyUser(user);
			}
			break;
		case "saveuser":
			bResult = SaveUser(request,response);
			if(bResult)
			{
				str = "success";
			}
			else
			{
				str = "error";
			}
			break;
		case "readpolicy":
			SettingInfo setting = ReadPolicy(request,response);
			str = jason.encodingMySettingInfo(setting);
			break;
		case "savepolicy":
			bResult = SavePolicy(request,response);
			if(bResult)
			{
				str = "success";
			}
			else
			{
				str = "error";
			}
			break;	
		}
		//����ַ���
		out.println(str);
		out.flush();
		out.close();
		
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		doGet(request,response);
	}
	
	//���������Ϣ����
	public boolean SavePolicy(HttpServletRequest request, HttpServletResponse response)  {
		
		String str = "";
		SettingInfo setting = new SettingInfo();
		//�û�ID
		str = request.getParameter("userid");
		setting.setUserID(str);
		//����������Ϣ
		str = request.getParameter("recAllMsg");
		if(str.equals("open"))
		{
			setting.setIsReceiveAllMsg(true);
		}
		else
		{
			setting.setIsReceiveAllMsg(false);
		}
		
		//����ʱ��
		str = request.getParameter("recTime");
		if(str.equals("open"))
		{
			setting.setIsSetReceiveTime(true);
		}
		else
		{
			setting.setIsSetReceiveTime(false);
		}
		str = request.getParameter("startTime");
		setting.setStartRecTime(str);
		str = request.getParameter("endTime");
		setting.setEndRecTime(str);
		//��Ϣ����
		str = request.getParameter("sysMsgPolicy");
		setting.setSysMsgPolicy(str);
		str = request.getParameter("appMsgPolicy");
		setting.setAppMsgPolicy(str);
		str = request.getParameter("userMsgPolicy");
		setting.setUserMsgPolicy(str);
		
		SettingOperater dbOpt = new SettingOperater();
		
		dbOpt.setMySettingInfo(setting);
		//��������
		if(dbOpt.saveMySetting())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//��ȡ����
	public SettingInfo ReadPolicy(HttpServletRequest request, HttpServletResponse response) {
		
		String str = "";
		SettingInfo setting = new SettingInfo();
		//�û�ID
		str = request.getParameter("userid");
		setting.setUserID(str);
		//���ݿ����
		SettingOperater dbOpt = new SettingOperater();
		
		dbOpt.setMySettingInfo(setting);
		setting = dbOpt.readMySetting(setting.getUserID());
		
		return setting;
	}
	
	public UserInfo ReadUser(HttpServletRequest request, HttpServletResponse response){
			
		String userID = request.getParameter("userid");
		UserOperater dbUser = new UserOperater();
		UserInfo  userInfo = dbUser.readUser(userID);
		
		return userInfo;
	}
	
	public boolean SaveUser(HttpServletRequest request, HttpServletResponse response){
		
		boolean bResult = false;
		UserOperater dbUser = new UserOperater();
		String userID =  request.getParameter("userid");
		UserInfo userInfo = dbUser.readUser(userID);
		userInfo.setUserID(request.getParameter("userid"));
		String userName = request.getParameter("userName");
		try 
        {
			userName = java.net.URLDecoder.decode(userName, "UTF-8");
		} 
        catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		userInfo.setUserName(userName);
		userInfo.setPassword(request.getParameter("password"));
		userInfo.setTelephone(request.getParameter("telephone"));
		userInfo.setEmail(request.getParameter("email"));
		userInfo.setWeixin(request.getParameter("weixin"));
		
		bResult = dbUser.saveUser(userInfo);
		
		return bResult;
	}
	
	public void init() throws ServletException {
		// Put your code here
	}

}
