#ifndef ISLOCKUSER
#define ISLOCKUSER
#define           ISLOCK            0
#define           UNLOCK            1  
unsigned char lock_user_num;        //��¼��ס���û���
unsigned char IsLock(unsigned char* name, unsigned char* passwd);  //�жϸ����û��Ƿ���ס���Ƿ���0 ���Ƿ��ط��� 
#endif
