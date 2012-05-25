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
     char RET;
     Initialization();
     unsigned char keya[16]={0xff,0xff,0xff,0xff,0xff,0xff};//���� 
    // cls();
     OpenCard();
   //  putstr("����Ѱ������...\n");
            RET = mif_request(IDLE ,atq);//Ѱ������ IDLEΪ����ģʽ ALL Ϊ�࿨ģʽ 
            if( RET != 0)
            {  
             return REQUESTCARDERROR;   
            }
            else
            {
               //  putstr("Ѱ������: OK\n");
            }
            
           // putstr("���ڷ�ֹ��ͻ...\n");
             RET= mif_anticoll(0,cardsn);//��ֹ��ͻ ���ؿ������к� 
            if( RET !=0)
            {
                return ANTICOLLCARDERROR; 
            }
            else
            {
              //  putstr("��ֹ��ͻ��OK\n");
            } 
           // putstr("����ѡ����...\n");
            RET = mif_select(cardsn);//ѡ���������кŵĿ� 
             if( RET !=0)
            {
                return SELECTCARDERROR;
            }
            else
            {
               // putstr("ѡ����OK\n");
            }
            
          //  putstr("װ�����뵽����...\n");
            RET = mif_load_key(keya);// ������װ���д���� 
            
             if( RET !=0)
            {
                return LOADKEYERROR;
            }
            else
            {
               // putstr("װ�����뵽������OK\n");
            } 
            return   INITCARDSUCCESS;
}

char OpenCard(){
	int RET=-1;
	Initialization();
	//cls();//�����Ļ
	//putstr("��ʼ������ģ��...\n");
	RET = mif_open();
	//printf("\nOpenCardRET:%d",RET);
	delay(3000);
	if(RET != 0 ){
		//��һ�δ򿪶���ģ��ʧ��
		delay(1000);
		return OPENCARDERROR;
	}
	// putstr("��ʼ������ģ�飺OK\n");
	return INITCARDSUCCESS;
}

char ReadUserInformation(unsigned char* name ,unsigned char * passwd)
{
     char RET;
     unsigned char mykey ;
     while(1)
     {
          RET = InitCard();
          if(RET == INITCARDSUCCESS)  //��ʼ����Ƭ�ɹ� ��ʼ��ȡ�û���Ϣ 
          {
             //���� 
              cls();
              RET = mif_authentication(1,1,cardsn);//��֤��������
              if( RET != 0)
              {
                  putstr("\n��֤�����������");
                  return 1; 
              }
              else
              {
                  RET = mif_read(5,name);
                  if( RET != 0 )
                  {
                      putstr("\n�û�����ȡ����\n");
                  }
                  else
                  {
                      //putstr("�û���Ϊ��");
                    // putstr(name);
                    // key(0);
                     // putstr("\n");
                  }
                  RET = mif_read(6,passwd);
                  if( RET != 0)
                  {
                      putstr("�����ȡ����");
                      key(0);
                  }
                  else
                  { 
                     // putstr("���룺");
                     // putstr(passwd);
                    // putstr("\n");
                    // key(0);
                  } 
                  return READUSERINFORMATIONSUCCESS;
              }
             return READUSERINFORMATIONERROR;
          }
          else
          {
                cls();
                bell(40);
                putstr("\n�޿�����˶�\n");
                putstr("��������˳�\n");
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

//mifare
//�����к�
int find_mifare_ID(unsigned char* buffer){   
    unsigned char type[3] = {0};
    
    int RET = mif_request(IDLE ,type);
    delay(3000);
    if(RET!=0) {
       printf("\n��M1��");
       return -1;
    }
    
    RET = mif_anticoll(0, buffer);
    
    if(RET!=0) {
       printf("\nM1����ȡ���к�ʧ��"); 
       return -2;
    }
    
   // printf("find_mifare RET:%d\n",RET);
    return 0;
}

//UL
//�����к�
int find_UL_ID(uchar *length,char* buffer){
    int RET = (int)ULight_findcarda(0x26,length,buffer);
    
   // printf("find_UL RET:%d\n",RET);
    return RET;
}
int ReadWineNum(unsigned char* winenum)
{
    int err ;
       unsigned char keya[16]={0xff,0xff,0xff,0xff,0xff,0xff};//���� 
    uchar atq[3]={0};
    //putstr("����readwinenum");
   // key(0); 
    err = OpenCard();
    if(err !=0)
    {
       putstr("\n�򿪶���ģ�����\n");
        key(0);
        return 1; 
    }
     err =InitCard();
     cls();
     if(err ==INITCARDSUCCESS)
     {
           // putstr("init  card success ");
           // key(0);
             err = mif_authentication(0,2,cardsn);
                       if(err == 0)
                       {   
                           //  putstr("��֤������ȷ ");
                          //  key(0);
                              err = mif_read(8,winenum);
                              if(err != 0)
                              {
                                     putstr("\n��������,�밴���������");
                                       key(0);
                                     return 1;
                              }
                              else
                              {
                                  return 0;
                              }
                       }
                       else if ( err != 0) 
                       {
                            putstr("��֤������� ");
                            key(0);
                            return 1; 
                       }
                     
     }

}
int readM1(uchar *length,uchar *serial_number,uchar* mybuffer){
    unsigned char mykey;
    int RET = OpenCard();
    if(RET != 0)
    {
        putstr("\n�򿪶���ģ�����\n");
        key(0);
        return -2;
    }
    RET = InitCard();
    delay(500);


    cls();
    if(RET == INITCARDSUCCESS )
    {
         
        
    RET = mif_authentication(1,1,serial_number);
     if( RET != 0)
     {
         putstr("\n��֤�������");
         key(0);
         return -3; 
     }
     else
     {
         memset(serial_number,0,40);
         RET = mif_read(4,serial_number);
    
         if( RET != 0)
         {
             putstr("\n��ȡ���ݴ���");
             key(0);
         }
         else
         {
          return 0;
          }
     }
     
        
    }
    else
    {
        
        cls();
        putstr("\n��ʼ��������");
        bell(40);
        putstr("�޿�����˶�\n");
        putstr("��������˳�\n");
        putstr("���������������\n");
        mykey=key(0);
        if(mykey == KEY_CLS)
        {
                return -4;
        }
    } 
    
    RET = mif_close();
    if(RET != 0)
    {
        putstr("\nmif_close RET in examing\n");
        key(0);
        return -1;
    }
    delay(500);
    
    return 0;
}

int readUL(uchar *length,unsigned char *serial_number){
    
    int RET = -1;
    
    RET = find_UL_ID(&length,serial_number);
        

    
    
    
    cls();
    //putstr("�ƹ޺�:");
    //putstr(buffer);

    RET = mif_read(4,serial_number);


    
    return 0;
}

