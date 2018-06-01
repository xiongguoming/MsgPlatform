
$(document).ready(function()
{
	document.onkeydown = function(event)
	{
		var e = event || window.event || arguments.callee.caller.arguments[0];
		//按下enter键
		if(e && e.keyCode==13)
		{
			UserLogin();
		}
	};
});

function UserLogin()
{
	var type = $("#login-select-type").val();
	var account = $("#login-input-account").val();
	var password = $("#login-input-password").val();
	
	if(account==""||password=="")
	{
		win.alertEx("用户名或密码不能为空！");
		return;
	}
	
	$.ajax({
        type:"GET",
        url:"/MsgService/UserLogin",
        data:{method:"login",type:type,account:account,password:password},
        datatype: "html",
        //调用执行后调用的函数
        complete: function(XMLHttpRequest, textStatus)
        {
        	var res = XMLHttpRequest.responseText;
        	
        	if(res.indexOf("failed") >=0)
    		{
        		$("#login-input-account").val("");
        		$("#login-input-password").val("");
        		win.alertEx("登录失败：账号或密码错误！");
    		}
        	else
        	{
        		var address=$("#idServerAddr").val();
        		//用户
        		if(type.indexOf("user") >=0)
    			{
        			window.location.href="http://"+address+":8080/MsgService/main.jsp";
    			}
        		//应用
        		else
    			{
        			window.location.href="http://"+address+":8080/MsgService/appMessage.jsp";
    			}
        		
        	}
        },
        //调用出错执行的函数
        error: function(){
        	win.alertEx("登录失败：与服务器通信异常！");
        },      
    });
}

//页面关闭事件
$(window).unload(function()
{
    deleteCookie("MyFriends");
}); 