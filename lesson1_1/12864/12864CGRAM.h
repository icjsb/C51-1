#include<REG51.H>
#define uchar unsigned char
#define uint unsigned int

/*引脚定义*/
sbit LCD_RS=P2^0;
sbit LCD_RW=P2^1;
sbit LCD_EN=P2^2;
sbit LCD_PSB=P2^3;

/*函数申明*/
void check_busy();                      //判忙函数
void delay_1ms(uint);                   //延时函数
void SET_CGRAM(uint,uchar*);            //设置CGRAM地址,并写入相应的字
void display_CGRAM(uint);               //呈现CGRAM,输入相应编号
void LCD_POS(uint,uint);                //调整DDRAM相应的位置
void LCD_init();                        //初始化LCD
void write_cmd(uchar);                       //写指令
void write_date(uchar);                      //写数据

/*函数定义*/
void check_busy()
{
    P0=0x00;
    LCD_RS=0;
    LCD_RW=1;
    LCD_EN=1;
    delay_1ms(5);
    while(P0 & 0x80);
    LCD_EN=0;
}

void delay_1ms(uint x)
{
   uint i,j;
   for(i=0;i<x;i++)
   for(j=0;j<110;j++);
}

void SET_CGRAM(uint num,uchar*p)
{
    uchar i,firstadd;
    write_cmd(0x34);//扩充指令集
    write_cmd(0x02);//第13条,允许设置CGRAM地址
    write_cmd(0x30);//回到基本指令集
    firstadd=0x40|(num<<4);
    for(i=0;i<16;i++)
    {
        write_cmd(firstadd+i);//设置纵坐标
        write_date(*p);
        write_date(*(p+1));
        p+=2;
    }
}

void display_CGRAM(uint num)//跟汉字一样占两个字节,所以要写入2个字节的数据,0000H,0002H,0004H,0006H
{
    write_date(0x00);
    write_date(num*2);
}

void LCD_POS(uint x,uint y)
{
    switch(x)
    {
       case 1:x=0x80;
       case 2:x=0x90;
       case 3:x=0x88;
       case 4:x=0x98;
    }
    write_cmd(x+y);
}

void LCD_init()
{
    LCD_PSB=1;
    write_cmd(0x30);//基本指令集
    write_cmd(0x0C);//整体显示开
    write_cmd(0x01);//清屏
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

