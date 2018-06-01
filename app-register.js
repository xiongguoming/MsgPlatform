
$(document).ready(function(){
	
});

function RegisterApp()
{
	var appId = $(id_register_appid).val();
	var appName = $(id_register_appname).val();
	var pwd = $(id_register_pwd).val();
	var reppwd = $(id_register_reppwd).val();
	var phone = $(id_register_phone).val();
	var icon = $(id_register_icon).val();//图标
	var remark = $(id_register_remark).val();
	var appType = $('input:radio[name="apptype"]:checked').val();
	
	if(appId==""||appName=="")
	{
		win.alertEx("错误：应用账号和名称不能为空!");
		return;
    }
	if(appType==null)
	{
		win.alertEx("错误：请选择应用类型!");
		return;
    }
	if(pwd==""||pwd!=reppwd)
	{
		win.alertEx("错误：密码为空，或两次密码不一致!");
		return;
	}
	
	$.ajax({
         type:"GET",
         url:"/MsgService/AppServiceEx",
         data:{type:"registerapp",appId:appId,appName:appName,password:pwd,appType:appType,phone:phone,icon:icon,remark:remark},
         datatype: "html",
         complete: function(XMLHttpRequest, textStatus){
        	 win.alertEx("注册完成，请等待审核!");  
         },
         error: function(){
        	 win.alertEx("注册失败，与服务器通信异常!");
         }         
     });
}