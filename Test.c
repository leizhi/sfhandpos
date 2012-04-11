#include "NetSetting.h"
#include "GPRS.H"
#include "CARD.H"
#include "User.H"
#include "LoginWay.H"
/*int InitSystem()
{
    
} 
int main()
{
    cls();
    int err;
    unsigned char get_ip[20]={0};
    unsigned char get_port[6]={0};
    err = InitNetSetting();
    err = GetIP(get_ip);
    err = GetPort(get_port);     
    putstr("\n");
    putstr(get_ip);
    putstr("\n");
    putstr(get_port);
    printf("\n%s",NET_IP);
    key(0);
    err = InitGPRS();
    putstr("INIT CARD\n");
    key(0);
   err = OpenCard();
 
   if( err != INITCARDSUCCESS)
   {
       putstr(" err in initcar"); 
   }
    cls();
    GetUserInformation();
    putstr(username);
    putstr("\n");
    putstr(password);
    
    unsigned char  flag ;
    
    flag = LoginChoose();
    if(flag == 1)
    {
            cls();
     putstr("Ë¢¿¨µÇÂ½");
    }
    if(flag ==2) 
        {
            cls();
     putstr("ÊäÈëµÇÂ½");
    }
    if(flag == 3)
   { 
            cls();
            putstr("ÍË³ö");
   }
    key(0);
    
    return 1;
} */
