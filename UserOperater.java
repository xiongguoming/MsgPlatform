package com.dbmanager;

import java.sql.*;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Date;

import com.pojo.UnitArray;
import com.pojo.UnitInfo;
import com.pojo.UserArray;
import com.pojo.UserInfo;

public class UserOperater extends DBOperater 
{
	private UserInfo user;
	
	public void setUserInfo(UserInfo user)
	{
		this.user = user;
	}
	public UserInfo getUserInfo()
	{
		return this.user;
	}
	//登录验证
	public boolean CheckLogin(String userID,String password)
	{
		UserInfo userinfo = readUser(userID);
		
		if(userinfo!=null && password.compareTo(userinfo.getPassword())==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//修改用户信息并保存
	public boolean saveUser(UserInfo user)
	{
		boolean result = false;
		String sqlString = "";
		//记录存在-更新
		if(!(user.getUserID().isEmpty()))
		{
			sqlString = "update user_info set USER_NAME='"+user.getUserName()+"', "
						+"PASSWORD='"+user.getPassword()+"', "+"TELEPHONE='"+user.getTelephone()+"', "
						+"EMAIL='"+user.getEmail()+"', "+"WEIXIN='"+user.getWeixin()+"', "+
						"FRIEND_CIRCLE='"+user.getFriendCircle()+"', "+"FOCUS_APP='"+user.getFocusApp()+"' "+
						"where USER_ID='"+user.getUserID()+"'";
			result = executUpdate(sqlString);
		}
		
		return result;
	}
	//修改用户信息并保存
	public boolean updateUserScore(String userId, int score)
	{
		boolean result = false;
		String sqlString = "";
		//记录存在-更新
		if(!(user.getUserID().isEmpty()))
		{
			sqlString = "update user_info set SCORE="+user.getScore()+" where USER_ID='"+user.getUserID()+"'";
			result = executUpdate(sqlString);
		}
		
		return result;
	}
		
	//根据用户ID从数据库中获取用户信息
	public UserInfo readUser(String userID)
	{
		UserInfo user = new UserInfo();
		String sqlString = "select * from USER_INFO where USER_ID='"+userID+"'";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return user;
			}
			//ResultSetMetaData rsdata = rs.getMetaData();
			int rowCount = 0;
			while(rs.next())
			{
				user.setUserID(rs.getString(1));
				user.setPassword(rs.getString(2));
				user.setUserName(rs.getString(3));
				user.setRight(rs.getInt(4));
				user.setSex(rs.getInt(5));
				user.setUnitID(rs.getInt(6));
				user.setFriendCircle(rs.getString(7));
				user.setFocusApp(rs.getString(8));
				user.setTelephone(rs.getString(9));
				user.setEmail(rs.getString(10));
				user.setWeixin(rs.getString(11));
				user.setOnlineStatus(rs.getBoolean(12));
				user.setScore(rs.getInt(13));
				rowCount++;
				break;
			}
			
			if(rowCount==0)
			{
				return null;
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			//closeDB();
			return null;
		}

		return user;
	}
	public UserArray readUsers()
	{
		UserArray userArray = new UserArray();
		
		String sqlString = "select * from USER_INFO";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return userArray;
			}
			int rowCount = 0;
			while(rs.next())
			{
				UserInfo user = new UserInfo();
				user.setUserID(rs.getString(1));
				user.setPassword(rs.getString(2));
				user.setUserName(rs.getString(3));
				user.setRight(rs.getInt(4));
				user.setSex(rs.getInt(5));
				user.setUnitID(rs.getInt(6));
				user.setFriendCircle(rs.getString(7));
				user.setFocusApp(rs.getString(8));
				user.setTelephone(rs.getString(9));
				user.setEmail(rs.getString(10));
				user.setWeixin(rs.getString(11));
				user.setOnlineStatus(rs.getBoolean(12));
				user.setScore(rs.getInt(13));
				userArray.addUser(user);
				rowCount++;
			}
			
			if(rowCount==0)
			{
				return null;
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			//closeDB();
			return null;
		}
		
		return userArray;
	}
	//读取某用户的所有好友
	public UserArray readFriends(String userID)
	{
		UserArray userArray = new UserArray();
		UserInfo my = readUser(userID);
		if(my == null)
		{
			return userArray;
		}
		
		String[] friendIds = splitIdFiled(my.getFriendCircle(),',');
		
		for (String userId : friendIds)  
        {  
			UserInfo user = readUser(userId);
			userArray.addUser(user);
        }  
		
		return userArray;
	}
	public static String[] splitIdFiled(String friendstr, char c)  
    {  
        //字符串中分隔符的个数  
        int count = 0;  
        
        if(friendstr==null)
        {
        	friendstr = "";
        }
        //如果不含分割符则返回字符本身  
        if (friendstr.indexOf(c) == -1)  
        {  
            return new String[]{friendstr};  
        }  
          
        char[] cs = friendstr.toCharArray();  
          
        //过滤掉第一个和最后一个是分隔符的情况  
        for (int i = 1; i < cs.length -1; i++)  
        {  
            if (cs[i] == c)  
            {  
                count++; //得到分隔符的个数  
            }  
        }  
          
        String[] strArray = new String[count + 1];  
        int k = 0, j = 0;  
        String str = friendstr;  
          
        //去掉第一个字符是分隔符的情况  
        if ((k = str.indexOf(c)) == 0)  
        {  
            str = friendstr.substring(k + 1);  
        }  
          
        //检测是否包含分割符，如果不含则返回字符串  
        if (str.indexOf(c) == -1)  
        {  
            return new String[]{str};  
        }  
          
        while ((k = str.indexOf(c)) != -1)  
        {  
            strArray[j++] = str.substring(0, k);  
            str = str.substring(k + 1);  
            if ((k = str.indexOf(c)) == -1 && str.length() > 0)  
            {  
                strArray[j++] = str.substring(0);  
            }  
        }  
          
        return strArray;  
    } 
	//读取所有单位信息
	public UnitArray readUnits()
	{
		UnitArray unitArray = new UnitArray();
		String sqlString = "select * from USER_UNIT";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return unitArray;
			}
			int rowCount = 0;
			while(rs.next())
			{
				UnitInfo unit = new UnitInfo();
				unit.setUnitID(rs.getInt(1));
				unit.setUnitName(rs.getString(2));
				unit.setSupID(rs.getInt(3));
				unit.setRank(rs.getInt(4));
				unitArray.addUnit(unit);
				rowCount++;
			}
			
			if(rowCount==0)
			{
				return null;
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			//closeDB();
			return null;
		}
		return unitArray;
	}
	//删除好友关系
	public boolean DeleteFriend(String myID,String yourID)
	{
		boolean flag1,flag2;
		UserInfo my = readUser(myID);
		String[] friendIds = splitIdFiled(my.getFriendCircle(),',');
		//我的朋友圈删掉你
		String newfirendIds = "";
		for (String temp : friendIds)  
        {  
			if(!temp.equals(yourID))
			{
				newfirendIds += temp;
				newfirendIds += ',';
			}
        }
		my.setFriendCircle(newfirendIds);
		flag1 = saveUser(my);
		
		//你的朋友圈删掉我
		UserInfo your = readUser(yourID);
		friendIds = splitIdFiled(your.getFriendCircle(),',');
		
		newfirendIds = "";
		for (String temp : friendIds)  
        {  
			if(!temp.equals(myID))
			{
				newfirendIds += temp;
				newfirendIds += ',';
			}
        }
		your.setFriendCircle(newfirendIds);
		flag2 = saveUser(your);
		
		return flag1&&flag2;
	}
	//建立好友关系
	public boolean MakeFriend(String senderID,String receiverID)
	{
		UserInfo sender = readUser(senderID);
		UserInfo receiver = readUser(receiverID);
		
		String flist = sender.getFriendCircle();
		//没有包含该好友
		if(!flist.contains(receiverID))
		{
			flist += receiverID;
			flist += ",";
			sender.setFriendCircle(flist);
			saveUser(sender);
		}
		
		flist = receiver.getFriendCircle();
		//没有包含该好友
		if(!flist.contains(senderID))
		{
			flist += senderID;
			flist += ",";
			receiver.setFriendCircle(flist);
			saveUser(receiver);
		}
		
		return true;
	}
	//添加黑名单
	public boolean AddBlackList(String userId,String ipAddr)
	{
		int recordId = -1;
		Calendar curTime = Calendar.getInstance();//获取当前时间
		Calendar endTime = Calendar.getInstance();//禁用结束时间
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd mm:hh:ss");
		endTime.add(Calendar.DAY_OF_MONTH, 3);//加3天
		
		//保证只存在一条用户记录
		String sqlString = "select * from USER_BLACKLIST where USER_ID='"+userId+"' and IP_ADDR='"+ipAddr+"'";
		
		try
		{
			ResultSet rs = executQuery(sqlString);
			//不存在记录
			if(rs == null)
			{
				HashMap<String,Object> filedValues = new HashMap<String, Object>();
				filedValues.put("USER_ID", userId);
				filedValues.put("IP_ADDR", ipAddr);
				filedValues.put("START_TIME", df.format(curTime));
				filedValues.put("END_TIME", df.format(curTime));
				
				sqlString = getSqlString("USER_BLACKLIST", filedValues,"insert");
				
				if(executUpdate(sqlString))
				{
					recordId = this.getAutoIncKey();
				}
			}
			//再次发送违规信息，时间顺延
			else
			{
				if(rs.next())
				{
					recordId = rs.getInt(1);
					rs.close();
				}

				sqlString = "update USER_BLACKLIST set START_TIME='"+df.format(curTime)+
							"',END_TIME='"+df.format(curTime)+"' where ID="+recordId;
				executUpdate(sqlString);
				
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			return false;
		}
		
		return true;
	}
	//删除黑名单记录，删除所有含该用户ID或IP地址的记录
	public boolean RemoveBlackList(String userId,String ipAddr)
	{
		String sqlString = "delete from USER_BLACKLIST where USER_ID='"+userId+"' or IP_ADDR='"+ipAddr+"'";
		return executUpdate(sqlString);
	}
	
	public boolean RemoveBlackList(int recordId)
	{
		String sqlString = "delete from USER_BLACKLIST where ID="+recordId;
		return executUpdate(sqlString);
	}
	//查询是否存在记录,只要存在
	public boolean QueryBlackList(String userId,String ipAddr)
	{
		//int itemCount = 0;//记录黑名单记录总数
		ArrayList<Integer> ids = new ArrayList<Integer>();
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd mm:hh:ss");
		Calendar curTime = Calendar.getInstance();
		Calendar endTime = Calendar.getInstance();
		
		String sqlString = "select * from USER_BLACKLIST where USER_ID='"+userId+"' or IP_ADDR='"+ipAddr+"'";
		//第一次调用，判断初始状态，黑名单是否存在该用户
		boolean bRemoveFlag = UpdateUserScore(userId,false);
		
		ResultSet rs = null;
		
		try 
		{
			rs = executQuery(sqlString);
			
			if(rs != null)
			{
				int recordId = 0;
				
				while(rs.next())
				{
					recordId = rs.getInt(1);
					curTime.setTime(df.parse(rs.getString(5)));
					endTime.setTime(df.parse(rs.getString(5)));
					//结束时间若小于现在时间，加入删除组
					if(endTime.before(curTime))
					{
						RemoveBlackList(recordId);
					}
					else
					{
						ids.add(recordId);
					}
				}
				rs.close();
				//第二次调用，如上次不存在该用户，本次也不对用户积分调整，若上次存在用户，本次调用将调整该用户积分
				UpdateUserScore(userId,bRemoveFlag);
			}
		} 
		catch (SQLException e) 
		{
			e.printStackTrace();
		}
		catch (ParseException e1)
		{
			e1.printStackTrace();
		}
		if(ids.size()>0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//该函数由QueryBlackList调用2次，第一次判断USER_BLACKLIST中是否存在该用户的记录，存在返回true,不存在返回false;
	//QueryBlackList记录第一次调用结果，第二次调用removeFlag必须为true,USER_BLACKLIST中应该没有该用户的记录
	//完成上述两次调用后，更新用户表，将该用户的可用分数还原为当前消息策略的初始积分
	public boolean UpdateUserScore(String userId,boolean removeFlag)
	{
		boolean existFlag = false;
		String sqlString = "select * from USER_BLACKLIST where USER_ID='"+userId+"'";
		
		ResultSet rs = null;
		
		try 
		{
			rs = executQuery(sqlString);
			if(rs != null)
			{
				existFlag = true;
				rs.close();
			}
		} 
		catch (SQLException e) 
		{
			e.printStackTrace();
		}
		//第二次调用
		if(removeFlag && !existFlag)
		{
			updateUserScore(userId,policy.getInitScore());
		}
		return existFlag;
	}
	
}
