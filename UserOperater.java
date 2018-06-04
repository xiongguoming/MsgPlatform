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
	//��¼��֤
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
	//�޸��û���Ϣ������
	public boolean saveUser(UserInfo user)
	{
		boolean result = false;
		String sqlString = "";
		//��¼����-����
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
	//�޸��û���Ϣ������
	public boolean updateUserScore(String userId, int score)
	{
		boolean result = false;
		String sqlString = "";
		//��¼����-����
		if(!(user.getUserID().isEmpty()))
		{
			sqlString = "update user_info set SCORE="+user.getScore()+" where USER_ID='"+user.getUserID()+"'";
			result = executUpdate(sqlString);
		}
		
		return result;
	}
		
	//�����û�ID�����ݿ��л�ȡ�û���Ϣ
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
	//��ȡĳ�û������к���
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
        //�ַ����зָ����ĸ���  
        int count = 0;  
        
        if(friendstr==null)
        {
        	friendstr = "";
        }
        //��������ָ���򷵻��ַ�����  
        if (friendstr.indexOf(c) == -1)  
        {  
            return new String[]{friendstr};  
        }  
          
        char[] cs = friendstr.toCharArray();  
          
        //���˵���һ�������һ���Ƿָ��������  
        for (int i = 1; i < cs.length -1; i++)  
        {  
            if (cs[i] == c)  
            {  
                count++; //�õ��ָ����ĸ���  
            }  
        }  
          
        String[] strArray = new String[count + 1];  
        int k = 0, j = 0;  
        String str = friendstr;  
          
        //ȥ����һ���ַ��Ƿָ��������  
        if ((k = str.indexOf(c)) == 0)  
        {  
            str = friendstr.substring(k + 1);  
        }  
          
        //����Ƿ�����ָ������������򷵻��ַ���  
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
	//��ȡ���е�λ��Ϣ
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
	//ɾ�����ѹ�ϵ
	public boolean DeleteFriend(String myID,String yourID)
	{
		boolean flag1,flag2;
		UserInfo my = readUser(myID);
		String[] friendIds = splitIdFiled(my.getFriendCircle(),',');
		//�ҵ�����Ȧɾ����
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
		
		//�������Ȧɾ����
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
	//�������ѹ�ϵ
	public boolean MakeFriend(String senderID,String receiverID)
	{
		UserInfo sender = readUser(senderID);
		UserInfo receiver = readUser(receiverID);
		
		String flist = sender.getFriendCircle();
		//û�а����ú���
		if(!flist.contains(receiverID))
		{
			flist += receiverID;
			flist += ",";
			sender.setFriendCircle(flist);
			saveUser(sender);
		}
		
		flist = receiver.getFriendCircle();
		//û�а����ú���
		if(!flist.contains(senderID))
		{
			flist += senderID;
			flist += ",";
			receiver.setFriendCircle(flist);
			saveUser(receiver);
		}
		
		return true;
	}
	//��Ӻ�����
	public boolean AddBlackList(String userId,String ipAddr)
	{
		int recordId = -1;
		Calendar curTime = Calendar.getInstance();//��ȡ��ǰʱ��
		Calendar endTime = Calendar.getInstance();//���ý���ʱ��
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd mm:hh:ss");
		endTime.add(Calendar.DAY_OF_MONTH, 3);//��3��
		
		//��ֻ֤����һ���û���¼
		String sqlString = "select * from USER_BLACKLIST where USER_ID='"+userId+"' and IP_ADDR='"+ipAddr+"'";
		
		try
		{
			ResultSet rs = executQuery(sqlString);
			//�����ڼ�¼
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
			//�ٴη���Υ����Ϣ��ʱ��˳��
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
	//ɾ����������¼��ɾ�����к����û�ID��IP��ַ�ļ�¼
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
	//��ѯ�Ƿ���ڼ�¼,ֻҪ����
	public boolean QueryBlackList(String userId,String ipAddr)
	{
		//int itemCount = 0;//��¼��������¼����
		ArrayList<Integer> ids = new ArrayList<Integer>();
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd mm:hh:ss");
		Calendar curTime = Calendar.getInstance();
		Calendar endTime = Calendar.getInstance();
		
		String sqlString = "select * from USER_BLACKLIST where USER_ID='"+userId+"' or IP_ADDR='"+ipAddr+"'";
		//��һ�ε��ã��жϳ�ʼ״̬���������Ƿ���ڸ��û�
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
					//����ʱ����С������ʱ�䣬����ɾ����
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
				//�ڶ��ε��ã����ϴβ����ڸ��û�������Ҳ�����û����ֵ��������ϴδ����û������ε��ý��������û�����
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
	//�ú�����QueryBlackList����2�Σ���һ���ж�USER_BLACKLIST���Ƿ���ڸ��û��ļ�¼�����ڷ���true,�����ڷ���false;
	//QueryBlackList��¼��һ�ε��ý�����ڶ��ε���removeFlag����Ϊtrue,USER_BLACKLIST��Ӧ��û�и��û��ļ�¼
	//����������ε��ú󣬸����û��������û��Ŀ��÷�����ԭΪ��ǰ��Ϣ���Եĳ�ʼ����
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
		//�ڶ��ε���
		if(removeFlag && !existFlag)
		{
			updateUserScore(userId,policy.getInitScore());
		}
		return existFlag;
	}
	
}
