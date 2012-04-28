#include"Main.h" 
int InitSystem() 
{
    int gprs_err ;
    char card_err;
    gprs_err = InitGPRS();
    if(gprs_err!= 0)
    {
         return INITSYSTEMERROR;
    }
    else
    {
        card_err = OpenCard();
        if(card_err !=0)
        {
           return INITSYSTEMERROR;
        }
        else
        {
            return INITSYSTEMSUCCESS;
        }
    }
} 
void CloseSystem()
{
     int err ;
     unsigned char exit_msg[10];
     memset(exit_msg,0,10);
     exit_msg[0] = '*';
     exit_msg[1] = '3';
     exit_msg[2]= '#';
     exit_msg[3] = '\n';
     
     err = mif_close();                    //�رն���ģ�� 

     err = WNetTxd(exit_msg,4);
     
     if(err !=0)
     { 
            int k =0;
            putstr("err in exit_msg");
            key(0);
            while(1)
            {
               err = WNetTxd(exit_msg,4);
               if(err!=0)
               {
                  k++;
               }
               else
               {
                    err =WNetIPClose("1",2000);
                    break ;
               }
               if(k ==2)
               {
                    break;
               }
            }
            
     }
     else
     {
         ulong  i =3600000;
         cls();
         putstr("���ڹر��豸�����Ե�...");
         while(i)
         {
                 i--;
         } 
   cls();     
         err =WNetIPClose("1",2000);
      
     }
  
}

int main()
{
     uchar choose;
     uchar flag =0;
  cls();
         while(1)
         {    
                
         moveto(4,6);
         putstr("��ӭʹ��");
         moveto(6,4);
         putstr("��ѡ���ѯ��ʽ");
         moveto(8,1);
         putstr("�� 1 ��: ���ز�ѯ");
         moveto(10,1);
         putstr("�� 2 ��: �����ѯ");
         moveto(12,1);
         putstr("��CLS�����˳���½");

         moveto(16,1);
         putstr("��ѡ��"); 
         moveto(16,8);
             choose = key(0);
             if(choose == 0x31)
             {
                moveto (16,1);
                clsn(16,2);
                moveto(16,1);
                putstr("��ѡ��"); 
                 moveto(16,8);
                 putch(choose);
                 flag = 1;
                
             }
             else if(choose == 0x32)
             {
                    moveto (16,1);
                clsn(16,2);
                moveto(16,1);
                  putstr("��ѡ��"); 
                     moveto(16,8);
                     putch(choose);
                     flag = 2;
             }
             else if(choose == KEY_CLS)
             {
                  return 1;
              } 
              else if(choose == KEY_ENTER)
              {
                    if(flag ==1 ||flag ==2)
                    { 
                               if(flag ==1)
                             {
                               WithoutNet(); 
                               cls();
                             }
                             if(flag ==2)
                             {
                                     UsingNet();
                                     cls();
                             }
                            
                    }
                    else
                    {
                        flag =0;
                        bell(20);
                    }
              }
              else
                {
                     bell(20);
                 
                 }
         }
     
    return 1;
}
int WithoutNet()
{
    int RET=-1;
     unsigned char mykey;
     uchar winenum[16]={0};
     uchar length=0;
     cls();
     int err = OpenCard();
     if(err !=0)
     {
            putstr("�򿪶���ģ��ʧ��\n");
            putstr("�����������\n");
            key(0);
            return 1; 
     }
     else if(err ==0)
     {    
          unsigned char serial_number[32]={0};      
        unsigned char read_buf[16]={0};
         unsigned char type[2]={0};
          while(1)
          {     
                err = OpenCard();
                if (err !=0)
                {
                 putstr("�򿪶���ģ��ʧ��\n");
                  putstr("�����������\n");
                 key(0);
                  return 1; 
            }
                  RET = mif_request(IDLE ,type);
                  
                 cls();
                  
                  if(RET ==0)
                  {
                      RET=swap(type);       
                      short cardType = toShort(type);
                      if(RET ==0)
                      {
                             if(cardType==0x04)
                                    {
                                        RET = mif_anticoll(0, serial_number);
                                        if(RET!=0) 
                                        {
                                            printf("\n����ȡ���к�ʧ��"); 
                                            key(0);
                                            return -2;
                                        }
                                     //   printf("\nSN RET:%d",RET);
                                       // key(0);
                                        
                                        memset(read_buf,0,16);
                                        RET = readM1(&length,serial_number,read_buf);
                                        
                                        if(RET == 0)
                                        {
                                                cls();
                                                RET = ReadWineNum(winenum);
                                                if(RET == 0)
                                                {
                                                       moveto(4,1);
                                                   putstr("�ƹ޺�:");
                                                 putstr(winenum);
                                                 putstr("\n");
                                                 moveto(6,1); 
                                               putstr("��α�룺");
                                               putstr(serial_number);
                                               printf("\n");
                                                 key(0); 
                                                 return 0;
                                                 }
                                                 else
                                                 {
                                                     putstr("���ƹ޺ų���\n");
                                                     key(0);
                                                 }
                                               
                                               
                                        }
                                        else
                                        {
                                            putstr("read m1 err\n");
                                        }
                                        
                                    }
                                    else if(cardType==0x44)
                                    {
                                           RET = readUL(&length,serial_number,read_buf);
                                           
                                            moveto(4,1);
                                                   putstr("�ƹ޺�:");
                                                 putstr(read_buf);
                                                 putstr("\n");
                                                 moveto(6,1); 
                                               putstr("��α�룺");
                                               putstr(serial_number);
                                               printf("\n");
                                                 key(0); 
                                           return 0;
   
                                    } 
                      } 
                  }
                  else
                  {
                            cls();
                             putstr("Ѱ��ʧ��\n");
                             bell(20);
                     	    putstr("���������CLS���˳�\n");
                			putstr("���������������\n");
                			uchar mykey = key(0);
                    		if(mykey == KEY_CLS)
                    		 {
                    		   return 0;
                    		 }
                  }
    
          }
     }

     
}
int UsingNet()
{
    
     int err=0 ;
    int login_num =0;
    bell(20);
    err = InitSystem();
    if( err != 0)
    {
        cls();
        bell(20);
        putstr("��ʼ��ϵͳ����\n");
        bell(50);
        putstr("��������˳�");
        key(0);
        CloseSystem();
        return 1; 
    }
    else
    {
        while(1)
        {
            bell(20);
         err = LoginChoose();
                if(err == 1)
                {
                        cls();
                        putstr("ˢ����½");
                        err = ReadUserInformation(username,password);
                        if(err != 0) //�޿��˳� 
                        {
                              return 1;
                        }
                        cls();
                }
                if(err ==2) 
                    {
                        cls();
                        putstr("�����½");
                        GetUserInformation();
                }
                if(err == 3)
               { 
                        cls();
                        putstr("�˳�");
                        CloseSystem();
                       // key(0);
                        WmodeClose();
                        return 1;
               }
           //��֤�û���Ϣ
                err = CheckUser(username,password);
                if(err == 0)
                {
                       putstr("�û��Ϸ�\n");
                     break;
                }
                else
                {
                    putstr("�û��Ƿ�");
                    key(0);
                    login_num++;
                    if(login_num==4)
                    {
                      //���������û� 
                      CloseSystem();
                        return 1;
                     
                    }
                    else
                    {
                      continue;
                    }
                    
                 }     
        }
    }
    
    unsigned char choose_value;
    while(1)
    {
      
      choose_value = MenuChoose();
      if(choose_value == CLS)
      {
        break;
      }
      else if(choose_value == VIEW)
      {
           putstr("���ڲ�ѯ���Ե�\n");
           Examine();
           delay(500);
      }
    }
    CloseSystem();
    //key(0);
    WmodeClose();
    return 1;
}

