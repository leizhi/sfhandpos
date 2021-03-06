#include "hspos.h"
#include "gprs_api.h"
#include "LoginWay.h" 
#include "GPRS.h"
#include "string.h"
#include "User.h"

unsigned char LoginChoose(){
	int RET=-1 ;
	unsigned char key_value;
	unsigned char choose;

	memset(username,0,20);
	memset(password,0,20);

	cls();
	while(1){
		moveto(4,6);
		putstr("欢迎使用");
		moveto(6,4);
		putstr("请选择登陆方式");
		moveto(8,1);
		putstr("【 1 】: 刷卡登陆");
		moveto(10,1);
		putstr("【 2 】: 输入登陆");
		moveto(12,1);
		putstr("【清除】：退出登陆");

		moveto(16,1);
		putstr("请选择");

		key_value = key(0);

		if(key_value == KEY_CLS){
			return -1;
		}else if((key_value == 0x31)||(key_value == 0x32)){
			choose = key_value;
			moveto(16,8);
			putch(choose);
		}else if(key_value == KEY_ENTER){
			if(choose == 0x31){
				cls();
				putstr("\n刷卡登陆");
				RET = ReadUserInformation(username,password);
				if(RET != 0){ //无卡循环等待
					cls(); 
					continue;
				}
				//验证用户信息
				RET = CheckUser(username,password);
				if(RET==0) return 0;
			}

			if(choose ==0x32) {
				cls();
				putstr("输入登陆");
				GetUserInformation();
			}
			cls();
		}
	}
} 

int CheckUser(unsigned char* name ,unsigned char* passwd)
{
    int RET ;
    int name_length=0;
    int passwd_length=0;
    int i=0;
    putstr("\n正在验证信息，请稍等...\n");
    while(1)
    {
       if((name[i] == 0x20)||(name[i]==0x00))
       {
                   break;
       }
      name_length++;
      i++;
    } 
    i =0;
    while(1)
    {
        if((passwd[i]==0x20)||(passwd[i]==0x00 ))
        {
           break;
        }
        else
        {
            passwd_length++;
            i++;
        }
    }
    /*
    uchar n_l[20];
    uchar p_l[20];
    itos(name_length,n_l);
    itos(passwd_length,p_l);
    */
    if(RET ==0)
    {
           putstr("InitGPRS success\n");
    }
     ////////////////////
     unsigned char send_buffer[100];
     memset(send_buffer,0,100);
     int len=0;
  
       send_buffer[len]= '*';
       len++;
       send_buffer[len]='1';
       len++;
       send_buffer[len]=',';
       len++;
       
       int m=0;
       for(;m<name_length;m++)
       {
          send_buffer[len]=name[m];
          len++;
       }
       //putstr("完成用户名封装\n");
       send_buffer[len]=',';
       len++;
       m=0;
       for(;m<passwd_length;m++)
       {
           send_buffer[len]=passwd[m];
           len++;
       }
       //putstr("完成密码封装\n");
      // key(0);      
       send_buffer[len]='#';
       len++;
       send_buffer[len]='\n';
       len++;
       //putstr(send_buffer);
      // key(0);
     
       int num =0;//尝试发送次数
       while(1)
       { 
           RET= WNetTxd(send_buffer,len);
           delay(2000);
           if(RET !=0 )
           {
                  num++;
                  putstr("发送数据错误\n");
                  if(num == 3)
                  {
                          return NETERROR;
                  }
                  putstr("正在尝试再次发送");
           }
           else
           {
               break;
           }
       }
     
	//接收验证信息 
	unsigned char recv_buffer[3000];
	memset(recv_buffer,0,3000);
	unsigned short recv_len;
	RET = WNetRxd(recv_buffer,&recv_len,10000);
	delay(2000);
	if(RET != 0){
		putstr("接收错误");
		key(0); 
		return NETERROR;
	}else{
		//判断返回信息 
		// putstr("接收数据为：");
		unsigned char login='N';
		int count = strlen(recv_buffer);

		printf("count:%d",count);
		if(count<3){
			putstr("网络通信错误\n");
			key(0);
			return NETERROR;
		}

		login=recv_buffer[1];

		if(login=='0'){
			return CHECKSUCCESS;
		}else{
			putstr("用户名或密码错误\n");
			key(0);
			return NETERROR;
		}
	}
 //   return  CHECKSUCCESS;
}
