/*
var totalAppArray = null;
var totalFocusApps = "";//格式xxx,xxx,xxx,
*/
var totalapp_delytime = -1;

$(document).ready(function(){
	
	initTotalAppsTable("total-app-showarea","total-applist");
	totalapp_delytime = setInterval(DisplayTotalApps,3000);
});


function initTotalAppsTable(divId,tableId)
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

function DisplayTotalApps()
{
	clearInterval(rmtimerid);
	
	var appAarray = totalAppArray;
	var count = 0;
	
	if(appAarray == null)
	{
		return;
	}
	for(var nIndex=0; nIndex<appAarray.length; nIndex++)
	{
		if(appAarray[nIndex].Status!='1')
		{
			continue;
		}
		insertTotalAppIntoTable(appAarray[nIndex],count);
		
		if(count++ > 20)
		{
			break;
		}
	}
	
	var appId = "";
	var userId = $("#total-app-userid").val();
	//查看应用
	$(".button-totalapp-view").click(function(){
		appId =  $(this).next().next().val();
		openAppInfo(appId);
	});
	//关注应用
	$(".button-totalapp-focus").click(function(){
		appId =  $(this).next().val();
		userFocusApp($(this),userId,appId);
	});
}

function getTotalAppInfoHtml(appId,iconName,AppName,describ)
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
	html += "<div class='total-applist-app'>";

	html += "<div class='total-applist-app-icon'>";
	dynHtml = "<img src='./res/appicon/"+iconName+"'/>";
	html += dynHtml;
	html += "</div>";

	html += "<div class='total-applist-app-info'>";
	html += "<form>";
	dynHtml = "<label><font><strong>"+AppName+"</strong></font></label><br/>";
	html += dynHtml;
	dynHtml = "<label style='display:block;height:18px'><font size='2' color='#696969'>"+describ+"</font></label><br/><br/>";
	html += dynHtml;
	html += "<input type='button' value='查看' class='button-totalapp-view'>&nbsp;";
	//已关注
	if(IsFocusedApp(appId))
	{
		html += "<input type='button' value='已关注' class='button-totalapp-focus' disabled='disabled'>";
	}
	else
	{
		html += "<input type='button' value='关注' class='button-totalapp-focus'>";
	}
	html += "<input type='hidden' value="+appId+">";
	html += "</form>";
	html += "</div>";	
	html += "</div>";
	
	return html;
}

function insertTotalAppIntoTable(appInfo,count)
{
	var row = parseInt(count/5);
	var col = count%5+1;//nth-child从1开始
	
	var postion = "#total-applist tr:eq("+row+") td:nth-child("+col+")";
	var apphtml = getTotalAppInfoHtml(appInfo.AppId,appInfo.Icon,appInfo.AppName,appInfo.Remark);
	$(postion).html(apphtml);
}

//查看应用信息
function openAppInfo(appId)
{
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
		openDialog("查看应用","dialog-totalapp-view",300,350);
		
		$(".input-totalapp-appid").val(curApp.AppId);//请求内容
		$(".input-totalapp-name").val(curApp.AppName);
		if(curApp.AppType == 0)
		{
			$(".input-totalapp-type").val("消息型");
		}
		else
		{
			$(".input-totalapp-type").val("应用型");
		}
		
		$(".input-totalapp-phone").val(curApp.Phone);
		
		$(".text_totalapp_remark").html(curApp.Remark);
	}
}

//用户关注App
function userFocusApp(btnObj, userId,appId)
{
	btnObj.attr("disabled","disabled");
	$.ajax({
        //提交数据的类型 POST GET
        type:"GET",
        //提交的网址
        url:"/MsgService/AppServiceEx",
        //提交的数据
        data:{type:"focusapp",userid:userId,appid:appId},
        //返回数据的格式
        datatype: "json",
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
        			win.alertEx("关注成功！");
        			btnObj.val("已关注");
        			
    			}
        		else
        		{
        			win.alertEx("关注失败！");
        			btnObj.attr("disabled","true");
        		}
        	}            
        },
        //调用出错执行的函数
        error: function(){
        	win.alertEx("关注失败！");
        	btnObj.attr("disabled","true");
        }         
    });
}
//判断是否是已关注应用
function IsFocusedApp(appId)
{
	var pos = totalFocusApps.indexOf(appId);
	var len = appId.length;
	if(pos<0)
	{
		return false;
	}
	//以下判断防止ID包含
	if(pos==0 && totalFocusApps.charAt(pos+len)==',')
	{
		return true;
	}
	if(totalFocusApps.charAt(pos-1)==',' && totalFocusApps.charAt(pos+len)==',')
	{
		return true;
	}
	
	return false;		
}