#include<REG52.H>
#include<math.h>

sbit key=P2^0; 
unsigned int c=1,led=1,current;
long  ci;
double time;
const double jq=1.0850694444444e-6;
unsigned char b[4]={0xfe,0xfd,0xfb,0xf7};

void setup()
{
    if(ci>=65535){current=65535;ci-=65535;}
    else {current=ci;ci=0;}
    TMOD = 0x01;
    TH0 = (65535-current)/256;
    TL0 = (65535-current)%256;
    EA = 1;
    ET0 = 1;
    EX0 = 1;
    IT0 = 1;
    TR0 = 1;
}
void main()
{
    time=1;
    ci=time/jq;
    setup();
    key=1;
    P1=b[0];
    while(1);
}

void OutsideInterrupt(void) interrupt 0
{
   c=-c;
   led=(led+2*c+4)%4; //��ʱת��״̬
}

void Timer0Interrupt(void) interrupt 1
{
    if(!ci)
    { 
    P1=b[led];
    led=(led+c+4)%4; 
    ci=time/jq;
    }
    if(ci>=65535){current=65535;ci-=65535;}
    else 
    {
        current=ci;
        ci=0;
    }
    TH0 = (65535-current)/256;
    TL0 = (65535-current)%256;         
}
