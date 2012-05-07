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
     char RET;
     Initialization();
     unsigned char keya[16]={0xff,0xff,0xff,0xff,0xff,0xff};//密码 
    // cls();
     OpenCard();
   //  putstr("正在寻卡请求...\n");
            RET = mif_request(IDLE ,atq);//寻卡请求 IDLE为单卡模式 ALL 为多卡模式 
            if( RET != 0)
            {  
             return REQUESTCARDERROR;   
            }
            else
            {
               //  putstr("寻卡请求: OK\n");
            }
            
           // putstr("正在防止冲突...\n");
             RET= mif_anticoll(0,cardsn);//防止冲突 返回卡的序列号 
            if( RET !=0)
            {
                return ANTICOLLCARDERROR; 
            }
            else
            {
              //  putstr("防止冲突：OK\n");
            } 
           // putstr("正在选卡中...\n");
            RET = mif_select(cardsn);//选定给点序列号的卡 
             if( RET !=0)
            {
                return SELECTCARDERROR;
            }
            else
            {
               // putstr("选卡：OK\n");
            }
            
          //  putstr("装载密码到扇区...\n");
            RET = mif_load_key(keya);// 将密码装入读写扇区 
            
             if( RET !=0)
            {
                return LOADKEYERROR;
            }
            else
            {
               // putstr("装载密码到扇区：OK\n");
            } 
            return   INITCARDSUCCESS;
}

char OpenCard(){
	int RET=-1;
	Initialization();
	//cls();//清除屏幕
	//putstr("初始化读卡模块...\n");
	RET = mif_open();
	//printf("\nOpenCardRET:%d",RET);
	delay(500);
	if(RET != 0 ){
		//第一次打开读卡模块失败
		delay(500);
		return OPENCARDERROR;
	}
	// putstr("初始化读卡模块：OK\n");
	return INITCARDSUCCESS;
}

char ReadUserInformation(unsigned char* name ,unsigned char * passwd)
{
     char RET;
     unsigned char mykey ;
     while(1)
     {
          RET = InitCard();
          if(RET == INITCARDSUCCESS)  //初始化卡片成功 开始读取用户信息 
          {
             //测试 
              cls();
              RET = mif_authentication(1,1,cardsn);//验证扇区密码
              if( RET != 0)
              {
                  putstr("验证扇区密码错误");
                  return 1; 
              }
              else
              {
                  RET = mif_read(5,name);
                  if( RET != 0 )
                  {
                      putstr("read name RET\n");
                  }
                  else
                  {
                      //putstr("用户名为：");
                    // putstr(name);
                    // key(0);
                     // putstr("\n");
                  }
                  RET = mif_read(6,passwd);
                  if( RET != 0)
                  {
                      putstr("read passwd error");
                      key(0);
                  }
                  else
                  { 
                     // putstr("密码：");
                     // putstr(passwd);
                    // putstr("\n");
                    // key(0);
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
                putstr("按清除键退出\n");
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

//mifare
//卡序列号
int find_mifare_ID(unsigned char* buffer){   
    unsigned char type[3] = {0};
    
    int RET = mif_request(IDLE ,type);
    
    if(RET!=0) {
       printf("\n无M1卡");
       return -1;
    }
    
    RET = mif_anticoll(0, buffer);
    
    if(RET!=0) {
       printf("\nM1卡读取序列号失败"); 
       return -2;
    }
    
   // printf("find_mifare RET:%d\n",RET);
    return 0;
}

//UL
//卡序列号
int find_UL_ID(uchar *length,char* buffer){
    int RET = (int)ULight_findcarda(0x26,length,buffer);
    
   // printf("find_UL RET:%d\n",RET);
    return RET;
}
int ReadWineNum(unsigned char* winenum)
{
    int err ;
       unsigned char keya[16]={0xff,0xff,0xff,0xff,0xff,0xff};//密码 
    uchar atq[3]={0};
    //putstr("进入readwinenum");
   // key(0); 
    err = OpenCard();
    if(err !=0)
    {
       putstr("打开读卡模块错误\n");
        key(0);
        return 1; 
    }
     err =InitCard();
     cls();
     if(err ==INITCARDSUCCESS)
     {
           // putstr("init  card success ");
           // key(0);
             err = mif_authentication(0,2,cardsn);
                       if(err == 0)
                       {   
                           //  putstr("验证密码正确 ");
                          //  key(0);
                              err = mif_read(8,winenum);
                              if(err != 0)
                              {
                                     putstr("读卡错误 ");
                                       key(0);
                                     return 1;
                              }
                              else
                              {
                                  return 0;
                              }
                       }
                       else if ( err != 0) 
                       {
                            putstr("验证密码错误 ");
                            key(0);
                            return 1; 
                       }
                     
     }

}
int readM1(uchar *length,uchar *serial_number,uchar* mybuffer){
    unsigned char mykey;
    int RET = OpenCard();
    if(RET != 0)
    {
        putstr("打开读卡模块错误\n");
        key(0);
        return -2;
    }
    RET = InitCard();
    delay(100);


    cls();
    if(RET == INITCARDSUCCESS )
    {
         
        
    RET = mif_authentication(1,1,serial_number);
     if( RET != 0)
     {
         putstr("验证密码错误");
         key(0);
         return -3; 
     }
     else
     {
         memset(serial_number,0,40);
         RET = mif_read(4,serial_number);
    
         if( RET != 0)
         {
             putstr("读取数据错误");
             key(0);
         }
         else
         {
          return 0;
          }
     }
     
        
    }
    else
    {
        
        cls();
        putstr("初始化卡错误");
        bell(40);
        putstr("无卡，请核对\n");
        putstr("按清除键退出\n");
        putstr("按其他任意键继续\n");
        mykey=key(0);
        if(mykey == KEY_CLS)
        {
                return -4;
        }
    } 
    
    RET = mif_close();
    if(RET != 0)
    {
        putstr("mif_close RET in examing\n");
        key(0);
        return -1;
    }
    delay(100);
    
    return 0;
}

int readUL(uchar *length,unsigned char *serial_number,char* buffer){
    
    int RET = -1;
    
    RET = find_UL_ID(&length,serial_number);
        
    RET = mif_read(8,buffer);
    
    int k=0;
    for(k=4;k<16;k++)
    buffer[k]=0;
    
    cls();
    //putstr("酒罐号:");
    //putstr(buffer);

    RET = mif_read(4,serial_number);


    
    return 0;
}

