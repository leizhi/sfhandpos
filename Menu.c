#include"Menu.H"
#include "CARD.H"
#include "User.H"
#include<gprs_api.h>
unsigned char  MenuChoose()
{
     unsigned char key_value; 
     unsigned char flag =0;
     static int index = 0;
     static unsigned char name_temp[20];
     if(index ==0)
     { 
        
         strcpy(name_temp,username);
         index = 1;
     }
       cls();
       
     while(1)
     {
         moveto(4,2);
         putstr("欢迎您：");
         putstr(name_temp); 
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
     int err ;
     unsigned char mykey;
     unsigned char cardnum_length;//序列号长度 
     unsigned char send_buffer[30];
     unsigned char query_information[1000];
     unsigned short query_length =1000;
     memset(query_information,0,1000);
     memset(send_buffer,0,30);
    
     cls();
     moveto(1,1);
      while(1)
     {
             err = mif_close();
             if(err != 0)
             {
                    return ;
             }
             err = OpenCard();
             if(err != 0)
             {
                    putstr("打开读卡模块错误\n");
                    return ;
             }
             err = InitCard();
             if(err == INITCARDSUCCESS )
             {
                 err = mif_authentication(1,1,cardsn);
                 if( err != 0)
                 {
                     putstr("验证密码错误");
                     return ; 
                 }
                 else
                 {
                     memset(cardnum,0,20);
                     err = mif_read(4,cardnum);

                     if( err != 0)
                     {
                         putstr("读取数据错误");
                         key(0);
                     }
                     else
                     {
                         //发送数据到服务器
                          cardnum_length = 0;
                         //封装cardsn
                          send_buffer[0]= '*';
                          cardnum_length++;
                          send_buffer[1]= '2';
                          cardnum_length++;
                           int k =0;
                          while(1)
                          {
                                 
                                  if(cardnum[k]== 0)
                                  {
                                     break;
                                  }
                                  else
                                  {
                                      send_buffer[cardnum_length]=cardnum[k];
                                      cardnum_length++;
                                  }
                                  k++;
                          } 
                          
                          send_buffer[cardnum_length]= '#';
                          cardnum_length++;
                          cls();
                          
                          putstr(send_buffer);
                          key(0);
                          
                          unsigned short send_length = cardnum_length;
                          
                          //err = WNetConnect(20000);
                          /*if ( err != 0)
                          {
                             putstr("连接网络超时\n");
                             return ;  
                          }
                          else
                          {*/
                            
                                  unsigned char send_num =0;
                                  while(send_num<2)
                                  {
                                    
                                     err = WNetTxd(send_buffer,send_length);
                                     if( err == 0)
                                     {
                                         break; 
                                     }
                                     else
                                     {
                                            cls();
                                            printf("%d",send_num);
                                            putstr("发送失败，再次尝试发送\n");
                                            key(0);
                                            send_num++;
                                     }
                                  }
                                  if(send_num ==2)
                                  {
                                          return ;
                                  }
                                  else
                                      {
                                           //然后接受返回信息 
                                           putstr("准备接受数据\n");
                                           err = WNetRxd(query_information,&query_length,10000);
                                           putstr(" 接收数据完成\n"); 
                                           if(err != 0)
                                           {
                                                  putstr("an err in recv\n");
                                                  key(0);
                                                  return ;
                                           }
                                           else
                                           {
                                               putstr(query_information);
                                               key(0);
                                           }
                                           WmodeClose();
                                           putstr("\nwnode clsoe\n");
                                           key(0);
                                      }
                             
                         // }
                          
                          
                        
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
