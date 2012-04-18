
#ifndef CARD
#define CARD
#define         BASECARDEROR            100    
#define OPENCARDERROR                  BASECARDEROR+1            //打开读卡模块错误 
#define REQUESTCARDERROR               BASECARDEROR+2            //请求卡错误
#define ANTICOLLCARDERROR              BASECARDEROR+3            //检测冲突错误
#define SELECTCARDERROR                BASECARDEROR+4            //选择卡错误
#define LOADKEYERROR                   BASECARDEROR+5            //装载密码错误 
 
#define INITCARDSUCCESS                0            //打开读卡模块成功 
#define READUSERINFORMATIONSUCCESS     0            //读取用户信息成功 

#define BASEUSERERROR                  1
#define READUSERINFORMATIONERROR        BASEUSERERROR+1;

unsigned char atq[3];//用来存储卡类型
unsigned char cardsn[20];//存储卡序列号 
char OpenCard();
char InitCard();
void Initialization();
char ReadUserInformation(unsigned char* name ,unsigned char * passwd);

/*
操作UL 
*/
int find_mifare_ID(unsigned char* buffer);

int find_UL_ID(uchar *length,char* buffer);

int readM1(uchar *length,uchar *cardnum,char* buffer);

int readUL(uchar *length,unsigned char *serial_number,char* buffer);

#endif
