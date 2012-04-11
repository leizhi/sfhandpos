#include<hspos.h>

#ifndef NETSETTING
#define NETSETTING

#define           IP_LENGTH                 16
#define           PORT_LENGTH               5
#define           IP_ADDRESS                0X40
#define           PORT_ADDRESS              0X30
#define           IP                        "122.225.88.87"   //��ʼ��IP 
#define           PORT                      "9315"            //��ʼ��PORT 

unsigned char NET_IP[IP_LENGTH];            //�����洢�޸ĺ��IP 
unsigned char NET_PORT[PORT_LENGTH];        //�����洢�޸ĺ��PORT 

int GetIP(unsigned char* s);                //��ȡIPֵ 
int GetPort(unsigned char* s);              //��ȡportֵ
int SetIP(unsigned char* s);                //����IPֵ
int SetPort(unsigned char* s);              //����portֵ
int InitNetSetting();
#endif


