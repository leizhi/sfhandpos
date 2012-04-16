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
     unsigned char send_buffer[100];
     unsigned char query_information[5000];
     unsigned short query_length;
     memset(query_information,0,5000);
     memset(send_buffer,0,100);
    
     cls();
     moveto(1,1);
      while(1)
     {
             err = mif_close();
             if(err != 0)
             {
                    putstr("mif_close err in examing\n");
                    key(0);
                    return ;
             }
             delay(100);
             err = OpenCard();
             if(err != 0)
             {
                    putstr("打开读卡模块错误\n");
                    key(0);
                    return ;
             }
             err = InitCard();
             delay(100);
             if(err == INITCARDSUCCESS )
             {
                
                 err = mif_authentication(1,1,cardsn);
                 if( err != 0)
                 {
                     putstr("验证密码错误");
                     key(0);
                     return ; 
                 }
                 else
                 {
                     memset(cardnum,0,40);
                     err = mif_read(4,cardnum);

                     if( err != 0)
                     {
                         putstr("读取数据错误");
                         key(0);
                     }
                     else
                     {
                         cls();
                         putstr("正在查询，请稍等\n");                         //发送数据到服务器
                          cardnum_length = 0;
                         //封装cardsn
                          send_buffer[0]= '*';
                          cardnum_length++;
                          send_buffer[1]= '2';
                          cardnum_length++;
                         // putstr("开始封装发送数据\n");
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
                         // putstr("完成封装发送数据\n");                          
                          send_buffer[cardnum_length]= '#';
                          cardnum_length++;
                          send_buffer[cardnum_length]='\n';
                          cardnum_length++;
                         // putstr("完成封装发送数据\n");  
                         
                         // putstr(send_buffer);
                         // key(0);
                          
                          unsigned short send_length = cardnum_length;

                         /*if ( err != 0)
                          {
                             putstr("连接网络超时\n");
                             key(0);
                             return ;  
                          }
                          */
                          /*else
                          {*/
                                 
                                  unsigned char send_num =0;
                                  while(send_num<2)
                                  { 
                                     err = WNetTxd(send_buffer,send_length);
                                     if( err == 0)
                                     {
                                         //putstr("发送数据成功\n");
                                         break; 
                                     }
                                     else
                                     {
                                            cls();
                                            putstr("发送失败，再次尝试发送\n");
                                            key(0);
                                            send_num++;
                                     }
                                  }
                                  
                                  if(send_num ==2)
                                  {
                                          putstr("发送数据两次错误\n");
                                          key(0);
                                          return ;
                                  }
                                  else
                                      {
                                           //然后接受返回信息 
                                          // putstr("准备接受数据\n");
                                           err = WNetRxd(query_information,&query_length,10000);
                                          // putstr(" 接收数据完成\n"); 
                                           if(err != 0)
                                           {
                                                  putstr("an err in recv\n");
                                                  key(0);
                                                  WmodeClose();
                                                  return ;
                                           }
                                           else
                                           {
                                               cls();
                                               unsigned char query_buffer[3000];
                                               memset(query_buffer,0,3000);
                                               int k = 0;
                                               for(;k<query_length;k++)
                                               {
                                                   if(query_information[k]!= ',')
                                                   {
                                                     query_buffer[k]= query_information[k];
                                                     query_information[k]=' ';
                                                   }
                                                   else
                                                   {
                                                      query_information[k] =' '; 
                                                       int j =k;
                                                       for(;k<query_length;k++)
                                                       {
                                                        query_information[k-j]=query_information[k];
                                                       }
                                                       query_information[k-j]=0;
                                                      break;
                                                   }
                                               }
                                              
                                               
                                                if(strcmp(query_buffer,"true")==0)
                                                {
                                                                                  
                                                   putstr(query_information);
                                                   key(0);
                                               }
                                               else
                                               {
                                                   putstr("查询无该记录！");
                                                   key(0); 
                                               }
                                              
                                           }
                                         
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
