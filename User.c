#include "User.h"
void Init()
{
     memset(username,0,20);
     memset(password,0,20);
}
/***********************
*函数名：GetUserInformation 
*功  能：获取用户输入的用户名和密码 
*参  数：无
*返回值：无 
***********************/
void GetUserInformation()
{
         cls();
         uchar keyvalue;            //接收键盘按键值 
         uchar x,y;                 //获取光标位置
         uchar index = 0;           //记录存储密码的长度 
         moveto(4,6);
         putstr("欢迎使用");
         moveto(8,1);
         putstr("用户名 :");
         moveto(10,1);
         putstr("密  码 :"); 
         
         moveto(8,10);              //键盘回写位置 
         keys(username);
         moveto(8,10);              //输出用户名位置 
         putstr(username);
         clsn(8,2);                 //清除键盘回写 
         
         moveto(8,1);
         putstr("用户名 :");
         moveto(8,10);
         putstr(username);
         moveto(10,10);             //开始输出密码位置 

         x = 10;
         y = 10;
         while(1)
         {
              keyvalue=key(0);                         //不带回显 
              if(KEY_ENTER == keyvalue)                //按下的是确认键
              {
                           if(index == 0)              //密码为空
                           {
                               bell(20); 
                           } 
                           else                        //密码不为空，且已经输入完毕 
                           {
                               break;
                           }
              }
              else if(KEY_CLS == keyvalue)             // 按下的是清除键
              {
                   if(index != 0)                      //没有删除完密码
                   {
                            index = index -1;
                            password[index] = 0;
                                                       //重新输出密码位数 用*号表示
                            moveto(10,1);
                            clsn(10,2);
                            
                             moveto(10,1);
                             putstr("密  码 :"); 
                            
                            moveto(10,10);
                            uchar i =0;
                            for(;i<index;i++)
                            {
                                 putch('*');            
                            }  
                          
                   } 
                   else
                   {
                       bell(20);
                   } 
              } 
              else if(((keyvalue >0x29)&&(keyvalue < 0x40))||(keyvalue == 0x2b)||(keyvalue== 0x2e))
              {
                      x = getx();
                      y = gety();
                      moveto(x,y);
                      putch('*');
                      password[index]= keyvalue;
                      index = index+1;
                     
              }
         }
         //测试用 
       
         cls();
         putstr(username);
         putstr("\n");
         putstr(password);  
         key(0); 
        //测试用

}
