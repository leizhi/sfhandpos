#ifndef LOGINWAY
#define LOGINWAY
#define     LOGINBYCARD              1   //用户选择读卡登陆
#define     LOGINBYINPUT             2   //用户选择输入信息登陆 
#define     LOGINCANCLE              3   //用户选择取消退出 

#define     NETERROR                 1   //网络故障
#define     USERINFORMATIONERROR     2   //用户信息错误
#define     CHECKSUCCESS            0   //用户验证通过 
unsigned char LoginChoose();    //供用户选项登陆验证方式，返回用户选择结果  
int CheckUser(unsigned char* name ,unsigned char* passwd); 
#endif
