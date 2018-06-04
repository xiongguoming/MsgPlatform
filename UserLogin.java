package com.sevlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.dbmanager.*;
import com.pojo.AppInfo;
import com.pojo.UserInfo;

public class UserLogin extends HttpServlet {

	private static final long serialVersionUID = 1L;

	public UserLogin() {
		super();
	}

	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		HttpSession session = request.getSession(true);
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		
		String method = request.getParameter("method");
		if(method == null)
		{
			return;
		}
		//登录
		if(method.equals("login"))
		{
			String userType = request.getParameter("type");
			String account = request.getParameter("account");
			String password = request.getParameter("password");
			
			if(userType.compareTo("user") == 0)
			{
				if(checkUserLoading(session,account,password))
				{
					out.println("success");
				}
				else
				{
					out.println("failed");
				}
			}
			//应用登录
			else
			{
				if(checkAppLoading(session,account,password))
				{
					out.println("success");
				}
				else
				{
					out.println("failed");
				}
			}
		}
		//注销
		else
		{
			session.removeAttribute("user");
			session.removeAttribute("app");
			RequestDispatcher rdis = request.getRequestDispatcher("index.jsp");
			if(rdis != null)
			{
				rdis.forward(request,response);
			}
		}
	}
	
	public boolean checkUserLoading(HttpSession session, String account,String password)
	{
		UserOperater userdb = new UserOperater();
		UserInfo user = userdb.readUser(account);
		//验证通过
		if(userdb.CheckLogin(account, password))
		{
			session.setAttribute("user", user);
			return true;
		}
		
		return false;	
	}
	
	public boolean checkAppLoading(HttpSession session, String account,String password)
	{
		AppOperater appdb = new AppOperater();
		AppInfo app = appdb.readApp(account);
		//验证通过
		if(password.compareTo(app.getPassword()) == 0)
		{
			session.setAttribute("app", app);
			return true;
		}
		
		return false;		
	}
	
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doGet(request,response);
	}

	public void init() throws ServletException {
		// Put your code here
	}

}
