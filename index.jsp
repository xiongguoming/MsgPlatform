<%@ page contentType="text/html; charset=UTF-8" language="java"%>
<%@ page language="java" import="java.util.*" pageEncoding="GBK"%>  
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />

<link href="./jquery/jquery-ui-custom/jquery-ui.css" rel="stylesheet" type="text/css">
<link href="./css/public.css" rel="stylesheet" type="text/css">
<link href="./css/user-login.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" src="./js/jquery-3.2.1.js"></script>
<script type="text/javascript" src="./jquery/jquery-ui-custom/external/jquery/jquery.js"></script>
<script type="text/javascript" src="./jquery/jquery-ui-custom/jquery-ui.js"></script>
<script type="text/javascript" src="./js/public.js"></script>
<script type="text/javascript" src="./js/user-login.js"></script>

<title>��½��Ϣ</title>
</head>

<body>
<%
 	String loginCode = (String)session.getAttribute("loginCode");
 	String serverAddr = request.getLocalAddr();
%>
  <form id="login-form">
    <table>
      <tr>
        <td>
	        <select name="select" id="login-select-type">
	          <option value="user" selected="selected">�����û�</option>
	          <option value="app">Ӧ��ϵͳ</option>
	        </select>
	    </td>
      </tr>
      <tr>
        <td><input type="text" id="login-input-account"/></td>
      </tr>
      <tr>
        <td><input type="password" id="login-input-password"/></td>
      </tr>
      <tr>
      	<td><input type="button" id="login-btn-submit" value="��½" onclick="UserLogin()"/></td>
      </tr>
    </table>
    <!-- ͨ������������JS��ֵ -->
    <input type="hidden" id="idLoginCode" value=<%=loginCode%>>
    <input type="hidden" id="idServerAddr" value=<%=serverAddr%>>
    
    <div id="login-app-register"><a href=appRegister.jsp target=_blank><font color=blue>Ӧ��ϵͳע��</font></a></div>
  </form>
  
</body>
</html>
