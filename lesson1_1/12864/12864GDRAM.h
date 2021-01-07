#include<REG51.H>
#define uchar unsigned char
#define uint unsigned int

sbit LCD_RS=P2^0;
sbit LCD_RW=P2^1;
sbit LCD_EN=P2^2;
sbit LCD_PSB=P2^3;

uchar readstatus();
void lcd_init();//初始化函数
void write(uchar,uchar);//写数据、指令,'z'表示指令,'s'表示数据
void check_busy();//判忙函数
void clear_screen();//清屏
void clear_GDRAM();//清除缓冲区
void delay_1ms(uint);//延时
void display_image(uchar*);//在指定位置显示单张图片
//void fill_point(uint,uint);//画点
//void fill_line(uint,uint,uint,uint);//画线
//void fill_circle(uint,uint,uint);//画圆

uchar readstatus()
{
    uchar temp;
    P0=0xff;//不大清楚
    LCD_RS=1;
    LCD_RW=1;
    LCD_EN=1;
    temp=P0;
    delay_1ms(5);
    LCD_EN=0;
    return temp;
}

void delay_1ms(uint x)
{
    uint i,j;
    for(i=0;i<x;i++)
    for(j=0;j<110;j++);
}

void lcd_init()
{
    LCD_PSB=1;
    write(0x30,'z');//功能设定,设置基本指令操作,0x34扩充指令
    write(0x0C,'z');//整体显示开,游标关,游标位置反白关
    clear_screen();//清屏
    clear_GDRAM();//清除缓冲区
}

void check_busy()
{
   P0=0x00;
   LCD_RW=1;
   LCD_RS=0;//读状态0,读数据1
   LCD_EN=1;
   delay_1ms(5);
   while(P0 & 0x80);//判忙循环
   LCD_EN=0;
}

void write(uchar date,uchar command)
{
    check_busy();
    LCD_RS=(command=='z')?0:1;
    LCD_RW=0;
    LCD_EN=0;
    P0=date;
    delay_1ms(5);
    LCD_EN=1;
    delay_1ms(5);
    LCD_EN=0;
}

void clear_screen()
{
    write(0x01,'z');
}

void clear_GDRAM()
{
    uchar i,j;
    write(0x34,'z');//扩充指令集操作
    write(0x34,'z');//关绘图显示功能
    /*上半屏显示设置*/
    for(i=0;i<32;i++)
    {
        write(0x80+i,'z');
        write(0x80,'z');
        for(j=0;j<16;j++)
        {
            write(0x00,'s');
        }
    }
    /*下半屏显示设置*/
    for(i=0;i<32;i++)
    {
        write(0x80+i,'z');
        write(0x88,'z');
        for(j=0;j<16;j++)
        {
            write(0x00,'s');
        }
    }
    write(0x36,'z');//开绘图模式
    write(0x30,'z');//回到基本指令
}

void display_image(uchar* p)
{
    uchar i,j;
    write(0x34,'z');//扩充指令集操作
    write(0x34,'z');//关绘图显示功能
    /*上半屏显示设置*/
    for(i=0;i<32;i++)
    {
        write(0x80+i,'z');
        write(0x80,'z');
        for(j=0;j<16;j++)
        {
            write(*p,'s');
            p++;
        }
    }
    /*下半屏显示设置*/
    for(i=0;i<32;i++)
    {
        write(0x80+i,'z');
        write(0x88,'z');
        for(j=0;j<16;j++)
        {
            write(*p,'s');
            p++;
        }
    }
    write(0x36,'z');//开绘图模式
    write(0x30,'z');//回到基本指令
}
