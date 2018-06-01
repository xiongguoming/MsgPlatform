<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'userFocusApp.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	
	<link href="./jquery/jquery-ui-custom/jquery-ui.css" rel="stylesheet" type="text/css"/>
	<link href="./css/public.css" rel="stylesheet" type="text/css"/>
	<link href="./css/user-focus-app.css" rel="stylesheet" type="text/css"/>
	
	<script type="text/javascript" src="./js/jquery-3.2.1.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/external/jquery/jquery.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/jquery-ui.js"></script>
	<script type="text/javascript" src="./js/public.js"></script>
	<script type="text/javascript" src="./js/user-focus-app.js"></script>

  </head>
  
  <body>
  	
  	<div id="focus-app-showarea"></div>
  	
  	<div id="dialog-focusapp-view" style="display:none">
  		<form class="form-focusapp">
			登录账号 : <input type="text" class="input-focusapp-appid">
			<br><br>
			应用名称 : <input type="text" class="input-focusapp-name">
			<br><br>
			应用类型 : <input type="text" class="input-focusapp-type">
			<br><br>
			联系电话 : <input type="text" class="input-focusapp-phone">
			<br><br>
			应用介绍 :<br>
			<p><textarea rows="6" cols="30" class="text_focusapp_remark"></textarea></p>
			<br><br>
			<input type="button" value="关闭" class="button-focusapp-close" onclick="closeDialog()"> 
  		</form>
   	 </div>
  </body>
</html>
