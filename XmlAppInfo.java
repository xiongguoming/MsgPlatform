package com.system;

import java.io.ByteArrayOutputStream;
import java.io.StringReader;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import com.pojo.AppInfo;

public class XmlAppInfo {
	
	public String parseRegInfoXml(AppInfo appInfo)
	{
		
		String xmlStr = null;
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        try 
        {
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.newDocument();
            document.setXmlVersion("1.0");
            
            //根节点
            Element rootElement = document.createElement("root");
            document.appendChild(rootElement);
            
            Element AppInfo = document.createElement("AppInfo");
            //账号
            Element appId = document.createElement("AppId");  
            appId.setTextContent(appInfo.getAppId());
            AppInfo.appendChild(appId);
            //应用名称
            Element appName = document.createElement("AppName");  
            appName.setTextContent(appInfo.getAppName());
            AppInfo.appendChild(appName);
            //密码
            Element password = document.createElement("Password");  
            password.setTextContent(appInfo.getPassword());
            AppInfo.appendChild(password);
            //应用类型
            Element appType = document.createElement("AppType");  
            appType.setTextContent(String.valueOf(appInfo.getAppType()));
            AppInfo.appendChild(appType);
            //联系电话
            Element phone = document.createElement("Phone");  
            phone.setTextContent(appInfo.getPhone());
            AppInfo.appendChild(phone);
            //图标
            Element icon = document.createElement("Icon");  
            icon.setTextContent(appInfo.getIcon());
            AppInfo.appendChild(icon);
            //备注
            Element remark = document.createElement("Remark");  
            remark.setTextContent(appInfo.getRemark());
            AppInfo.appendChild(remark);
            
            Element status = document.createElement("Status");  
            status.setTextContent(String.valueOf(appInfo.getStatus()));
            AppInfo.appendChild(status);

            rootElement.appendChild(AppInfo);
            
            TransformerFactory transFactory = TransformerFactory.newInstance();
            Transformer transFormer = transFactory.newTransformer();
            DOMSource domSource = new DOMSource(document);
            
            //export string
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            transFormer.transform(domSource, new StreamResult(bos));
            xmlStr = new String(bos.toString().getBytes(),"UTF-8");
        } 
        catch(Exception e)
		{
			 e.printStackTrace(); 
		}
        
        return xmlStr;
	}
	
	public AppInfo parseRegInfoApp(String xmlRegInfo)
	{
 		AppInfo appInfo = new AppInfo();
		String nodeValue = "";
		
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        try 
        {
            DocumentBuilder builder = factory.newDocumentBuilder();
            InputSource is = new InputSource(new StringReader(xmlRegInfo));
            Document doc = builder.parse(is);
            
            Element AppRoot = doc.getDocumentElement();
            
            NodeList regApp = AppRoot.getElementsByTagName("AppInfo");
            Element appNode  = (Element)regApp.item(0);
            NodeList properties = appNode.getChildNodes();
            
            for (int j = 0; j < properties.getLength(); j++) 
            {
                Node property = properties.item(j);
                String nodeName = property.getNodeName();
                
                if (nodeName.equals("AppId")) 
                {
                	if(property.getFirstChild()!=null)
                	{
                		nodeValue = property.getFirstChild().getNodeValue();
                		appInfo.setAppId(nodeValue);
                	}
                } 
                else if (nodeName.equals("AppName")) 
                {
                	if(property.getFirstChild()!=null)
                	{
                		nodeValue = property.getFirstChild().getNodeValue();
                    	appInfo.setAppName(nodeValue);
                	}
                	
                }
                else if (nodeName.equals("Password")) 
                {
                	if(property.getFirstChild()!=null)
                	{
                		nodeValue = property.getFirstChild().getNodeValue();
                    	appInfo.setPassword(nodeValue);
                	}
                }
                
                else if (nodeName.equals("AppType")) 
                {
                	if(property.getFirstChild()!=null)
                	{
                		nodeValue = property.getFirstChild().getNodeValue();
                    	appInfo.setAppType(Integer.parseInt(nodeValue));
                	}
                }
                
                else if (nodeName.equals("Phone")) 
                {
                	if(property.getFirstChild()!=null)
                	{
                		nodeValue = property.getFirstChild().getNodeValue();
                		appInfo.setPhone(nodeValue);
                	}
                }
                else if (nodeName.equals("Icon")) 
                {
                	if(property.getFirstChild()!=null)
                	{
                		nodeValue = property.getFirstChild().getNodeValue();
                		appInfo.setIcon(nodeValue);
                	}
                }
                else if (nodeName.equals("Remark")) 
                {
                	if(property.getFirstChild()!=null)
                	{
                		nodeValue = property.getFirstChild().getNodeValue();
                		appInfo.setRemark(nodeValue);
                	}
                }
                else if (nodeName.equals("Status")) 
                {
                	if(property.getFirstChild()!=null)
                	{
                		nodeValue = property.getFirstChild().getNodeValue();
                    	appInfo.setStatus(Integer.parseInt(nodeValue));
                	}
                }
                else
                {
                	//do nothing
                }
            }
            
            
        } 
        catch(Exception e)
		{
			 e.printStackTrace(); 
		}
        return appInfo;  
	}
}
