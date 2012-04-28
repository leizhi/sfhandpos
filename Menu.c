#include"Menu.H"
#include "CARD.H"
#include "User.H"
#include "GPRS.H"
#include<gprs_api.h>
#include "Comm.h"

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
int Examine()
{
     int RET=-1;
     unsigned char mykey;
     uchar length=0;
    
     cls();
     putstr("正在查询，请稍等...");
     moveto(1,1);
      while(1)
     {   
		unsigned char serial_number[32]={0};      
        unsigned char read_buf[16]={0};
        
		if(MI_OK!=mif_open())
        {
    		cls();
    		putstr("\n inital error");
    		key(0);
    		return -1;
        }
        cls();
       // printf("mi_ok:%d\n",MI_OK);
        
        unsigned char type[2]={0};
        
        RET = mif_request(IDLE ,type);
        if(RET!=0) {
           printf("\n无卡");
           return -1;
        }
                
        RET=swap(type);
               
        short cardType = toShort(type);
        
        //printf("cardType:%d %04x\n",cardType,cardType);
        if(RET!=0) {
           printf("\n寻卡失败"); 
           return -2;
        }

		if(cardType==0x04){
            RET = mif_anticoll(0, serial_number);
            if(RET!=0) {
                printf("\n卡读取序列号失败"); 
                return -2;
            }
           // printf("\nSN RET:%d",RET);
            
            RET = readM1(&length,serial_number,read_buf);

            //putstr("readM1\n");
            //key(0);
        }else if(cardType==0x44){
               RET = readUL(&length,serial_number,read_buf);

               //putstr("readUL\n");
               //key(0);
        }
        
       // putstr("\nRFID防伪码:");
        //putstr(serial_number);
       // key(0);
        
		if(RET==-1)
		{
			cls();
			putstr("初始化卡错误");
			bell(40);
			putstr("无卡，请核对\n");
			putstr("按清除键【CLS】退出\n");
			putstr("按其他任意键继续\n");
    		if(mykey == KEY_CLS)
    		 {
    		   return 0;
    		 }
		}else{
			search_card(serial_number);
		}

  }
}
