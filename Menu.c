#include"Menu.H"
#include "CARD.H"
#include "User.H"
unsigned char  MenuChoose()
{
     unsigned char key_value; 
     unsigned char flag =0;
       cls();
       
     while(1)
     {
         moveto(4,2);
         putstr("��ӭ����");
         putstr(username); 
         moveto(6,4);
         putstr("��ѡ�����������");
         moveto(8,1);
         putstr("�� 1 ��: Ѳ��");
         moveto(10,1);
         putstr("��CLS�����˳���½");
        
         moveto(14,1);
         putstr("��ѡ��");
         key_value = key(0);
         
         if(key_value == KEY_CLS)
         {
               cls();
             return CLS;
         }
         else if(key_value == 0x31)
         {
            flag = 1;
            moveto(14,1);
            clsn(14,2);
            moveto(14,1);  
            putstr("��ѡ��");
             moveto(14,8);
             putch(key_value);
         }
          else if(key_value == KEY_ENTER)
          {
               if(flag == 1)
               {
                  return VIEW;
               }
               else
               {
                   bell(20);
               }
          }
          else
          {
              bell(20);
              continue;
          }
     }
}
void Examine()
{
     char err ;
     unsigned char mykey;
     cls();
     moveto(1,1);
     putstr("examing ������\n"); 
     key(0);
      while(1)
     {
             mif_close();
             OpenCard();
             err = InitCard();
             if(err == INITCARDSUCCESS )
             {
                putstr("initcard success");
                 err = mif_authentication(1,0,cardsn);
                 if( err != 0)
                 {
                     putstr("��֤�������");
                     return ; 
                 }
                 else
                 {
                     err = mif_read(0,cardsn);
                     if( err != 0)
                     {
                         putstr("��ȡ���ݴ���");
                     }
                     else
                     {
                         putstr(cardsn);
                         key(0);
                         //�������ݵ�������
                         //Ȼ����ܷ�����Ϣ 
                         break;
                     } 
                 }
                    
             }
             else
             {
            
                cls();
                putstr("��ʼ��������");
                bell(40);
                putstr("�޿�����˶�\n");
                putstr("���������CLS���˳�\n");
                putstr("���������������\n");
                mykey=key(0);
               if(mykey == KEY_CLS)
                {
                        return ;
                }
             } 
     }
}
