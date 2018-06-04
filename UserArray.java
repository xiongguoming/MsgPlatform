package com.pojo;
import java.util.ArrayList;
import java.util.List;

public class UserArray {
	
	private List<UserInfo> userArray = new ArrayList<UserInfo>();
	
	public void setUserArray(List<UserInfo> userArray)
	{
		this.userArray = userArray;
	}
	public List<UserInfo> getUserArray()
	{
		return 	this.userArray;
	}
	
	public void addUser(UserInfo user)
	{
		userArray.add(user);
	}
	
	public int getUserNum()
	{
		return userArray.size();
	}
	public UserInfo getUserInfo(int nIndex)
	{
		return userArray.get(nIndex);
	}
}
