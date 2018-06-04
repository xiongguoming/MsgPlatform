package com.pojo;

public class UnitInfo 
{
	private int unitID;
	private int supID;
	private String unitName;
	private int rank;
	
	public void setUnitID(int unitID)
	{
		this.unitID = unitID;
	}
	public int getUnitID()
	{
		return this.unitID;
	}
	
	public void setSupID(int supID)
	{
		this.supID = supID;
	}
	public int getSupID()
	{
		return this.supID;
	}
	
	public void setUnitName(String unitName)
	{
		this.unitName = unitName;
	}
	public String getUnitName()
	{
		return this.unitName;
	}
	
	public void setRank(int rank)
	{
		this.rank = rank;
	}
	public int getRank()
	{
		return this.rank;
	}
}
