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
         putstr("exiting ");
         key(0);
         err =WNetIPClose("1",2000);
     }
  
}

int main()
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
           Examine();
           delay(500);
      }
    }
    CloseSystem();
    return 1;
}

