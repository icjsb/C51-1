#include<REG51.H>
#define uchar unsigned char
#define uint unsigned int

/*���Ŷ���*/
sbit LCD_RS=P2^0;
sbit LCD_RW=P2^1;
sbit LCD_EN=P2^2;
sbit LCD_PSB=P2^3;

/*��������*/
void check_busy();                      //��æ����
void delay_1ms(uint);                   //��ʱ����
void SET_CGRAM(uint,uchar*);            //����CGRAM��ַ,��д����Ӧ����
void display_CGRAM(uint);               //����CGRAM,������Ӧ���
void LCD_POS(uint,uint);                //����DDRAM��Ӧ��λ��
void LCD_init();                        //��ʼ��LCD
void write_cmd(uchar);                       //дָ��
void write_date(uchar);                      //д����

/*��������*/
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
    write_cmd(0x34);//����ָ�
    write_cmd(0x02);//��13��,��������CGRAM��ַ
    write_cmd(0x30);//�ص�����ָ�
    firstadd=0x40|(num<<4);
    for(i=0;i<16;i++)
    {
        write_cmd(firstadd+i);//����������
        write_date(*p);
        write_date(*(p+1));
        p+=2;
    }
}

void display_CGRAM(uint num)//������һ��ռ�����ֽ�,����Ҫд��2���ֽڵ�����,0000H,0002H,0004H,0006H
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
    write_cmd(0x30);//����ָ�
    write_cmd(0x0C);//������ʾ��
    write_cmd(0x01);//����
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

