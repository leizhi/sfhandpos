#include "display.h"
int block(unsigned char *begin,unsigned char delimiter)
{
	int block=0;
    if(begin==NULL || delimiter==NULL) return 0;
    while(*begin!=0)
    {
        if(*begin==delimiter) block++;
        begin++;
	}
    return block+1;
}

char **cutting(unsigned char *begin,unsigned char delimiter)
{
    unsigned char result[128][128]={0};
	if(begin==NULL || delimiter==NULL) 
    return NULL;

	int size = block(begin,delimiter);
	int j;
	for(j=0;j<size;j++)
    {
        unsigned char *p=begin;
		int length=0;
		while(*p!=0 && *p!=delimiter)
        {
			length++;
			p++;
		}
/*		printf("begin:%c\n",*begin);*/
/*		printf("length:%d \n",length);*/
		unsigned char section[length];
//		ret[j] = malloc(length * sizeof(char ));
		p=begin;
		int i=0;
		for(i=0;i<length;i++)
        {
			section[i]=*p;
			p++;
 			result[j][i]=section[i];
//			ret[j+i]=section[i];
//			printf("0x%x ",&result[j][i]);
//			printf("0x%x ",&ret[j+i]);
//			printf("%c",ret[j+i]);
        }
		begin+=length+1;
		section[length]=0;
//		printf("\n");
//      putch('\n');
/*		printf("%s\n",section);*/
/*		printf("%s\n",result[j]);*/
//		*ret=result[j];
//		printf("%s \n",**ret);
//		ret++;
	}
//	printf("%s",**ret);
	return result;
}

void printSC(unsigned char** buffer,int block)
{
     unsigned char inkey;
     int index;
     int i;
     int flag;
     if(buffer==NULL || block==NULL) 
     return;

	 myStr p;
	 p=buffer;
	 index=0;
	 flag=0;
	 cls();
	 for(i=0;i<MAX_LINE;i++)
		{
		putstr(*p);
		p++;
		putch('\n');
		}
	 while(flag==0)
     {
     p=buffer;
     switch(inkey=key(0))
     {
        case 0x82:
        return;
        /*cls();
        flag++;
        moveto(8,3);
        putstr("请按清除返回查询！");
        break;
        */
		case 0x8E:
        cls();  
        index--;
		if(index<1)
        {
        index=0;
        }
		p+=index;
	    for(i=0;i<MAX_LINE;i++)
		{
		putstr(*p);
		p++;
		putch('\n');
		}
        break;
		
		case 0x8F:
        cls();
        index++;
		if(index>block-1)
        {
		index=block-1;
        }
		p+=index;
	    for(i=0;i<MAX_LINE;i++)
		{
		putstr(*p);
		p++;
		putch('\n');
		}
		break;
		
        case 0x8D:
        cls();
        p+=index;
        for(i=0;i<MAX_LINE;i++)
		{
		putstr(*p);
		p++;
		putch('\n');
		}
		break;

		default:
        break;
    }
    }
}
