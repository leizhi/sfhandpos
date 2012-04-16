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
     err = mif_close();                    //�رն���ģ�� 
     err = WmodeClose();                   //�ر�GPRSģ�� 
} 
int main()
{
    int err=0 ;
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
        return 1; 
    }
    else
    {
                
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
                        //putstr(username);
                        //putstr("\n");
                        //putstr(password);
                        //key(0);
                        
                 
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
                        key(0);
                        return 1;
               }
    }
    //�ж��Ƿ��������û�
    // ��ʱû�����ģ��
    
    //��֤�û���Ϣ
    err = CheckUser(username,password);
   // err = CHECKSUCCESS;
    printf("err is %d",err);
    putstr("��֤�ɹ�\n");
    key(0); 
    if(err == CHECKSUCCESS)
    {
           putstr("�û��Ϸ�\n");
    }
    else
    {
        putstr("�û��Ƿ�");
        //�˳�����
      //  CloseSystem(); 
         
    } 
    
    putstr("��ѯ\n"); 
    key(0);
    
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
      }
    }
    key(0);
    return 1;
}

