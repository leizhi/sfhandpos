#include<hspos.h>

#ifndef NETSETTING
#define NETSETTING

#define           IP_LENGTH                 16
#define           PORT_LENGTH               5
#define           IP_ADDRESS                0X40
#define           PORT_ADDRESS              0X30
#define           IP                        "122.225.88.87"   //初始化IP 
#define           PORT                      "8000"            //初始化PORT 

unsigned char NET_IP[IP_LENGTH];            //用来存储修改后的IP 
unsigned char NET_PORT[PORT_LENGTH];        //用来存储修改后的PORT 

int GetIP(unsigned char* s);                //获取IP值 
int GetPort(unsigned char* s);              //获取port值
int SetIP(unsigned char* s);                //设置IP值
int SetPort(unsigned char* s);              //设置port值
int InitNetSetting();
#endif


