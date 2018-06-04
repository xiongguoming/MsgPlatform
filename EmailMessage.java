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
    public static String sendEmailPassword = "zynacbgbhnuvcaaa";//��Ѷ���ɵ���Ȩ��
    public static String sendEmailSMTPHost = "smtp.qq.com";
    public static String recEmailAccount = "xiongguoming@ecjtu.edu.cn";
    public static ArrayList<String> ccEmailAccounts = new ArrayList<String>();
    //�������˻�
    public void setRecAccount(String account)
    {
    	recEmailAccount = account;
    }
    //���ó����˻�
    public void setCCAccounts(ArrayList<String> ccAccounts)
    {
    	ccEmailAccounts = ccAccounts;
    }
	public void sendEmail(String title,String content)
	{
		//���ܷ��͵����
		if(title==""||content==""||recEmailAccount==""||!recEmailAccount.contains("@"))
		{
			return;
		}
		
		try
		{
			// 1. ������������, ���������ʼ��������Ĳ�������
	        Properties props = new Properties();                    // ��������
	        props.setProperty("mail.transport.protocol", "smtp");   // ʹ�õ�Э�飨JavaMail�淶Ҫ��
	        props.setProperty("mail.smtp.host", sendEmailSMTPHost); // �����˵������ SMTP ��������ַ
	        props.setProperty("mail.smtp.auth", "true");            // ��Ҫ������֤
			
	        //ĳЩ���������SMTP����ʱ����Ҫʹ�� SSL����Ҫ���´���
	        final String smtpPort = "465";//�˿ڲ�׼ȷʱ�鿴��Ӧ�ʼ�
	        props.setProperty("mail.smtp.port", smtpPort);
	        props.setProperty("mail.smtp.socketFactory.class", "javax.net.ssl.SSLSocketFactory");
	        props.setProperty("mail.smtp.socketFactory.fallback", "false");
	        props.setProperty("mail.smtp.socketFactory.port", smtpPort);
	       
	        // 2. �������ô����Ự����, ���ں��ʼ�����������,debugģʽ ���Բ鿴��ϸ�ķ���log
	        Session session = Session.getDefaultInstance(props);
	        session.setDebug(true);

	        // 3. ����һ���ʼ�
	        MimeMessage message = createMimeMessage(session, title, content);
	        // 4. ���� Session ��ȡ�ʼ��������
	        Transport transport = session.getTransport();
	        // 5. ʹ�� �����˺� �� ���� �����ʼ�������, ������֤����������� message �еķ���������һ��, ���򱨴�
	        transport.connect(sendEmailAccount, sendEmailPassword);
	        // 6. �����ʼ�, �������е��ռ���ַ, message.getAllRecipients() ��ȡ�������ڴ����ʼ�����ʱ��ӵ������ռ���, ������, ������
	        transport.sendMessage(message, message.getAllRecipients());
	        // 7. �ر�����
	        transport.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	/**
     * ����һ��ֻ�����ı��ļ��ʼ�
     * @param session �ͷ����������ĻỰ
     * @param subject �ʼ�����
     * @param content �ʼ�����
     * @return �ʼ�
     * @throws Exception
     */
    public static MimeMessage createMimeMessage(Session session, String subject,String content) throws Exception {

        MimeMessage message = new MimeMessage(session);
        message.setFrom(new InternetAddress(sendEmailAccount, "��Ϣƽ̨", "UTF-8"));
        //���ý����û�
        message.setRecipient(MimeMessage.RecipientType.TO, new InternetAddress(recEmailAccount, "�����û�", "UTF-8"));
        //���ó����û�
        for(int nIndex=0; nIndex<ccEmailAccounts.size(); nIndex++)
        {
        	message.setRecipient(MimeMessage.RecipientType.CC, new InternetAddress(ccEmailAccounts.get(nIndex), "�����û�", "UTF-8"));
        }
        message.setSubject(subject, "UTF-8");
        message.setContent(content, "text/html;charset=UTF-8");
        message.setSentDate(new Date());
        message.saveChanges();
        return message;
    }
}
