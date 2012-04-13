#include "NetSetting.h"
#include "GPRS.H"
#include "CARD.H"
#include "User.H"
#include "LoginWay.H"
#include "Menu.H"

#ifndef MAIN
#define MAIN

#define              INITSYSTEMERROR             1
#define              INITSYSTEMSUCCESS           0
int InitSystem();     //初始化系统 
void CloseSystem();   //释放资源，关闭系统 
#endif
