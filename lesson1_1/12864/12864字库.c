#include<REG51.H>
#include<stdlib.h>
#define uchar unsigned char
#define uint unsigned int

sbit LCD_RS=P3^5;
sbit LCD_RW=P3^6;
sbit LCD_EN=P3^4;
sbit LCD_PSB=P3^7;
uchar code str1[]="2021";

void write_cmd(uchar);//дָ��,RS=L,RW=L
void write_date(uchar);//д����,RS=H,RW=L
void lcd_pos(uchar,uchar);//�ַ�λ��,�������ַ�16*16����Ϊ��λ
void lcd_init();//��ʼ��,���ò���(��Щ�ͺŵ�12864��������)
void delay_1ms(uint);//��ʱ,��msΪ��λ
void check_busy();//�ж�12864�Ƿ���æ

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
   P0=0x00;
   LCD_RW=1;
   LCD_RS=0;//��״̬0,������1
   LCD_EN=1;
   delay_1ms(5);
   while(P0 & 0x80);//��æѭ��
   LCD_EN=0;
}
void lcd_init()
{
    LCD_PSB=1;
    write_cmd(0x30);//�����趨,���û���ָ�����,0x34����ָ��
    write_cmd(0x0C);//������ʾ��,�α��,�α�λ�÷��׹�
    write_cmd(0x01);//����
}
void delay_1ms(uint x)
{
    uint i,j;
    for(i=0;i<x;i++)
    for(j=0;j<110;j++);
}
void lcd_pos(uchar x,uchar y)
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
void write_date(uchar date)
{
    check_busy();
    LCD_RS=1;
    LCD_RW=0;
    LCD_EN=0;
    P0=date;
    delay_1ms(5);
    LCD_EN=1;
    delay_1ms(5);
    LCD_EN=0;
}
void write_cmd(uchar cmd)
{
    check_busy();
    LCD_RS=0;
    LCD_RW=0;
    LCD_EN=0;
    P0=cmd;
    delay_1ms(5);
    LCD_EN=1;
    delay_1ms(5);
    LCD_EN=0;
}
