#include<REG52.H>
#include<math.h>
sbit key=P2^0; 
int c=0;
void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x0FF;
    TL0 = 0x0A4;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void col(int);
void main()
{
    InitTimer0();
    key=1;
    while(1) 
    col(c);
}
void col(int a)
{    
    unsigned char b[4]={0xfe,0xfd,0xfb,0xf7};
    long i,j;
    for(i=0;i<4;i++)
    {   
        P1=b[abs(a*3-i)];
        for(j=0;j<3000;j++)if(!key)c=1-c;
    }
}

void Timer0Interrupt(void) interrupt 1
{
    TH0 = 0x0FF;
    TL0 = 0x0A4;
    if(!key)c=1-c;
}
