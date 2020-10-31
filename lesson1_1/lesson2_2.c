#include<REG52.H>
#define UINT  unsigned int  
#define uchar unsigned char 
sbit D1=P1^0;
void delay()
{
    UINT  x,y;
    for(x=100;x>0;x--)
        for(y=2000;y>0;y--);
}
void main()
{
    while (1)
    {
       D1=0;
       delay();
       D1=1;
       delay();
    }
    
}
