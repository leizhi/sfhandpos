#ifndef LOGINWAY
#define LOGINWAY

#define     NETERROR                 1   //网络故障
#define     USERINFORMATIONERROR     2   //用户信息错误
#define     CHECKSUCCESS            0   //用户验证通过 

unsigned char LoginChoose();    //供用户选项登陆验证方式，返回用户选择结果  
int CheckUser(unsigned char* name ,unsigned char* passwd); 
#endif
