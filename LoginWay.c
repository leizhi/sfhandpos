#include<hspos.h>
#include<gprs_api.h>
#include"LoginWay.h" 
#include"GPRS.h"
unsigned char LoginChoose()
{
         unsigned char key_value;
         unsigned char choose;
         unsigned char flag = 0;
         cls();
         moveto(4,6);
         putstr("��ӭʹ��");
         moveto(6,4);
         putstr("��ѡ���½��ʽ");
         moveto(8,1);
         putstr("�� 1 ��: ˢ����½");
         moveto(10,1);
         putstr("�� 2 ��: �����½");
         moveto(12,1);
         putstr("��CLS�����˳���½");

         moveto(16,1);
         putstr("��ѡ��"); 
         while(1)
         {
                 key_value = key(0);
                 if(key_value == KEY_CLS)
                 {
                       return LOGINCANCLE;    
                 }
                 else if(key_value == KEY_ENTER)
                         {
                            if( flag == 0)//ֱ�Ӱ�ȷ�ϼ�
                            {
                                bell(20); 
                            }    
                            else
                            {
                                return choose;
                            }
                         } 
                         else if((key_value == 0x31)||(key_value == 0x32))
                                         {
                                                    choose = key_value;
                                                    moveto(16,8);
                                                    putch(choose);
                                                    if(key_value == 0x31)
                                                    choose = LOGINBYCARD;
                                                    else
                                                    {
                                                        choose = LOGINBYINPUT;
                                                    }
                                                    flag =1;
                                         }
                                         else
                                         {
                                             bell(20);
                                         }
                         
                
         }
         
} 

int CheckUser(unsigned char* name ,unsigned char* passwd)
{
    int err ;
    int name_length=0;
    int passwd_length=0;
    int i=0;
    putstr("������֤��Ϣ�����Ե�\n");
    while(1)
    {
       if((name[i] == 0x20)||(name[i]==0X00))
       {
                   break;
       }
      name_length++;
      i++;
    } 
    i =0;
    while(1)
    {
        if((passwd[i]==0x20)||(passwd[i]==0x00 ))
        {
           break;
        }
        else
        {
            passwd_length++;
            i++;
        }
    }
    uchar n_l[20];
    uchar p_l[20];
    itos(name_length,n_l);
    itos(passwd_length,p_l);
    if(err ==0)
    {
           putstr("InitGPRS success\n");
    }
    //��������
     err = WNetConnect(50000);
     
     if(err != 0)  //�������糬ʱ 
     {
            putstr("�������ӳ�ʱ");
            key(0); 
            return NETERROR;
     }  
     unsigned char send_buffer[100];
     memset(send_buffer,0,100);
     int len=0;
  
       send_buffer[len]= '*';
       len++;
       send_buffer[len]='1';
       len++;
       int m=0;
       for(;m<name_length;m++)
       {
          send_buffer[len]=name[m];
          len++;
       }
       //putstr("����û�����װ\n");
       send_buffer[len]=',';
       len++;
       m=0;
       for(;m<passwd_length;m++)
       {
           send_buffer[len]=passwd[m];
           len++;
       }
       //putstr("��������װ\n");
      // key(0);      
       send_buffer[len]='#';
       len++;
       send_buffer[len]='\n';
       len++;
      // putstr(send_buffer);
      // key(0);
     
       int num =0;//���Է��ʹ���
       while(1)
       { 
           err= WNetTxd(send_buffer,len);
           if(err !=0 )
           {
                  num++;
                  putstr("�������ݴ���\n");
                  if(num == 3)
                  {
                          return NETERROR;
                  }
                  putstr("���ڳ����ٴη���");
           }
           else
           {
               break;
           }
       }
     
            //������֤��Ϣ 
            unsigned char recv_buffer[3000];
            memset(recv_buffer,0,3000);
            unsigned short recv_len;
            err = WNetRxd(recv_buffer,&recv_len,10000);
            
            if(err != 0)
            {
                   putstr("���մ���");
                   key(0); 
                   return NETERROR;
            } 
            else
            {
                //�жϷ�����Ϣ 
                putstr("��������Ϊ��");
                putstr(recv_buffer);
                key(0); 
                return CHECKSUCCESS;
            } 
 //   return  CHECKSUCCESS;
}
