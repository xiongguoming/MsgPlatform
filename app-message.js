var g_HistoryAppMsgAarray = null;

$(document).ready(function()
{
	var fields = ["序号","内容摘要","发送时间","操作"];
	var Size = [50,400,200,120];
	CreateBlankTable("appmsg-history-zone","appmsg-history-table",fields,Size,13);
	
	var appId = $("#app-sendmsg-id").val();
	
	$.ajax({
        //提交数据的类型 POST GET
        type:"GET",
        //提交的网址
        url:"/MsgService/MessageSender",
        //提交的数据
        data:{type:"history",receiverid:appId,msgtype:"appmsg"},
        //返回数据的格式
        datatype: "json",
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus){
        	var strJson = XMLHttpRequest.responseText;
        	if(strJson == "")
        	{
        		return;
        	}
    		var jsonObj = JSON.parse(strJson);
    		var msgArray = jsonObj;
    		
    		if(msgArray != null)
    		{
    			var rowCount = 0;
        		for(var nIndex=0; nIndex<msgArray.length; nIndex++)
        		{
        			InsertHistoryAppMessage(msgArray[nIndex],rowCount);
        			
        			if(rowCount++ > 9)
        			{
        				break;
        			}
        		}
    		}
    		//查询消息
    		$(".queryAppMessage").click(function(){
    			var msgID =  $(this).next().val();
    			QueryAppMessage(msgID); 
    		});
    		/*
    		//删除消息
    		$(".deleteAppMessage").click(function(){
    			var msgID =  $(this).next().val();
    			//DeleteAppMessage(msgID);
    		});
    		*/
    		g_HistoryAppMsgAarray = msgArray;
        },
        //调用出错执行的函数
        error: function(){
        }         
    });
	
	$("#button-appmsg-send").click(function()
	{ 
		var appId = $("#app-sendmsg-id").val();
		var title = $("#app-sendmsg-title").val();
		var content = $("#app-sendmsg-content").val();
		
		var sdTemp = new Array();
		for(var nIndex=0; nIndex<5; nIndex++)
		{
			sdTemp[nIndex] = '0';
		}
		
		$.each($('input:checkbox:checked'),function(){
			
			var type = $(this).val();
			switch(type)
			{
			case '1'://
				sdTemp[0] = '1';
				break;
			case '2'://
				sdTemp[1] = '1';		
				break;
			case '3'://
				sdTemp[2] = '1';		
				break;
			case '4'://
				sdTemp[3] = '1';		
				break;
			}
	    });
		
		var sendType = sdTemp[0]+sdTemp[1]+sdTemp[2]+sdTemp[3];
		
		win.alertEx(appId+title+content+sendType);
		
		$.ajax({
	        type:"GET",
	        url:"/MsgService/MessageReceiver",
	        data:{type:"appmsg",appId:appId,title:title,content:content,sendType:sendType},
	        datatype: "html",
	        
	        complete: function(XMLHttpRequest, textStatus){
	       	 win.alertEx("发送成功!");  
	        },
	        
	        error: function(){
	       	 win.alertEx("发送失败!");
	        }         
	    });
	});
});

function InsertHistoryAppMessage(msg,row)
{
	RemoveMsgFromTable(row);
	var rowID = "#appmsg-history-table_"+row;
	
	for(var coloumn=0; coloumn<5; coloumn++)
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
			cell.text(msg.MsgTitle);
			cell.css("text-align","left");
			break;
		case 2:
			cell.text(msg.GenerTime);
			cell.css("text-align","center");
			break;
		case 3://操作
			cell.append("<input type='button' class='queryAppMessage' value='查看'/>");
			//cell.append("<input type='button' class='deleteAppMessage' value='删除'/>");
			cell.append("<input type='hidden' name='receive-msg-id-histoy' value="+msg.MessageID+">");
			cell.css("text-align","center");
		}
	}
}
function QueryAppMessage(msgId)
{
	var curmsg = null;
	for(var nIndex=0; nIndex<g_HistoryAppMsgAarray.length; nIndex++)
	{
		if(g_HistoryAppMsgAarray[nIndex].MessageID == msgId)
		{
			curmsg = g_HistoryAppMsgAarray[nIndex];
			break;
		}	
	}
	if(curmsg==null)
	{
		return;
	}
	
	openDialog("应用消息","div-appmsg-dialog",435,350);
	$(".text-appmsg-title").val(curmsg.MsgTitle);
	$(".texta-appmsg-content").val(curmsg.MsgString);
}

//将某行数据清除
function RemoveMsgFromTable(row)
{
	var rowID = "#appmsg-history-table_"+row;
	
	for(var coloumn=0; coloumn<5; coloumn++)
	{
		var nthchild = "td:nth-child("+(coloumn+1)+")";
		var cell = $(rowID+" "+nthchild);
		switch(coloumn)
		{
		case 0:
			cell.text(""); 
			break;
		case 1:
			cell.text("");
			break;
		case 2:
			cell.text("");
			break;
		case 3:
			cell.text("");
			break;
		case 4://操作
			cell.text("");
		}
	}
}