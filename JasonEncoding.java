package com.system;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import com.message.TextMessage;
import com.pojo.*;
import org.json.JSONArray;
import org.json.JSONObject;

public class JasonEncoding {
	
	public String encodingMySettingInfo(SettingInfo setting)
	{
		if(setting==null)
		{
			return "";
		}
		
		JSONObject jsonObj = new JSONObject();
		Map <String, String> msgSetting = new HashMap <String, String>();
		msgSetting.put("userId", setting.getUserID());
		msgSetting.put("recAllMsg",String.valueOf(setting.getIsReceiveAllMsg()));
		msgSetting.put("recAppMsg",String.valueOf(setting.getIsReceiveAppMsg()));
		msgSetting.put("recUserMsg",String.valueOf(setting.getIsReceiveUserMsg()));
		msgSetting.put("setRecTime",String.valueOf(setting.getIsSetReceiveTime()));
		msgSetting.put("startTime", setting.getStartRecTime());
		msgSetting.put("endTime", setting.getEndRecTime());
		msgSetting.put("sysMsgPolicy", setting.getSysMsgPolicy());
		msgSetting.put("appMsgPolicy", setting.getAppMsgPolicy());
		msgSetting.put("userMsgPolicy", setting.getUserMsgPolicy());
		jsonObj.put("msg_setting", msgSetting);
		
		return jsonObj.toString();
	}
	
	public String encodingUnits(UnitArray unitArray)
	{
		if(unitArray==null)
		{
			return "";
		}
		
		JSONArray jsonArray = new JSONArray();
		
		for(int nIndex=0; nIndex<unitArray.getUnitNum(); nIndex++)
		{
			JSONObject jsonObj = new JSONObject();
			UnitInfo unit = unitArray.getUnitInfo(nIndex);
			jsonObj.put("UnitId", String.valueOf(unit.getUnitID()));
			jsonObj.put("SuperID", String.valueOf(unit.getSupID()));
			jsonObj.put("UnitName", unit.getUnitName());
			jsonObj.put("Rank", String.valueOf(unit.getRank()));
			
			jsonArray.put(jsonObj);
		}
		
		return jsonArray.toString();
	}
	public String encodingUsers(UserArray userArray)
	{
		if(userArray==null)
		{
			return "";
		}
		
		JSONArray jsonArray = new JSONArray();
		
		for(int nIndex=0; nIndex<userArray.getUserNum(); nIndex++)
		{
			JSONObject jsonObj = new JSONObject();
			UserInfo user = userArray.getUserInfo(nIndex);
			if(user==null)
			{
				continue;
			}
			jsonObj.put("UserId", String.valueOf(user.getUserID()));
			//jsonObj.put("Password", String.valueOf(user.getPassword()));
			jsonObj.put("UserName", String.valueOf(user.getUserName()));
			//jsonObj.put("Right", String.valueOf(user.getRight()));
			jsonObj.put("Sex", String.valueOf(user.getSex()));
			jsonObj.put("UnitID", String.valueOf(user.getUnitID()));
			//jsonObj.put("FriendCircle", String.valueOf(user.getFriendCircle()));
			//jsonObj.put("FocusApp", String.valueOf(user.getFocusApp()));
			//jsonObj.put("Telphone", String.valueOf(user.getTelephone()));
			//jsonObj.put("Email", String.valueOf(user.getEmail()));
			//jsonObj.put("Weixin", String.valueOf(user.getWeixin()));
			jsonObj.put("OnlineStatus", String.valueOf(user.getOnlineStatus()));
			jsonArray.put(jsonObj);
		}
		
		return jsonArray.toString();
	}
	
	public String encodingApps(AppArray appArray)
	{
		if(appArray==null)
		{
			return "";
		}
		
		JSONArray jsonArray = new JSONArray();
		
		for(int nIndex=0; nIndex<appArray.getAppNum(); nIndex++)
		{
			JSONObject jsonObj = new JSONObject();
			AppInfo app = appArray.getAppInfo(nIndex);
			if(app==null)
			{
				continue;
			}
			jsonObj.put("AppId", String.valueOf(app.getAppId()));
			jsonObj.put("AppName", String.valueOf(app.getAppName()));
			jsonObj.put("AppType", String.valueOf(app.getAppType()));
			jsonObj.put("Phone", String.valueOf(app.getPhone()));
			jsonObj.put("Icon", String.valueOf(app.getIcon()));
			jsonObj.put("Remrk", String.valueOf(app.getRemark()));
			jsonObj.put("RegTime", String.valueOf(app.getRegTime()));
			jsonObj.put("Status", String.valueOf(app.getStatus()));
			jsonObj.put("Describe", String.valueOf(app.getDescribe()));
			jsonArray.put(jsonObj);
		}
		
		return jsonArray.toString();
	}
	
	public String encodingOnlyUser(UserInfo user)
	{
		JSONObject jsonObj = new JSONObject();
		Map <String, String> userInfo = new HashMap <String, String>();
		
		if(user == null)
		{
			return "";
		}
		
		userInfo.put("UserId", String.valueOf(user.getUserID()));
		userInfo.put("Password", String.valueOf(user.getPassword()));
		userInfo.put("UserName", String.valueOf(user.getUserName()));
		userInfo.put("Right", String.valueOf(user.getRight()));
		userInfo.put("Sex", String.valueOf(user.getSex()));
		userInfo.put("UnitID", String.valueOf(user.getUnitID()));
		userInfo.put("FriendCircle", String.valueOf(user.getFriendCircle()));
		userInfo.put("FocusApp", String.valueOf(user.getFocusApp()));
		
		if(user.getTelephone()!=null)
		{
			userInfo.put("Telephone", String.valueOf(user.getTelephone()));
		}
		else
		{
			userInfo.put("Telephone","");
		}
		if(user.getEmail()!=null)
		{
			userInfo.put("Email", String.valueOf(user.getEmail()));
		}
		else
		{
			userInfo.put("Email", "");
		}
		if(user.getWeixin()!=null)
		{
			userInfo.put("Weixin", String.valueOf(user.getWeixin()));
		}
		else
		{
			userInfo.put("Weixin","");
		}
		userInfo.put("OnlineStatus", String.valueOf(user.getOnlineStatus()));
		
		jsonObj.put("userInfo", userInfo);
		
		return jsonObj.toString();
	}
	
	public String encodingUserMessage(ArrayList<TextMessage> msgArray)
	{
		if(msgArray==null || msgArray.size()==0)
		{
			return "";
		}
		JSONArray jsonArray = new JSONArray();
		
		for(int nIndex=0; nIndex<msgArray.size(); nIndex++)
		{
			JSONObject jsonObj = new JSONObject();
			TextMessage msg = msgArray.get(nIndex);
			
			if(msg.getSenderID().contains("SYSTEM"))
			{
				jsonObj.put("MessageID", "SYS"+String.valueOf(msg.getMessageID()));
			}
			else
			{
				if(!msg.getMsgType().contains("AppMessage"))
				{
					jsonObj.put("MessageID", "USER"+String.valueOf(msg.getMessageID()));
				}
				else
				{
					jsonObj.put("MessageID", "APP"+String.valueOf(msg.getMessageID()));
				}
			}
			
			jsonObj.put("SenderID", msg.getSenderID());
			jsonObj.put("ReceiverID", msg.getReceiverID());
			
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String generTime = sdf.format(new Date(msg.getTimeStap()));
			jsonObj.put("GenerTime", generTime);
			jsonObj.put("Priority", msg.getPriority());
			jsonObj.put("MsgType", msg.getMsgType());
			jsonObj.put("MsgTitle", msg.getMsgTitle());
			jsonObj.put("MsgString", msg.getMsgString());
			jsonObj.put("Status", msg.getStatus());
	
			jsonArray.put(jsonObj);
		}

		return jsonArray.toString();
	}
}
