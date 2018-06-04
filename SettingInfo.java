package com.pojo;


public class SettingInfo {
	private String userID;
	//允许接收消息（接收所有消息）
	private boolean isReceiveAllMsg = true;
	//是否接收应用消息
	private boolean isReceiveAppMsg = true;
	//是否接收用户消息
	private boolean isReceiveUserMsg = true;
	//是否设置接收时间
	private boolean isSetReceiveTime = true;
	//开始接收时间
	private String startRecTime="00:00:00";
	//结束接收时间
	private String endRecTime="23:59:59";
	//用三位字符设置：系统消息策略
	private String sysMsgPolicy = "111";
	//应用消息策略
	private String appMsgPolicy = "111";
	//用户消息策略
	private String userMsgPolicy = "111";
	
	public void setUserID(String userID)
	{
		this.userID = userID;
	}
	public String getUserID()
	{
		return this.userID;
	}
	
	public void setIsReceiveAllMsg(boolean isReceiveAllMsg)
	{
		this.isReceiveAllMsg = isReceiveAllMsg;
	}
	public boolean getIsReceiveAllMsg()
	{
		return this.isReceiveAllMsg;
	}
	
	public void setIsReceiveAppMsg(boolean isReceiveAppMsg)
	{
		this.isReceiveAppMsg = isReceiveAppMsg;
	}
	public boolean getIsReceiveAppMsg()
	{
		return this.isReceiveAppMsg;
	}
	
	public void setIsSetReceiveTime(boolean isSetReceiveTime)
	{
		this.isSetReceiveTime = isSetReceiveTime;
	}
	public boolean getIsSetReceiveTime()
	{
		return this.isSetReceiveTime;
	}
	
	public void setIsReceiveUserMsg(boolean isReceiveUserMsg)
	{
		this.isReceiveUserMsg = isReceiveUserMsg;
	}
	public boolean getIsReceiveUserMsg()
	{
		return this.isReceiveUserMsg;
	}
	
	public void setStartRecTime(String startRecTime)
	{
		this.startRecTime = startRecTime;
	}
	public String getStartRecTime()
	{
		return this.startRecTime;
	}
	
	public void setEndRecTime(String endRecTime)
	{
		this.endRecTime = endRecTime;
	}
	public String getEndRecTime()
	{
		return this.endRecTime;
	}
	
	public void setSysMsgPolicy(String sysMsgPolicy)
	{
		this.sysMsgPolicy = sysMsgPolicy;
	}
	public String getSysMsgPolicy()
	{
		return this.sysMsgPolicy;
	}
	
	public void setAppMsgPolicy(String appMsgPolicy)
	{
		this.appMsgPolicy = appMsgPolicy;
	}
	public String getAppMsgPolicy()
	{
		return this.appMsgPolicy;
	}
	
	public void setUserMsgPolicy(String userMsgPolicy)
	{
		this.userMsgPolicy = userMsgPolicy;
	}
	public String getUserMsgPolicy()
	{
		return this.userMsgPolicy;
	}
}
