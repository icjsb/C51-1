#ifndef _INC_LCD12864
#define _INC_LCD12864
#define uchar unsigned char
#define uint unsigned int
#endif

//PSB ���������ڿ�ͨ��
sbit lcd_12864_RS = P2 ^ 0;  //Ƭѡ
sbit lcd_12864_WRD = P2 ^ 1; //����
sbit lcd_12864_EN = P2 ^ 2;  //ʱ��

void delay(unsigned int wait_time);
void lcd_12864_commode(uchar data1);

uint qi_take_length(char *input_data_char)
{
    uint i = 0;
    while (input_data_char[i] != '\0')
    {
        i++;
    };
    return i;
}

void int_lcd_12864()
{
    delay(10);               //��ʱ10
    lcd_12864_commode(0x30); //1100 ��ַ��Ϊ
    delay(100);              //��ʱ100
    lcd_12864_commode(0x08); //1000 �����ʾ
    delay(100);              //��ʱ100
    lcd_12864_commode(0x10); //���ù��
    delay(100);              //��ʱ100
    lcd_12864_commode(0x0C); //1100 ����ʾ
    delay(100);              //��ʱ100
    lcd_12864_commode(0x01); //1000 �����ʾ
    delay(10);               //��ʱ100
    lcd_12864_commode(0x06); //�������
    delay(100);              //��ʱ100
}

void lcd_12864_commode(uchar data1)
{
    lcd_12864_WRD = 0;
    lcd_12864_RS = 0;
    delay(1);
    P0 = data1;
    lcd_12864_EN = 1;
    delay(5);
    lcd_12864_EN = 0;
}
void lcd_12864_data(uchar data1)
{
    lcd_12864_WRD = 0;
    lcd_12864_RS = 1;
    delay(1);
    P0 = data1;
    lcd_12864_EN = 1;
    delay(5);
    lcd_12864_EN = 0;
}

void lcd_12864_text(uchar *data1)
{
    uint i;
    uint strlong = qi_take_length(data1);
    lcd_12864_commode(0x80); //��1��
    for (i = 0; i < strlong; i++)
    {
        if (i == 16)
            lcd_12864_commode(0x90); //��2��
        if (i == 32)
            lcd_12864_commode(0x88); //��3��
        if (i == 48)
            lcd_12864_commode(0x98); //��4��

        lcd_12864_data(*data1);
        data1++;
    }
}