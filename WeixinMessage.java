package com.webservice;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class WeixinMessage {
	
	
	/**

     * ΢�Ź����˺ŷ��͸��˺�

     * @param content �ı�����

     * @param toUser ΢���û�  

     * @return

     */
    public  void sendTextMessageToUser(String content,String toUser){

    	/*
       String json = "{\"touser\": \""+toUser+"\",\"msgtype\": \"text\", \"text\": {\"content\": \""+content+"\"}}";

       //��ȡaccess_token

       GetExistAccessToken getExistAccessToken = GetExistAccessToken.getInstance();

       String accessToken = getExistAccessToken.getExistAccessToken();

       //��ȡ����·��

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

     * ��������΢�ź�̨�ӿ�

     * @param action �ӿ�url

     * @param json  ����ӿڴ��͵�json�ַ���

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

           System.setProperty("sun.net.client.defaultConnectTimeout", "30000");// ���ӳ�ʱ30��

           System.setProperty("sun.net.client.defaultReadTimeout", "30000"); // ��ȡ��ʱ30��

           http.connect();

           OutputStream os = http.getOutputStream();

           os.write(json.getBytes("UTF-8"));// �������

           InputStream is = http.getInputStream();

           int size = is.available();

           byte[] jsonBytes = new byte[size];

           is.read(jsonBytes);

           String result = new String(jsonBytes, "UTF-8");

           System.out.println("���󷵻ؽ��:"+result);

           os.flush();

           os.close();

       } catch (Exception e) {
           e.printStackTrace();
       }
    }

}
