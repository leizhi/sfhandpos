#include <hspos.h>
#include<gprs_api.h>
#include"GPRS.H"
#include"CARD.H"
#include"NetSetting.h"
/***********************
*��������InitGPRS 
*��  �ܣ���ʼ��GPRSģ�� 
*��  ������
*����ֵ��int  
***********************/
int InitGPRS()
{
    int RET; 
    int i = 0; 
    unsigned char key_value;

  cls();
  WmodeClose();
  InitNetSetting();
 /* putstr(NET_IP);
  putstr(NET_PORT);
  key(0);
  */
  putstr("��ʼ��,���Ժ�...\n");
  putstr("���ڴ�GPRSģ��\n");
  while(1)
   { 
       key_value = keygo();
       if(key_value == KEY_CLS)
       {
            return INITCANCLE;
       }
       
       RET=WmodeOpen();
       if(RET!=0)
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
   
       RET=WmodeCheckSIM();
       if(RET==0)
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
    RET = WmodeREGStatus(s);//����s������  ���GPRSģ���Ƿ�ע�� 
    if(RET != 0)
    {
           return REGSTATUSERROR; 
    }
    else
    {
        putstr("ģ��ע�᣺OK\n");
    }
    
    putstr("���ģ���Ƿ�֧��GPRS\n");
    RET = WmodeCheckGPRSSupport();//����Ƿ�֧��GPRS
    if(RET != 0)
    {
           return GPRSSUPPORTERROR; 
    } 
    else
    {
        putstr("֧��GPRS��OK\n");
    } 
    delay(10000);
    cls();
    putstr("���GPRS����״̬\n");
    RET = WmodeCheckGPRSstatus(s);//���GPRS����״̬
     if( RET !=0)
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
    RET=WmodeCheckSignal(ss);
     if( RET !=0)
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
    putstr("������������IP�Ͷ˿�...\n") ;
    RET=WNetSeting("2","5001",NET_IP,NET_PORT);//����˿����� 
    if(RET != 0)
    {
           return NETSETERROR;
    }
    else
    {
        putstr("����IP�Ͷ˿����ã�OK\n");
    } 
    
    putstr("���������������...");
    RET = WNetInit("512","6000","6000","6000");//����������� 
    if(RET !=0 )
    {
           return NETINITERROR;
    } 
    else
    {
        putstr("�����������: OK\n");
    } 
    delay(10000);
    cls(); 
    putstr("����������������...\n");
    RET =   WNetCont("1","IP","CMNET","0,0");     //������������
    if( RET != 0)
    {
        return NETCONTERRRO;
    } 
    else
    {
        putstr("������������: OK\n"); 
    }
    putstr("���ڱ����������...\n");
    RET = WmodeSave();                  //�����������
    if( RET != 0 )
    {
        return MODESAVEERROR;
    } 
    else
    {
        putstr("�������������OK");
    }
   
    RET =WNetConnect(20000); //��������
    if( RET !=0)
    {   
        cls(); 
        putstr("\n ������ֹ��� ����");
        key(0);
        return NETCONNECTERROR;
    } 
   else
    {
        putstr("\n�������ӳɹ�");
         return INITGPRSSUCCESS;  
    } 
    
     
}

void search_card(uchar *sealNo)
{                 
     putstr("search_card3\n");                 
     unsigned char send_buffer[100]={0};
     unsigned char *p=send_buffer;
     
     int sealNo_length;
     int k;
     int RET;

     memset(send_buffer,0,100);
     sealNo_length=0;
     
     cls();
     putstr("���ڲ�ѯ�����Ե�\n");                         //�������ݵ�������
     printf("send buffer:%s\n",send_buffer);
     
     *p='*';
     p++;
     
     *p='2';
     p++;
     
     while(*sealNo!=0x00){
         if(*sealNo== 0x00) {
                 putstr("��ѯ������");       
                 break;
             }
             
        *p=*sealNo;
        
        p++;
        sealNo++;
     }
     
     
     //                      
      *p = '#';
       p++;
      *p='\n';
      putstr("��ɷ�װ��������\n");  
     
      putstr(send_buffer);
      key(0);
      
      p=send_buffer;
      k=0;
      while(*p!='\n' && *p!=0){
          p++;
          k++;    
      }

      printf("k:%d",k);
      key(0);
      
      unsigned char send_num =0;
      while(send_num<2)
      { 
         cls();
         putstr("\nend_buffer:");
         putstr(send_buffer);
         RET = WNetTxd(send_buffer,k);
         printf("\nsender_buffer_error:%d",RET);
         key(0);
                 
         if( RET == 0)
         {
             putstr("�������ݳɹ�\n");
             break; 
         }
         else
         {
                cls();
                putstr("����ʧ�ܣ��ٴγ��Է���\n");
                key(0);
                send_num++;
         }
      }
              
      if(send_num ==2)
      {
              putstr("�����������δ���\n");
              key(0);
              return ;
      }

        //Ȼ����ܷ�����Ϣ 
        cls();

        unsigned char recv_buffer[3000];
        memset(recv_buffer,0,3000);
        unsigned short recv_len;
        
        putstr("׼����������\n");
        RET = WNetRxd(recv_buffer,&recv_len,10000);
        putstr("�����������\n");
        printf("\nrecv_len:%d",recv_len);
        putstr(recv_buffer);
        printf("\nRET:%d",RET);
        
        key(0);
        
        if(RET != 0)
        {
          cls();
          putstr("an RET in recv\n");
          key(0);

          return ;
        }
        else
        {
        cls();
        
        unsigned char query_buffer[3000];
        memset(query_buffer,0,3000);
        int k = 0;
        for(;k<recv_len;k++)
        {
           if(recv_buffer[k]!= ',')
           {
             query_buffer[k]= recv_buffer[k];
             recv_buffer[k]=' ';
           }
           else
           {
              recv_buffer[k] =' '; 
               int j =k;
               for(;k<recv_len;k++)
               {
                recv_buffer[k-j]=recv_buffer[k];
               }
               recv_buffer[k-j]=0;
              break;
           }
        }
        
        
        if(strcmp(query_buffer,"true")==0)
        {
                                          
           putstr(recv_buffer);
           key(0);
        }
        else
        {
           putstr("��ѯ�޸ü�¼��");
           key(0); 
           
        }
    }
}
