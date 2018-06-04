package com.webservice;


import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

import java.util.ArrayList;
import java.util.Date;
import java.util.Properties;

public class EmailMessage 
{
    public static String sendEmailAccount = "37800827@qq.com";
    public static String sendEmailPassword = "zynacbgbhnuvcaaa";//腾讯生成的授权码
    public static String sendEmailSMTPHost = "smtp.qq.com";
    public static String recEmailAccount = "xiongguoming@ecjtu.edu.cn";
    public static ArrayList<String> ccEmailAccounts = new ArrayList<String>();
    //主接收账户
    public void setRecAccount(String account)
    {
    	recEmailAccount = account;
    }
    //设置抄送账户
    public void setCCAccounts(ArrayList<String> ccAccounts)
    {
    	ccEmailAccounts = ccAccounts;
    }
	public void sendEmail(String title,String content)
	{
		//不能发送的情况
		if(title==""||content==""||recEmailAccount==""||!recEmailAccount.contains("@"))
		{
			return;
		}
		
		try
		{
			// 1. 创建参数配置, 用于连接邮件服务器的参数配置
	        Properties props = new Properties();                    // 参数配置
	        props.setProperty("mail.transport.protocol", "smtp");   // 使用的协议（JavaMail规范要求）
	        props.setProperty("mail.smtp.host", sendEmailSMTPHost); // 发件人的邮箱的 SMTP 服务器地址
	        props.setProperty("mail.smtp.auth", "true");            // 需要请求认证
			
	        //某些邮箱服务器SMTP连接时，需要使用 SSL，需要以下代码
	        final String smtpPort = "465";//端口不准确时查看相应邮件
	        props.setProperty("mail.smtp.port", smtpPort);
	        props.setProperty("mail.smtp.socketFactory.class", "javax.net.ssl.SSLSocketFactory");
	        props.setProperty("mail.smtp.socketFactory.fallback", "false");
	        props.setProperty("mail.smtp.socketFactory.port", smtpPort);
	       
	        // 2. 根据配置创建会话对象, 用于和邮件服务器交互,debug模式 可以查看详细的发送log
	        Session session = Session.getDefaultInstance(props);
	        session.setDebug(true);

	        // 3. 创建一封邮件
	        MimeMessage message = createMimeMessage(session, title, content);
	        // 4. 根据 Session 获取邮件传输对象
	        Transport transport = session.getTransport();
	        // 5. 使用 邮箱账号 和 密码 连接邮件服务器, 这里认证的邮箱必须与 message 中的发件人邮箱一致, 否则报错
	        transport.connect(sendEmailAccount, sendEmailPassword);
	        // 6. 发送邮件, 发到所有的收件地址, message.getAllRecipients() 获取到的是在创建邮件对象时添加的所有收件人, 抄送人, 密送人
	        transport.sendMessage(message, message.getAllRecipients());
	        // 7. 关闭连接
	        transport.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	/**
     * 创建一封只包含文本的简单邮件
     * @param session 和服务器交互的会话
     * @param subject 邮件主题
     * @param content 邮件内容
     * @return 邮件
     * @throws Exception
     */
    public static MimeMessage createMimeMessage(Session session, String subject,String content) throws Exception {

        MimeMessage message = new MimeMessage(session);
        message.setFrom(new InternetAddress(sendEmailAccount, "消息平台", "UTF-8"));
        //设置接收用户
        message.setRecipient(MimeMessage.RecipientType.TO, new InternetAddress(recEmailAccount, "接收用户", "UTF-8"));
        //设置抄送用户
        for(int nIndex=0; nIndex<ccEmailAccounts.size(); nIndex++)
        {
        	message.setRecipient(MimeMessage.RecipientType.CC, new InternetAddress(ccEmailAccounts.get(nIndex), "接收用户", "UTF-8"));
        }
        message.setSubject(subject, "UTF-8");
        message.setContent(content, "text/html;charset=UTF-8");
        message.setSentDate(new Date());
        message.saveChanges();
        return message;
    }
}
