package com.pojo;


public class SettingInfo {
	private String userID;
	//���������Ϣ������������Ϣ��
	private boolean isReceiveAllMsg = true;
	//�Ƿ����Ӧ����Ϣ
	private boolean isReceiveAppMsg = true;
	//�Ƿ�����û���Ϣ
	private boolean isReceiveUserMsg = true;
	//�Ƿ����ý���ʱ��
	private boolean isSetReceiveTime = true;
	//��ʼ����ʱ��
	private String startRecTime="00:00:00";
	//��������ʱ��
	private String endRecTime="23:59:59";
	//����λ�ַ����ã�ϵͳ��Ϣ����
	private String sysMsgPolicy = "111";
	//Ӧ����Ϣ����
	private String appMsgPolicy = "111";
	//�û���Ϣ����
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
