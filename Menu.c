#include"Menu.H"
#include "CARD.H"
unsigned char MenuChoose()
{
     unsigned char key_value; 
     cls();
     moveto(4,6);
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
                  return CLS;
     }
     else if(key_value == 0x31)
     {
          //调用巡检函数 
      }
      else
      {
          bell(20);
      }
}
void InitMenu()
{
     
}
void Examine()
{
     char err ;
     err = InitCard();
     if(err != INITCARDSUCCESS )
     {
            putstr("初始化卡错误");
            return ; 
     }
     else
     {
         
     } 
}
