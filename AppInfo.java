package com.pojo;

public class AppInfo {
	
	private String appId="";
	private String appName="";
	private int appType=1;//1-��Ϣ��,2-Ӧ����
	private String password="";
	private String phone="";
	private String icon="";
	private String remark="";
	private String regTime="";
	private int status=0;//0-����ˣ�1-���ͨ����2-������
	private String describe;//״̬����
	private int score=24;
	
	
	public void setAppId(String appId)
	{
		if(appId!=null)
		{
			this.appId = appId;
		}
	}
	
	public String getAppId()
	{
		return this.appId;	
	}
	
	public void setAppName(String appName)
	{
		if(appName!=null)
		{
			this.appName = appName;	
		}
	}
	
	public String getAppName()
	{
		return this.appName;	
	}
	
	public void setAppType(int appType)
	{
		this.appType = appType;	
	}
	
	public int getAppType()
	{
		return this.appType;	
	}
	
	public void setPassword(String password)
	{
		if(password!=null)
		{
			this.password = password;
		}
	}
	
	public String getPassword()
	{
		return this.password;	
	}
	
	public void setPhone(String phone)
	{
		if(phone!=null)
		{
			this.phone = phone;
		}	
	}
	
	public String getPhone()
	{
		return this.phone;	
	}
	
	public void setIcon(String icon)
	{
		if(icon!=null)
		{
			this.icon = icon;
		}
	}
	
	public String getIcon()
	{
		return this.icon;	
	}
	
	public void setRemark(String remark)
	{
		if(remark!=null)
		{
			this.remark = remark;
		}	
	}
	
	public String getRemark()
	{
		return this.remark;	
	}
	
	public void setRegTime(String regTime)
	{
		if(regTime!=null)
		{
			this.regTime = regTime;
		}	
	}
	
	public String getRegTime()
	{
		return this.regTime;	
	}
	
	public void setStatus(int status)
	{
		this.status = status;
		
		switch(status)
		{
		case 0:
			describe = "�����";
			break;
		case 1:
			describe = "���ͨ��";
			break;
		case 2:
			describe = "������";
			break;
		}
	}
	
	public int getStatus()
	{
		return this.status;	
	}
	public String getDescribe()
	{
		return this.describe;
	}
	
	public void setScore(int score)
	{
		this.score = score;
	}
	
	public int getScore()
	{
		return this.score;	
	}
	
}
