
#ifndef CARD
#define CARD
#define         BASECARDEROR            100    
#define OPENCARDERROR                  BASECARDEROR+1            //�򿪶���ģ����� 
#define REQUESTCARDERROR               BASECARDEROR+2            //���󿨴���
#define ANTICOLLCARDERROR              BASECARDEROR+3            //����ͻ����
#define SELECTCARDERROR                BASECARDEROR+4            //ѡ�񿨴���
#define LOADKEYERROR                   BASECARDEROR+5            //װ��������� 
 
#define INITCARDSUCCESS                0            //�򿪶���ģ��ɹ� 
#define READUSERINFORMATIONSUCCESS     0            //��ȡ�û���Ϣ�ɹ� 

#define BASEUSERERROR                  1
#define READUSERINFORMATIONERROR        BASEUSERERROR+1;

unsigned char atq[3];//�����洢������
unsigned char cardsn[20];//�洢�����к� 
char OpenCard();
char InitCard();
void Initialization();
char ReadUserInformation(unsigned char* name ,unsigned char * passwd);
int ReadWineNum(unsigned char* winenum);
/*
����UL 
*/
int find_mifare_ID(unsigned char* buffer);

int find_UL_ID(uchar *length,char* buffer);

int readM1(uchar *length,uchar *cardnum,uchar* buffer);

int readUL(uchar *length,unsigned char *serial_number);

#endif
