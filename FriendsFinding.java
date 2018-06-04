package com.sevlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.dbmanager.UserOperater;
import com.system.JasonEncoding;
import com.pojo.UnitArray;
import com.pojo.UserArray;


public class FriendsFinding extends HttpServlet {

	private static final long serialVersionUID = 1L;

	public FriendsFinding() {
		super();
	}

	public void destroy() {
		super.destroy(); 
	}
		
	public String ReadUnits() {
		
		String strJson = "";
		UserOperater dbUser = new UserOperater();
		UnitArray unitArray = new UnitArray();
		unitArray = dbUser.readUnits();
		
		if(unitArray != null)
		{
			JasonEncoding jsonObj = new JasonEncoding();
			strJson = jsonObj.encodingUnits(unitArray);
		}
		return strJson;
	}
	
	public String ReadUsers() {
		
		String strJson = "";
		UserOperater dbUser = new UserOperater();
		UserArray userArray = new UserArray();
		userArray = dbUser.readUsers();
		
		if(userArray != null)
		{
			JasonEncoding jsonObj = new JasonEncoding();
			strJson = jsonObj.encodingUsers(userArray);
		}
		return strJson;
	}
	
	public String ReadFriends(String userID){
		
		String strJson = "";
		UserOperater dbUser = new UserOperater();
		UserArray userArray = new UserArray();
		userArray = dbUser.readFriends(userID);
		if(userArray != null)
		{
			JasonEncoding jsonObj = new JasonEncoding();
			strJson = jsonObj.encodingUsers(userArray);
		}
		return strJson;
	}
	
	public String DeleteFriend(String userID,String delUserID){
		
		String strJson = "";
		UserOperater dbUser = new UserOperater();
		
		if(dbUser.DeleteFriend(userID,delUserID))
		{
			strJson = "success";
		}
		else
		{
			strJson = "error";
		}
		return strJson;
	}
	
	
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		
		String strjson = "";
		String optType = request.getParameter("type");
		
		if(optType.equals("readunit"))
		{
			strjson = ReadUnits();
			out.println(strjson);               
		}
		if(optType.equals("readuser"))
		{
			strjson = ReadUsers();
			out.println(strjson);
		}
		if(optType.equals("readfriend"))
		{
			String userID = request.getParameter("userid");
			strjson = ReadFriends(userID);
			out.println(strjson);
		}
		if(optType.equals("deletefriend"))
		{
			String userID = request.getParameter("userid");
			String delUserID = request.getParameter("deluserid");
			
			strjson = DeleteFriend(userID,delUserID);
			//out.println(strjson);
		}
		
		//var url = "/MsgService/FriendsFinding?deluserid="+userID+"&type=deletefriend";
		
		out.flush();
		out.close();
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

	}

	public void init() throws ServletException {
		// Put your code here
	}

}
