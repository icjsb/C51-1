#include<Reg51.h>
void main()
{ 
    int i;
    while(1)
    {
       P1=0xfe;
       for(i=0;i<10000;i++);
       P1=0xfd;
       for(i=0;i<10000;i++);
       P1=0xfb;
       for(i=0;i<10000;i++);
       P1=0xf7;
       for(i=0;i<10000;i++);
    }
}