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
    while(name[i])
    {
      name_length++;
      i++;
    } 
    i =0;
    while(passwd[i])
    {
        passwd_length++;
        i++;
    }
    uchar n_l[20];
    uchar p_l[20];
    itos(name_length,n_l);
    itos(passwd_length,p_l);
    putstr("�û�������\n");
    putstr(n_l);
    putstr("���볤��\n");
    putstr(p_l);
    
    //WmodeClose();
    
    //key(0);
    //err = InitGPRS();
    if(err ==0)
    {
           putstr("InitGPRS success\n");
    }
    //��������
     err = WNetConnect(10000);
     if(err != 0)  //�������糬ʱ 
     {
            putstr("�������ӳ�ʱ");
            key(0); 
            return NETERROR;
     } 
     
    err = WNetTxd(name,name_length);
    if( err != 0)
    {
         putstr("�����û�������");
            key(0); 
        return NETERROR; 
    }
    err = WNetTxd(passwd,passwd_length);
    if(err != 0)
    {
           putstr("�����������");
            key(0); 
        return NETERROR;
    } 
    else
    {
        //������֤��Ϣ 
        unsigned char recv_buffer[30];
        memset(recv_buffer,0,30);
        unsigned short len;
        err = WNetRxd(recv_buffer,&len,10000);
        if(err != 0)
        {
               putstr("���մ���");
            key(0); 
               return NETERROR;
        } 
        else
        {
            //�жϷ�����Ϣ 
            return  CHECKSUCCESS;
        }
    }
    
}
