package com.dbmanager;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;

import com.pojo.MsgLog;

public class LogOperater extends DBOperater
{
	//����һ����־
	public int SaveLog(MsgLog log)
	{
		int logID = -1;
		String sqlString = "";
		//��¼����-����
		HashMap<String,Object> filedValues = new HashMap<String, Object>();
		filedValues.put("OPERATER_ID", log.getOperaterId());
		filedValues.put("OPERATER_TYPE", log.getOperaterType());
		filedValues.put("OCC_TIME", log.getOccTime());
		filedValues.put("REMARK", log.getRemark());		
		sqlString = getSqlString("msg_log", filedValues,"insert");
		
		if(executUpdate(sqlString))
		{
			logID = this.getAutoIncKey();
		}
		
		return logID;
	}

	//��Ϣ�����Ƿ����
	public boolean IsMsgUpdated(long curTime)
	{
		//ȡID����һ��,�Ƚ�ʱ�䣬�Ӷ��жϵ�ǰʱ���Ժ���Ϣ�����Ƿ������²���
		String sqlString = "select * from msg_log order by ID desc limit 1";
		MsgLog log = new MsgLog();
		try
		{
			ResultSet rs = executQuery(sqlString);
			if(rs == null)
			{
				return false;
			}
			if(rs.next())
			{
				log.setId(rs.getString(1));
				log.setOperaterId(rs.getString(2));
				log.setOperaterType(rs.getString(3));
				log.setOccTime(rs.getString(4));
				log.setRemark(rs.getString(5));
			}
		}
		catch(SQLException e)
		{
			System.out.print(e.getMessage());
			//closeDB();
		}
		//�Ƚ�ʱ���
		long dbTime = Long.parseLong(log.getOccTime());
		
		if(curTime>dbTime)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
