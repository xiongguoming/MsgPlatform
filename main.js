
$(document).ready(function(){
	
	g_curUserId = $("#main-userid").val();
	
	ReadFocusApps(g_curUserId);
	ReadTotalApps();
});

function ReadFocusApps(userId)
{
	$.ajax({
        type:"GET",
        url:"/MsgService/AppServiceEx",
        data:{type:"totalfocus",userid:userId},
        datatype: "json",
        success:function(data){
        },
        complete: function(XMLHttpRequest, textStatus){
        	if(XMLHttpRequest.readyState == 4)
        	{	
        		totalFocusApps = XMLHttpRequest.responseText;
        	}            
        },
        error: function(){
        }         
    });
}

function ReadTotalApps()
{
	$.ajax({
        type:"GET",
        url:"/MsgService/AppServiceEx",
        data:{type:"totalapp"},
        datatype: "json",
        success:function(data){
        },
        complete: function(XMLHttpRequest, textStatus){
        	if(XMLHttpRequest.readyState == 4)
        	{	
        		var strJson = XMLHttpRequest.responseText;
        		totalAppArray = JSON.parse(strJson);
        	}            
        },
        error: function(){
        }         
    });
}