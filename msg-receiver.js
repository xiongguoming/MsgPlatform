
var g_RecMsgArray;
var g_FriendArray;

var g_curSelectID;
var g_curSelectType;//(0-用户,1-应用，2,3,4-系统)
var rmtimerid = -1;

//定时刷新
$(document).ready(function(){
	
	rmtimerid = setInterval(QueryMyMessage,1000);
	
	//创建表格
	var fields = ["序号","内容摘要","消息来源","接收时间","操作"];
	var Size = [40,180,80,100,120];
	CreateBlankTable("receive-msg-zone","table-system-msg",fields,Size,13);
	ReadMyFreinds();
});

//查询消息
var QueryMyMessage = function()
{
	//已经初始化,后台连续处理，前端不重发？
	if(rmtimerid != -1)
	{
		clearInterval(rmtimerid);
		setInterval(QueryMyMessage,10000);
		rmtimerid = -1;
	}	
	var receiverID = $('#receiver-msg-userid').val();
	
	$.ajax({
        type:"POST",
        url:"/MsgService/MessageSender",
        data:{type:"recroll",receiveid:receiverID},
        datatype: "html",
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus)
        {
        	ReceiveServerMessage(XMLHttpRequest.responseText);
        },
        //调用出错执行的函数
        error: function(){
        	clearInterval(rmtimerid);
        	rmtimerid = -1;
        	win.alertEx("无法获取消息！");
        },      
    });
	DisplyFocusApps();
};

//读取好友
function ReadMyFreinds()
{
	var userID = $("#receiver-msg-userid").val();
	
	$.ajax({
        //提交数据的类型 POST GET
        type:"GET",
        //提交的网址
        url:"/MsgService/FriendsFinding",
        //提交的数据
        data:{type:"readfriend",userid:userID},
        //返回数据的格式
        datatype: "json",//"xml", "html", "script", "json", "jsonp", "text".
        //在请求之前调用的函数
        //beforeSend:function(){$("#msg").html("logining");},
        //成功返回之后调用的函数             
        success:function(data){
       	 //$("#msg").html(decodeURI(data));            
        },
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus){
        	var strJson = XMLHttpRequest.responseText;
        	var userAarray = $.parseJSON(strJson);
        	
        	if(userAarray == null)
        	{
        		return;
        	}
        	
        	for(var nIndex=0; nIndex<userAarray.length; nIndex++)
        	{
        		var nodehtml = "<li onclick='ChangeFriend(\"";
        		nodehtml += userAarray[nIndex].UserId;
        		nodehtml += "\")'><a href='Javascript:void(0)'>";
        		nodehtml += userAarray[nIndex].UserName;
        		nodehtml += "</a></li>";
        		$("#receive-reclist-user ul").append(nodehtml);
        	}
        	
        	g_FriendArray = userAarray;
        },
        //调用出错执行的函数
        error: function(){
       	 	
        }         
    });
}
//显示所有应用信息
function DisplyFocusApps()
{
	$("#receive-reclist-app ul").html("");
	//从total-app-list.js获取数据
	var appArray = totalAppArray;
	var focusAppString = totalFocusApps;
	
	if(appArray==null)
	{
		return;
	}
	var count = 0;
	for(var nIndex=0; nIndex<appArray.length; nIndex++)
	{
		//未通过审核或被禁用的应用
		if(appArray[nIndex].Status!='1')
		{
			continue;
		}
		if(IsUserFocusedApp(appArray[nIndex].AppId,focusAppString))
		{
			var nodehtml = "<li onclick='ChangeApp(\"";
    		nodehtml += appArray[nIndex].AppId;
    		nodehtml += "\")'><a href='Javascript:void(0)'>";
    		nodehtml += appArray[nIndex].AppName;
    		nodehtml += "</a></li>";
    		$("#receive-reclist-app ul").append(nodehtml);
		}	
	}
}

function ChangeFriend(friendId)
{
	g_curSelectID = friendId;
	g_curSelectType = 0;//选择了用户
	for(var nIndex=0; nIndex<13; nIndex++)
	{
		RemoveMsgFromTable(nIndex);
	}

	var  msgArray = g_RecMsgArray;
	if(msgArray == null)
	{
		return;
	}
	var rowCount = 0;
	for(var nIndex=0; nIndex<msgArray.length; nIndex++)
	{
		if(msgArray[nIndex].SenderID == friendId)
		{
			AddMessageToTable(msgArray[nIndex],rowCount);
			if(rowCount++ > 12)
			{
				break;
			}
		}	
	}
	//查询消息
	$(".rmQueryMessage").click(function(){
		var msgID =  $(this).next().next().val();
		QueryMessage(msgID);
	});
	//删除消息
	$(".rmDeleteMessage").click(function(){
		var msgID =  $(this).next().val();
		DeleteMessage(msgID);
	});
}

//改变了App
function ChangeApp(AppId)
{
	g_curSelectID = AppId;
	g_curSelectType = 1;//选择了应用
	
	for(var nIndex=0; nIndex<13; nIndex++)
	{
		RemoveMsgFromTable(nIndex);
	}

	var  msgArray = g_RecMsgArray;
	if(msgArray == null)
	{
		return;
	}
	var rowCount = 0;
	
	for(var nIndex=0; nIndex<msgArray.length; nIndex++)
	{
		//在服务端已经处理过关注用户消息的筛选，此处直接显示即可
		if(msgArray[nIndex].MsgType == "AppMessage" && msgArray[nIndex].SenderID == AppId)
		{
			AddMessageToTable(msgArray[nIndex],rowCount);
			if(rowCount++ > 12)
			{
				break;
			}
		}	
	}
	//查询消息
	$(".rmQueryMessage").click(function(){
		var msgID =  $(this).next().next().val();
		QueryMessage(msgID);
	});
	//删除消息
	$(".rmDeleteMessage").click(function(){
		var msgID =  $(this).next().val();
		DeleteMessage(msgID);
	});
}
function ChangeSysMsg(MsgType)
{
	for(var nIndex=0; nIndex<13; nIndex++)
	{
		RemoveMsgFromTable(nIndex);
	}
	
	var msgArray = g_RecMsgArray;
	if(msgArray == null)
	{
		return;
	}
	
	if(MsgType == "NOTICE")
	{
		g_curSelectType = 2;
		var rowCount = 0;
		for(var nIndex=0; nIndex<msgArray.length; nIndex++)
		{
			if(msgArray[nIndex].SenderID.indexOf("SYSTEM")>=0  && msgArray[nIndex].Priority==0)
			{
				AddMessageToTable(msgArray[nIndex],rowCount);
				if(rowCount++ > 12)
				{
					break;
				}
			}	
		}
	}
	else if(MsgType == "INFO")
	{
		g_curSelectType = 3;
		var rowCount = 0;
		for(var nIndex=0; nIndex<msgArray.length; nIndex++)
		{
			if(msgArray[nIndex].SenderID.indexOf("SYSTEM")>=0 && msgArray[nIndex].Priority==1)
			{
				AddMessageToTable(msgArray[nIndex],rowCount);
				if(rowCount++ > 12)
				{
					break;
				}
			}	
		}
	}
	//warn
	else
	{
		g_curSelectType = 4;
		var rowCount = 0;
		for(var nIndex=0; nIndex<msgArray.length; nIndex++)
		{
			if(msgArray[nIndex].SenderID.indexOf("SYSTEM")>=0 && msgArray[nIndex].Priority==2)
			{
				AddMessageToTable(msgArray[nIndex],rowCount);
				if(rowCount++ > 12)
				{
					break;
				}
			}	
		}
	}
	
	//查询消息
	$(".rmQueryMessage").click(function(){
		var msgID =  $(this).next().next().val();
		QueryMessage(msgID); 
	});
	//删除消息
	$(".rmDeleteMessage").click(function(){
		var msgID =  $(this).next().val();
		DeleteMessage(msgID);
	});
	
	
}
//接收服务器的消息
function ReceiveServerMessage(jsonStr)
{
	if(jsonStr != null && jsonStr != "")
	{
		g_RecMsgArray = $.parseJSON(jsonStr);
	}
}

function QueryMessage(msgid)
{
	//修改数据库中的已读状态
	$.ajax({
        type:"GET",
        url:"/MsgService/MessageReceiver",
        data:{type:"readmsg",msgid:msgid},
        datatype: "html",
        complete: function(XMLHttpRequest, textStatus){
        },
        error: function(){
        }    
    });
	
	//修改界面的已读状态
	for(var row=0; row<11; row++)
	{
		var rowID = "#table-system-msg_"+row;
		var nthchild = "td:nth-child(5)";
		var rowMsgId = $(rowID+" "+nthchild+" :hidden").val();
		
		if(rowMsgId == msgid)
		{
			$(rowID).css("color","#1E1E1E");
			break;
		}
	}
	var curmsg = null;
	//修改本地缓存状态
	for(var nIndex=0; nIndex<g_RecMsgArray.length; nIndex++)
	{
		if(g_RecMsgArray[nIndex].MessageID == msgid)
		{
			curmsg = g_RecMsgArray[nIndex];
			g_RecMsgArray[nIndex].Ststus = 1;
			break;
		}	
	}
	if(curmsg==null)
	{
		return;
	}
	var url = "";
	
	//弹出对话框显示内容
	if(curmsg.MsgType=="SysMessage")
	{
		var senderId = "";
		var friendName = "";
		if(curmsg.SenderID.indexOf("SYSTEM")>=0)
		{
			senderId = curmsg.SenderID.substring(7);
		}
		for(var nIndex=0; nIndex<g_FriendArray.length; nIndex++)
		{
			if(g_FriendArray[nIndex].UserId == senderId)
			{
				friendName = g_FriendArray[nIndex].UserName;
				break;
			}
		}
		
		if(curmsg.MsgTitle == "ReplyFriend")
		{
			if(curmsg.MsgString == "agree")
			{
				win.alertEx(friendName+"同意加您为好友！");
			}
			else
			{
				win.alertEx(friendName+"没有通过您的好友申请！");
			}
		}
		else
		{
			//要先打开对话框再赋值
			openDialog("好友申请","div-rqfriend-dialog",380,280);
			$(".p-rqfreind-name").html(friendName);//好友姓名
			
			if(getSenderSex(curmsg.SenderID)=='1')
			{
				$(".img-rqfreind-sex").attr("src","./res/user-male.png");
			}
			else
			{
				$(".img-rqfreind-sex").attr("src","./res/user-female.png");
			}
			$(".texta-rqfriend-info").val(curmsg.MsgString);//请求内容
			$(".hidden-recmsg-msgid").val(curmsg.MessageID);
			//如果两个用户已经是好友关系，不能再执行应答操作
			if(IsMyFriend(curmsg.SenderID))
			{
				$(".button-reply-friend").attr('disabled','true');
			}
			else
			{
				$(".button-reply-friend").removeAttr('disabled');
			}
		}
	}
	//UserMessage
	else
	{
		//为避免ID冲突（新创建的对话框div与隐藏的div），JSP中确保使用类名来赋值
		openDialog("用户消息","div-recmsg-dialog",435,350);
		$(".text-recmsg-title").val(curmsg.MsgTitle);
		$(".texta-recmsg-content").val(curmsg.MsgString);
	}
}

//答复好友请求,三种回复：agree,disagree,ignore
function replyFriend()
{
	var reply = $('input[name="radio-rqfriend-repaly"]:checked').val();
	var msgid = $(".hidden-recmsg-msgid").val();
	
	if(reply != 'ignore')
	{
		$.ajax({
	        type:"GET",
	        url:"/MsgService/MessageReceiver",
	        data:{type:"replyfriend",reply:reply,msgid:msgid},
	        datatype: "html",
	        complete: function(XMLHttpRequest, textStatus){
	        },
	        error: function(){
	        }   
	    });
	}
	
	closeDialog();
}


function DeleteMessage(msgid)
{
	win.confirm('删除确认', '删除后无法找回，确定删除消息吗？', function (res) 
	{
		if(res == true)
		{
			$.ajax({
		         type:"GET",
		         url:"/MsgService/MessageReceiver",
		         data:{type:"deletemsg",msgid:msgid},
		         datatype: "html",
		         complete: function(XMLHttpRequest, textStatus){
		        	//修改本地缓存状态
	        		for(var nIndex=0; nIndex<g_RecMsgArray.length; nIndex++)
	        		{
	        			if(g_RecMsgArray[nIndex].MessageID == msgid)
	        			{
	        				g_RecMsgArray.splice(nIndex,1);//删除数组元素
	        				break;
	        			}
	        		}
	        		//修改界面状态,重新刷新页面
	        		switch(g_curSelectType)
	        		{
	        		case 0://好友
	        			ChangeFriend(g_curSelectID);
	        			break;
	        		case 1://应用
	        			ChangeApp(g_curSelectID);
	        			break;
	        		case 2://系统-提示
	        			ChangeSysMsg("NOTICE");
	        			break;
	        		case 3://系统-消息
	        			ChangeSysMsg("INFO");
	        			break;	
	        		case 4://系统-告警
	        			ChangeSysMsg("WARN");
	        			break;
	        		}
		         },
		         error: function(){
		        	 win.alertEx("删除失败！");
		         }         
		     });
		} 
    });
}

//将消息添加进列表
function AddMessageToTable(msg,row)
{
	RemoveMsgFromTable(row);
	var rowID = "#table-system-msg_"+row;

	for(var coloumn=0; coloumn<6; coloumn++)
	{
		var nthchild = "td:nth-child("+(coloumn+1)+")";
		var cell = $(rowID+" "+nthchild);
		
		//填充数据 
		switch(coloumn)
		{
		case 0://序号
			cell.text(row+1); 
			cell.css("text-align","center");
			break;
		case 1:
			if(msg.MsgTitle == "AddFriend")
			{
				cell.text("申请加为好友");
			}
			else if(msg.MsgTitle == "ReplyFriend")
			{
				cell.text("添加好友回复");
			}
			else
			{
				cell.text(msg.MsgTitle);
			}
			cell.css("text-align","left");
			break;
		case 2:
			var senderName = getSenderName(msg.SenderID);
			cell.text(senderName);
			cell.css("text-align","left");
			break;
		case 3:
			cell.text(msg.GenerTime);
			cell.css("text-align","center");
			break;
		case 4://操作
			cell.append("<input type='button' class='rmQueryMessage' value='查看'/>");
			cell.append("<input type='button' class='rmDeleteMessage' value='删除'/>");
			cell.append("<input type='hidden' name='receive-msg-id' value="+msg.MessageID+">");
			cell.css("text-align","center");
		}
	}
	//根据状态显示颜色，如果
	if(msg.Status==0)
	{
		$(rowID).css("color","blue");
	}
	else
	{
		$(rowID).css("color","#1E1E1E");
	}
}

//获得消息来源
function getSenderName(senderID)
{
	//:(0-用户,1-应用，2,3,4-系统)
	var name = "";
	switch(g_curSelectType)
	{
	case 0://用户
		for(var nIndex=0; nIndex<g_FriendArray.length; nIndex++)
		{
			if(g_FriendArray[nIndex].UserId == senderID)
			{
				name = g_FriendArray[nIndex].UserName;
				break;
			}
		}
		break;
	case 1://应用
		for(var nIndex=0; nIndex<totalAppArray.length; nIndex++)
		{
			if(totalAppArray[nIndex].AppId == senderID)
			{
				name = totalAppArray[nIndex].AppName;
				break;
			}
		}
		break;
	case 2://系统-提醒
		if(senderID.indexOf("SYSTEM")>=0)
		{
			senderID = senderID.substring(7);
		}
		name = "系统提醒";
		break;
	case 3://系统-消息
		name = "系统消息";
		break;
	case 4://系统-告警
		name = "系统告警";
		break;
	}
	
	return name;
}

function getSenderSex(senderID)
{
	var Sex = '0';
	for(var nIndex=0; nIndex<g_FriendArray.length; nIndex++)
	{
		if(g_FriendArray[nIndex].UserId == senderID)
		{
			Sex = g_FriendArray[nIndex].Sex;
			break;
		}
	}
	return Sex;
}

function RemoveMsgFromTable(row)
{
	var rowID = "#table-system-msg_"+row;
	
	for(var coloumn=0; coloumn<5; coloumn++)
	{
		var nthchild = "td:nth-child("+(coloumn+1)+")";
		var cell = $(rowID+" "+nthchild);
		cell.text("");	
	}
}

function IsMyFriend(userId)
{
	if(userId.indexOf("SYSTEM")>=0)
	{
		userId = userId.substring(7);
	}
	
	var res = false;
	for(var nIndex=0; nIndex<g_FriendArray.length; nIndex++)
	{
		if(g_FriendArray[nIndex].UserId==userId)
		{
			res = true;
			break;
		}
	}
	
	return res;
}