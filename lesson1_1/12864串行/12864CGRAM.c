/*该程序展示如何使用CGRAM造字(图)*/
#include"libraries\12864libs.h"
uchar code str1[]=
{
0x08,0x80,0x08,0x80,0x08,0x80,0x11,0xFE,0x11,0x02,0x32,0x04,0x34,0x20,0x50,0x20,
0x91,0x28,0x11,0x24,0x12,0x24,0x12,0x22,0x14,0x22,0x10,0x20,0x10,0xA0,0x10,0x40/*"你"*/
};

uchar code str2[]=
{
0x10,0x00,0x10,0xFC,0x10,0x04,0x10,0x08,0xFC,0x10,0x24,0x20,0x24,0x20,0x25,0xFE,
0x24,0x20,0x48,0x20,0x28,0x20,0x10,0x20,0x28,0x20,0x44,0x20,0x84,0xA0,0x00,0x40/*"好"*/
};

uchar code str3[]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x78,
0x00,0x44,0x00,0x02,0x00,0x02,0x00,0x42,0x00,0x44,0x00,0x38,0x00,0x00,0x00,0x00/*"5"*/
};

uchar code str4[]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x38,0x00,0x08,0x00,0x08,0x00,0x08,
0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x3E,0x00,0x00,0x00,0x00/*"1"*/ 
};

void main()
{
    LCD12864_init();
    LCD12864_SET_CGRAM(0,str1);
    LCD12864_SET_CGRAM(1,str2);
    LCD12864_SET_CGRAM(2,str3);
    LCD12864_SET_CGRAM(3,str4);
    LCD12864_pos(0,0);
    LCD12864_display_CGRAM(0);
    LCD12864_pos(0,2);
    LCD12864_display_CGRAM(1);
    LCD12864_pos(0,4);
    LCD12864_display_CGRAM(2);
    LCD12864_pos(0,6);
    LCD12864_display_CGRAM(3);
    LCD12864_showstring("加载成功！",1,0);
    while(1);
}
