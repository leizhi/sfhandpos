#ifndef LOGINWAY
#define LOGINWAY
#define     LOGINBYCARD              1   //�û�ѡ�������½
#define     LOGINBYINPUT             2   //�û�ѡ��������Ϣ��½ 
#define     LOGINCANCLE              3   //�û�ѡ��ȡ���˳� 

#define     NETERROR                 1   //�������
#define     USERINFORMATIONERROR     2   //�û���Ϣ����
#define     CHECKSUCCESS            0   //�û���֤ͨ�� 
unsigned char LoginChoose();    //���û�ѡ���½��֤��ʽ�������û�ѡ����  
int CheckUser(unsigned char* name ,unsigned char* passwd); 
#endif
