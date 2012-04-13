#include "NetSetting.h"

/**************************************************** 
*函 数 名： InitNetSetting
*入口参数： 无 
*返 回 值： int
*函数说明：初始化IP和PORT到EEROM中，成功返回0 失败 非零 
****************************************************/ 
//修改方向，读取某位后判断地址是否修改过 没有则不重新写入  否则将新的值写入相应地址 待修改 
int InitNetSetting()
{
    //int ip_err;
   // int port_err; 
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
*函 数 名： GetIP
*入口参数： unsgined char*
*返 回 值： int
*函数说明：获取EEROM中的IP值，返回值为0成功，
*非零失败，返回结果存放在入口参数中 
****************************************************/ 
int GetIP(unsigned char* s)
{
    return EEROM_read(IP_ADDRESS,IP_LENGTH,s);
} 
/**************************************************** 
*函 数 名： GetPort 
*入口参数： unsgined char*
*返 回 值： int
*函数说明：获取EEROM中的Port值，返回值为0成功，
*非零失败，返回结果存放在入口参数中 
****************************************************/ 
int GetPort(unsigned char* s)
{
    return EEROM_read(PORT_ADDRESS,PORT_LENGTH,s);
}
/**************************************************** 
*函 数 名： SetIP 
*入口参数： unsgined char*
*返 回 值： int
*函数说明：写入口参数到EEROM中，返回值为0成功 非零失败 
****************************************************/ 
int SetIP(unsigned char* s)
{
    return EEROM_write(IP_ADDRESS,IP_LENGTH,s);
}
/**************************************************** 
*函 数 名： SetPort 
*入口参数： unsgined char*
*返 回 值： int
*函数说明：写入口参数到EEROM中，返回值为0成功 非零失败 
****************************************************/ 
int SetPort(unsigned char* s)
{
    return EEROM_write(PORT_ADDRESS,PORT_LENGTH,s);
}


