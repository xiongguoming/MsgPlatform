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
    <title>用户个人设置</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">
	
	<link rel="stylesheet" type="text/css" href="./css/table-style.css"/>

	<script type="text/javascript" src="./js/json2.js"></script>
	<script type="text/javascript" src="./js/public.js"></script>
	<script type="text/javascript" src="./js/my-setting.js"></script>
  </head>
  
  <body>
<%
 	String UserID = (String)session.getAttribute("loginCode");	
%>
   <div id="userinfo_setting" align="center" style="margin-top:30px;" >
	  
	  <!-- 个人信息设置 -->
	  <form id="MySettingEx">
	       <table class="TableStyle_1" width=1100>
				<thead>
			    	<tr>
						<td colspan="4">个人信息设置</td>
					</tr>
				</thead>
				<tbody>
					<tr>
						<td width="275">用户账号</td>
						<td width="275" style="text-align:right;"><jsp:getProperty name="user" property="userID"/></td>
						<td width="275">用户姓名</td>
						<td width="275" style="text-align:right;" id="UserName_td"><input type="text" class="TableInputText" id ="UserNameEx"></td>
					</tr>
					<tr>
						<td>登录密码</td>
						<td id="Password_td" style="text-align:right;"><input type="text" class="TableInputText" id="PasswordEx"></td>
						<td>电话号码</td>
						<td id="Telephone_td" style="text-align:right;"><input type="text" class="TableInputText" id="TelephoneEx"></td>
					</tr>
					<tr>
						<td>电子邮箱</td>
						<td id="Email_td" style="text-align:right;"><input type="text" class="TableInputText" id="EmailEx"></td>
						<td>微信账号</td>
						<td id="Weixin_td" style="text-align:right;"><input type="text" class="TableInputText" id="WeixinEx"></td>
					</tr>
				</tbody>
				
				<tfoot>
					<tr>
						<td colspan="4">
							<input type="button" value="修改" id="btnModify" class="settingbutton" onclick="ModifyUserInfo()">
							 &nbsp; &nbsp;&nbsp; 
							<input type="button" value="提交" id="btnSubmit" class="settingbutton" onclick="SaveUserInfo()">
						</td>
					</tr>
				</tfoot>
			</table>
	    </form>
	  </div>
	  
      <!-- 消息订阅设置 -->
      <div id="subscription_setting" align="center" style="margin-top:30px;">
	   <form action="MySetting">
	   		
		    <table class="TableStyle_1" width=1100>
		    	<thead>
			    	<tr>
						<td colspan="5">消息订阅设置</td>
					</tr>
				</thead>
				
				<tbody>
				<tr>
					<td>允许接收消息<br></td>
					<td align="center" colspan="4">
						<input type="radio" checked="checked" value="open" name="ReceiveAllMsg">打开
						<input type="radio" value="close" name="ReceiveAllMsg">关闭
					</td>
				</tr>
				<tr>
					<td>夜间免打扰<br>(22:00:00-8:00:00不接收消息)</td>
					<td align="center" colspan="4">
						<input type="radio" checked="checked" value="open" name="ReceiveTime">打开
						<input type="radio" value="close" name="ReceiveTime">关闭
					</td>
				</tr>
				
				<tr>
					<td>设置接收消息类型</td>
					<td width="150" align="center">客户端</td>
					<td width="150" align="center">短信</td>
					<td width="150" align="center">邮件</td>
					<td width="150" align="center">微信</td>
				</tr>
				<tr>
					<td>系统消息</td>
					<td align="center">
						<input type="checkbox" name="chSysMsg_web">
					</td>
					<td align="center">
						<input type="checkbox" name="chSysMsg_sms">
					</td>
					<td align="center">
						<input type="checkbox" name="chSysMsg_email">
					</td>
					<td align="center">
						<input type="checkbox" name="chSysMsg_weixin">
					</td>
				</tr>
				
				<tr>
					<td>应用消息</td>
					<td align="center">
						<input type="checkbox" name="chAppMsg_web">
					</td>
					<td align="center">
						<input type="checkbox" name="chAppMsg_sms">
					</td>
					<td align="center">
						<input type="checkbox" name="chAppMsg_email">
					</td>
					<td align="center">
						<input type="checkbox" name="chAppMsg_weixin">
					</td>
				</tr>
				
				<tr>
					<td>用户消息</td>
					<td align="center">
						<input type="checkbox" name="chUserMsg_web">
					</td>
					<td align="center">
						<input type="checkbox" name="chUserMsg_sms">
					</td>
					<td align="center">
						<input type="checkbox" name="chUserMsg_email">
					</td>
					<td align="center">
						<input type="checkbox" name="chUserMsg_weixin">
					</td>
				</tr>
				</tbody>
				
				<tfoot>
					<tr>
						<td colspan="5">
							<input type="button" value="提交"  onclick="SaveMsgPolicy()">
							 &nbsp; &nbsp;&nbsp;&nbsp;&nbsp; 
							<input type="reset" value="重置">	
						</td>
					</tr>
				</tfoot>
			</table>
			
			<input type="hidden" id="idUserID" name="UserID" value=<jsp:getProperty name="user" property="userID"/>>
		</form>
	</div>
  </body>
</html>
