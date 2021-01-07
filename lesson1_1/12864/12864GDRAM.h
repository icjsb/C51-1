#include<REG51.H>
#define uchar unsigned char
#define uint unsigned int

sbit LCD_RS=P2^0;
sbit LCD_RW=P2^1;
sbit LCD_EN=P2^2;
sbit LCD_PSB=P2^3;

uchar readstatus();
void lcd_init();//��ʼ������
void write(uchar,uchar);//д���ݡ�ָ��,'z'��ʾָ��,'s'��ʾ����
void check_busy();//��æ����
void clear_screen();//����
void clear_GDRAM();//���������
void delay_1ms(uint);//��ʱ
void display_image(uchar*);//��ָ��λ����ʾ����ͼƬ
//void fill_point(uint,uint);//����
//void fill_line(uint,uint,uint,uint);//����
//void fill_circle(uint,uint,uint);//��Բ

uchar readstatus()
{
    uchar temp;
    P0=0xff;//�������
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
    write(0x30,'z');//�����趨,���û���ָ�����,0x34����ָ��
    write(0x0C,'z');//������ʾ��,�α��,�α�λ�÷��׹�
    clear_screen();//����
    clear_GDRAM();//���������
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
    write(0x34,'z');//����ָ�����
    write(0x34,'z');//�ػ�ͼ��ʾ����
    /*�ϰ�����ʾ����*/
    for(i=0;i<32;i++)
    {
        write(0x80+i,'z');
        write(0x80,'z');
        for(j=0;j<16;j++)
        {
            write(0x00,'s');
        }
    }
    /*�°�����ʾ����*/
    for(i=0;i<32;i++)
    {
        write(0x80+i,'z');
        write(0x88,'z');
        for(j=0;j<16;j++)
        {
            write(0x00,'s');
        }
    }
    write(0x36,'z');//����ͼģʽ
    write(0x30,'z');//�ص�����ָ��
}

void display_image(uchar* p)
{
    uchar i,j;
    write(0x34,'z');//����ָ�����
    write(0x34,'z');//�ػ�ͼ��ʾ����
    /*�ϰ�����ʾ����*/
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
    /*�°�����ʾ����*/
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
    write(0x36,'z');//����ͼģʽ
    write(0x30,'z');//�ص�����ָ��
}
