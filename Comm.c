#include "Comm.h"

/****************************************************************************
��������: str_to_hex
��������: �ַ���ת��Ϊʮ������
�������: string �ַ��� cbuf ʮ������
�������: ��
*****************************************************************************/
void toHex(unsigned char *src,unsigned char *hex){
     while(*src!=0){
        char hex1;
        char hex2;
        int value=*src; //ֱ�ӽ�unsigned char��ֵ�����͵�ֵ��ϵͳ������ǿ��ת��
        int v1=value/16;
        int v2=value % 16;
        
        //����ת����ĸ
        if (v1>=0&&v1<=9)
        hex1=(char)(48+v1);
        else
        hex1=(char)(55+v1);
        
        //������ת����ĸ
        if (v2>=0&&v2<=9)
        hex2=(char)(48+v2);
        else
        hex2=(char)(55+v2);
        
        //����ĸ���ӳɴ�
        *hex=hex1;
        hex++;
        *hex=hex2;
        hex++;
        
        src++;
    }
}
/****************************************************************************
��������: swap
��������: �ߵ��ֽڽ��� 
�������: src �ַ���
�������: ��
*****************************************************************************/
int swap(unsigned char *src){
    unsigned char buffer[2]={0};
    short i;
    short size=2;
    for (i = 0; i < size ; i++) {
        buffer[i]=src[size-1-i];
    }

    for (i = 0; i < size ; i++) {
        src[i]=buffer[i];
    }
    return 0;
}
/****************************************************************************
��������: toShort
��������: �ֽ�ת���ɶ����� 
�������: buffer �ַ���
�������: short
*****************************************************************************/
short toShort(unsigned char *buffer){
    unsigned char *p=buffer;
    
    unsigned short mask = 0xff;
    unsigned short temp = 0;
    unsigned short result = 0;
    
    unsigned short i;
    for (i = 0; i < 2 ; i++) {
    	result <<= 8;
    	temp = *p & mask;
    	result |= temp;
    	
    	p++;
    }
    
   // printf("buf:%d 0x%04x\n",result,result);
    return result;
}
