
#ifndef GPRS
#define GPRS
#define BASEGPRSERROR                  50

#define OPENGPRSERROR       BASEGPRSERROR+6            //��GPRSģ����� 
#define CHECKSIMERROR       BASEGPRSERROR+7            //���SIM������ ������SIM�� 
#define REGSTATUSERROR      BASEGPRSERROR+8            //���ģ���Ƿ�ע����� 
#define GPRSSUPPORTERROR    BASEGPRSERROR+9            //����Ƿ�֧��GPRS���� 
#define CHECKSTATUSERROR    BASEGPRSERROR+10           //���GPRS����״̬���� 
#define NETSETERROR         BASEGPRSERROR+11           //����˿����ô��� 
#define NETINITERROR        BASEGPRSERROR+12           //����������ô��� 
#define NETCONTERRRO        BASEGPRSERROR+13           //�����������ô���
#define MODESAVEERROR       BASEGPRSERROR+14           //��������������� 
#define NETCONNECTERROR     BASEGPRSERROR+15           //�����������

#define INITGPRSSUCCESS     0            //��GPRSģ��ɹ� 

#define NETTXDERROR         BASEGPRSERROR+16           //�������ݴ���
#define NETRXDERROR         BASEGPRSERROR+17           //�������ݴ���
#define CHECKSIGNALERROR    BASEGPRSERROR+18           //����źŴ��� 
 



#define INITCANCLE              BASEGPRSERROR+ 20           //�û�ȡ����ʼ�� 
unsigned char signal[8];
int InitGPRS(); 

int search_card(uchar *sealNo);
#endif


