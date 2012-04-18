#include "Comm.h"

/****************************************************************************
函数名称: str_to_hex
函数功能: 字符串转换为十六进制
输入参数: string 字符串 cbuf 十六进制
输出参数: 无
*****************************************************************************/
void toHex(unsigned char *src,unsigned char *hex){
     while(*src!=0){
        char hex1;
        char hex2;
        int value=*src; //直接将unsigned char赋值给整型的值，系统会正动强制转换
        int v1=value/16;
        int v2=value % 16;
        
        //将商转成字母
        if (v1>=0&&v1<=9)
        hex1=(char)(48+v1);
        else
        hex1=(char)(55+v1);
        
        //将余数转成字母
        if (v2>=0&&v2<=9)
        hex2=(char)(48+v2);
        else
        hex2=(char)(55+v2);
        
        //将字母连接成串
        *hex=hex1;
        hex++;
        *hex=hex2;
        hex++;
        
        src++;
    }
}
