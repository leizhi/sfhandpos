#include<hspos.h>
#include "CARD.H"
#include"user.h"

void Initialization()
{
     memset(atq,0,3);
     memset(cardsn,0,20);  
     Init();
}
char InitCard()
{
     char err;
     Initialization();
     unsigned char keya[16]={0xff,0xff,0xff,0xff,0xff,0xff};//���� 
     cls();
    // OpenCard();
     putstr("����Ѱ������...\n");
            err = mif_request(IDLE ,atq);//Ѱ������ IDLEΪ����ģʽ ALL Ϊ�࿨ģʽ 
            if( err != 0)
            {  
             return REQUESTCARDERROR;   
            }
            else
            {
                 putstr("Ѱ������: OK\n");
            }
            
            putstr("���ڷ�ֹ��ͻ...\n");
             err= mif_anticoll(0,cardsn);//��ֹ��ͻ ���ؿ������к� 
            if( err !=0)
            {
                return ANTICOLLCARDERROR; 
            }
            else
            {
                putstr("��ֹ��ͻ��OK\n");
            } 
            putstr("����ѡ����...\n");
            err = mif_select(cardsn);//ѡ���������кŵĿ� 
             if( err !=0)
            {
                return SELECTCARDERROR;
            }
            else
            {
                putstr("ѡ����OK\n");
            }
            
            putstr("װ�����뵽����...\n");
            err = mif_load_key(keya);// ������װ���д���� 
            
             if( err !=0)
            {
                return LOADKEYERROR;
            }
            else
            {
                putstr("װ�����뵽������OK\n");
            } 
            return   INITCARDSUCCESS;
}
char OpenCard()
{
    char err;
    Initialization();
    cls();//�����Ļ
    putstr("��ʼ������ģ��...\n");
    int i = 0; 
    while(1)
         {
              err = mif_open();
              if(err != 0 ) 
              {
                     i++;
                     if(i>0)                    //��һ�δ򿪶���ģ��ʧ��
                     {
                             mif_close();
                             delay(10);
                             if(i>1)            //�ڶ��δ򿪶���ģ��ʧ��
                             {
                                    return OPENCARDERROR; 
                             } 
                             
                     } 
              }
              else
              {
                  break;
              }
         }
    putstr("��ʼ������ģ�飺OK\n");
    return   INITCARDSUCCESS;  
}

char ReadUserInformation(unsigned char* name ,unsigned char * passwd)
{
     char err;
     unsigned char mykey ;
     while(1)
     {
          err = InitCard();
          if(err == INITCARDSUCCESS)  //��ʼ����Ƭ�ɹ� ��ʼ��ȡ�û���Ϣ 
          {
             //���� 
              cls();
              err = mif_authentication(1,1,cardsn);//��֤��������
              if( err != 0)
              {
                  putstr("��֤�����������");
                  return 1; 
              }
              else
              {
                  err = mif_read(5,name);
                  if( err != 0 )
                  {
                      putstr("read name err\n");
                  }
                  else
                  {
                      putstr("�û���Ϊ��");
                     // putstr(name);
              
                      //putstr("\n");
                  }
                  err = mif_read(6,passwd);
                  if( err != 0)
                  {
                      putstr("read passwd error");
                  }
                  else
                  { 
                      putstr("���룺");
                     // putstr(passwd);
                     // putstr("\n");
                  } 
                  return READUSERINFORMATIONSUCCESS;
              }
             return READUSERINFORMATIONERROR;
          }
          else
          {
                cls();
                bell(40);
                putstr("�޿�����˶�\n");
                putstr("���������CLS���˳�\n");
                putstr("���������������\n");
                mykey=key(0);
               if(mykey == KEY_CLS)
                {
                        return READUSERINFORMATIONERROR;
                }
          } 
     }
     return READUSERINFORMATIONSUCCESS;
   
}
