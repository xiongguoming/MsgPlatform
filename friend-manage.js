//当前操作的好友ID
var fmCurFriendId;					

//初始化页面
$(document).ready(function(){
	ReadFriends();
});

//获取好友列表
function ReadFriends()
{
	var userID = $("#friend-manage-userid").val();

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
        },
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus){
        	if(XMLHttpRequest.readyState == 4)
        	{	
        		var strJson = XMLHttpRequest.responseText;
        		var jsonObj = JSON.parse(strJson);
        		var userArray = jsonObj;
        		var rowCount = 0;
        		
        		for(var nIndex=0; nIndex<userArray.length; nIndex++)
        		{
        			AddFriendToTable(userArray[nIndex],rowCount);
        			
        			if(rowCount++ > 9)
        			{
        				break;
        			}
        		}
        		totalUserArray = userArray;
        		
        		$(".fmSendMessage").click(function(){
        			fmCurFriendId =  $(this).next().next().next().val();
        			OpenMsgSender(fmCurFriendId);
        		});
        		//删除好友
        		$(".fmDeleteFriend").click(function(){
        			fmCurFriendId =  $(this).next().val();
        			DeleteFriend(fmCurFriendId);
        		});
        		
        		setCookie("MyFriends",strJson);
        	}            
        },
        //调用出错执行的函数
        error: function(){
        	win.alertEx("消息发送失败！");
        }         
    });
}

function AddFriendToTable(user,row)
{
	var rowID = "#FriendRow_"+(row+1);
	
	for(var coloumn=0; coloumn<6; coloumn++)
	{
		var nthchild = "td:nth-child("+(coloumn+1)+")";
		var cell = $(rowID+" "+nthchild);
		//填充数据 
		switch(coloumn)
		{
		case 0:
			cell.text(row+1); 
			cell.css("text-align","center");
			break;
		case 1:
			cell.text(user.UserName);
			cell.css("text-align","left");
			break;
		case 2:
			if(user.Sex==0)
			{
				cell.text("女");
			}
			else
			{
				cell.text("男");
			}
			cell.css("text-align","center");
			break;
		case 3:
			cell.text("现代教育技术中心");
			cell.css("text-align","left");
			break;
		case 4:
			if(user.OnlineStatus)
			{
				cell.text("在线");
			}
			else
			{
				cell.text("离线");
			}
			cell.css("text-align","center");
			break;
		case 5://操作
			cell.append("<input type='button' class='fmSendMessage' value='发送消息'/>");
			cell.append("<span>&nbsp;</span>");
			cell.append("<input type='button' class='fmDeleteFriend' value='删除'/>");
			cell.append("<input type='hidden' name='UserID' value="+user.UserId+">");
			cell.css("text-align","center");
		}
	}
}

function QueryFriend(userID)
{
	//创建一个新窗口
	OpenWindow = window.open("", "ShowUserInfo", "height=200, width=300, top=200, left=600," +
	"toolbar=no, menubar=no, scrollbars=no, resizable=no, location=no, status=no"); 
	
	//写成一行  
	OpenWindow.document.write("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">"); 
	OpenWindow.document.write("<HTML>");
    OpenWindow.document.write("<HEAD><TITLE>查看用户信息</TITLE></HEAD>");  
    OpenWindow.document.write("<BODY BGCOLOR=#E6E6FA>"); 
    OpenWindow.document.write("<h3>用户信息</h3>");
  
    var userAarray = g_UserAarray;
    var userInfo = "";
    for(var nIndex=0; nIndex<userAarray.length; nIndex++)
	{
		if(userAarray[nIndex].UserId == userID)
		{
			userInfo += "<br/>账号：";
			userInfo += userAarray[nIndex].UserId;
			userInfo += "<br/>姓名：";
			userInfo += userAarray[nIndex].UserName;
			userInfo += "<br/>性别：";
			if(userAarray[nIndex].Sex)
			{
				userInfo += "女";
			}
			else
			{
				userInfo += "男";
			}
			userInfo += "<br/>单位：";
			userInfo += getUnitInfo(userAarray[nIndex].UnitID);
			userInfo += "<br/>在线状态：";
			if(userAarray[nIndex].OnlineStatus)
			{
				userInfo += "在线";
			}
			else
			{
				userInfo += "离线";
			}
			break;
		}	
	}
   
    OpenWindow.document.write(userInfo);
    OpenWindow.document.write("</BODY>");
    OpenWindow.document.write("</HTML>"); 
    OpenWindow.document.close(); 
    $('#dlg-user-Info').html(userInfo);
	//event.preventDefault(); 
}

function DeleteFriend(delUserID)
{
	if(!window.confirm('删除好友后不可恢复，您确定还要继续吗？'))
	{
       return;
    }
	var userID = $("#friend-manage-userid").val();

	$.ajax({
        type:"GET",
        url:"/MsgService/FriendsFinding",
        data:{type:"deletefriend",userid:userID,deluserid:delUserID},
        datatype: "json",
        //在请求之前调用的函数
        //beforeSend:function(){$("#msg").html("logining");},
        //成功返回之后调用的函数             
        success:function(data){
       	 //$("#msg").html(decodeURI(data));            
        },
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus){
        	
        	if(XMLHttpRequest.readyState == 4)
        	{
        		if(XMLHttpRequest.responseText.indexOf("success")<0)
        		{
        			alert("删除用户失败!");
        		}
        		else
        		{
        			RefreshTable();
        			alert("删除用户成功!");
        		}
        	}
        },
        //调用出错执行的函数
        error: function(){
       	 alert("删除用户失败！");
        }         
    });
}

function RefreshTable()
{
	var nIndex = 0;
	for(nIndex=0; nIndex<totalUserArray.length; nIndex++)
	{
		RemoveFriendFromTable(nIndex);
	}
	
	if(fmCurFriendId!=null && fmCurFriendId!="")
	{
		for(nIndex=0; nIndex<totalUserArray.length; nIndex++)
		{
			if(totalUserArray[nIndex].UserId == fmCurFriendId)
			{
				//删除索引位置为nIndex的一个元素
				totalUserArray.splice(nIndex,1);
				break;
			}
		}	
		
		fmCurFriendId = null;
	}
	
	for(nIndex=0; nIndex<totalUserArray.length; nIndex++)
	{
		AddFriendToTable(totalUserArray[nIndex],nIndex);
		//当前列表最多只能存放9条记录
		if(nIndex > 9)
		{
			break;
		}
	}
	
	//为满足连续删除用户，在删除用户后，要重新加载消息事件
	$(".fmSendMessage").click(function(){
		//当前发送消息的好友ID
		fmCurFriendId =  $(this).next().next().next().val();
		OpenMsgSender();
	});
	//删除好友
	$(".fmDeleteFriend").click(function(){
		//当前删除好友的ID
		fmCurFriendId =  $(this).next().val();
		DeleteFriend(fmCurFriendId);
	});
}

function RemoveFriendFromTable(row)
{
	var rowID = "#FriendRow_"+(row+1);
	
	for(var coloumn=0; coloumn<6; coloumn++)
	{
		var nthchild = "td:nth-child("+(coloumn+1)+")";
		var cell = $(rowID+" "+nthchild);
		cell.html("");	
	}
}

//打开发送消息对话框
function OpenMsgSender()
{
	openDialog("发送消息","div-sendmsg-dialog",435,350);
}

//发送消息
function SendUserMessage()
{
	closeDialog("div-sendmsg-dialog");
	
	var senderID = $("#friend-manage-userid").val();
	var title = $(".text-sendmsg-title").val();
	var content = $(".texta-sendmsg-content").val();
	
	var nIndex = 0;
	var sdTemp = new Array();
	
	for(nIndex=0; nIndex<5; nIndex++)
	{
		sdTemp[nIndex] = '0';
	}
	
	//获取每一个选中值
	if($(".input-sendtype1").attr("checked"))
	{
		sdTemp[0] = '1';
	}
	if($(".input-sendtype2").attr("checked"))
	{
		sdTemp[1] = '1';
	}
	if($(".input-sendtype3").attr("checked"))
	{
		sdTemp[2] = '1';
	}
	if($(".input-sendtype4").attr("checked"))
	{
		sdTemp[3] = '1';
	}
    
	var sendType = sdTemp[0]+sdTemp[1]+sdTemp[2]+sdTemp[3];
	
	//win.alertEx(sendType);
	
	$.ajax({
        type:"POST",
        url:"/MsgService/MessageReceiver",
        data:{type:"usermsg",senderid:senderID,receiverid:fmCurFriendId,title:title,content:content,sendType:sendType},
        datatype: "html",
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus){
        	win.alertEx("消息已发送！");
        },
        //调用出错执行的函数
        error: function(){
        	win.alertEx("消息发送失败！");
        }         
    });
}
