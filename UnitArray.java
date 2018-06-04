package com.pojo;

import java.util.ArrayList;
import java.util.List;

import com.pojo.UnitInfo;

public class UnitArray 
{
	private List<UnitInfo> unitArray = new ArrayList<UnitInfo>();
	
	public void setUnitArray(List<UnitInfo> unitArray)
	{
		this.unitArray = unitArray;
	}
	public List<UnitInfo> getUnitArray()
	{
		return 	this.unitArray;
	}
	
	public void addUnit(UnitInfo unit)
	{
		unitArray.add(unit);
	}
	
	public int getUnitNum()
	{
		return unitArray.size();
	}
	public UnitInfo getUnitInfo(int nIndex)
	{
		return unitArray.get(nIndex);
	}
}
