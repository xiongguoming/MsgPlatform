
var focusapp_dely_timer = -1;

$(document).ready(function(){
	
	initAppsTable("focus-app-showarea","focus-applist");
	focusapp_dely_timer = setInterval(DisplayFocusApps,3000);
});

function RemaveAllApps()
{
	var row = 0;
	var col = 0;
	var postion = null;
	for(var count=0; count<20; count++)
	{
		row = parseInt(count/5);
		col = count%5+1;	
		postion = "#focus-applist tr:eq("+row+") td:nth-child("+col+")";
		$(postion).html("");
	}
}
function DisplayFocusApps()
{
	if(focusapp_dely_timer>0)
	{
		clearInterval(focusapp_dely_timer);
	}
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
			insertAppIntoTable(appArray[nIndex],count);
			
			if(count++ > 20)
			{
				break;
			}
		}	
	}
	var appId = "";
	var userId = $("#total-app-userid").val();
	//查看应用
	$(".button-focusapp-view").click(function(){
		appId =  $(this).next().next().val();
		OpenFocusAppInfo(appId);
	});
	//取消关注
	$(".button-focusapp-cancel").click(function(){
		appId =  $(this).next().val();
		cancelFocusApp(userId,appId);
	});
}
//打开关注应用信息
function OpenFocusAppInfo(appId)
{
	//win.alertEx(appId);
	var curApp = null;
	for(var nIndex=0; nIndex<totalAppArray.length; nIndex++)
	{
		if(totalAppArray[nIndex].AppId == appId)
		{
			curApp = totalAppArray[nIndex];
			break;
		}
	}
	
	if(curApp!=null)
	{
		openDialog("查看应用","dialog-focusapp-view",300,350);
		
		$(".input-focusapp-appid").val(curApp.AppId);//请求内容
		$(".input-focusapp-name").val(curApp.AppName);
		if(curApp.AppType == 0)
		{
			$(".input-focusapp-type").val("消息型");
		}
		else
		{
			$(".input-focusapp-type").val("应用型");
		}
		
		$(".input-focusapp-phone").val(curApp.Phone);
		
		$(".text_focusapp_remark").html(curApp.Remark);
	}
}

//取消关注app
function cancelFocusApp(userId,appId)
{
	//win.alertEx(userId+appId);
	$.ajax({
        //提交数据的类型 POST GET
        type:"GET",
        //提交的网址
        url:"/MsgService/AppServiceEx",
        //提交的数据
        data:{type:"cancelfocus",userid:userId,appid:appId},
        //返回数据的格式
        datatype: "json",//"xml", "html", "script", "json", "jsonp", "text".
        //成功返回之后调用的函数             
        success:function(data){
        },
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus){
        	if(XMLHttpRequest.readyState == 4)
        	{	
        		var res = XMLHttpRequest.responseText;
        		if(res.indexOf("success")>=0)
    			{
        			EndFocusApp(appId);
        			win.alertEx("操作成功！");
    			}
        		else
        		{
        			win.alertEx("操作失败！");
        		}
        	}            
        },
        //调用出错执行的函数
        error: function(){
        	win.alertEx("关注失败！");
        }         
    });
}

//初始化4X5表格
function initAppsTable(divId,tableId)
{
	var tbody = "";
	var tr = "";
	
	for(var row=0; row<4; row++)
	{
		tr = "<tr>";
		for(var col=0; col<5; col++)
		{
			tr += "<td></td>";
		}
		tr += "</tr>";
		tbody += tr;
	}
	
	
	var table = "<table id=" + tableId +">";
	table += tbody;
	table += "</table>";
	$('#'+divId).html(table);
}

function getAppInfoHtml(appId,iconName,AppName,describ)
{
	if(iconName==""||typeof(iconName)=="undefined")
	{
		iconName = "app-default.png";
	}
	if(typeof(describ)=="undefined")
	{
		describ = "";
	}
	
	var html = "";
	var dynHtml = "";
	html += "<div class='focus-applist-app'>";
	//应用图片
	html += "<div class='focus-applist-app-icon'>";
	dynHtml = "<img src='./res/appicon/"+iconName+"'/>";
	html += dynHtml;
	html += "</div>";
	//应用信息
	html += "<div class='focus-applist-app-info'>";
	html += "<form>";
	dynHtml = "<label><font><strong>"+AppName+"</strong></font></label><br/>";
	html += dynHtml;
	dynHtml = "<label style='display:block;height:18px'><font size='2' color='#696969'>"+describ+"</font></label><br/><br/>";
	html += dynHtml;
	html += "<input type='button' value='查看' class='button-focusapp-view'>&nbsp;";
	html += "<input type='button' value='取消关注' class='button-focusapp-cancel'>";
	html += "<input type='hidden' value="+appId+">";
	html += "</form>";
	html += "</div>";	
	html += "</div>";
	
	return html;
}
//插入应用到列表(第一行从0开始，第一列从0开始)
function insertAppIntoTable(appInfo,count)
{
	var row = parseInt(count/5);
	var col = count%5+1;//nth-child从1开始
	
	var postion = "#focus-applist tr:eq("+row+") td:nth-child("+col+")";
	var apphtml = getAppInfoHtml(appInfo.AppId,appInfo.Icon,appInfo.AppName,appInfo.Remark);
	$(postion).html(apphtml);
}

function IsUserFocusedApp(appId,focusedStr)
{
	if(appId==null||focusedStr==null)
	{
		return false;
	}
	var pos = focusedStr.indexOf(appId);
	var len = appId.length;
	if(pos<0)
	{
		return false;
	}
	//以下判断防止ID包含
	if(pos==0 && focusedStr.charAt(pos+len)==',')
	{
		return true;
	}
	if(focusedStr.charAt(pos-1)==',' && focusedStr.charAt(pos+len)==',')
	{
		return true;
	}
	
	return false;	
}
//结束关注app
function EndFocusApp(appId)
{
	if(appId==null||totalFocusApps==null)
	{
		return;
	}
	var pos = totalFocusApps.indexOf(appId);
	var len = appId.length;
	
	var front = totalFocusApps.substring(0,pos-1);
	var rear = totalFocusApps.substring(pos+len);
	
	totalFocusApps = front+','+rear;
	
	RemaveAllApps();
	DisplayFocusApps();
}
