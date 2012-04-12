#include <hspos.h>
#include<gprs_api.h>
#include"GPRS.H"
#include"NetSetting.h"
/***********************
*函数名：InitGPRS 
*功  能：初始化GPRS模块 
*参  数：无
*返回值：int  
***********************/
int InitGPRS()
{
    int err; 
    int i = 0; 
    unsigned char key_value;

  cls();
  InitNetSetting();
 /* putstr(NET_IP);
  putstr(NET_PORT);
  key(0);
  */
  putstr("初始化,请稍候...\n");
  putstr("正在打开GPRS模块\n");
  while(1)
   { 
       key_value = keygo();
       if(key_value == KEY_CLS)
       {
            return INITCANCLE;
       }
       
       err=WmodeOpen();
       if(err!=0)
       { 	
     		i++;
     		if(i>0)                    //第一次打开失败，关闭模块 
     		{
                 WmodeClose();
                 delay(200);
                 if(i>2)               //第二次打开失败，退出 
                 {
                  return OPENGPRSERROR;
                 } 	
     		}	
       }
       else
       {   
       		break;	
       }		  
	}
 putstr("打开GPRS模块：OK\n");		
 putstr("正在检测SIM卡\n");
 i =0;
  while(1) 
  {
   
       err=WmodeCheckSIM();
       if(err==0)
       {
       		putstr("检测SIM卡：ok\n");
       		break;
       }		
       else
       {	
       		 delay(1000);
       		 i++;
   		 	if(i==5)
        	{
        		return CHECKSIMERROR;	
        	}
       }
	}

    
    unsigned char s[2];
    putstr("检查模块是否注册\n");
    err = WmodeREGStatus(s);//参数s无意义  检查GPRS模块是否注册 
    if(err != 0)
    {
           return REGSTATUSERROR; 
    }
    else
    {
        putstr("模块注册：OK\n");
    }
    
    putstr("检测模块是否支持GPRS\n");
    err = WmodeCheckGPRSSupport();//检查是否支持GPRS
    if(err != 0)
    {
           return GPRSSUPPORTERROR; 
    } 
    else
    {
        putstr("支持GPRS：OK\n");
    } 
    delay(10000);
    cls();
    putstr("检测GPRS网络状态\n");
    err = WmodeCheckGPRSstatus(s);//检查GPRS网络状态
     if( err !=0)
    {
        return CHECKSTATUSERROR;
    }
    else
    {
        putstr("GPRS网络状态:OK\n");
    }
    
    putstr("检测信号强度...\n");
    unsigned char ss[10];
    memset(ss,0,10);
    err=WmodeCheckSignal(ss);
     if( err !=0)
    {
        return CHECKSIGNALERROR;
    }
    else
    {
        putstr("信号强度为：");
        putstr(ss);
        putstr("\n");
        //低于10 提示用户信号弱
         
    }
    putstr("正在设置网络IP和端口...\n") ;
    err=WNetSeting("2","5001",NET_IP,NET_PORT);//网络端口设置 
    if(err != 0)
    {
           return NETSETERROR;
    }
    else
    {
        putstr("网络IP和端口设置：OK\n");
    } 
    
    putstr("正在设置网络参数...");
    err = WNetInit("512","6000","6000","6000");//设置网络参数 
    if(err !=0 )
    {
           return NETINITERROR;
    } 
    else
    {
        putstr("网络参数设置: OK\n");
    } 
    delay(10000);
    cls(); 
    putstr("正在设置网络连接...\n");
    err =   WNetCont("1","IP","CMNET","0,0");     //网络连接设置
    if( err != 0)
    {
        return NETCONTERRRO;
    } 
    else
    {
        putstr("设置网络连接: OK\n"); 
    }
    putstr("正在保存网络参数...\n");
    err = WmodeSave();                  //保存网络参数
    if( err != 0 )
    {
        return MODESAVEERROR;
    } 
    else
    {
        putstr("保存网络参数：OK");
    }
    /*
    err =WNetConnect(20000); //连接网络
    if( err !=0)
    {   
        cls(); 
        putstr("\n 网络出现故障 请检查");
        key(0);
        return NETCONNECTERROR;
    } 
    else
    {
        putstr("\n网络连接成功");
    } 
    */
    return INITGPRSSUCCESS;    
}
