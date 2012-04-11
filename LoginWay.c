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
         putstr("欢迎使用");
         moveto(6,4);
         putstr("请选择登陆方式");
         moveto(8,1);
         putstr("【 1 】: 刷卡登陆");
         moveto(10,1);
         putstr("【 2 】: 输入登陆");
         moveto(12,1);
         putstr("【CLS】：退出登陆");

         moveto(16,1);
         putstr("请选择"); 
         while(1)
         {
                 key_value = key(0);
                 if(key_value == KEY_CLS)
                 {
                       return LOGINCANCLE;    
                 }
                 else if(key_value == KEY_ENTER)
                         {
                            if( flag == 0)//直接按确认键
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
    putstr("用户名长度\n");
    putstr(n_l);
    putstr("密码长度\n");
    putstr(p_l);
    
    //WmodeClose();
    
    //key(0);
    //err = InitGPRS();
    if(err ==0)
    {
           putstr("InitGPRS success\n");
    }
    //连接网络
     err = WNetConnect(10000);
     if(err != 0)  //连接网络超时 
     {
            putstr("网络连接超时");
            key(0); 
            return NETERROR;
     } 
     
    err = WNetTxd(name,name_length);
    if( err != 0)
    {
         putstr("发送用户名错误");
            key(0); 
        return NETERROR; 
    }
    err = WNetTxd(passwd,passwd_length);
    if(err != 0)
    {
           putstr("发送密码错误");
            key(0); 
        return NETERROR;
    } 
    else
    {
        //接收验证信息 
        unsigned char recv_buffer[30];
        memset(recv_buffer,0,30);
        unsigned short len;
        err = WNetRxd(recv_buffer,&len,10000);
        if(err != 0)
        {
               putstr("接收错误");
            key(0); 
               return NETERROR;
        } 
        else
        {
            //判断返回信息 
            return  CHECKSUCCESS;
        }
    }
    
}
