package com.message;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Date;
import javax.servlet.AsyncContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dbmanager.AppMsgOperater;
import com.dbmanager.AppOperater;
import com.dbmanager.LogOperater;
import com.dbmanager.SettingOperater;
import com.dbmanager.SysMsgOperater;
import com.dbmanager.UserMsgOperater;
import com.pojo.SettingInfo;
import com.system.JasonEncoding;

//��Ϣ����
public class MsgDispatch extends Thread 
{
	//�û���Ϣ
	private AppMessageQueue appMsgQueue = null;
	//�û���Ϣ
	private UserMessageQueue userMsgQueue = null;
	//ϵͳ��Ϣ
	private SysMessageQueue sysMsgQueue = null;
	//����ͻ���
	@SuppressWarnings("unused")
	private HttpServletRequest request = null;
	//��Ӧ�ͻ���
	private HttpServletResponse response = null;
	//�����û�ID
	private String receiverID = "";
	//json������
	private JasonEncoding jasonOpt;
	//��־�ӿ�
	private LogOperater dbLog;
	//�û���Ϣ���ݿ�ӿ�
	private AppMsgOperater appmsgDB;
	//�û���Ϣ���ݿ�ӿ�
	private UserMsgOperater usermsgDB;
	//ϵͳ��Ϣ���ݿ�ӿ�
	private SysMsgOperater sysmsgDB;
	//servlet����ӿ�
	private AsyncContext act = null;
	//��Ϣ����ʱ��
	private long updateOccasion = 0;
	
	
	public MsgDispatch()
	{ 
		jasonOpt = new JasonEncoding();
		dbLog = new LogOperater();
		
		appmsgDB = new AppMsgOperater();
		appMsgQueue = new AppMessageQueue();
		appMsgQueue.SetQueueName("APP-MESSAGE");
		
		usermsgDB = new UserMsgOperater();
		userMsgQueue = new UserMessageQueue();
		userMsgQueue.SetQueueName("USER-MESSAGE");
		
		sysmsgDB = new SysMsgOperater();
		sysMsgQueue = new SysMessageQueue();
		sysMsgQueue.SetQueueName("SYS-MESSAGE");
		
		UpdateMsgQueue();
	}
	
	public void SetAsyncContext(AsyncContext act)
	{
		this.act = act;
		response = (HttpServletResponse) act.getResponse();
	}
	
	//������Ϣ����
	public void UpdateMsgQueue()
	{
		if(receiverID.length()<1)
		{
			return;
		}
		
		//�����ݿ��ж�ȡ�����û���Ϣ
		if(IsSubscribeMsg(receiverID,0))
		{	
			ArrayList<TextMessage> userMsgArray = usermsgDB.getUserMessage();
			
			if(userMsgArray != null)
			{
				userMsgQueue.clearQueue();
				for(int nIndex=0; nIndex<userMsgArray.size(); nIndex++)
				{
					userMsgQueue.addQueueMsg(userMsgArray.get(nIndex));
				}
			}
			
		}
		
		//�����ݿ��ж�ȡ����Ӧ����Ϣ
		if(IsSubscribeMsg(receiverID,1))
		{
			ArrayList<TextMessage> appMsgArray = appmsgDB.getAppMessage();
			
			if(appMsgArray != null)
			{
				appMsgQueue.clearQueue();
				for(int nIndex=0; nIndex<appMsgArray.size(); nIndex++)
				{
					appMsgQueue.addQueueMsg(appMsgArray.get(nIndex));
				}
			}
		}
		
		
		if(IsSubscribeMsg(receiverID,2))
		{
			//�����ݿ��ж�ȡ����ϵͳ��Ϣ
			ArrayList<TextMessage> sysMsgArray = sysmsgDB.getSysMessage();
			
			if(sysMsgArray != null)
			{
				sysMsgQueue.clearQueue();
				for(int nIndex=0; nIndex<sysMsgArray.size(); nIndex++)
				{
					sysMsgQueue.addQueueMsg(sysMsgArray.get(nIndex));
				}
			}
		}
		
		
		//��ǰ��Ϣ����ʱ��
		updateOccasion = System.currentTimeMillis();
	}
	
	//����receiveID��ȡ��Ϣ
	public ArrayList<TextMessage> pickMessage()
	{
		ArrayList<TextMessage> msgArray = new ArrayList<TextMessage>();
		
		//�û���Ϣ
		if(userMsgQueue!=null)
		{
			ArrayList<TextMessage> userMsgArray = userMsgQueue.getMessageQueue();
			
			for(int nIndex=0; nIndex<userMsgArray.size(); nIndex++)
			{
				if(receiverID.equals(userMsgArray.get(nIndex).getReceiverID()))
				{
					msgArray.add(userMsgArray.get(nIndex));
				}
			}
		}
		
		//ϵͳ��Ϣ
		if(sysMsgQueue!=null)
		{
			ArrayList<TextMessage> sysMsgArray = sysMsgQueue.getMessageQueue();
			
			for(int nIndex=0; nIndex<sysMsgArray.size(); nIndex++)
			{
				if(receiverID.equals(sysMsgArray.get(nIndex).getReceiverID()))
				{
					msgArray.add(sysMsgArray.get(nIndex));
				}
			}
		}
		
		
		//Ӧ����Ϣ
		if(appMsgQueue!=null)
		{
			ArrayList<TextMessage> appMsgArray = appMsgQueue.getMessageQueue();
			
			for(int nIndex=0; nIndex<appMsgArray.size(); nIndex++)
			{
				//�Ƿ��ע�˸�Ӧ��
				if(IsFocusedApp(receiverID,appMsgArray.get(nIndex).getSenderID()))
				{
					msgArray.add(appMsgArray.get(nIndex));
				}
			}
		}
		
		return msgArray;
	}
	//��ҳ��Ϣ����
	public boolean IsSubscribeMsg(String receiverId,int nType)
	{
		SettingOperater settingdb = new  SettingOperater();
		SettingInfo setting =  settingdb.readMySetting(receiverId);
		
		if(setting == null)
		{
			setting = new SettingInfo();
		}
		
		String policy = "";
		switch(nType)
		{
		case 0:
			policy = setting.getUserMsgPolicy();
			break;
		case 1:
			policy = setting.getAppMsgPolicy();
			break;	
		case 2:
			policy = setting.getSysMsgPolicy();
			break;
		}
	
		if(policy.charAt(0)=='1')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//ִ����Ϣ����
	@Override
	public void run() 
	{
		receiverID = act.getRequest().getParameter("receiveid");
		//�Ƿ��и�����Ϣ������û�ȡ������WEB��Ϣ�����������µ�WEB��Ϣ
		if(dbLog.IsMsgUpdated(updateOccasion))
		{
			UpdateMsgQueue();
			System.out.print("���߳�ID-"+String.valueOf(getId())+"�����µ�ǰ��Ϣ���У�" + new Date() + ".\n");
		}
			
		String optType = act.getRequest().getParameter("type");
		
		if(optType == null)
		{
			return;
		}
		//�ͻ���������Ϣ����
		if(optType.equals("recroll"))
		{
			TransferMessage();
		}
	}
	
	//��Ӧ��Ϣ����
	public void TransferMessage()
	{
		//���ݽ���ID��ȡ��Ϣ
		ArrayList<TextMessage> msgArray = pickMessage();
		
		String jsonStr = jasonOpt.encodingUserMessage(msgArray);
		
		if(jsonStr==null||jsonStr.equals("")||response==null)
		{
			return;
		}
		//��Ӧ�ͻ���
		response.setContentType("text/html");
		PrintWriter out = null;
		try 
		{
			out = response.getWriter();
			if(out != null)
			{
				out.println(jsonStr);               
				out.flush();
				out.close();	
			}
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	
	//�û��Ƿ��ע��App
	public boolean IsFocusedApp(String userId,String appId)
	{
		if(userId==null||userId==""||appId==null||appId=="")
		{
			return false;
		}
		AppOperater appdb = new AppOperater();
		return appdb.IsFocusedApp(userId,appId);
	}
}
