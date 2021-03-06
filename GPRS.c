#include <hspos.h>
#include<gprs_api.h>
#include"GPRS.H"
#include"CARD.H"
#include"NetSetting.h"
#include"display.h"
/***********************
*函数名：InitGPRS 
*功  能：初始化GPRS模块 
*参  数：无
*返回值：int  
***********************/
int InitGPRS()
{
    int RET; 
    int i = 0; 
    unsigned char key_value;

  cls();
  WmodeClose();
  InitNetSetting();
 /* putstr(NET_IP);
  putstr(NET_PORT);
  key(0);
  */
  putstr("\n初始化，请稍候...\n");
  putstr("正在打开GPRS模块\n");
  while(1)
   { 
       key_value = keygo();
       if(key_value == KEY_CLS)
       {
            return INITCANCLE;
       }
       
       RET=WmodeOpen();
       if(RET!=0)
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
   
       RET=WmodeCheckSIM();
       if(RET==0)
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
    RET = WmodeREGStatus(s);//参数s无意义  检查GPRS模块是否注册 
    if(RET != 0)
    {
           return REGSTATUSERROR; 
    }
    else
    {
        putstr("模块注册：OK\n");
    }
    
    putstr("检测模块是否支持GPRS\n");
    RET = WmodeCheckGPRSSupport();//检查是否支持GPRS
    if(RET != 0)
    {
           return GPRSSUPPORTERROR; 
    } 
    else
    {
        putstr("支持GPRS：OK\n");
    } 
    delay(10000);
    cls();
    putstr("\n检测GPRS网络状态\n");
    RET = WmodeCheckGPRSstatus(s);//检查GPRS网络状态
     if( RET !=0)
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
    RET=WmodeCheckSignal(ss);
     if( RET !=0)
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
    RET=WNetSeting("2","5001",NET_IP,NET_PORT);//网络端口设置 
    if(RET != 0)
    {
           return NETSETERROR;
    }
    else
    {
        putstr("网络IP和端口设置：OK\n");
    } 
    
    putstr("正在设置网络参数...");
    RET = WNetInit("512","6000","6000","6000");//设置网络参数 
    if(RET !=0 )
    {
           return NETINITERROR;
    } 
    else
    {
        putstr("网络参数设置: OK\n");
    } 
    delay(10000);
    cls(); 
    putstr("\n正在设置网络连接...\n");
    RET =   WNetCont("1","IP","CMNET","0,0");     //网络连接设置
    if( RET != 0)
    {
        return NETCONTERRRO;
    } 
    else
    {
        putstr("设置网络连接: OK\n"); 
    }
    putstr("正在保存网络参数...\n");
    RET = WmodeSave();                  //保存网络参数
    if( RET != 0 )
    {
        return MODESAVEERROR;
    } 
    else
    {
        putstr("保存网络参数：OK");
    }
   
    RET =WNetConnect(20000); //连接网络
    if( RET !=0)
    {   
        cls(); 
        putstr("\n网络出现故障，请检查");
        key(0);
        return NETCONNECTERROR;
    } 
   else
    {
        putstr("\n网络连接成功");
         return INITGPRSSUCCESS;  
    } 
    
     
}

int search_card(uchar *sealNo){
	unsigned char send_buffer[100]={0};
	unsigned char *p=send_buffer;

	int sealNo_length;
	int k;
	int RET=-1;

	memset(send_buffer,0,100);
	sealNo_length=0;

	//发送数据到服务器
	// printf("send buffer:%s\n",send_buffer);

	*p='*';
	p++;

	*p='2';
	p++;

	*p=',';
	p++;

	while(*sealNo!=0x00){
		if(*sealNo== 0x00) {
			moveto(8,3);
			putstr("查询卡错误"); 
			break;
		}

		*p=*sealNo;

		p++;
		sealNo++;
	}


	*p = '#';
	p++;
	*p='\n';
	//putstr("完成封装发送数据\n");  
	p=send_buffer;
	k=0;
	while(*p!=0){
		p++;
		k++;
	}

	// printf("k:%d",k);
	// key(0);

	unsigned char send_num =0;
	while(send_num<2){ 
		cls();
		// putstr("\nend_buffer:");
		// putstr(send_buffer);
		RET = WNetTxd(send_buffer,k);
		delay(2000);
		//printf("\nsender_buffer_error:%d",RET);
		//key(0);

		if( RET == 0){
			//putstr("\n发送数据成功\n");
			break; 
		}else{
			cls();
			putstr("\n发送失败，再次尝试发送\n");
			key(0);
			send_num++;
		}
	}

	if(send_num ==2){
		putstr("发送数据两次错误\n");
		key(0);
		return ;
	}

	//然后接受返回信息 
	unsigned char recv_buffer[3000];
	memset(recv_buffer,0,3000);
	unsigned short recv_len;
	unsigned char delimiter=',';
	unsigned char query_buffer[3000];
	memset(query_buffer,0,3000);
	int blo;
	myStr pStr;
	unsigned char buffer[2048]={0};
	
	putstr("\n准备接收数据，请稍等...\n");
	RET = WNetRxd(recv_buffer,&recv_len,10000);
	delay(2000);
	//putstr("接收数据完成\n");
	//printf("\nrecv_len:%d",recv_len);
	//putstr(recv_buffer);
	//printf("\nRET:%d",RET);

	if(RET != 0){
		cls();
		putstr("\n接收数据错误，请按任意键返回！\n");
		key(0);
		return ;
	}

	cls();
	char result='N';
	int count = strlen(recv_buffer);

	if(count<5){
		putstr("网络通信错误\n");
		key(0);
		return ;
	}

	result=recv_buffer[1];
	if(result=='0'){
		//putstr("\n查询成功，请按任意键继续！");
		int i=0;
		for(i=5;i<count-1;i++){
			buffer[i-5]=recv_buffer[i];
		}

		pStr=cutting(buffer,delimiter);
		blo = block(buffer,delimiter);
		RET=printSC(pStr,blo);
		//key(0);
	}else if(result=='1'){
		int i=0;
		for(i=3;i<count-1;i++){
			buffer[i-5]=recv_buffer[i];
		}

		pStr=cutting(buffer,delimiter);
		blo = block(buffer,delimiter);
		printSC(pStr,blo);
		//key(0);
	}else{
		moveto(8,3);
		putstr("查询无该记录！");
		key(0);
	}
	return 0;
}
