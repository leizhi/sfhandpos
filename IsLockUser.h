#ifndef ISLOCKUSER
#define ISLOCKUSER
#define           ISLOCK            0
#define           UNLOCK            1  
unsigned char lock_user_num;        //记录锁住的用户数
unsigned char IsLock(unsigned char* name, unsigned char* passwd);  //判断给定用户是否被锁住，是返回0 不是返回非零 
#endif
