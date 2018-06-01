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
    <title>接收消息</title>
    
	<link href="./jquery/jquery-ui-custom/jquery-ui.css" rel="stylesheet" type="text/css">
	<link href="./css/msg-receiver-history.css" rel="stylesheet" type="text/css">
	
	<script type="text/javascript" src="./jquery/jquery-ui-custom/external/jquery/jquery.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/jquery-ui.js"></script>
	<script type="text/javascript" src="./js/public.js"></script>
	<script type="text/javascript" src="./js/msg-receiver-history.js"></script>
  </head>
  
  <body> 
    <div id="receive-filter-histoy">
       <div id="receive-filter-content-histoy">
			<label>消息分类</label>
			<select id="select-msg-type-histoy">
				<option>全部消息</option>
				<option>系统消息</option>
				<option>应用消息</option>
				<option>用户消息</option>
			</select>
			
			<span class="vertical-split"></span>
			
			<label for="title-keyword-histoy">标题</label>
			<input type="text" id="title-keyword-histoy">
			<label for="sender-name-histoy">发送方</label>
			<input type="text" id="sender-name-histoy">
			
			<span class="vertical-split"></span>
			
			<label for="receiver-time-histoy">到达时间</label>
			
			<select id="receiver-time-histoy">
				<option>所有时间</option>
				<option>今天</option>
				<option>三天以内</option>
				<option>一周以内</option>
			</select>
	
			<span class="vertical-split"></span>
			
			<button id="btn-query-receivermsg-histoy">查找</button>
			<input type="hidden" id="receiver-msg-userid-histoy" value=<jsp:getProperty name="user" property="userID"/>>
			<button id="btn-query-deletemsg-histoy">批量删除</button>
		</div>
	</div>
	
    <div id="msg-zone-histoy" style="margin-top:35px;">
    </div>
    <!-- 用户消息、应用消息对话框 -->
    <div id="div-historymsg-dialog" style="display:none">
  		<form>
  			<table id="table-historymsg-grid">
  				<tr>
  					<td>
		  				<label><font color="blue">标题</font></label><br>
		  				<input type="text" class="text-historymsg-title" readonly="true">
		  				<br><br>
	  				</td>
	  			</tr>
	  			<tr>
  					<td>
		  				<label><font color="blue">正文</font></label><br>
		  				<textarea class="texta-historymsg-content" readonly="true"></textarea> 
	  				</td>
	  			</tr>
	  			<tr>
  					<td align="right" valign="middle">
		  				<input type="button" value="关闭" id="button-historymsg-close" onclick="closeDialog()">
	  				</td>
	  			</tr>
  			</table>
  		</form>
   	 </div>
  </body>
</html>

