<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>第三方应用注册</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">
	
	<link href="./jquery/jquery-ui-custom/jquery-ui.css" rel="stylesheet" type="text/css"/>
	<link href="./css/public.css" rel="stylesheet" type="text/css"/>
	<link href="./css/app-register.css" rel="stylesheet" type="text/css"/>
	
	<script type="text/javascript" src="./js/jquery-3.2.1.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/external/jquery/jquery.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/jquery-ui.js"></script>
	<script type="text/javascript" src="./js/public.js"></script>
	<script type="text/javascript" src="./js/app-register.js"></script>
	
  </head>
  
  <body>
	<div  id="id_appregister_content">
	   <h2>欢迎注册华东交大消息平台</h2>
	   <br><br>
	   <form>
			登录账号 : <input type="text" id="id_register_appid" class="app-register-edit"><label>&nbsp;*</label>
			<br><br>
			应用名称 : <input type="text" id="id_register_appname" class="app-register-edit"><label>&nbsp;*</label> 
			<br><br>
			登录密码 : <input type="password" id="id_register_pwd"  class="app-register-edit"><label>&nbsp;*</label>
			<br><br>
			重复密码 : <input type="password" id="id_register_reppwd"  class="app-register-edit"><label>&nbsp;*</label>
			<br><br>
			应用类型: <input type="radio" name="apptype" value="1">消息型&nbsp;&nbsp;&nbsp;<input type="radio" name="apptype"  value="2">应用型
			<label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&thinsp;*</label> 
			<br><br>
			联系电话 : <input type="text" id="id_register_phone"  class="app-register-edit">
			<br><br>
			显示图标 : <input type="text" id="id_register_icon"  class="app-register-edit"> <button>...</button>
			<br><br>
			应用介绍：<p><textarea rows="6" cols="40" id="id_register_remark"></textarea></p>
			<input type="button" value="注册" id="id-register-submit" onclick="RegisterApp()"> 
		</form>
	</div>
  </body>
</html>
