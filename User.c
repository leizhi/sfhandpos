#include "User.h"
void Init()
{
     memset(username,0,20);
     memset(password,0,20);
}
/***********************
*��������GetUserInformation 
*��  �ܣ���ȡ�û�������û��������� 
*��  ������
*����ֵ���� 
***********************/
void GetUserInformation()
{
         cls();
         uchar keyvalue;            //���ռ��̰���ֵ 
         uchar x,y;                 //��ȡ���λ��
         uchar index = 0;           //��¼�洢����ĳ��� 
         moveto(4,6);
         putstr("��ӭʹ��");
         moveto(8,1);
         putstr("�û��� :");
         moveto(10,1);
         putstr("��  �� :"); 
         
         moveto(8,10);              //���̻�дλ�� 
         keys(username);
         moveto(8,10);              //����û���λ�� 
         putstr(username);
         clsn(8,2);                 //������̻�д 
         
         moveto(8,1);
         putstr("�û��� :");
         moveto(8,10);
         putstr(username);
         moveto(10,10);             //��ʼ�������λ�� 

         x = 10;
         y = 10;
         while(1)
         {
              keyvalue=key(0);                         //�������� 
              if(KEY_ENTER == keyvalue)                //���µ���ȷ�ϼ�
              {
                           if(index == 0)              //����Ϊ��
                           {
                               bell(20); 
                           } 
                           else                        //���벻Ϊ�գ����Ѿ�������� 
                           {
                               break;
                           }
              }
              else if(KEY_CLS == keyvalue)             // ���µ��������
              {
                   if(index != 0)                      //û��ɾ��������
                   {
                            index = index -1;
                            password[index] = 0;
                                                       //�����������λ�� ��*�ű�ʾ
                            moveto(10,1);
                            clsn(10,2);
                            
                             moveto(10,1);
                             putstr("��  �� :"); 
                            
                            moveto(10,10);
                            uchar i =0;
                            for(;i<index;i++)
                            {
                                 putch('*');            
                            }  
                          
                   } 
                   else
                   {
                       bell(20);
                   } 
              } 
              else if(((keyvalue >0x29)&&(keyvalue < 0x40))||(keyvalue == 0x2b)||(keyvalue== 0x2e))
              {
                      x = getx();
                      y = gety();
                      moveto(x,y);
                      putch('*');
                      password[index]= keyvalue;
                      index = index+1;
                     
              }
         }
         //������ 
       
         cls();
         putstr(username);
         putstr("\n");
         putstr(password);  
         key(0); 
        //������

}
