#include<REG51.H>
#include<stdlib.h>
#include<INTRINS.H>
#define uchar unsigned char
#define uint unsigned int
#define LCD_COM P0

sbit CS=P2^0;                 //RS
sbit SID=P2^1;                //RW
sbit SCK=P2^2;                //EN
uchar code str1[]="�����˲�����°�";

void  write_cmd(uchar);            //дָ��,RS=L,RW=L
void  write_date(uchar);           //д����,RS=H,RW=L
void  lcd_sendbyte(uchar);         //�����ֽ�,�Ӹߵ������
void  lcd_pos(uchar,uchar);        //�ַ�λ��,�������ַ�16*16����Ϊ��λ
void  lcd_init();                  //��ʼ��,���ò���(��Щ�ͺŵ�12864��������)
void  check_busy();                //�ж�12864�Ƿ���æ
uchar lcd_receivebyte();           //�����ֽ�,�Ӹߵ���д��

void main()
{
   uint i=0;
   lcd_init();
   lcd_pos(0,0);
   while(str1[i]!='\0')
   {
       write_date(str1[i]);
       i++;
   }
}
void check_busy()
{
   do lcd_sendbyte(0xfc);
   while(0x80&lcd_receivebyte());
}
void  lcd_init()
{
    write_cmd(0x30);//�����趨,���û���ָ�����,0x34����ָ��
    write_cmd(0x01);//����
    write_cmd(0x06);
    write_cmd(0x0C);//������ʾ��,�α��,�α�λ�÷��׹�
}
void  lcd_pos(uchar x,uchar y)
{
    if(x==0)
       x=0x80;
    else if(x==1)
       x=0x90;
    else if(x==2)
       x=0x88;
    else 
       x=0x98;
    write_cmd(x+y);
}
void  write_date(uchar date)
{
    check_busy();
    lcd_sendbyte(0xf8);
    lcd_sendbyte(date&0xf0);
    lcd_sendbyte(date<<4);
}
void  write_cmd(uchar cmd)
{
    check_busy();
    lcd_sendbyte(0xf8);
    lcd_sendbyte(cmd&0xf0);
    lcd_sendbyte(cmd<<4);
}
void  lcd_sendbyte(uchar date)
{
   uchar i;
   for(i=0;i<8;i++)
   {
       SCK=0;
       SID=date>>7;
       date<<=1;
       SCK=1;
       SCK=0;
   }
}
uchar lcd_receivebyte()
{
   uchar i,tmp1,tmp2;
   tmp1=0;
   tmp2=0;
   for(i=0;i<8;i++)
   {
       tmp1<<=1;
       SCK=0;
       SCK=1;
       SCK=0;
       if(SID)
       tmp1++;
   }
   for(i=0;i<8;i++)
   {
       tmp2<<=1;
       SCK=0;
       SCK=1;
       SCK=0;
       if(SID)
       tmp2++;
   }
   return (tmp1&0xf0)|(tmp2>>4);
}