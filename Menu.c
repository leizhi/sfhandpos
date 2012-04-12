#include"Menu.H"
#include "CARD.H"
#include "User.H"
unsigned char  MenuChoose()
{
     unsigned char key_value; 
     unsigned char flag =0;
       cls();
       
     while(1)
     {
         moveto(4,2);
         putstr("欢迎您：");
         putstr(username); 
         moveto(6,4);
         putstr("请选择所需操作：");
         moveto(8,1);
         putstr("【 1 】: 巡检");
         moveto(10,1);
         putstr("【CLS】：退出登陆");
        
         moveto(14,1);
         putstr("请选择");
         key_value = key(0);
         
         if(key_value == KEY_CLS)
         {
               cls();
             return CLS;
         }
         else if(key_value == 0x31)
         {
            flag = 1;
            moveto(14,1);
            clsn(14,2);
            moveto(14,1);  
            putstr("请选择");
             moveto(14,8);
             putch(key_value);
         }
          else if(key_value == KEY_ENTER)
          {
               if(flag == 1)
               {
                  return VIEW;
               }
               else
               {
                   bell(20);
               }
          }
          else
          {
              bell(20);
              continue;
          }
     }
}
void Examine()
{
     char err ;
     unsigned char mykey;
     cls();
     moveto(1,1);
     putstr("examing 。。。\n"); 
     key(0);
      while(1)
     {
             mif_close();
             OpenCard();
             err = InitCard();
             if(err == INITCARDSUCCESS )
             {
                putstr("initcard success");
                 err = mif_authentication(1,0,cardsn);
                 if( err != 0)
                 {
                     putstr("验证密码错误");
                     return ; 
                 }
                 else
                 {
                     err = mif_read(0,cardsn);
                     if( err != 0)
                     {
                         putstr("读取数据错误");
                     }
                     else
                     {
                         putstr(cardsn);
                         key(0);
                         //发送数据到服务器
                         //然后接受返回信息 
                         break;
                     } 
                 }
                    
             }
             else
             {
            
                cls();
                putstr("初始化卡错误");
                bell(40);
                putstr("无卡，请核对\n");
                putstr("按清除键【CLS】退出\n");
                putstr("按其他任意键继续\n");
                mykey=key(0);
               if(mykey == KEY_CLS)
                {
                        return ;
                }
             } 
     }
}
