package com.webservice;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class WeixinMessage {
	
	
	/**

     * 微信公共账号发送给账号

     * @param content 文本内容

     * @param toUser 微信用户  

     * @return

     */
    public  void sendTextMessageToUser(String content,String toUser){

    	/*
       String json = "{\"touser\": \""+toUser+"\",\"msgtype\": \"text\", \"text\": {\"content\": \""+content+"\"}}";

       //获取access_token

       GetExistAccessToken getExistAccessToken = GetExistAccessToken.getInstance();

       String accessToken = getExistAccessToken.getExistAccessToken();

       //获取请求路径

       String action = "https://api.weixin.qq.com/cgi-bin/message/custom/send?access_token="+accessToken;

       System.out.println("json:"+json);

       try {

           connectWeiXinInterface(action,json);

       } catch (Exception e) {

           e.printStackTrace();

       }
       */
   }
    /**

     * 连接请求微信后台接口

     * @param action 接口url

     * @param json  请求接口传送的json字符串

     */

    public  void connectWeiXinInterface(String action,String json){

        URL url;

       try {

           url = new URL(action);

           HttpURLConnection http = (HttpURLConnection) url.openConnection();

           http.setRequestMethod("POST");

           http.setRequestProperty("Content-Type",

                   "application/x-www-form-urlencoded");

           http.setDoOutput(true);

           http.setDoInput(true);

           System.setProperty("sun.net.client.defaultConnectTimeout", "30000");// 连接超时30秒

           System.setProperty("sun.net.client.defaultReadTimeout", "30000"); // 读取超时30秒

           http.connect();

           OutputStream os = http.getOutputStream();

           os.write(json.getBytes("UTF-8"));// 传入参数

           InputStream is = http.getInputStream();

           int size = is.available();

           byte[] jsonBytes = new byte[size];

           is.read(jsonBytes);

           String result = new String(jsonBytes, "UTF-8");

           System.out.println("请求返回结果:"+result);

           os.flush();

           os.close();

       } catch (Exception e) {
           e.printStackTrace();
       }
    }

}
