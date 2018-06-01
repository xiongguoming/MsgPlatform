
var unitTree;

$(document).ready(function(){
	ReadUnits();
	ReadUsers();
});

//发送请求好友信息
function SendRFInfo()
{
	//关闭对话框，获取对话框数据内容
	closeDialog("div-addfriend-dialog");
	
	var receiverID = $(".newfriendID").val();
	var senderID = $(ffUserID).val();//自己的ID
	var content = $(".text-addfriend-info").val();//请求信息
	
	$.ajax({
         type:"GET",
         url:"/MsgService/MessageReceiver",
         data:{type:"requestfriend",senderid:senderID,receiverid:receiverID,rqcontent:content},
         datatype: "html",
         //调用执行后调用的函数
         complete: function(XMLHttpRequest, textStatus){
        	 win.alertEx("请求已经发送!"); 
         },
         //调用出错执行的函数
         error: function(){
        	 win.alertEx("请求好友失败！");
         }         
     });
}
//事件函数
function OnAddFriend(rfUserId)
{
	$(".newfriendID").val(rfUserId);
	$(".p-addfriend-name").html(getNewFriendName(rfUserId));
	if(getNewFriendSex(rfUserId)=='1')
	{
		$(".img-addfreind-sex").attr("src","./res/user-male.png");
	}
	else
	{
		$(".img-addfreind-sex").attr("src","./res/user-female.png");
	}
	
	openDialog("添加好友","div-addfriend-dialog",380,250);
}

function SwitchUnit(unitID)
{
	unitTree.openTo(unitID,true);
	//totalUserArray
	var userAarray = totalUserArray;
	var rowCount = 0;
	
	for(rowCount=0; rowCount<10; rowCount++)
	{
		RemoveUserFromTable(rowCount);
	}
	
	rowCount = 0;
	for(var nIndex=0; nIndex<userAarray.length; nIndex++)
	{
		if(unitID == "-1")
		{
			AddUserToTable(userAarray[nIndex],rowCount++);	
		}
		else
		{
			if(userAarray[nIndex].UnitID == unitID)
			{
				AddUserToTable(userAarray[nIndex],rowCount++);	
			}	
		}
		if(rowCount>9)
		{
			break;
		}
	}
	//添加好友
	$(".ffAddFriend").click(function()
	{
		var userID = $(this).next().val();
		OnAddFriend(userID);
	});
}

function initUnitTree(jsonStr)
{
	//创建树对象,unitTree为对象名称
	unitTree = new dTree('unitTree');
	var rootId = 99999;
	//创建根节点
	unitTree.add(rootId, -1, "华东交通大学");
	//根据单位数据动态创建节点
	var jsonObj = JSON.parse(jsonStr);
	if(jsonObj != null)
	{
		var unitArray = jsonObj;
		var superId = 0;
		var owerId = 0;
		var unitName = "";
		var selectFun = "";
		for(var nIndex=0; nIndex<unitArray.length; nIndex++)
		{
			superId = unitArray[nIndex].SuperID;
			owerId = unitArray[nIndex].UnitId;
			unitName = unitArray[nIndex].UnitName;
			selectFun = 'javascript:SwitchUnit('+owerId+')';
			
			if(superId>0)
			{
				unitTree.add(owerId,superId,unitName,selectFun,'','','img/unitlevel2.png','img/unitlevel2.png');
			}
			else
			{
				superId = rootId;
				unitTree.add(owerId,superId,unitName,selectFun,'','','img/unitlevel1.png','img/unitlevel1.png');
			}
		}
		
		totalUnitArray = unitArray;
	}
    //config配置，设置文件夹不能被链接，即有子节点的不能被链接。  
	unitTree.config.folderLinks = false;
	
    $(".dtree").append(unitTree.toString());
}
//读取所有单位信息
function ReadUnits()
{
	ajaxRequest.get({
        url:"/MsgService/FriendsFinding",
        data:{type:"readunit"},
        //调用执行后调用的函数
        success: function(data)
        {
        	initUnitTree(data);
        },
        //调用出错执行的函数
        error: function()
        {
       	 	win.alertEx("读取单位失败！");
        }         
	});
}
//读取所有用户信息
function ReadUsers()
{
	$.ajax({
        type:"GET",
        url:"/MsgService/FriendsFinding",
        data:{type:"readuser"},
        datatype: "html",
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus)
        {
        	InitUserTable(XMLHttpRequest.responseText);
        },
        //调用出错执行的函数
        error: function()
        {
       	 	win.alertEx("请求好友失败！");
        }         
    });
}

function InitUserTable(jsonStr)
{
	var jsonObj = $.parseJSON(jsonStr);
	var userArray = jsonObj;
	var rowCount = 0;
	
	for(var nIndex=0; nIndex<userArray.length; nIndex++)
	{
		AddUserToTable(userArray[nIndex],rowCount);
		
		if(rowCount++ > 12)
		{
			break;
		}
	}
	
	//添加好友
	$(".ffAddFriend").click(function()
	{
		var userID =  $(this).next().val();
		OnAddFriend(userID);
	});
	
	totalUserArray = userArray;
}
//增加一行记录到表格
function AddUserToTable(user,row)
{
	var rowID = "#UserRow_"+(row+1);
	var myID = $(ffUserID).val();//自己的ID
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
			if(myID!=user.UserId && !IsMyFriend(user.UserId))
			{
				cell.append("<input type='button' class='ffAddFriend' value='加为好友'/>");
			}
			else
			{
				cell.append("<input type='button' class='ffAddFriend' disabled='disabled' value='加为好友'/>");
			}
			cell.append("<input type='hidden' name='UserID' value="+user.UserId+">");
			cell.css("text-align","center");
		}
	}
}

function RemoveUserFromTable(row)
{
	var rowID = "#UserRow_"+(row+1);
	
	for(var coloumn=0; coloumn<6; coloumn++)
	{
		var nthchild = "td:nth-child("+(coloumn+1)+")";
		var cell = $(rowID+" "+nthchild);
		cell.text("");	
	}
}

//获得发送者名字
function getNewFriendName(userID)
{
	var name = "";
	for(var nIndex=0; nIndex<totalUserArray.length; nIndex++)
	{
		if(totalUserArray[nIndex].UserId == userID)
		{
			name = totalUserArray[nIndex].UserName;
			break;
		}
	}
	return name;
}

function getNewFriendSex(userID)
{
	var Sex = '0';
	for(var nIndex=0; nIndex<totalUserArray.length; nIndex++)
	{
		if(totalUserArray[nIndex].UserId == userID)
		{
			Sex = totalUserArray[nIndex].Sex;
			break;
		}
	}
	return Sex;
}

function getUnitInfo(unitID)
{
	return "现代教育技术中心";
}
 

 