#include"Main.h" 
int InitSystem() 
{
    int gprs_err ;
    char card_err;
    gprs_err = InitGPRS();
    if(gprs_err!= 0)
    {
         return INITSYSTEMERROR;
    }
    else
    {
        card_err = OpenCard();
        if(card_err !=0)
        {
           return INITSYSTEMERROR;
        }
        else
        {
            return INITSYSTEMSUCCESS;
        }
    }
} 
void CloseSystem()
{
     int err ;
     unsigned char exit_msg[10];
     memset(exit_msg,0,10);
     exit_msg[0] = '*';
     exit_msg[1] = '3';
     exit_msg[2]= '#';
     exit_msg[3] = '\n';
     
     err = mif_close();                    //关闭读卡模块 

     err = WNetTxd(exit_msg,4);
     
     if(err !=0)
     { 
            int k =0;
            putstr("err in exit_msg");
            key(0);
            while(1)
            {
               err = WNetTxd(exit_msg,4);
               if(err!=0)
               {
                  k++;
               }
               else
               {
                    err =WNetIPClose("1",2000);
                    break ;
               }
               if(k ==2)
               {
                    break;
               }
            }
            
     }
     else
     {
         ulong  i =3600000;
         cls();
         putstr("正在关闭设备，请稍等...");
         while(i)
         {
                 i--;
         } 
   cls();     
         err =WNetIPClose("1",2000);
      
     }
  
}

int main()
{
     uchar choose;
     uchar flag =0;
  cls();
         while(1)
         {    
                
         moveto(4,6);
         putstr("欢迎使用");
         moveto(6,4);
         putstr("请选择查询方式");
         moveto(8,1);
         putstr("【 1 】: 本地查询");
         moveto(10,1);
         putstr("【 2 】: 网络查询");
         moveto(12,1);
         putstr("【CLS】：退出登陆");

         moveto(16,1);
         putstr("请选择"); 
         moveto(16,8);
             choose = key(0);
             if(choose == 0x31)
             {
                moveto (16,1);
                clsn(16,2);
                moveto(16,1);
                putstr("请选择"); 
                 moveto(16,8);
                 putch(choose);
                 flag = 1;
                
             }
             else if(choose == 0x32)
             {
                    moveto (16,1);
                clsn(16,2);
                moveto(16,1);
                  putstr("请选择"); 
                     moveto(16,8);
                     putch(choose);
                     flag = 2;
             }
             else if(choose == KEY_CLS)
             {
                  return 1;
              } 
              else if(choose == KEY_ENTER)
              {
                    if(flag ==1 ||flag ==2)
                    { 
                               if(flag ==1)
                             {
                               WithoutNet(); 
                               cls();
                             }
                             if(flag ==2)
                             {
                                     UsingNet();
                                     cls();
                             }
                            
                    }
                    else
                    {
                        flag =0;
                        bell(20);
                    }
              }
              else
                {
                     bell(20);
                 
                 }
         }
     
    return 1;
}
int WithoutNet()
{
    int RET=-1;
     unsigned char mykey;
     uchar winenum[16]={0};
     uchar length=0;
     cls();
     int err = OpenCard();
     if(err !=0)
     {
            putstr("打开读卡模块失败\n");
            putstr("按任意键返回\n");
            key(0);
            return 1; 
     }
     else if(err ==0)
     {    
          unsigned char serial_number[32]={0};      
        unsigned char read_buf[16]={0};
         unsigned char type[2]={0};
          while(1)
          {     
                err = OpenCard();
                if (err !=0)
                {
                 putstr("打开读卡模块失败\n");
                  putstr("按任意键返回\n");
                 key(0);
                  return 1; 
            }
                  RET = mif_request(IDLE ,type);
                  
                 cls();
                  
                  if(RET ==0)
                  {
                      RET=swap(type);       
                      short cardType = toShort(type);
                      if(RET ==0)
                      {
                             if(cardType==0x04)
                                    {
                                        RET = mif_anticoll(0, serial_number);
                                        if(RET!=0) 
                                        {
                                            printf("\n卡读取序列号失败"); 
                                            key(0);
                                            return -2;
                                        }
                                     //   printf("\nSN RET:%d",RET);
                                       // key(0);
                                        
                                        memset(read_buf,0,16);
                                        RET = readM1(&length,serial_number,read_buf);
                                        
                                        if(RET == 0)
                                        {
                                                cls();
                                                RET = ReadWineNum(winenum);
                                                if(RET == 0)
                                                {
                                                       moveto(4,1);
                                                   putstr("酒罐号:");
                                                 putstr(winenum);
                                                 putstr("\n");
                                                 moveto(6,1); 
                                               putstr("防伪码：");
                                               putstr(serial_number);
                                               printf("\n");
                                                 key(0); 
                                                 return 0;
                                                 }
                                                 else
                                                 {
                                                     putstr("读酒罐号出错\n");
                                                     key(0);
                                                 }
                                               
                                               
                                        }
                                        else
                                        {
                                            putstr("read m1 err\n");
                                        }
                                        
                                    }
                                    else if(cardType==0x44)
                                    {
                                           RET = readUL(&length,serial_number,read_buf);
                                           
                                            moveto(4,1);
                                                   putstr("酒罐号:");
                                                 putstr(read_buf);
                                                 putstr("\n");
                                                 moveto(6,1); 
                                               putstr("防伪码：");
                                               putstr(serial_number);
                                               printf("\n");
                                                 key(0); 
                                           return 0;
   
                                    } 
                      } 
                  }
                  else
                  {
                            cls();
                             putstr("寻卡失败\n");
                             bell(20);
                     	    putstr("按清除键【CLS】退出\n");
                			putstr("按其他任意键继续\n");
                			uchar mykey = key(0);
                    		if(mykey == KEY_CLS)
                    		 {
                    		   return 0;
                    		 }
                  }
    
          }
     }

     
}
int UsingNet()
{
    
     int err=0 ;
    int login_num =0;
    bell(20);
    err = InitSystem();
    if( err != 0)
    {
        cls();
        bell(20);
        putstr("初始化系统出错！\n");
        bell(50);
        putstr("按任意键退出");
        key(0);
        CloseSystem();
        return 1; 
    }
    else
    {
        while(1)
        {
            bell(20);
         err = LoginChoose();
                if(err == 1)
                {
                        cls();
                        putstr("刷卡登陆");
                        err = ReadUserInformation(username,password);
                        if(err != 0) //无卡退出 
                        {
                              return 1;
                        }
                        cls();
                }
                if(err ==2) 
                    {
                        cls();
                        putstr("输入登陆");
                        GetUserInformation();
                }
                if(err == 3)
               { 
                        cls();
                        putstr("退出");
                        CloseSystem();
                       // key(0);
                        WmodeClose();
                        return 1;
               }
           //验证用户信息
                err = CheckUser(username,password);
                if(err == 0)
                {
                       putstr("用户合法\n");
                     break;
                }
                else
                {
                    putstr("用户非法");
                    key(0);
                    login_num++;
                    if(login_num==4)
                    {
                      //可以锁定用户 
                      CloseSystem();
                        return 1;
                     
                    }
                    else
                    {
                      continue;
                    }
                    
                 }     
        }
    }
    
    unsigned char choose_value;
    while(1)
    {
      
      choose_value = MenuChoose();
      if(choose_value == CLS)
      {
        break;
      }
      else if(choose_value == VIEW)
      {
           putstr("正在查询等稍等\n");
           Examine();
           delay(500);
      }
    }
    CloseSystem();
    //key(0);
    WmodeClose();
    return 1;
}

