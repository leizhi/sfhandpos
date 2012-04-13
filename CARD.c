#include<hspos.h>
#include "CARD.H"
#include"user.h"

void Initialization()
{
     memset(atq,0,3);
     memset(cardsn,0,20);  
     Init();
}
char InitCard()
{
     char err;
     Initialization();
     unsigned char keya[16]={0xff,0xff,0xff,0xff,0xff,0xff};//密码 
     cls();
    // OpenCard();
     putstr("正在寻卡请求...\n");
            err = mif_request(IDLE ,atq);//寻卡请求 IDLE为单卡模式 ALL 为多卡模式 
            if( err != 0)
            {  
             return REQUESTCARDERROR;   
            }
            else
            {
                 putstr("寻卡请求: OK\n");
            }
            
            putstr("正在防止冲突...\n");
             err= mif_anticoll(0,cardsn);//防止冲突 返回卡的序列号 
            if( err !=0)
            {
                return ANTICOLLCARDERROR; 
            }
            else
            {
                putstr("防止冲突：OK\n");
            } 
            putstr("正在选卡中...\n");
            err = mif_select(cardsn);//选定给点序列号的卡 
             if( err !=0)
            {
                return SELECTCARDERROR;
            }
            else
            {
                putstr("选卡：OK\n");
            }
            
            putstr("装载密码到扇区...\n");
            err = mif_load_key(keya);// 将密码装入读写扇区 
            
             if( err !=0)
            {
                return LOADKEYERROR;
            }
            else
            {
                putstr("装载密码到扇区：OK\n");
            } 
            return   INITCARDSUCCESS;
}
char OpenCard()
{
    char err;
    Initialization();
    cls();//清除屏幕
    putstr("初始化读卡模块...\n");
    int i = 0; 
    while(1)
         {
              err = mif_open();
              if(err != 0 ) 
              {
                     i++;
                     if(i>0)                    //第一次打开读卡模块失败
                     {
                             mif_close();
                             delay(10);
                             if(i>1)            //第二次打开读卡模块失败
                             {
                                    return OPENCARDERROR; 
                             } 
                             
                     } 
              }
              else
              {
                  break;
              }
         }
    putstr("初始化读卡模块：OK\n");
    return   INITCARDSUCCESS;  
}

char ReadUserInformation(unsigned char* name ,unsigned char * passwd)
{
     char err;
     unsigned char mykey ;
     while(1)
     {
          err = InitCard();
          if(err == INITCARDSUCCESS)  //初始化卡片成功 开始读取用户信息 
          {
             //测试 
              cls();
              err = mif_authentication(1,1,cardsn);//验证扇区密码
              if( err != 0)
              {
                  putstr("验证扇区密码错误");
                  return 1; 
              }
              else
              {
                  err = mif_read(5,name);
                  if( err != 0 )
                  {
                      putstr("read name err\n");
                  }
                  else
                  {
                      putstr("用户名为：");
                     // putstr(name);
              
                      //putstr("\n");
                  }
                  err = mif_read(6,passwd);
                  if( err != 0)
                  {
                      putstr("read passwd error");
                  }
                  else
                  { 
                      putstr("密码：");
                     // putstr(passwd);
                     // putstr("\n");
                  } 
                  return READUSERINFORMATIONSUCCESS;
              }
             return READUSERINFORMATIONERROR;
          }
          else
          {
                cls();
                bell(40);
                putstr("无卡，请核对\n");
                putstr("按清除键【CLS】退出\n");
                putstr("按其他任意键继续\n");
                mykey=key(0);
               if(mykey == KEY_CLS)
                {
                        return READUSERINFORMATIONERROR;
                }
          } 
     }
     return READUSERINFORMATIONSUCCESS;
   
}
