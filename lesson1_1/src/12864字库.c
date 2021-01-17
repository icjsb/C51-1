#include<REG51.H>
#include<stdlib.h>
#include<INTRINS.H>
#define uchar unsigned char
#define uint unsigned int
#define LCD_COM P0

sbit CS=P2^0;                 //RS
sbit SID=P2^1;                //RW
sbit SCK=P2^2;                //EN
uchar code str1[]="年轻人不讲武德啊";

void  write_cmd(uchar);            //写指令,RS=L,RW=L
void  write_date(uchar);           //写数据,RS=H,RW=L
void  lcd_sendbyte(uchar);         //传输字节,从高到低输出
void  lcd_pos(uchar,uchar);        //字符位置,以中文字符16*16点阵为单位
void  lcd_init();                  //初始化,设置并口(有些型号的12864分左右屏)
void  check_busy();                //判断12864是否在忙
uchar lcd_receivebyte();           //接受字节,从高到低写入

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
    write_cmd(0x30);//功能设定,设置基本指令操作,0x34扩充指令
    write_cmd(0x01);//清屏
    write_cmd(0x06);
    write_cmd(0x0C);//整体显示开,游标关,游标位置反白关
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