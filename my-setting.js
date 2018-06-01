
var cur_password = "";

 $(document).ready(function(){
	
	 var userID = document.getElementById('idUserID').value;
	 
	 //个人订阅设置
	 $.ajax({
	        type:"GET",
	        url:"/MsgService/MySetting",
	        data:{type:"readpolicy",userid:escape(userID)},
	        datatype: "html",
	        complete: function(XMLHttpRequest, textStatus)
	        {
	        	ReadMsgPolicy(XMLHttpRequest.responseText);
	        },
	        error: function()
	        {
	       	 	win.alertEx("读取数据失败");
	        }         
	    });
	 
	 //个人信息
	 $.ajax({
	        type:"GET",
	        url:"/MsgService/MySetting",
	        data:{type:"readuser",userid:escape(userID)},
	        datatype: "html",
	        complete: function(XMLHttpRequest, textStatus)
	        {
	        	ReadUserInfo(XMLHttpRequest.responseText);
	        },
	        error: function()
	        {
	       	 	win.alertEx("读取数据失败");
	        }         
	    });
	 
	var btnModify = document.getElementById('btnModify');
	var btnSubmit = document.getElementById('btnSubmit');
	btnModify.disabled = false;
	btnSubmit.disabled = true;
	
	SetModfifyModeEx(false);
});

 /*以下部分为个人信息设置*/
function SaveUserInfo()
{ 
	var userID = document.getElementById('idUserID').value;
	var userName = document.getElementById("UserNameEx").value;
	var password = cur_password;//document.getElementById('PasswordEx').value;
	var telephone = document.getElementById('TelephoneEx').value;
	var email = document.getElementById('EmailEx').value;
	var weixin = document.getElementById('WeixinEx').value;

	 $.ajax({
	        type:"GET",
	        url:"/MsgService/MySetting",
	        data:{
	        	type:"saveuser",
	        	userid:userID,
	        	userName:userName,
	        	password:password,
	        	telephone:telephone,
	        	email:email,
	        	weixin:weixin},
        	
	        datatype: "html",
	        complete: function(XMLHttpRequest, textStatus)
	        {
	        	win.alertEx("保存成功!");
	        },
	        error: function()
	        {
	       	 	win.alertEx("保存失败!");
	        }         
	    });
	 
    SetModfifyModeEx(false);
}

function ModifyUserInfo()
{
	SetModfifyModeEx(true);
}

function ReadUserInfo(jsonStr)
{
	if(jsonStr!=null && jsonStr.length>1)
	{	
		var jsonObj = JSON.parse(jsonStr);
		
		if(jsonObj != null)
		{
			var userInfo = jsonObj.userInfo;
			
			if(userInfo != null)
			{
				$("#UserName_td").html(userInfo.UserName);
				$("#Password_td").html("************");
				$("#Telephone_td").html(userInfo.Telephone);
				$("#Email_td").html(userInfo.Email);
				$("#Weixin_td").html(userInfo.Weixin);
				//记录当前密码
				cur_password = userInfo.Password;
			}
		}
	}
}

function SetModfifyModeEx(isModifyed)
{
	var btnModify = document.getElementById('btnModify');
	var btnSubmit = document.getElementById('btnSubmit');
	if(isModifyed)
	{
		btnModify.disabled = true;
		btnSubmit.disabled = false;
		
		var UserName = $("#UserName_td").html();
		$("#UserName_td").html("<input type='text' class='TableInputText' id='UserNameEx'>");
		document.getElementById('UserNameEx').value = UserName;
	
		var Password = cur_password;//$("#Password_td").html();
		$("#Password_td").html("<input type='text' class='TableInputText' id='PasswordEx'>");
		document.getElementById('PasswordEx').value = cur_password;
		
		var Telephone = $("#Telephone_td").html();
		$("#Telephone_td").html("<input type='text' class='TableInputText' id='TelephoneEx'>");
		document.getElementById('TelephoneEx').value = Telephone;
		
		var Email = $("#Email_td").html();
		$("#Email_td").html("<input type='text' class='TableInputText' id='EmailEx'>");
		document.getElementById('EmailEx').value = Email;
		
		var Weixin = $("#Weixin_td").html();
		$("#Weixin_td").html("<input type='text' class='TableInputText' id='WeixinEx'>");
		document.getElementById('WeixinEx').value = Weixin;
	}
	else
	{
		btnModify.disabled = false;
		btnSubmit.disabled = true;
		
		$("#UserName_td").html($("#UserName_td input").val());
		cur_password = $("#Password_td input").val();
		$("#Password_td").html("***********");
		$("#Telephone_td").html($("#Telephone_td input").val());
		$("#Email_td").html($("#Email_td input").val());
		$("#Weixin_td").html($("#Weixin_td input").val());
	}
}
 
/*以下部分为消息订阅设置*/
function SaveMsgPolicy()
{ 
	var userID = document.getElementById('idUserID').value;
	var obj = document.getElementsByName('ReceiveAllMsg');
    for(var i=0; i<obj.length; i++)
    {
        if(obj[i].checked)
        {
        	var recAllMsg = obj[i].value;
        	break;
        }
    }
    //夜间模式
    obj = document.getElementsByName("ReceiveTime");
    for(var i=0; i<obj.length; i++)
    {
        if(obj[i].checked)
        {
        	var recTime = obj[i].value;
        	break;
        }
    }
    var startTime,endTime;
	if(recTime == "true")
	{
		startTime = "22:00:00";
	    endTime = "08:00:00";
	}
	else
	{
		startTime = "00:00:00";
	    endTime = "23:59:59";
	}
    
    /*系统消息策略*/
    
    var sysMsgPolicy = "";
    obj = document.getElementsByName("chSysMsg_web");
    if(obj[0].checked)
	{
    	sysMsgPolicy += '1';
	}
    else
    {
    	sysMsgPolicy += '0';
    }
    obj = document.getElementsByName("chSysMsg_sms");
    if(obj[0].checked)
	{
    	sysMsgPolicy += '1';
	}
    else
    {
    	sysMsgPolicy += '0';
    }
    obj = document.getElementsByName("chSysMsg_email");
    if(obj[0].checked)
	{
    	sysMsgPolicy += '1';
	}
    else
    {
    	sysMsgPolicy += '0';
    }
    
    obj = document.getElementsByName("chSysMsg_weixin");
    if(obj[0].checked)
	{
    	sysMsgPolicy += '1';
	}
    else
    {
    	sysMsgPolicy += '0';
    }
    
    /*应用消息策略*/
    
    var appMsgPolicy = "";
    obj = document.getElementsByName("chAppMsg_web");
    if(obj[0].checked)
	{
    	appMsgPolicy += '1';
	}
    else
    {
    	appMsgPolicy += '0';
    }
    obj = document.getElementsByName("chAppMsg_sms");
    if(obj[0].checked)
	{
    	appMsgPolicy += '1';
	}
    else
    {
    	appMsgPolicy += '0';
    }
    obj = document.getElementsByName("chAppMsg_email");
    if(obj[0].checked)
	{
    	appMsgPolicy += '1';
	}
    else
    {
    	appMsgPolicy += '0';
    }
    
    obj = document.getElementsByName("chAppMsg_weixin");
    if(obj[0].checked)
	{
    	appMsgPolicy += '1';
	}
    else
    {
    	appMsgPolicy += '0';
    } 
    
    /*用户消息策略*/
    
    var userMsgPolicy = "";
    obj = document.getElementsByName("chUserMsg_web");
    if(obj[0].checked)
	{
    	userMsgPolicy += '1';
	}
    else
    {
    	userMsgPolicy += '0';
    }
    obj = document.getElementsByName("chUserMsg_sms");
    if(obj[0].checked)
	{
    	userMsgPolicy += '1';
	}
    else
    {
    	userMsgPolicy += '0';
    }
    obj = document.getElementsByName("chUserMsg_email");
    if(obj[0].checked)
	{
    	userMsgPolicy += '1';
	}
    else
    {
    	userMsgPolicy += '0';
    }
    
    obj = document.getElementsByName("chUserMsg_weixin");
    if(obj[0].checked)
	{
    	userMsgPolicy += '1';
	}
    else
    {
    	userMsgPolicy += '0';
    }
  
    $.ajax({
        type:"GET",
        url:"/MsgService/MySetting",
        data:{
        	type:"savepolicy",
        	userid:userID,
        	recAllMsg:recAllMsg,
        	recTime:recTime,
        	startTime:startTime,
        	endTime:endTime,
        	sysMsgPolicy:sysMsgPolicy,
        	appMsgPolicy:appMsgPolicy,
        	userMsgPolicy:userMsgPolicy},
        datatype: "html",

        complete: function(XMLHttpRequest, textStatus)
        {
        	win.alertEx("保存成功！");
        },

        error: function()
        {
       	 	win.alertEx("保存失败！");
        }         
    });
}

function ReadMsgPolicy(jsonStr)
{
	if(jsonStr!=null && jsonStr.length>2)
	{	
		var jsonObj = JSON.parse(jsonStr);
		
		if(jsonObj != null)
		{
			var setting = jsonObj.msg_setting;
			
			if(setting != null)
			{
				var obj = document.getElementsByName("ReceiveAllMsg");
				if(setting.recAllMsg == "true")
				{
					obj[0].checked = true;
					obj[1].checked = false;
				}
				else
				{
					obj[0].checked = false;
					obj[1].checked = true;
				}
				
				obj = document.getElementsByName("ReceiveTime");
				if(setting.setRecTime == "true")
				{
					obj[0].checked = true;
					obj[1].checked = false;
				}
				else
				{
					obj[0].checked = false;
					obj[1].checked = true;
				}
				
				//系统消息
				obj = document.getElementsByName("chSysMsg_web");
				if(setting.sysMsgPolicy.charAt(0) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				obj = document.getElementsByName("chSysMsg_sms");
				if(setting.sysMsgPolicy.charAt(1) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				obj = document.getElementsByName("chSysMsg_email");
				if(setting.sysMsgPolicy.charAt(2) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				
				obj = document.getElementsByName("chSysMsg_weixin");
				if(setting.sysMsgPolicy.charAt(3) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				
				
				//应用消息
				obj = document.getElementsByName("chAppMsg_web");
				if(setting.appMsgPolicy.charAt(0) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				obj = document.getElementsByName("chAppMsg_sms");
				if(setting.appMsgPolicy.charAt(1) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				obj = document.getElementsByName("chAppMsg_email");
				if(setting.appMsgPolicy.charAt(2) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				obj = document.getElementsByName("chAppMsg_weixin");
				if(setting.appMsgPolicy.charAt(3) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				
				//用户消息
				obj = document.getElementsByName("chUserMsg_web");
				if(setting.userMsgPolicy.charAt(0) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				obj = document.getElementsByName("chUserMsg_sms");
				if(setting.userMsgPolicy.charAt(1) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				obj = document.getElementsByName("chUserMsg_email");
				if(setting.userMsgPolicy.charAt(2) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
				
				obj = document.getElementsByName("chUserMsg_weixin");
				if(setting.userMsgPolicy.charAt(3) == '1')
				{
					obj[0].checked = true;
				}
				else
				{
					obj[0].checked = false;
				}
			}
		}
	}
}