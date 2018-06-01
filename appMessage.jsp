<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<jsp:useBean scope="session" id="app" class="com.pojo.AppInfo"/>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>应用发送消息</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    

	<link href="./jquery/jquery-ui-custom/jquery-ui.css" rel="stylesheet" type="text/css"/>
	<link href="./css/public.css" rel="stylesheet" type="text/css"/>
	<link rel="stylesheet" type="text/css" href="./css/table-style.css"/>
	<link href="./css/app-message.css" rel="stylesheet" type="text/css"/>
	
	<script type="text/javascript" src="./js/jquery-3.2.1.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/external/jquery/jquery.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/jquery-ui.js"></script>
	<script type="text/javascript" src="./js/public.js"></script>
	<script type="text/javascript" src="./js/app-message.js"></script>

  </head>
  
  <body>
  	<div id="app-header" align="right">
		<font color="blue" size="4"><jsp:getProperty name="app" property="appName"/>【<jsp:getProperty name="app" property="describe"/>】
		<a href="/MsgService/UserLogin?method='logout'">注销</a><br><br></font>
	</div>
   	<div id="appmsg-content">
   		<div id="appmsg-sendmsg-area">	
	   		<form>
	   			<input type="hidden" id="app-sendmsg-id" value=<jsp:getProperty name="app" property="appId"/>>
	  			<table id="table-appmsg-grid">
	  				<tr>
	  					<td>
			  				<label>标题</label><br>
			  				<input type="text" id="app-sendmsg-title">
			  				<br><br>
		  				</td>
		  			</tr>
		  			<tr>
	  					<td>
			  				<label>正文</label><br>
			  				<textarea id="app-sendmsg-content"></textarea> 
		  				</td>
		  			</tr>
		  			<tr>
	  					<td align="right" valign="middle">
	  						<input name="app-send-type" type="checkbox" value="1" />网页
							<input name="app-send-type" type="checkbox" value="2" />短信
							<input name="app-send-type" type="checkbox" value="3" />邮件
							<input name="app-send-type" type="checkbox" value="4" />微信
			  				<input type="button" value="发送" id="button-appmsg-send">
		  				</td>
		  			</tr>
	  			</table>
	  		</form>
	  	</div>
  		<!-- 历史消息接收区 -->
   		<div id="appmsg-history-zone"></div>
   	</div>
   	
   	 <!-- 接收消息对话框设计。不要使用ID，否则与对话框ID会冲突导致赋值失败-->
    <div id="div-appmsg-dialog" style="display:none">
  		<form>
  			<table id="table-appmsg-grid">
  				<tr>
  					<td>
		  				<label><font color="blue">标题</font></label><br>
		  				<input type="text" class="text-appmsg-title" readonly="true">
		  				<br><br>
	  				</td>
	  			</tr>
	  			<tr>
  					<td>
		  				<label><font color="blue">正文</font></label><br>
		  				<textarea class="texta-appmsg-content" readonly="true"></textarea> 
	  				</td>
	  			</tr>
	  			<tr>
  					<td align="right" valign="middle">
		  				<input type="button" value="关闭" id="button-appmsg-close" onclick="closeDialog()">
	  				</td>
	  			</tr>
  			</table>
  		</form>
   	 </div>
   	
   	<div id="app-footer" align="center">
    	<font style="FONT-SIZE: 9pt" face="Tahoma" color="#333333">
		            华东交通大学 2015-2017年版权所有&copy;<br />
		  	如果你有任何意见或建议请联系我们的
		  	<a href="mailto:37800827@qq.com"><font color="#005826">软件维护人员</font></a>
		</font>
    </div>
   	
  </body>
</html>
