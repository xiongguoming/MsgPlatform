package com.pojo;

public class UserInfo 
{
	private String userID = "";
	private String password = "";
	private String userName = "";
	private int sex = 0;
	private int right = 0;
	private int unitID = 0;
	private String friendCircle = "";
	private String focusApp = "";
	private boolean onlineStatus = false;
	private String telephone = "";
	private String email = "";
	private String weixin = "";
	private int score = 0;
	
	//账号
	public String getUserID()
	{
		return this.userID;
	}
	public void setUserID(String userID)
	{
		if(userID == null)
		{
			userID = "";
		}
		this.userID = userID;
	}
	//密码
	public String getPassword()
	{
		return this.password;
	}
	
	public void setPassword(String password)
	{
		if(password == null)
		{
			password = "";
		}
		this.password = password;
	}
	//用户名
	public String getUserName()
	{
		return this.userName;
	}
	
	public void setUserName(String userName)
	{
		if(userName == null)
		{
			userName = "";
		}
		this.userName = userName;
	}
	//性别
	public int getSex()
	{
		return this.sex;
	}
	public void setSex(int sex)
	{
		this.sex = sex;
	}
	//权限
	public int getRight()
	{
		return this.right;
	}
	public void setRight(int right)
	{
		this.right = right;
	}
	public int getUnitID()
	{
		return this.unitID;
	}
	public void setUnitID(int unitID)
	{
		this.unitID = unitID;
	}
	public int getScore()
	{
		return this.score;
	}
	public void setScore(int score)
	{
		this.score = score;
	}
	//朋友圈
	public String getFriendCircle()
	{
		return this.friendCircle;
	}
	
	public void setFriendCircle(String friendCircle)
	{
		if(friendCircle == null)
		{
			friendCircle = "";
		}
		this.friendCircle = friendCircle;
	}
	//关注应用
	public String getFocusApp()
	{
		return this.focusApp;
	}
	
	public void setFocusApp(String focusApp)
	{
		if(focusApp == null)
		{
			focusApp = "";
		}
		this.focusApp = focusApp;
	}
	//在线状态
	public boolean getOnlineStatus()
	{
		return this.onlineStatus;
	}
	
	public void setOnlineStatus(boolean onlineStatus)
	{
		this.onlineStatus = onlineStatus;
	}	
	//电话号码
	public String getTelephone()
	{
		return this.telephone;
	}
	
	public void setTelephone(String telephone)
	{
		if(telephone == null)
		{
			telephone = "";
		}
		this.telephone = telephone;
	}
	
	//邮件
	public String getEmail()
	{
		return this.email;
	}
	
	public void setEmail(String email)
	{
		if(email == null)
		{
			email = "";
		}
		this.email = email;
	}
	
	//微信
	public String getWeixin()
	{
		return this.weixin;
	}
	
	public void setWeixin(String weixin)
	{
		if(weixin == null)
		{
			weixin = "";
		}
		this.weixin = weixin;
	}	
}