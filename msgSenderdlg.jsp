<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>发送消息</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0"> 
	   
	<link href="./css/msg-sender-dialog.css" rel="stylesheet" type="text/css">
	<script type="text/javascript" src="./js/jquery-3.2.1.js"></script>
	<script type="text/javascript" src="./js/msg-sender-dialog.js"></script>
  </head>
  
  <body>
  	<div id="div-sendmsg-container">
  		<form>
  			<table id="table-sendmsg-grid">
  				<tr>
  					<td>
		  				<label>标题</label><br>
		  				<input type="text" id="text-sendmsg-title">
		  				<br><br>
	  				</td>
	  			</tr>
	  			<tr>
  					<td>
		  				<label>正文</label><br>
		  				<textarea id="texta-sendmsg-content"></textarea> 
	  				</td>
	  			</tr>
	  			<tr>
  					<td align="right" valign="middle">
  						<br>
		  				<input type="button" value="发送消息" id="button-sendmsg-send" onclick="SendUserMessageD()"> 
	  				</td>
	  			</tr>
  			</table>
  		</form>
   	 </div>
  </body>
</html>
