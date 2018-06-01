<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ page language="java" import="com.pojo.*"%>
<jsp:useBean scope="session" id="user" class="com.pojo.UserInfo"/>
<!-- 由于session已经存在名为"user"的对象，将id设为"user",创建的对象将自动引用会话中的同名对象-->
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    <title>消息平台个人页面</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">
	<link rel="stylesheet" type="text/css" href="./css/main-style.css"/>
	<link rel="stylesheet" type="text/css" href="./css/main-menu-style.css"/>
	
	<script type="text/javascript" src="./js/jquery-3.2.1.js"></script>
	<script type="text/javascript" src="./js/menu.js"></script>
	<script type="text/javascript" src="./js/public.js"></script>
	<script type="text/javascript" src="./js/main.js"></script>
  </head>
  
  <body>
  	<input type="hidden" id="main-userid" value=<jsp:getProperty name="user" property="userID"/>>
  	<div id="Header" align="right">   
	       	欢迎 <font color="red"><jsp:getProperty name="user" property="userName"/></font> 登录系统!
		 	<a href="/MsgService/UserLogin?method='logout'">注销</a><br><br>
	</div>
  	<div id="Container">
	    <div id="Content">
	        <div id="MenuBox">
	        	<h2>消息菜单</h2>
				<ul class="menu">
					<li class="level1">
						<a>消息管理</a>
						<ul class="level2">
							<li id="level2-0"><a href='Javascript:void(0)'>接收消息</a></li>
							<li id="level2-1"><a href='Javascript:void(0)'>历史消息</a></li>
						</ul>
					</li>
					<li class="level1">
						<a>好友管理</a>
						<ul class="level2">
							<li id="level2-2"><a href='Javascript:void(0)'>我的好友</a></li>
							<li id="level2-3"><a href='Javascript:void(0)'>所有用户</a></li>
						</ul>
					</li>
					<li class="level1">
						<a>应用管理</a>
						<ul class="level2">
							<li id="level2-4"><a href='Javascript:void(0)'>我的应用</a></li>
							<li id="level2-5"><a href='Javascript:void(0)'>全部应用</a></li>
						</ul>
					</li>  
					<li class="level1">
						<a>消息订阅</a>
						<ul class="level2">
							<li id="level2-6"><a href='Javascript:void(0)'>消息订阅设置</a></li>
						</ul>
					</li>
				</ul>
			</div>
			<!--各子栏目标题-->
			<div id="Content-Title"><h2 id="Content-Title-H2">接收消息</h2></div>
	        <div id="Content-Main" class="mainContent">
				<!-- 添加上选项卡及页面 -->
				 <div class="mainLayout"><jsp:include page="./msgReceiver.jsp" flush="true"/></div>
		         <div class="mainLayout"><jsp:include page="./msgReceiverHistory.jsp" flush="false"/></div>
				 <div class="mainLayout"><jsp:include page="./friendManage.jsp" flush="false"/></div>
		         <div class="mainLayout"><jsp:include page="./friendFind.jsp" flush="false"/></div>
		         <div class="mainLayout"><jsp:include page="./userFocusApp.jsp" flush="false"/></div>
		         <div class="mainLayout"><jsp:include page="./totalAppList.jsp" flush="false"/></div>
				 <div class="mainLayout"><jsp:include page="./mySetting.jsp" flush="false"/></div>
			</div>
	    </div>
	    <div class="Clear"><!--如何你上面用到float,下面布局开始前最好清除一下。--></div>
	    <div id="Footer" align="center">
	    	<font style="FONT-SIZE: 12pt" face="Tahoma" color="#333333">
			            华东交通大学 2016-2018年版权所有&copy;<br/>如果你有任何意见或建议请联系我们的
			  	<a href="mailto:37800827@qq.com"><font color="#005826">软件维护人员</font></a>
			</font>
	    </div>
    </div>
  </body>
  
  <script language="javascript" type="text/javascript">
	//判断如果无登录信息，跳到登录页面
	if($("#main-userid").val() == "")
	{
		window.location.href = "/MsgService/index.jsp";
	}
	//增加当期页面类名
	$("ul.menu li.level1 ul:first-child").addClass("current");
	//显示首页面
	$("div.mainContent").find("div.mainLayout:not(:first-child)").hide();
	//增加页面ID
	$("div.mainContent div.mainLayout").attr("id", function(){
		return "No"+ $("div.mainContent div.mainLayout").index(this);}
	);
	
	//添加单击事件
	$(".level2 li").click(function()
	{ 
		var index = $(this).attr('id').substring(7);
		
		//根据选中菜单显示不同页面
		var pageIndex = "No" + index;
	    $('#'+pageIndex).siblings().hide();
	    $('#'+pageIndex).show();
	    
	    var controlMenu = $("ul.menu li");
	    controlMenu.eq(index).addClass("current").siblings().removeClass("current");
	    //更新标题栏 
	    var textword = $(this).text();
		$("#Content-Title-H2").text(textword);
	});
</script>
</html>
