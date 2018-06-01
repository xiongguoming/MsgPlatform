

var history_timer_id;

$(document).ready(function(){
	//创建表格
	var fields = ["序号","标题","类型","发送方","接收时间"];
	var Size = [60,300,80,100,150];
	CreateBlankTable("msg-zone-histoy","table-system-msg-histoy",fields,Size,11);
	//延迟三秒读历史数据
	history_timer_id = setInterval(QueryHistoryMessage,3000);
	
	$("#btn-query-receivermsg-histoy").click(filterHistoryMessage);
	
});

//定时请求消息
function QueryHistoryMessage()
{
	clearInterval(history_timer_id);
	
	var receiverid = $("#receiver-msg-userid-histoy").val();
	
	$.ajax({
        //提交数据的类型 POST GET
        type:"GET",
        //提交的网址
        url:"/MsgService/MessageSender",
        //提交的数据
        data:{type:"history",receiverid:receiverid,msgtype:"allmsg"},
        //返回数据的格式
        datatype: "json",
        success:function(data){           
        },
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus){
        	var strJson = XMLHttpRequest.responseText;
        	if(strJson == "")
        	{
        		return;
        	}
    		var jsonObj = JSON.parse(strJson);
    		var msgArray = jsonObj;
    		var rowCount = 0;
    		
    		for(var nIndex=0; nIndex<msgArray.length; nIndex++)
    		{
    			AddHisMessageToTable(msgArray[nIndex],rowCount);
    			
    			if(rowCount++ > 9)
    			{
    				break;
    			}
    		}
    		//查询消息
    		$(".historymsg-link").click(function(){
    			var msgID =  $(this).next().val();
    			QueryHisMessage(msgID);
    		});
    		
    		g_HistoryMsgArray = msgArray;
        },
        //调用出错执行的函数
        error: function(){
        }         
    });
}

//将消息添加进列表
function AddHisMessageToTable(msg,row)
{
	RemoveMsgFromTable(row);
	var rowID = "#table-system-msg-histoy_"+row;

	var space = "     ";
	var msgType = "sysmsg";
	
	for(var coloumn=0; coloumn<5; coloumn++)
	{
		var nthchild = "td:nth-child("+(coloumn+1)+")";
		var cell = $(rowID+" "+nthchild);
		
		//填充数据 
		switch(coloumn)
		{
		case 0://序号
			row = row+1;
			if(msg.MsgType=="AppMessage")
			{
				cell.append("<input type='checkbox' name='selectmsg' class='historymsg-checkbox' disabled='true'/>"+space+row);
			}
			else
			{
				cell.append("<input type='checkbox' name='selectmsg' class='historymsg-checkbox'/>"+space+row);
			}
			
			cell.css("text-align","center");
			break;
		case 1:
			var TitleText = "";
			if(msg.MsgType=="SysMessage")
			{
				if(msg.MsgTitle == "AddFriend")
				{
					TitleText = "申请加为好友";
				}
				if(msg.MsgTitle == "ReplyFriend")
				{
					if(msg.MsgString=="agree")
					{
						TitleText = "同意加为好友";
					}
					else
					{
						TitleText = "拒绝加您为好友";
					}
				}
			}
			else
			{
				TitleText = msg.MsgTitle;
			}
			cell.append("<a class='historymsg-link' href='Javascript:void(0)'>"+TitleText+"</a>");
			cell.append("<input type='hidden' name='receive-msg-id-histoy' value="+msg.MessageID+">");
			cell.css("text-align","left");
			break;
		case 2:
			if(msg.MsgType=="SysMessage")
			{
				cell.text("系统消息");
				msgType = "sysmsg";
			}
			else if(msg.MsgType=="AppMessage")
			{
				cell.text("应用消息");
				msgType = "appmsg";
			}
			else
			{
				cell.text("用户消息");
				msgType = "usermsg";
			}
			cell.css("text-align","center");
			break;
		case 3:
			var senderName = getHisSenderName(msgType,msg.SenderID);
			cell.text(senderName);
			cell.css("text-align","center");
			break;
		case 4:
			cell.text(msg.GenerTime);
			cell.css("text-align","center");
			break;
		}
	}
	
	
}

function QueryHisMessage(msgid)
{
	var curmsg = null;
	//修改本地缓存状态
	for(var nIndex=0; nIndex<g_HistoryMsgArray.length; nIndex++)
	{
		if(g_HistoryMsgArray[nIndex].MessageID == msgid)
		{
			curmsg = g_HistoryMsgArray[nIndex];
			break;
		}	
	}
	if(curmsg==null)
	{
		return;
	}
	
	//弹出对话框显示内容(系统消息要重新整理)
	if(curmsg.MsgType=="SysMessage")
	{
		//添加好友及好友回复消息
		if(curmsg.MsgTitle == "AddFriend"||curmsg.MsgTitle == "ReplyFriend")
		{
			var msgstring = "";
			if(curmsg.MsgString == "agree")
			{
				msgstring = "同意";
			}
			else if(curmsg.MsgString == "disagree")
			{
				msgstring = "不同意";
			}
			else
			{
				msgstring = curmsg.MsgString;
			}
			
			var content = getHisSenderName("usermsg",curmsg.SenderID)+"添加您为好友</br>";
			content += "附加信息："+msgstring;
			win.alertEx(content);
			
		}
		//其它系统消息
		else
		{
			if(curmsg.MsgTitle == "SysWarn")
			{
				curmsg.MsgTitle = "系统警告";
			}
			if(curmsg.MsgTitle == "SysMsg")
			{
				curmsg.MsgTitle = "系统消息";
			}
			openDialog("查看消息","div-historymsg-dialog",435,350);
			$(".text-historymsg-title").val(curmsg.MsgTitle);
			$(".texta-historymsg-content").val(curmsg.MsgString);
		}
	}
	//UserMessage及AppMessage
	else
	{
		openDialog("查看消息","div-historymsg-dialog",435,350);
		$(".text-historymsg-title").val(curmsg.MsgTitle);
		$(".texta-historymsg-content").val(curmsg.MsgString);
	}
}

function RemoveHisMsgFromTable(row)
{
	var rowID = "#table-system-msg-histoy_"+row;
	
	for(var coloumn=0; coloumn<6; coloumn++)
	{
		var nthchild = "td:nth-child("+(coloumn+1)+")";
		var cell = $(rowID+" "+nthchild);
		cell.text("");	
	}
}

function DeleteHisMessage(msgid)
{
	
}
//获得发送者名字
function getHisSenderName(msgType,senderID)
{
	var name = "消息平台";
	switch(msgType)
	{
	case "allmsg":
	case "sysmsg":
		if(msgType == "sysmsg")
		{
			break;
		}
	case "appmsg":
		if(totalAppArray != null)
		{
			for(var nIndex=0; nIndex<totalAppArray.length; nIndex++)
			{
				if(totalAppArray[nIndex].AppId == senderID)
				{
					name = totalAppArray[nIndex].AppName;
					break;
				}
			}
		}
		if(msgType == "appmsg")
		{
			break;
		}
	case "usermsg":
		if(totalUserArray != null)
		{
			for(var nIndex=0; nIndex<totalUserArray.length; nIndex++)
			{
				if(totalUserArray[nIndex].UserId == senderID)
				{
					name = totalUserArray[nIndex].UserName;
					break;
				}
			}
		}
	}
	return name;
}

//消息筛选
function filterHistoryMessage()
{
	 ClearHistoryMsgTable();
	 var msgType = $("#select-msg-type-histoy option:selected").val();
	 var keyword = $("#title-keyword-histoy").val();
	 var sender = $("#sender-name-histoy").val();
	 var sendTime = $("#receiver-time-histoy option:selected").val();
	 //根据条件筛选历史消息。
	 //alert(msgType+keyword+sender+sendTime);
	 
	 var rowCount = 0;
	 for(var nIndex=0; nIndex<g_HistoryMsgArray.length; nIndex++)
	 {
		 var curMsg = g_HistoryMsgArray[nIndex];
		 var tempType = "allmsg";
		 //筛选消息类型
		 switch(msgType)
		 {
		 case "系统消息":
			 if(curMsg.MsgType=="AppMessage"||curMsg.MsgType=="UserMessage")
			 {
				 continue;
			 }
			 tempType = "sysmsg";
			 break;
		 case "应用消息":
			 if(curMsg.MsgType!="AppMessage")
			 {
				 continue;
			 }
			 tempType = "appmsg";
			 break;
		 case "用户消息":
			 if(curMsg.MsgType!="UserMessage")
			 {
				 continue;
			 }
			 tempType = "usermsg";
			 break;
		 }
		 //筛选标题关键字
		 if(keyword.length>0 && curMsg.MsgTitle.indexOf(keyword)<0)
		 {
			 continue;
		 }
		 //筛选姓名
		 if(sender != "消息平台")
		 {
			 var senderName = getHisSenderName(tempType,curMsg.SenderID);
			 if(sender.length>0 && senderName.indexOf(sender)<0)
			 {
				 continue;
			 }
		 }
		 else
		 {
			 if(curMsg.MsgType=="AppMessage"||curMsg.MsgType=="UserMessage")
			 {
				 continue;
			 }
		 }
		 //筛选发送时间
		 var generTime = new Date(curMsg.GenerTime);//标准时间格式转换为时间戳
		 var compTime = new Date();	//当前时间~比较时间
		 switch(sendTime)
		 {
		 case "今天"://从凌晨0点开始计算
			 compTime.setHours(0);
			 compTime.setMinutes(0);
			 compTime.setSeconds(0);
			 if(generTime<compTime)
			 {
				 continue;
			 }
			 break;
		 case "三天以内":
			 compTime.setDate(compTime.getDate()-3);
			 if(generTime<compTime)
			 {
				 continue;
			 }
			 break;	
		 case "一周以内":
			 compTime.setDate(compTime.getDate()-7);
			 if(generTime<compTime)
			 {
				 continue;
			 }
			 break;	 
		 }
		 //满足时间筛选条件的可以添加到列表
		 AddHisMessageToTable(curMsg,rowCount);
			
		 if(rowCount++ > 10)
		 {
			break;
		 }
		 
		//查询消息
		$(".historymsg-link").click(function(){
			var msgID =  $(this).next().val();
			QueryHisMessage(msgID);
		});
	 }
	 
	 function ClearHistoryMsgTable()
	 {
		 for(var nIndex=0; nIndex<11; nIndex++)
		 {
			 RemoveHisMsgFromTable(nIndex);
		 }
	 }
}