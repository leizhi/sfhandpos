#ifndef LOGINWAY
#define LOGINWAY

#define     NETERROR                 1   //�������
#define     USERINFORMATIONERROR     2   //�û���Ϣ����
#define     CHECKSUCCESS            0   //�û���֤ͨ�� 

unsigned char LoginChoose();    //���û�ѡ���½��֤��ʽ�������û�ѡ����  
int CheckUser(unsigned char* name ,unsigned char* passwd); 
#endif
