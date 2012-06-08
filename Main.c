#include "Main.h" 

int InitSystem(){
	int RET=-1;

	RET = InitGPRS();
	if(RET!= 0){
		return INITSYSTEMERROR;
	}

	RET = OpenCard();
	if(RET!=0){
		return INITSYSTEMERROR;
	}

	return INITSYSTEMSUCCESS;
}

void CloseSystem(){
	int RET=-1 ;

	cls();
	RET = mif_close();	//关闭读卡模块
	delay(2000);
	
	char exit_msg[2]={0};
	//memset(exit_msg,0,100);
	
	exit_msg[0]='3';
	exit_msg[1]='\n';
	//exit_msg[2]='#';
	//exit_msg[3]='\n';
	//key(0);
	
	RET = WNetTxd(exit_msg,strlen(exit_msg));

	cls();
	putstr("正在退出系统");

	delay(36000000);

	if(RET !=0) {
		moveto(8,3);
		putstr("\n关闭系统错误!");
		key(0);
		
		int k =0;
		for(k=0;k<2;k++){
			RET = WNetTxd(exit_msg,strlen(exit_msg));
			delay(2400);
			if(RET ==0) break ;
		}
	}

	RET =WNetIPClose("1",2000);
	delay(2400);

	RET =WmodeClose();
	delay(2400);
}

int main(){
	unsigned char action =0;
	int flag=0;
	cls();
	while(1){
		moveto(4,6);
		putstr("欢迎使用");
		moveto(6,4);
		putstr("请选择查询方式");
		moveto(8,1);
		putstr("【 1 】: 本地查询");
		moveto(10,1);
		putstr("【 2 】: 网络查询");
		moveto(12,1);
		putstr("【清除】：退出登陆");

		moveto(16,1);
		putstr("请选择");
		
		action=key(0);
		if(action==0x31){
			moveto(16,8);
			putch(action);
			flag=1;
		}else if(action==0x32){
			moveto(16,8);
			putch(action);
			flag=2;
		}else if(action==KEY_CLS){
			return 0;
		}else if((action == KEY_ENTER)&&(flag!=0)){
			if(flag==1){
				if(WithoutNet()!=0)
					continue;
			} else if(flag==2){
				UsingNet();
				cls();
			}else{
				bell(20);
				continue;
			}
		}else{
			bell(20);
			continue;
		}
	}
	return 0;
}

int WithoutNet(){
	int RET=-1;

	unsigned char winenum[16]={0};
	unsigned char length=0;

	unsigned char serial_number[32]={0};
	unsigned char read_buf[16]={0};
	unsigned char type[2]={0};
	while(1) {
		RET = OpenCard();
		delay(3000);
		if (RET !=0){
			putstr("\n打开读卡模块失败\n");
			putstr("按任意键返回\n");
			key(0);
			return -1;
		}
		RET = mif_request(IDLE ,type);
		delay(2000);
		//printf("\mif_request RET:%d",RET); 
		//key(0);
		if (RET !=0){
			cls();
			putstr("\n寻卡失败\n");
			putstr("按任意键返回\n");
			bell(20);
			key(0);
			cls();
			return -2;
		}

		//start read
		cls();
		RET=swap(type);
		short cardType = toShort(type);
		//printf("\RET:%d",RET); 
		//printf("\ncardType:%d",cardType); 
		//key(0);
		if (RET !=0){
			cls();
			putstr("\n此卡协议不支持\n");
			putstr("按任意键返回\n");
			bell(20);
			key(0);
			return -3;
		}
		//read card for type
		if(cardType==0x04){
			RET = mif_anticoll(0, serial_number);
			if(RET!=0) {
				printf("\n卡读取序列号失败"); 
				key(0);
				return -4;
			}

			memset(read_buf,0,16);
			RET = readM1(&length,serial_number,read_buf);

			if(RET == 0){
				cls();
				RET = ReadWineNum(winenum);
				if (RET !=0){
					putstr("\n读标识号出错\n");
					key(0);
					cls();
					return -5;
				}
				putstr("\n标识号:\n");
				putstr(winenum);
				putstr("\n");
				//moveto(6,1); 
				//putstr("防伪码：");
				//putstr(serial_number);
				//printf("\n");
				key(0); 
				cls();
				return 0;
			}else{
				putstr("read m1 RET\n");
			}
		}else if(cardType==0x44){
			memset(read_buf,0,16);
			RET = readUL(&length,serial_number);
			if (RET !=0){
				putstr("\n读标识号出错\n");
				key(0);
				cls();
				return -6;
			}
			putstr("\n标识号:\n");
			putstr(serial_number);
			putstr("\n");
			
			//moveto(6,1); 
			//putstr("防伪码：");
			//putstr(serial_number);
			//printf("\n");
			key(0); 
			cls();
			return 0;
		}
	}//end while
}

int UsingNet(){
	int RET=0 ;
	int login_num =0;

	bell(20);
	if((RET=InitSystem())!=0){
		cls();
		bell(20);
		putstr("\n初始化系统出错！\n");
		bell(50);

		CloseSystem();
		return -1; 
	}

	//用户登录
	bell(20);
	if((RET=LoginChoose())!=0){
		CloseSystem();
		return -2;
	}


	//巡检
	bell(20);
	if((RET=MenuChoose())!=0){
		CloseSystem();
		return -3;
	}

	CloseSystem();
	return 0;
}

