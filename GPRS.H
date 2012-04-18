
#ifndef GPRS
#define GPRS
#define BASEGPRSERROR                  50

#define OPENGPRSERROR       BASEGPRSERROR+6            //打开GPRS模块错误 
#define CHECKSIMERROR       BASEGPRSERROR+7            //检查SIM卡错误 不存在SIM卡 
#define REGSTATUSERROR      BASEGPRSERROR+8            //检查模块是否注册错误 
#define GPRSSUPPORTERROR    BASEGPRSERROR+9            //检查是否支持GPRS错误 
#define CHECKSTATUSERROR    BASEGPRSERROR+10           //检查GPRS网络状态错误 
#define NETSETERROR         BASEGPRSERROR+11           //网络端口设置错误 
#define NETINITERROR        BASEGPRSERROR+12           //网络参数设置错误 
#define NETCONTERRRO        BASEGPRSERROR+13           //网络连接设置错误
#define MODESAVEERROR       BASEGPRSERROR+14           //保存网络参数错误 
#define NETCONNECTERROR     BASEGPRSERROR+15           //连接网络错误

#define INITGPRSSUCCESS     0            //打开GPRS模块成功 

#define NETTXDERROR         BASEGPRSERROR+16           //发送数据错误
#define NETRXDERROR         BASEGPRSERROR+17           //接收数据错误
#define CHECKSIGNALERROR    BASEGPRSERROR+18           //检测信号错误 
 



#define INITCANCLE              BASEGPRSERROR+ 20           //用户取消初始化 
unsigned char signal[8];
int InitGPRS(); 

void search_card(uchar *sealNo);
#endif


