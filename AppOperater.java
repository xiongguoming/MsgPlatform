package com.dbmanager;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import com.pojo.AppArray;
import com.pojo.AppInfo;
import com.pojo.UserArray;
import com.pojo.UserInfo;

public class AppOperater  extends DBOperater
{
	//�޸��û���Ϣ������
	public boolean saveApp(AppInfo app)
	{
		String sqlString = "";
		Date regTime = new Date();
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		//��ʼ����
		app.setScore(policy.getInitScore());
		//��¼����-����
		HashMap<String,Object> filedValues = new HashMap<String, Object>();
		filedValues.put("APP_ID", app.getAppId());
		filedValues.put("APP_NAME", app.getAppName());
		filedValues.put("PASSWORD", app.getPassword());
		filedValues.put("APP_TYPE", app.getAppType());
		filedValues.put("ICON", app.getIcon());
		filedValues.put("PHONE", app.getPhone());
		filedValues.put("REGIST_TIME", sdf.format(regTime));
		filedValues.put("REMARK", app.getRemark());
		filedValues.put("STATUS", app.getStatus());
		filedValues.put("SCORE", app.getScore());
		
		sqlString = getSqlString("APP_INFO", filedValues,"insert");
		
		if(executUpdate(sqlString))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	//�����û�ID�����ݿ��л�ȡӦ����Ϣ
	public AppInfo readApp(String appID)
	{
		AppInfo app = new AppInfo();
		String sqlString = "select * from APP_INFO where APP_ID='"+appID+"'";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return app;
			}
			int rowCount = 0;
			while(rs.next())
			{
				app.setAppId(rs.getString(1));
				app.setAppName(rs.getString(2));
				app.setPassword(rs.getString(3));
				app.setAppType(rs.getInt(4));
				app.setIcon(rs.getString(5));
				app.setPhone(rs.getString(6));
				app.setRegTime(rs.getString(7));
				app.setRemark(rs.getString(8));
				app.setStatus(rs.getInt(9));
				app.setScore(rs.getInt(10));
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
			//closeDB();
			return null;
		}

		return app;
	}
	
	//�����û�ID�����ݿ��л�ȡӦ����Ϣ
	public AppArray readAllApps()
	{
		AppArray appArray = new AppArray();
		String sqlString = "select * from APP_INFO";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return appArray;
			}
			
			int rowCount = 0;
			while(rs.next())
			{
				AppInfo app = new AppInfo();
				app.setAppId(rs.getString(1));
				app.setAppName(rs.getString(2));
				app.setPassword(rs.getString(3));
				app.setAppType(rs.getInt(4));
				app.setIcon(rs.getString(5));
				app.setPhone(rs.getString(6));
				app.setRegTime(rs.getString(7));
				app.setRemark(rs.getString(8));
				app.setStatus(rs.getInt(9));
				app.setScore(rs.getInt(10));
				appArray.addApp(app);
				rowCount++;
			}
			
			if(rowCount==0)
			{
				return null;
			}
		}
		catch(SQLException e)
		{
			//closeDB();
			return null;
		}

		return appArray;
	}
	//�û���עӦ��
	public int UserFocusApp(String userId,String appId)
	{
		int msgID = -1;
		
		//�ж��Ƿ��ѹ�ע
		String sqlString = "select * from app_users_focus where APP_ID='"+appId+"'and USER_ID='"+userId+"'";
	
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs != null && rs.next())
			{
				return msgID;
			}
			
			rs.close();
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
		//��¼����-����
		HashMap<String,Object> filedValues = new HashMap<String, Object>();
		filedValues.put("APP_ID", appId);
		filedValues.put("USER_ID", userId);
		
		sqlString = getSqlString("app_users_focus", filedValues,"insert");
			
		if(executUpdate(sqlString))
		{
			msgID = this.getAutoIncKey();
		}
		
		return msgID;
	}
	//ȡ����ע�û�
	public boolean CancelFocusApp(String userId,String appId)
	{
		String sqlString = "delete from app_users_focus where APP_ID='"+appId+"'and USER_ID='"+userId+"'";
		
		
		if(executUpdate(sqlString))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//��ù�עӦ��
	public String GetFocusApps(String userId)
	{
		String sqlString = "select * from app_users_focus where USER_ID='"+userId+"'";
		String res = "";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs != null)
			{
				while(rs.next())
				{
					String appId = rs.getString(2);
					res += appId;
					res += ',';
				}
			}
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
		
		return res;
	}
	//�û��Ƿ��ע�˸�app
	public boolean IsFocusedApp(String userId,String appId)
	{
		boolean isFocused = false;
		//�ж��Ƿ��ѹ�ע
		String sqlString = "select * from app_users_focus where APP_ID='"+appId+"'and USER_ID='"+userId+"'";
	
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs != null && rs.next())
			{
				isFocused = true;
				rs.close();
			}
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
		
		return isFocused;
	}
	
	//��ȡ���й�ע�û���Ϣ
	public UserArray GetFocusUsers(String appId)
	{
		String userId = "";
		ArrayList<String>  userIdArray = new ArrayList<String> ();
		
		//��ȡ�����û�ID
		String sqlString = "select * from app_users_focus where APP_ID='"+appId+"'";
	
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs != null)
			{
				while(rs.next())
				{
					userId = rs.getString(3);
					userIdArray.add(userId);
				}
			}
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
		
		//��ȡ�����û���Ϣ���ж��Ƿ�Ϊ��ע��Ӧ�õ��û�
		UserArray userArray = new UserArray();
		
		sqlString = "select * from USER_INFO";
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return userArray;
			}
			boolean bIsFocused = false;
			int rowCount = 0;
			while(rs.next())
			{
				UserInfo user = new UserInfo();
				user.setUserID(rs.getString(1));
				for(int nIndex=0; nIndex<userIdArray.size(); nIndex++)
				{
					if(user.getUserID().compareTo(userIdArray.get(nIndex)) == 0)
					{
						bIsFocused = true;
						break;
					}
				}
				if(bIsFocused)
				{
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
				
				bIsFocused = false;
			}
			if(rowCount==0)
			{
				return null;
			}
			rs.close();
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			return null;
		}
		
		return userArray;
		
	}
	//�޸��û���Ϣ������
	public boolean updateAppScore(String appId, int score)
	{
		boolean result = false;
		String sqlString = "";
		
		AppInfo app = this.readApp(appId);
		
		//��¼����-����
		if(app != null)
		{
			sqlString = "update app_info set SCORE="+score+" where APP_ID='"+appId+"'";
			result = executUpdate(sqlString);
		}
		return result;
	}
	//��Ӻ�����
	public boolean AddBlackList(String appId,String ipAddr)
	{
		int recordId = -1;
		Calendar curTime = Calendar.getInstance();//��ȡ��ǰʱ��
		Calendar endTime = Calendar.getInstance();//���ý���ʱ��
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd mm:hh:ss");
		endTime.add(Calendar.DAY_OF_MONTH, 3);//��3��
		
		//��ֻ֤����һ���û���¼
		String sqlString = "select * from APP_BLACKLIST where APP_ID='"+appId+"' and IP_ADDR='"+ipAddr+"'";
		
		try
		{
			ResultSet rs = executQuery(sqlString);
			//�����ڼ�¼
			if(rs == null)
			{
				HashMap<String,Object> filedValues = new HashMap<String, Object>();
				filedValues.put("APP_ID", appId);
				filedValues.put("IP_ADDR", ipAddr);
				filedValues.put("START_TIME", df.format(curTime));
				filedValues.put("END_TIME", df.format(curTime));
				
				sqlString = getSqlString("APP_BLACKLIST", filedValues,"insert");
				
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

				sqlString = "update APP_BLACKLIST set START_TIME='"+df.format(curTime)+
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
	public boolean RemoveBlackList(String appId,String ipAddr)
	{
		String sqlString = "delete from APP_BLACKLIST where APP_ID='"+appId+"' or IP_ADDR='"+ipAddr+"'";
		return executUpdate(sqlString);
	}
	
	public boolean RemoveBlackList(int recordId)
	{
		String sqlString = "delete from APP_BLACKLIST where ID="+recordId;
		return executUpdate(sqlString);
	}
	//��ѯ�Ƿ���ڼ�¼,ֻҪ����
	public boolean QueryBlackList(String appId,String ipAddr)
	{
		ArrayList<Integer> ids = new ArrayList<Integer>();
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd mm:hh:ss");
		Calendar curTime = Calendar.getInstance();
		Calendar endTime = Calendar.getInstance();
		String sqlString = "select * from APP_BLACKLIST where APP_ID='"+appId+"' or IP_ADDR='"+ipAddr+"'";
		boolean bRemoveFlag = UpdateUserScore(appId,false);
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
				UpdateUserScore(appId,bRemoveFlag);
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
	
	//�ú�����QueryBlackList����2�Σ���һ���ж�APP_BLACKLIST���Ƿ���ڸ��û��ļ�¼�����ڷ���true,�����ڷ���false;
	//QueryBlackList��¼��һ�ε��ý�����ڶ��ε���removeFlag����Ϊtrue,APP_BLACKLIST��Ӧ��û�и��û��ļ�¼
	//����������ε��ú󣬸����û��������û��Ŀ��÷�����ԭΪ��ǰ��Ϣ���Եĳ�ʼ����
	public boolean UpdateUserScore(String appId,boolean removeFlag)
	{
		boolean existFlag = false;
		String sqlString = "select * from APP_BLACKLIST where APP_ID='"+appId+"'";
		
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
			updateAppScore(appId,policy.getInitScore());
		}
		return existFlag;
	}
}
