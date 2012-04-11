#include "NetSetting.h"

/**************************************************** 
*�� �� ���� InitNetSetting
*��ڲ����� �� 
*�� �� ֵ�� int
*����˵������ʼ��IP��PORT��EEROM�У��ɹ�����0 ʧ�� ���� 
****************************************************/ 
//�޸ķ��򣬶�ȡĳλ���жϵ�ַ�Ƿ��޸Ĺ� û��������д��  �����µ�ֵд����Ӧ��ַ ���޸� 
int InitNetSetting()
{
    int ip_err;
    int port_err; 
     memset(NET_IP,0,IP_LENGTH);
     memset(NET_PORT,0,PORT_LENGTH);
     strcpy(NET_IP,IP);
     strcpy(NET_PORT,PORT); 
     return 0;  
     //ip_err = EEROM_write(IP_ADDRESS,IP_LENGTH,NET_IP);
    // port_err = EEROM_write(PORT_ADDRESS,PORT_LENGTH,NET_PORT);
     //return (ip_err || port_err);
}
/**************************************************** 
*�� �� ���� GetIP
*��ڲ����� unsgined char*
*�� �� ֵ�� int
*����˵������ȡEEROM�е�IPֵ������ֵΪ0�ɹ���
*����ʧ�ܣ����ؽ���������ڲ����� 
****************************************************/ 
int GetIP(unsigned char* s)
{
    return EEROM_read(IP_ADDRESS,IP_LENGTH,s);
} 
/**************************************************** 
*�� �� ���� GetPort 
*��ڲ����� unsgined char*
*�� �� ֵ�� int
*����˵������ȡEEROM�е�Portֵ������ֵΪ0�ɹ���
*����ʧ�ܣ����ؽ���������ڲ����� 
****************************************************/ 
int GetPort(unsigned char* s)
{
    return EEROM_read(PORT_ADDRESS,PORT_LENGTH,s);
}
/**************************************************** 
*�� �� ���� SetIP 
*��ڲ����� unsgined char*
*�� �� ֵ�� int
*����˵����д��ڲ�����EEROM�У�����ֵΪ0�ɹ� ����ʧ�� 
****************************************************/ 
int SetIP(unsigned char* s)
{
    return EEROM_write(IP_ADDRESS,IP_LENGTH,s);
}
/**************************************************** 
*�� �� ���� SetPort 
*��ڲ����� unsgined char*
*�� �� ֵ�� int
*����˵����д��ڲ�����EEROM�У�����ֵΪ0�ɹ� ����ʧ�� 
****************************************************/ 
int SetPort(unsigned char* s)
{
    return EEROM_write(PORT_ADDRESS,PORT_LENGTH,s);
}


