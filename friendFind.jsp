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
    <title>所有用户</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">
	
	<link rel="stylesheet" type="text/css" href="./css/dtree.css"/>
	<link rel="stylesheet" type="text/css" href="./css/friend-find.css"/>
	<link rel="stylesheet" type="text/css" href="./css/table-style.css"/>
	
	<script src="./js/dtree.js" type="text/javascript"></script>
	<script src="./js/json2.js" type="text/javascript"></script>
	<script src="./js/public.js" type="text/javascript"></script>
	<!--script src="./js/msg_receiver.js" type="text/javascript"></script-->
	<script src="./js/friend-find.js" type="text/javascript" ></script>
  </head>
  
  <body>
  		<input type="hidden" id="ffUserID" value=<jsp:getProperty name="user" property="userID"/>>
  		<!-- 左边显示单位树状图 (动态生成)-->
    	<div id="div-unit-tree">
    		<div id="root-unit-tree" class="dtree"></div>
		</div>
		<!-- 右边显示用户列表 -->		
        <div id="div-user-list">
			<table class="TableStyle_1"  id="table-userList">
		   	 	<thead>
			    	<tr>
						<td width="60" align="center">序号</td>
						<td width="100" align="center">用户名</td>
						<td width="60" align="center">性别</td>
						<td width="300" align="center">所属单位</td>
						<td width="60" align="center">状态</td>
						<td width="100" align="center">操作</td>
					</tr>
				</thead>
				<tbody>
					<tr id="UserRow_1">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_2">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_3">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_4">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_5">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_6">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_7">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_8">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_9">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_10">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_11">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
					<tr id="UserRow_12">
						<td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td>
					</tr>
				</tbody>
				
				<tfoot>
					<tr id="idNavigation">
						<td colspan="6" >
							<span>当前：1/1页</span>
							<input type="text" id="ff-footspaces" disabled="disabled">
							<a href='Javascript:void(0)'>上一页|</a>
							<a href='Javascript:void(0)'>下一页|</a>
							<a href='Javascript:void(0)'>最后一页</a>	
						</td>
					</tr>
				</tfoot>
			</table>
		</div>
		
		<!--查看好友信息 -->
		<div id=div-addfriend-dialog style="display:none;">
		  	<input type="hidden" class="newfriendID"/>
		  	<div class='div-addfriend-userinfo'>
		  		<img class='img-addfreind-sex' src="./res/user-female.png"/>
		  		<p class='p-addfriend-name' align='center'>系统管理员</p>
		  		<p class='p-addfriend-unit' align='center'>现代教育中心</p>
		  	</div>
		  	
		  	<div class='div-addfriend-content'>
			  	<form>
					<table class="table-addfriend-grid">
				      <tr>	
				        <td>
					       <label class='label-addfreind-title'>请输入请求信息</label>
					    </td>
				      </tr>
				      <tr>	
				        <td>
				           <textarea rows="6" cols="24" class='text-addfriend-info'></textarea>
					    </td>
				      </tr>
				 	</table>
				 </form>
				 <div class='div-addfriend-operater'>
			 		<input type='button' class='button-addfriend-request' value='发送请求' onclick="SendRFInfo()"/>&nbsp;
			    	<input type='button' class='button-addfriend-ignore' value='关闭' onclick="closeDialog()"/>
			 	</div>
			 </div>
		 </div>
  </body>
  
</html>
