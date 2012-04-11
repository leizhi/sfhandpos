#include <hspos.h>
#include<gprs_api.h>
#include"GPRS.H"
#include"NetSetting.h"
/***********************
*��������InitGPRS 
*��  �ܣ���ʼ��GPRSģ�� 
*��  ������
*����ֵ��int  
***********************/
int InitGPRS()
{
    int err; 
    int i = 0; 
    unsigned char key_value;

  cls();
  InitNetSetting();
  putstr(NET_IP);
  putstr(NET_PORT);
  key(0);
  putstr("��ʼ��,���Ժ�...\n");
  putstr("���ڴ�GPRSģ��\n");
  while(1)
   { 
       key_value = keygo();
       if(key_value == KEY_CLS)
       {
            return INITCANCLE;
       }
       
       err=WmodeOpen();
       if(err!=0)
       { 	
     		i++;
     		if(i>0)                    //��һ�δ�ʧ�ܣ��ر�ģ�� 
     		{
                 WmodeClose();
                 delay(200);
                 if(i>2)               //�ڶ��δ�ʧ�ܣ��˳� 
                 {
                  return OPENGPRSERROR;
                 } 	
     		}	
       }
       else
       {   
       		break;	
       }		  
	}
 putstr("��GPRSģ�飺OK\n");		
	
 putstr("���ڼ��SIM��\n");
 i =0;
  while(1) 
  {
   
       err=WmodeCheckSIM();
       if(err==0)
       {
       		putstr("���SIM����ok\n");
       		break;
       }		
       else
       {	
       		 delay(1000);
       		 i++;
   		 	if(i==5)
        	{
        		return CHECKSIMERROR;	
        	}
       }
	}

    
    unsigned char s[2];
    putstr("���ģ���Ƿ�ע��\n");
    err = WmodeREGStatus(s);//����s������  ���GPRSģ���Ƿ�ע�� 
    if(err != 0)
    {
           return REGSTATUSERROR; 
    }
    else
    {
        putstr("ģ��ע�᣺OK\n");
    }
    
    putstr("���ģ���Ƿ�֧��GPRS\n");
    err = WmodeCheckGPRSSupport();//����Ƿ�֧��GPRS
    if(err != 0)
    {
           return GPRSSUPPORTERROR; 
    } 
    else
    {
        putstr("֧��GPRS��OK\n");
    } 
    
    cls();
    putstr("���GPRS����״̬\n");
    err = WmodeCheckGPRSstatus(s);//���GPRS����״̬
     if( err !=0)
    {
        return CHECKSTATUSERROR;
    }
    else
    {
        putstr("GPRS����״̬:OK\n");
    }
    
    putstr("����ź�ǿ��...\n");
    unsigned char ss[10];
    memset(ss,0,10);
    err=WmodeCheckSignal(ss);
     if( err !=0)
    {
        return CHECKSIGNALERROR;
    }
    else
    {
        putstr("�ź�ǿ��Ϊ��");
        putstr(ss);
        putstr("\n");
        //����10 ��ʾ�û��ź���
         
    }
    key(0);
        putstr("������������IP�Ͷ˿�...\n") ;
    err=WNetSeting("2","5001",NET_IP,NET_PORT);//����˿����� 
    if(err != 0)
    {
           return NETSETERROR;
    }
    else
    {
        putstr("����IP�Ͷ˿����ã�OK\n");
    } 
    
    putstr("���������������...");
    err = WNetInit("512","6000","6000","6000");//����������� 
    if(err !=0 )
    {
           return NETINITERROR;
    } 
    else
    {
        putstr("�����������: OK\n");
    } 
    
    cls(); 
    putstr("����������������...\n");
    err =   WNetCont("1","IP","CMNET","0,0");     //������������
    if( err != 0)
    {
        return NETCONTERRRO;
    } 
    else
    {
        putstr("������������: OK\n"); 
    }
    putstr("���ڱ����������...\n");
    err = WmodeSave();                  //�����������
    if( err != 0 )
    {
        return MODESAVEERROR;
    } 
    else
    {
        putstr("�������������OK");
    }
    /*
    err =WNetConnect(20000); //��������
    if( err !=0)
    {   
        cls(); 
        putstr("\n ������ֹ��� ����");
        key(0);
        return NETCONNECTERROR;
    } 
    else
    {
        putstr("\n�������ӳɹ�");
    } 
    */
    key(0); 
    return INITGPRSSUCCESS;    
}
