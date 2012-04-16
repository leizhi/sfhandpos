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
     err = mif_close();                    //关闭读卡模块 
     err = WmodeClose();                   //关闭GPRS模块 
} 
int main()
{
    int err=0 ;
   //     int login_num =0;
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
        return 1; 
    }
    else
    {
       
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
                        return 1;
               }
           //验证用户信息
                err = CheckUser(username,password);
                if(err == 0)
                {
                       putstr("用户合法\n");
                     
                }
                else
                {
                    putstr("用户非法");
                    key(0);
                    CloseSystem();  
                    return 1;
                    /*login_num++;
                    if(login_num==4)
                    {
                      //可以锁定用户 
                     return 1; 
                    }
                    else
                    {
                      continue;
                    } */
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
           Examine();
           delay(500);
      }
    }
    key(0);
    
    return 1;
}

