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
	<link href="./css/msg-receiver.css" rel="stylesheet" type="text/css">
	<link href="./css/public.css" rel="stylesheet" type="text/css">
	
	<script type="text/javascript" src="./js/jquery-3.2.1.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/external/jquery/jquery.js"></script>
	<script type="text/javascript" src="./jquery/jquery-ui-custom/jquery-ui.js"></script>
	<script type="text/javascript" src="./js/public.js"></script>
	<script type="text/javascript" src="./js/total-app-list.js"></script>
	<script type="text/javascript" src="./js/msg-receiver.js"></script>
  </head>
  
  <body>
  	<input type="hidden" id="receiver-msg-userid" value=<jsp:getProperty name="user" property="userID"/>> 
    <div id="receive-reclist">
    	<h3>用户消息</h3>
    	<div id="receive-reclist-user" >
    		<ul class="receive-reclist-type">
	  		</ul>
    	</div>
      	<h3>应用消息<br></h3>
        <div id="receive-reclist-app">
	 		<ul class="receive-reclist-type">
	  		</ul>
        </div>
        <h3>系统消息<br></h3>
        <div id="receive-reclist-sys">
	 		<ul class="receive-reclist-type">
		 		<li onclick="ChangeSysMsg('NOTICE')"><a href='Javascript:void(0)'>提醒</a></li>
		 		<li onclick="ChangeSysMsg('INFO')"><a href='Javascript:void(0)'>消息</a></li>
		 		<li onclick="ChangeSysMsg('WARN')"><a href='Javascript:void(0)'>告警</a></li>
	  		</ul>
        </div>
	</div>
	
    <div id="receive-msg-zone">
	 	<!-- form method="get" action="MsgDispatch" name="MsgDispatch">
    	</form-->
    </div>
    <!-- 接收消息对话框设计。不要使用ID，否则与对话框ID会冲突导致赋值失败-->
    <div id="div-recmsg-dialog" style="display:none">
  		<form>
  			<table id="table-recmsg-grid">
  				<tr>
  					<td>
		  				<label><font color="blue">标题</font></label><br>
		  				<input type="text" class="text-recmsg-title" readonly="true">
		  				<br><br>
	  				</td>
	  			</tr>
	  			<tr>
  					<td>
		  				<label><font color="blue">正文</font></label><br>
		  				<textarea class="texta-recmsg-content" readonly="true"></textarea> 
	  				</td>
	  			</tr>
	  			<tr>
  					<td align="right" valign="middle">
  						<br>
		  				<input type="button" value="回复" id="button-recmsg-answer">
		  				<input type="button" value="关闭" id="button-recmsg-close" onclick="closeDialog()">
	  				</td>
	  			</tr>
  			</table>
  		</form>
   	 </div>
   	 <!-- 添加好友请求对话框 -->
  	 <div id=div-rqfriend-dialog style="display:none;">
	  	<div id='div-rqfriend-userinfo'>
	  		<img class='img-rqfreind-sex' src="./res/user-female.png"/>
	  		<br/>
	  		<p class='p-rqfreind-name' align='center'>系统管理员</p>
	  		<p class='p-rqfreind-unit' align='center'>现代教育技术中心</p>
	  	</div>
	  	
	  	<div id='div-rqfriend-content'>
		  	<form>
				<table id='table-rqfriend-grid' cellspacing="15">
			      <tr>	
			        <td>
				       <label class='label-rqfreind-title'>请求添加您为好友？</label>
				    </td>
			      </tr>
			      <tr>	
			        <td>
			           <textarea rows="5" cols="24" class='texta-rqfriend-info'></textarea>
				    </td>
			       <tr>
			        <td>
				       <input type='radio' name='radio-rqfriend-repaly' value='agree' checked>同意
				       <input type='radio' name='radio-rqfriend-repaly' value='disagree'>拒绝
				    </td>
			      </tr>
			 	</table>
			 </form>
		 </div>
		 
		 <div id='div-qrfriend-operater' align="right">
		 	<input type='button' class='button-reply-friend' value='确定' onclick="replyFriend()"/>&nbsp;
		    <input type='button' class='button-ignore-friend' value='忽略' onclick="closeDialog()"/>
		    <input type="hidden" class="hidden-recmsg-senderid">
		  	<input type="hidden" class="hidden-recmsg-msgid"> 
		 </div>
	 </div>
	 
    <script>
        //$( "#controlgroup" ).controlgroup();
        $("#receive-reclist").accordion();
    </script>
  </body>
</html>

