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
	
	//�˺�
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
	//����
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
	//�û���
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
	//�Ա�
	public int getSex()
	{
		return this.sex;
	}
	public void setSex(int sex)
	{
		this.sex = sex;
	}
	//Ȩ��
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
	//����Ȧ
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
	//��עӦ��
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
	//����״̬
	public boolean getOnlineStatus()
	{
		return this.onlineStatus;
	}
	
	public void setOnlineStatus(boolean onlineStatus)
	{
		this.onlineStatus = onlineStatus;
	}	
	//�绰����
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
	
	//�ʼ�
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
	
	//΢��
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