<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<jsp:useBean scope="session" id="user" class="com.pojo.UserInfo"/>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>好友设置</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">
	<!-- CSS -->
	<link rel="stylesheet" type="text/css" href="./css/table-style.css"/>
	<link rel="stylesheet" type="text/css" href="./css/friend-manage.css"/>
	<link rel="stylesheet" type="text/css" href="./jquery/jquery-ui-custom/jquery-ui.css" >
	<!-- Java script -->
	<script type="text/javascript" src="./js/json2.js"></script>
	<script type="text/javascript" src="./js/jquery-3.2.1.js"></script>
	<script type="text/javascript" src="./js/public.js"></script> 
	<script type="text/javascript" src="./jquery/jquery-ui-custom/external/jquery/jquery.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/jquery-ui.js"></script>
	<script type="text/javascript" src="./js/friend-manage.js" charset="UTF-8"></script>
	
  </head>
  
  <body>
  	  <input type="hidden" id="friend-manage-userid" value=<jsp:getProperty name="user" property="userID"/>>
  	  <div id="friend-accordion">
		<h3>我的好友</h3>
	  	<div id="div-myfriend"> 	 
	   	 <table class="TableStyle_1"  width=1100>
	   	 	<thead>
		    	<tr>
					<td width="100" align="center">序号</td>
					<td width="150" align="center">用户名</td>
					<td width="100" align="center">性别</td>
					<td width="350" align="center">所属单位</td>
					<td width="100" align="center">状态</td>
					<td width="200" align="center">操作</td>
				</tr>
			</thead>
			<tbody>
				<tr id="FriendRow_1">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_2">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_3">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_4">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_5">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_6">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_7">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_8">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_9">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
				<tr id="FriendRow_10">
					<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
				</tr>
			</tbody>
			<tfoot>
				<tr id="TableOperation">
					<td colspan="6" >
						<span>当前：1/1页</span>
						<input type="text" id="fm-footspaces" disabled="disabled">
						<a href='Javascript:void(0)'>首页|</a>
						<a href='Javascript:void(0)'>上一页|</a>
						<a href='Javascript:void(0)'>下一页|</a>
						<a href='Javascript:void(0)'>最后一页</a>	
					</td>
				</tr>
			</tfoot>
		  </table>
		</div>
		<h3>单位好友</h3>
		<div id="div-unitfriend">暂无好友</div>
	  </div>
	  <!-- 接收消息对话框设计。不要使用ID，否则与对话框ID冲突导致赋值失败-->
	  <div id="div-sendmsg-dialog" style="display:none">
		<form>
			<table class="table-sendmsg-grid">
				<tr>
					<td>
						<label><font color="blue">标题</font></label><br>
						<input type="text" class="text-sendmsg-title">
						<br><br>
					</td>
				</tr>
				<tr>
					<td>
						<label><font color="blue">正文</font></label><br>
						<textarea class="texta-sendmsg-content"></textarea> 
					</td>
				</tr>
				<tr>
					<td align="right" valign="middle">
						<br/>
						<!--
						<input class="input-sendtype1" name="user-send-type" type="checkbox" value="1" />网页
						<input class="input-sendtype2" name="user-send-type" type="checkbox" value="2" />短信
						<input class="input-sendtype3" name="user-send-type" type="checkbox" value="3" />邮件
						<input class="input-sendtype4" name="user-send-type" type="checkbox" value="4" />微信
						-->
						<input type="button" value="发送" id="button-sendmsg-send" onclick="SendUserMessage()">
						<input type="button" value="关闭" id="button-sendmsg-close" onclick="closeDialog()">
					</td>
				</tr>
			</table>
		</form>
	  </div>
	  <script>
	  	$("#friend-accordion").accordion();
	  </script>
	</body>
</html>
