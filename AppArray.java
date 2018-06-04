package com.pojo;

import java.util.ArrayList;
import java.util.List;

public class AppArray {
	
	private List<AppInfo> appArray = new ArrayList<AppInfo>();
	
	public void setAppArray(List<AppInfo> appArray)
	{
		this.appArray = appArray;
	}
	public List<AppInfo> getAppArray()
	{
		return 	this.appArray;
	}
	
	public void addApp(AppInfo app)
	{
		appArray.add(app);
	}
	
	public int getAppNum()
	{
		return appArray.size();
	}
	public AppInfo getAppInfo(int nIndex)
	{
		return appArray.get(nIndex);
	}

}
