#include"Menu.H"
#include "CARD.H"
unsigned char MenuChoose()
{
     unsigned char key_value; 
     cls();
     moveto(4,6);
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
                  return CLS;
     }
     else if(key_value == 0x31)
     {
          //����Ѳ�캯�� 
      }
      else
      {
          bell(20);
      }
}
void InitMenu()
{
     
}
void Examine()
{
     char err ;
     err = InitCard();
     if(err != INITCARDSUCCESS )
     {
            putstr("��ʼ��������");
            return ; 
     }
     else
     {
         
     } 
}
