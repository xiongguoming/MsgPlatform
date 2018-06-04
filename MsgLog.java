package com.pojo;

//日志
public class MsgLog 
{
	private String id="";
	private String operaterId="";
	private String operaterType="0";
	private String occTime="0";
	private String remark="";
	
	//新增一条日志
	public void addLog(String userId,int optType,long occTime,String remark)
	{
		operaterId = userId;
		switch(optType)
		{
		case 0:
			operaterType = "发送用户消息";
			break;
		case 1:
			operaterType = "申请好友";
			break;	
		case 2:
			operaterType = "申请好友回复";
			break;	
		case 3:
			operaterType = "已读消息";
			break;
		case 4:
			operaterType = "删除消息";
			break;
		}
		this.occTime = String.valueOf(occTime);
		this.remark = remark;
	}
	
	public void setId(String id)
	{
		this.id = id;
	}
	public String getId()
	{
		return this.id;
	}
	public void setOperaterId(String operaterId)
	{
		this.operaterId = operaterId;
	}
	public String getOperaterId()
	{
		return this.operaterId;
	}
	public void setOperaterType(String operaterType)
	{
		this.operaterType = operaterType;
	}
	public String getOperaterType()
	{
		return this.operaterType;
	}
	public void setOccTime(String occTime)
	{
		if(occTime!=null)
		{
			this.occTime = occTime;
		}
	}
	public String getOccTime()
	{
		return this.occTime;
	}
	public void setRemark(String remark)
	{
		this.remark = remark;
	}
	public String getRemark()
	{
		return this.remark;
	}
}
