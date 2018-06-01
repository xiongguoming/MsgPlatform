/* Create a new XMLHttpRequest object to talk to the Web server */

//=========================================
//公共变量
//=========================================
//当前用户Id
var g_curUserId = "";
//所有的App列表
var totalAppArray = null;
//所有用户
var totalUserArray = null;
//所有单位
var totalUnitArray = null;
//所有关注App格式xxx,xxx,xxx,
var totalFocusApps = "";
//历史消息
var g_HistoryMsgArray;


/*
var g_FriendsArray;		//所有好友信息
var g_RecMsgArray;		//所有接收的消息
*/
//=========================================
//创建通用表格
//=========================================
function CreateBlankTable(divName,tableName,fields,size,rowcount)
{ 
	var thead = "<thead>";
	var tr = "<tr>";
	for(var nIndex=0; nIndex<fields.length; nIndex++)
	{
		tr += "<td width='100'>"+fields[nIndex]+"</td>";
	}
	tr += "</tr>";
	thead += tr;
	thead += "</thead>";
	var tbody = "<tbody>";
	
	for(var count=0; count<rowcount; count++)
	{
		var rowid = tableName+"_"+count;
		tr = "<tr id="+rowid+">";
		for(var nIndex=0; nIndex<fields.length; nIndex++)
		{
			tr += "<td>"+"&nbsp;"+"</td>";
		}
		tr += "</tr>";
		tbody += tr;
	}
	tbody += "</tbody>";
	
	var tfoot = "<tfoot>";
	tr = "<tr>";
	tr += "<td colspan="+fields.length+">";
	tr += "</td>"; 
	tr += "</tr>";
	tfoot += tr;
	tfoot += "</tfoot>";
	
	var table = "<table class='TableStyle_1' id=" + tableName +">";
	table += thead;
	table += tbody;
	table += tfoot;
	table += "</table>";
	$('#'+divName).html(table);
	//resize
	$('#'+tableName+' tr td:'+'nth-child(1)').attr("width",size[0]);
	$('#'+tableName+' tr td:'+'nth-child(2)').attr("width",size[1]);
	$('#'+tableName+' tr td:'+'nth-child(3)').attr("width",size[2]);
	$('#'+tableName+' tr td:'+'nth-child(4)').attr("width",size[3]);
	$('#'+tableName+' tr td:'+'nth-child(5)').attr("width",size[4]);
	$('#'+tableName+' tr td:'+'nth-child(6)').attr("width",size[5]);
}

//=========================================
//Cookie相关操作
//=========================================

function setCookie(name,value)
{
	var Days = 1;
	var exp = new Date();
	exp.setTime(exp.getTime() + Days*24*60*60*1000);
	document.cookie = name + "="+ escape (value) + ";expires=" + 5000;
}

function getCookie(name)
{
	var arr,reg=new RegExp("(^| )"+name+"=([^;]*)(;|$)");
	if(arr=document.cookie.match(reg))
		return unescape(arr[2]);
	else
		return null;
}

function deleteCookie(name)
{
	var exp = new Date();
	exp.setTime(exp.getTime()-1);
	var cval = getCookie(name);
	if(cval!=null)
		document.cookie = name + "="+cval+";expires="+exp.toGMTString();
}

//=========================================
//以下定义对话框相关元素
//=========================================

//根据ID获取节点元素,第一个参数是节点ID
var getDocElement = function()
{
	var ele = document.getElementById(arguments[0]);
	
	if(ele != null)
		return ele;
	else
		return false;
};

var divDialogCenter = null;
//打开模态对话框
function openDialog(title,divid,width,height)
{
	var dlgid = "ID_DIALOG";
    var maskid = "ID_DLG_MASK";
    
    if (getDocElement(dlgid)) 
    	document.body.removeChild(getDocElement(dlgid));
    
    if (getDocElement(maskid)) 
    	document.body.removeChild(getDocElement(maskid));
     
    //mask遮罩层
    var divMask = document.createElement("div");
    divMask.id = maskid;
    divMask.style.position = "absolute";
    divMask.style.zIndex = "1";
	var _scrollWidth = Math.max(document.body.scrollWidth,document.documentElement.scrollWidth);
	var _scrollHeight = Math.max(document.body.scrollHeight,document.documentElement.scrollHeight);
	divMask.style.width = _scrollWidth + "px";
	divMask.style.height = _scrollHeight + "px";
	divMask.style.top = "0px";
	divMask.style.left = "0px";
	divMask.style.background = "#33393C";
	divMask.style.filter = "alpha(opacity=40)";
	divMask.style.opacity = "0.40";
	document.body.appendChild(divMask);
     
    //新弹出层
    var divDialog = document.createElement("div");
    divDialog.id = dlgid;
    divDialog.style.position = "absolute";
    divDialog.style.zIndex = "9999";
    divDialog.style.width = width + "px";
    divDialog.style.height = height + "px";
    divDialog.style.top = (document.body.scrollTop + document.body.clientHeight/2 - height/2) + "px";
    divDialog.style.left = (document.body.scrollLeft + document.body.clientWidth/2 - width/2) + "px";
    divDialog.style.background = "#EFEFEF";
    divDialog.style.border = "1px solid #860001";
    divDialog.style.padding = "5px";
    
    //创建标题栏
    var divHead = document.createElement("div");
    if (title != undefined) 
    {
        divHead.innerHTML = title;
        //divHead.appendChild(document.createTextNode(title));
    } 
    else 
    {
        divHead.appendChild(document.createTextNode("消息"));
    }
    
    divHead.style.width = "100%";
    divHead.style.height = "25px";
    divHead.style.lineHeight = "25px";
    divHead.style.fontSize = "14px";        
    divHead.style.fontWeight = "bold";
    divHead.style.borderBottom = "1px outset #8989FF";
    divHead.style.color = "white";
    divHead.style.textIndent = "10px";
    divHead.style.backgroundColor = "blue";
    divHead.style.backgroundImage = "url(../MsgService/res/headbg.png)";
    divHead.style.cursor = "move";
    
    divHead.onmousedown = function() {
        divDialog.dragging = true; 
    };
    
    divHead.onmouseup = function() {
        divDialog.dragging = false;
    };
    
    //添加对话框标题
    divDialog.appendChild(divHead);
    
    //创建对话框内容
    var divContent = document.createElement("div");
    
    divContent.setAttribute("id","dialog_content");
    //外部定义的div层，传递进来作为对话框内容(包括外部值也传进来了)
    divContent.innerHTML = document.getElementById(divid).innerHTML;
    
    divContent.style.textAlign = "center";
    divContent.style.padding = "15px";
    divContent.style.fontSize = "12px";
    divDialog.appendChild(divContent);
    
    //将对话框添加进document
    document.body.appendChild(divDialog);
    
    //弹出层滚动居中
    divDialogCenter = function()
    {
         divDialog.style.top = (document.body.scrollTop + document.body.clientHeight/2 - height/2) + "px";
         divDialog.style.left = (document.body.scrollLeft + document.body.clientWidth/2 - width/2) + "px";
    };
    
    if(document.all)
    {
         window.attachEvent("onscroll",divDialogCenter);
    }
    else
    {
         window.addEventListener('scroll',divDialogCenter,false);
    }
    
    document.body.onmousemove = function(e) {
        if (!divDialog.dragging) 
        	return;
        e = e || window.event;
        var mouseX, mouseY;
        var mouseOffsetX, mouseOffsetY;
        if (e.pageX || e.pageY) {
            mouseX = e.pageX;
            mouseY = e.pageY;

        } else {
            mouseX =
                e.clientX + document.body.scrollLeft -
                document.body.clientLeft;
            mouseY =
                e.clientY + document.body.scrollTop -
                document.body.clientTop;

        }
        
        divDialog.style.left = (mouseX - width * 0.4) + "px";
        divDialog.style.top = (mouseY - 10) + "px";            
    };
} 

//关闭模态对话框
function closeDialog(divid)
{
	//关闭对话框时，应该把值传递回去？
	if(typeof divid != "undefined")
	{
		var dlgcontent = $("#dialog_content");
		var divcontent = $("#"+divid);
		//根据对话框不同，可以增加过滤条件
		var dlgelems = dlgcontent.find("input[class],textarea[class]");
		var divelems = divcontent.find("input[class],textarea[class]");
		
		for(var i=0;i<dlgelems.length;i++)
		{
			for(var j=0;j<divelems.length;j++)
			{
				if(dlgelems[i].className == divelems[j].className)
				{
					//文本框、多行文本
					divelems[j].value = dlgelems[i].value;
					//复选框
					divelems[j].checked = dlgelems[i].checked;
					break;
				}
			}
		}
	}
    if(document.all)
    {
    	window.detachEvent("onscroll",divDialogCenter);
    }
    else
    {
        window.removeEventListener('scroll',divDialogCenter,false);
    }
	document.body.removeChild(getDocElement("ID_DIALOG"));
	document.body.removeChild(getDocElement("ID_DLG_MASK"));
	
	return false;
} 

//定义win对象，模拟window对象的alert,confirm对话框
var win = new function () {
    // 确认框和提示框宽度
    this.width = 300;

    // 确认框和提示框高度
    this.height = 172;

    // 手动关闭窗体
    this.close = function () {
        $('.win iframe').remove();
        $('.win').remove();
    };

    // 打开窗体
    this.open = function (width, height, title, url, closed) {
        this._close = function () {
            this.close();
            if ($.isFunction(closed)) closed();
        };

        var html = '<div class="win"><div class="mask-layer"></div><div class="window-panel"><iframe class="title-panel" frameborder="0" marginheight="0" marginwidth="0" scrolling="no"></iframe><div class="title"><h3></h3></div><a href="javascript:void(0)" onclick="win._close();" class="close-btn" title="关闭">×</a><iframe class="body-panel" frameborder="0" marginheight="0" marginwidth="0" scrolling="auto" src=""></iframe></div></div>';
        var jq = $(html);
        jq.find(".window-panel").height(height).width(width).css("margin-left", -width / 2).css("margin-top", -height / 2);
        jq.find(".title").find(":header").html(title);
        jq.find(".body-panel").height(height - 36).attr("src", url);
        jq.appendTo('body').fadeIn();
        $(".win .window-panel").focus();
    };

    // 显示消息框
    function messageBox(html, title, message) {
        win.close();
        var jq = $(html);

        jq.find(".window-panel").height(win.height).width(win.width).css("margin-left", -win.width / 2).css("margin-top", -win.height / 2);
        jq.find(".title-panel").height(win.height);
        jq.find(".title").find(":header").html(title);
        jq.find(".body-panel").height(win.height - 36);
        if(message!=null)
        {
        	jq.find(".content").html(message.replace('\r\n', '<br/>'));
        }
        jq.appendTo('body').show();
        $(".win .w-btn:first").focus();
    }

    // 确认框
    this.confirm = function (title, message, selected) {
        this._close = function (r) {
            this.close();
            if ($.isFunction(selected)) selected(r);
        };

        var html = '<div class="win"><div class="mask-layer"></div><div class="window-panel"><iframe class="title-panel" frameborder="0" marginheight="0" marginwidth="0" scrolling="no"></iframe><div class="title"><h3></h3></div><a href="javascript:void(0)" onclick="win._close(false);" class="close-btn" title="关闭">×</a><div class="body-panel"><p class="content"></p><p class="btns"><button class="w-btn" tabindex="1" onclick="win._close(true);">确定</button><button class="w-btn" onclick="win._close(false);">取消</button></p></div></div></div>';
        messageBox(html, title, message);
    };

    // 提示框
    this.alert = function (title, message, closed) {
        this._close = function () {
            this.close();
            if ($.isFunction(closed)) closed();
        };

        var html = '<div class="win"><div class="mask-layer"></div><div class="window-panel"><iframe class="title-panel" frameborder="0" marginheight="0" marginwidth="0" scrolling="no"></iframe><div class="title"><h3></h3></div><a href="javascript:void(0)" onclick="win._close();" class="close-btn" title="关闭">×</a><div class="body-panel"><p class="content"></p><p class="btns"><button class="w-btn" tabindex="1" onclick="win._close();">确定</button></p></div></div></div>';
        messageBox(html, title, message);
    };

    // 提示框
    this.alertEx = function (message) {
        this.alert('系统提示', message);
    };   
};

//=========================================
//自定义的ajax对象,页面中主要还是使用jquery的ajax方法
//=========================================
var ajaxRequest = {
	//post请求
	post: function(params)
	{
        var xmlhttp = this.createXMLHttpRequest();  
        if (xmlhttp != null)  
        {
        	var async = true;  
            if (typeof params.async != "undefined")
        	{
            	async = params.async;
        	}
            var data = null;  
            if (typeof params.data != "undefined")
            {
            	data = params.data;
            }
            var url = "";  
            if (typeof params.url != "undefined")
            {
            	url = params.url;
            }
            if (url == null || url.length == 0)
            {
            	return;	
            }
            xmlhttp.open("POST", url, async);
            
            if (async)
            {
            	xmlhttp.onreadystatechange = function() 
            	{
            		if (this.readyState==4)
            		{
            			if (this.status==200)
            			{
            				if (typeof params.success != "undefined") 
            				{
            					params.success(xmlhttp.responseText);
            				}
            			}  
	            		else 
	            		{  
	            			if (typeof params.error != "undefined") 
	            			{  
	            				params.error(xmlhttp.status + xmlhttp.statusText);  
	            			}  
	            			console.error(url + ": " + xmlhttp.status);  
	            		}  
            		}
            	};
            }  
          
			xmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");  
			var param = "";  
			for (var prop in data) 
			{
				param += prop + "=" + data[prop] + "&";
			}  
			param = param.substring(0, param.length-1);
			
			xmlhttp.send(param);  
			
			if (!async) 
			{
				if (xmlhttp.readyState == 4 && xmlhttp.status == 200)
				{
					if (typeof params.success != "undefined") 
					{  
				        params.success(xmlhttp.responseText);  
				    }
				}
					  
				else 
				{  
				    if (typeof params.error != "undefined")
				    {  
				    	params.error(xmlhttp.status + xmlhttp.statusText);  
				    }  
				    console.error(url + ": " + xmlhttp.status);  
				}
			}
		}  
	}, 
	//get请求
    get: function(params)
    {  
        var xmlhttp = this.createXMLHttpRequest();
        
        if (xmlhttp != null)  
        {  
            var async = true;  
            if (params.async != undefined)
        	{
            	async = params.async;
        	}
            var url = "";  
            if (params.url != undefined)
            {
            	url = params.url;
            }
            if (url == null || url.length == 0)
            {
            	return;
            }
            if (params.data != null) 
            {  
                var data = params.data;  
                var paramPrefix = url.indexOf("?") == -1 ? "?" : "&";
                url = url + paramPrefix;
                for (var prop in data) 
                {
                	url += prop + "=" + data[prop] + "&";  
                }  
                url = url.substring(0, url.length - 1);  
            }
            
            xmlhttp.open("GET", url, async);
            
            if (async)
            {  
                xmlhttp.onreadystatechange = function()
                {  
                    if (this.readyState==4)
                    {  
                        if (this.status==200)
                        {  
                            if (typeof params.success != "undefined") 
                            {  
                                params.success(xmlhttp.responseText);  
                            }  
                        }  
                        else 
                        {  
                            if (typeof params.error != "undefined") 
                            {  
                                params.error(xmlhttp.status + xmlhttp.statusText);  
                            }  
                            console.error(url + ": " + xmlhttp.status);  
                        }  
                    }  
                };  
            }  
  
            xmlhttp.send(null);
            
            if (!async) 
            {  
                if (xmlhttp.readyState == 4 && xmlhttp.status == 200)
                {
                	if (typeof params.success != "undefined") 
                	{  
                        params.success(xmlhttp.responseText);  
                    }	
                } 
                else 
                {  
                    if (typeof params.error != "undefined") 
                    {  
                        params.error(xmlhttp.status + xmlhttp.statusText);  
                    }  
                    console.error(url + ": " + xmlhttp.status);  
                }   
            }  
        }  
    },
    
    createXMLHttpRequest: function()
    {  
        if (window.XMLHttpRequest)  
        {  
            return new XMLHttpRequest();  
        }  
        else if (window.ActiveXObject)  
        {  
        	//code for IE5 and IE6  
            return new ActiveXObject("Microsoft.XMLHTTP");  
        }  
        return null;  
    },
    
    getJSONP: function(params) 
    {  
        var url = null;  
        if (typeof params.url != "undefined") 
        {  
            url = params.url;  
        }  
        if (url == null) 
        {  
            return;  
        }  
        var ff = "" + new Date().getTime() + (parseInt(Math.random() * 10000000000));  
        eval("jsonpCallback_" + ff + "=" + function(data)
        { 
            if (typeof params.success != "undefined")
            {  
                params.success(data);  
            }  
        });  
        
        //根据url中是否出现过 "?" 来决定添加时间戳参数时使用 "?" 还是 "&"    
        var paramPrefix = url.indexOf("?") == -1 ? "?" : "&";
        url = url + paramPrefix + "jsonpCallback=" + "jsonpCallback_" + ff;  
        var param = "";  
        
        if (typeof params.data != "undefined" && params.data != null)
        {  
            var data = params.data;  
            for (var prop in data)
            {  
                param += prop + "=" + data[prop] + "&";  
            }  
            param = param.substring(0, param.length - 1);  
        }
        
        if (param.length > 0)
        {
        	url = url + "&" + param;
        }
        var script = document.createElement("script");    
        document.body.appendChild(script);    
        script.src = url;    
        script.charset ="UTF-8";  
        // for firefox, google etc.  
        script.onerror = function() 
        {  
            if (typeof params.error != "undefined") 
            {  
                params.error();  
            }    
        };  
        script.onload = function() 
        {  
        	document.body.removeChild(script);    
        };  
        // for ie    
        script.onreadystatechange = function()
        {
            if (this.readyState == "loaded" || this.readyState == "complete") 
            {   
               document.body.removeChild(script);  
            }    
        };  
    }
}; 
//简单的获取ajax对象的方法
function getXMLHttpRequest() 
{ 
	var xmlHttpReq; 
	try 
	{  
		xmlHttpReq = new XMLHttpRequest(); // Firefox, Opera 8.0+, Safari
	} 
	catch (e) 
	{ 
		try 
		{ 
			xmlHttpReq = new ActiveXObject("Msxml2.XMLHTTP"); // Internet Explorer
		} 
		catch (e) 
		{ 
			try 
			{ 
				xmlHttpReq = new ActiveXObject("Microsoft.XMLHTTP"); 
			} 
			catch (e) 
			{
				xmlHttpReq = null;
			} 
		} 
	} 
	return xmlHttpReq; 
};


