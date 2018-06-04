package com.pojo;

public class MsgPolicy 
{
	private String sysMsgPolicy;
	private String appMsgPolicy;
	private String userMsgPolicy;
	
	int initScore;
	int subScore;
	int appMsgLimit;
	int userMsgLimit;
	
	public void setSysMsgPolicy(String policy)
	{
		this.sysMsgPolicy = policy;
	}
	public String getSysMsgPolicy()
	{
		return this.sysMsgPolicy;
	}
	
	public void setAppMsgPolicy(String policy)
	{
		this.appMsgPolicy = policy;
	}
	public String getAppMsgPolicy()
	{
		return this.appMsgPolicy;
	}
	
	public void setUserMsgPolicy(String policy)
	{
		this.userMsgPolicy = policy;
	}
	public String getUserMsgPolicy()
	{
		return this.userMsgPolicy;
	}
	
	public void setInitScore(int score)
	{
		this.initScore = score;	
	}
	
	public int getInitScore()
	{
		return this.initScore;	
	}
	
	public void setSubScore(int score)
	{
		this.subScore = score;	
	}
	
	public int getSubScore()
	{
		return this.subScore;	
	}
	
	public void setAppMsgLimit(int amount)
	{
		this.appMsgLimit = amount;	
	}
	
	public int getAppMsgLimit()
	{
		return this.appMsgLimit;	
	}
	
	public void setUserMsgLimit(int amount)
	{
		this.userMsgLimit = amount;	
	}
	
	public int getUserMsgLimit()
	{
		return this.userMsgLimit;	
	}
}
