#include "NetSetting.h"
#include "GPRS.H"
#include "CARD.H"
#include "LoginWay.H"
#include "Menu.H"
#include "display.h"

#ifndef MAIN
#define MAIN

#define              INITSYSTEMERROR             1
#define              INITSYSTEMSUCCESS           0
int InitSystem();     //��ʼ��ϵͳ 
void CloseSystem();   //�ͷ���Դ���ر�ϵͳ 
int UsingNet();
int WithoutNet();
#endif
