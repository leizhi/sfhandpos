#include"Menu.H"
#include "CARD.H"
#include "User.H"
#include<gprs_api.h>
unsigned char  MenuChoose()
{
     unsigned char key_value; 
     unsigned char flag =0;
     static int index = 0;
     static unsigned char name_temp[20];
     if(index ==0)
     { 
        
         strcpy(name_temp,username);
         index = 1;
     }
       cls();
       
     while(1)
     {
         moveto(4,2);
         putstr("��ӭ����");
         putstr(name_temp); 
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
     int err ;
     unsigned char mykey;
     unsigned char cardnum_length;//���кų��� 
     unsigned char send_buffer[100];
     unsigned char query_information[5000];
     unsigned short query_length;
     memset(query_information,0,5000);
     memset(send_buffer,0,100);
    
     cls();
     moveto(1,1);
      while(1)
     {
             err = mif_close();
             if(err != 0)
             {
                    putstr("mif_close err in examing\n");
                    key(0);
                    return ;
             }
             err = OpenCard();
             if(err != 0)
             {
                    putstr("�򿪶���ģ�����\n");
                    key(0);
                    return ;
             }
             err = InitCard();
             if(err == INITCARDSUCCESS )
             {
                 err = mif_authentication(1,1,cardsn);
                 if( err != 0)
                 {
                     putstr("��֤�������");
                     key(0);
                     return ; 
                 }
                 else
                 {
                     memset(cardnum,0,40);
                     err = mif_read(4,cardnum);

                     if( err != 0)
                     {
                         putstr("��ȡ���ݴ���");
                         key(0);
                     }
                     else
                     {
                         //�������ݵ�������
                          cardnum_length = 0;
                         //��װcardsn
                          send_buffer[0]= '*';
                          cardnum_length++;
                          send_buffer[1]= '2';
                          cardnum_length++;
                          putstr("��ʼ��װ��������\n");
                           int k =0;
                          while(1)
                          {
                                 
                                  if(cardnum[k]== 0)
                                  {
                                     break;
                                  }
                                  else
                                  {
                                      send_buffer[cardnum_length]=cardnum[k];
                                      cardnum_length++;
                                  }
                                  k++;
                          } 
                          putstr("��ɷ�װ��������\n");                          
                          send_buffer[cardnum_length]= '#';
                          cardnum_length++;
                          send_buffer[cardnum_length]='\n';
                          cardnum_length++;
                          putstr("��ɷ�װ��������\n");  
                          
                          key(0); 
                          cls();
                          putstr(send_buffer);
                          key(0);
                          
                          unsigned short send_length = cardnum_length;

                         /*if ( err != 0)
                          {
                             putstr("�������糬ʱ\n");
                             key(0);
                             return ;  
                          }
                          */
                          /*else
                          {*/
                                 
                                  unsigned char send_num =0;
                                  while(send_num<2)
                                  { 
                                     err = WNetTxd(send_buffer,send_length);
                                     if( err == 0)
                                     {
                                         putstr("�������ݳɹ�\n");
                                         key(0);
                                         break; 
                                     }
                                     else
                                     {
                                            cls();
                                            printf("%d",send_num);
                                            putstr("����ʧ�ܣ��ٴγ��Է���\n");
                                            key(0);
                                            send_num++;
                                     }
                                  }
                                  
                                  if(send_num ==2)
                                  {
                                          putstr("�����������δ���\n");
                                          key(0);
                                          return ;
                                  }
                                  else
                                      {
                                           //Ȼ����ܷ�����Ϣ 
                                           putstr("׼����������\n");
                                           err = WNetRxd(query_information,&query_length,10000);
                                           putstr(" �����������\n"); 
                                           if(err != 0)
                                           {
                                                  putstr("an err in recv\n");
                                                  key(0);
                                                  return ;
                                           }
                                           else
                                           {
                                               putstr(query_information);
                                               key(0);
                                           }
                                         
                                      }
                             
                         // }
                          
                          
                        
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
