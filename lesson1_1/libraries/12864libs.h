#include<REG52.H>
#define uchar unsigned char
#define uint unsigned int

/*引脚定义*/

sbit CS=P2^7;                //RS
sbit SID=P2^6;               //RW
sbit SCK=P2^5;               //EN

/*函数声明*/
void  LCD12864_clear_DDRAM();                //清屏
void  LCD12864_sendbyte(uchar);              //发送字节,从高到低
void  LCD12864_write_cmd(uchar);             //写指令,RS=L,RW=L
void  LCD12864_write_data(uchar);            //写数据,RS=H,RW=L
void  LCD12864_pos(uchar,uchar);             //字符位置,以中文字符16*16点阵为单位
void  LCD12864_init();                       //初始化,设置并口(有些型号的12864分左右屏)
void  LCD12864_check_busy();                 //判断12864是否在忙,一定要有,否则可能导致数据丢失
void  LCD12864_SET_CGRAM(uchar,uchar*);      //写入CGRAM
void  LCD12864_display_CGRAM(uchar);         //显示CGRAM
void  LCD12864_showstring(uchar*,uint,uint); //不能把vscode里面显示的汉字所占位数当作实际位数！！！中文就是占2个字节的
void  LCD12864_display_image(uchar*);        //GDRAM绘图模式
void  LCD12864_clear_GDRAM();                //清空GDRAM
uchar LCD12864_receivebyte();                //读取字节,从高到低
uchar LCD12864_read_data();                  //读数据,RS=H,RW=H
uchar LCD12864_read_status();                //读状态,RS=L,RW=H

/*函数定义*/
void  LCD12864_clear_DDRAM()
{
      LCD12864_write_cmd(0x01);
}
void  LCD12864_sendbyte(uchar Data)
{
      uchar i;
      for(i=0;i<8;i++)
      {
          SCK=0;
          SID=Data>>7;          
          Data<<=1;
          SCK=1;
          SCK=0;
      }
}
void  LCD12864_write_cmd(uchar cmd)
{
      CS=1;
      LCD12864_check_busy();
      LCD12864_sendbyte(0xf8);
      LCD12864_sendbyte(0xf0&cmd);
      LCD12864_sendbyte(0xf0&cmd<<4);
      CS=0;
}
void  LCD12864_write_data(uchar Data)
{
      CS=1;
      LCD12864_check_busy();
      LCD12864_sendbyte(0xfa);
      LCD12864_sendbyte(0xf0&Data);
      LCD12864_sendbyte(0xf0&Data<<4);
      CS=0;
}
void  LCD12864_pos(uchar x,uchar y)
{
    switch (x)
    {
    case 0:x=0x80;
           break;
    case 1:x=0x90;
           break;
    case 2:x=0x88;
           break;
    case 3:x=0x98;
           break;
    }
    LCD12864_write_cmd(x+y);
}
void  LCD12864_init()
{
      LCD12864_clear_GDRAM();
      LCD12864_write_cmd(0x30);
      LCD12864_write_cmd(0x0C);
      LCD12864_write_cmd(0x01);
      LCD12864_write_cmd(0x06);
}
void  LCD12864_check_busy()
{
      do ;
      while(LCD12864_read_status()&0x80);
}
void  LCD12864_SET_CGRAM(uchar num,uchar *p)
{
      uchar i,firstadd;
      LCD12864_write_cmd(0x34);             //扩充指令集
      LCD12864_write_cmd(0x02);             //第13条,允许设置CGRAM地址
      LCD12864_write_cmd(0x30);             //回到基本指令集
      firstadd=(0x40|num<<4);
      for(i=0;i<16;i++)
      {
          LCD12864_write_cmd(firstadd+i);   //设置纵坐标
          LCD12864_write_data(p[i*2]);
          LCD12864_write_data(p[i*2+1]);
      }
}
void  LCD12864_display_CGRAM(uchar num)
{
      LCD12864_write_data(0x00);            //CGRAM当作数据调用
      LCD12864_write_data(num*2);
}
void  LCD12864_showstring(uchar*p,uint row,uint col)
{
      uchar i;
      LCD12864_pos(row,col);
      switch (row)
      {
      case 0:row=0x80;
             break;
      case 1:row=0x90;
             break;
      case 2:row=0x88;
             break;
      case 3:row=0x98;
             break;
      }
      row+=col;
      for(i=0;p[i]!='\0';i++)
      {
            LCD12864_write_data(p[i]);
            if(i%2)
            { 
               row++;
               switch (row)
               {
               case 0x88:row=0x90;
                         LCD12864_write_cmd(row);
                         break;
               case 0x98:row=0x88;
                         LCD12864_write_cmd(row);
                         break;
               case 0x8f:row=0x98;
                         LCD12864_write_cmd(row);
                         break;
               }
               if(row==0xa0)break;
            }
      }
}
void  LCD12864_display_image(uchar*p)
{
      uchar i,j;
      LCD12864_write_cmd(0x34);              //扩充指令集,绘图模式关
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x80);
            for(j=0;j<16;j++)
                {
                  LCD12864_write_data(*p);
                  p++;
                }       
      }
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x88);
            for(j=0;j<16;j++)
                {
                  LCD12864_write_data(*p);
                  p++;
                }       
      }
      LCD12864_write_cmd(0x36);
      LCD12864_write_cmd(0x30);
}
void  LCD12864_clear_GDRAM()
{
      uchar i,j;
      LCD12864_write_cmd(0x34);              //扩充指令集,绘图模式关
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x80);
            for(j=0;j<16;j++)
                {
                  LCD12864_write_data(0x00);
                }       
      }
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x88);
            for(j=0;j<16;j++)
                {
                  LCD12864_write_data(0x00);
                }       
      }
      LCD12864_write_cmd(0x36);
      LCD12864_write_cmd(0x30);
}
uchar LCD12864_receivebyte()
{
      uchar tmp1,tmp2,i;
      tmp1=0;
      tmp2=0;
      for(i=0;i<8;i++)
      {          
          tmp1<<=1;
          SCK=0;
          SCK=1;
          SCK=0;
          if(SID)tmp1++;
      }
      for(i=0;i<8;i++)
      {          
          tmp2<<=1;
          SCK=0;
          SCK=1;
          SCK=0;
          if(SID)tmp2++;
      }
      return (tmp1&0xf0)|(tmp2>>4);
}
uchar LCD12864_read_data()
{   
      LCD12864_sendbyte(0xfe);
      return LCD12864_receivebyte();
}
uchar LCD12864_read_status()
{
      LCD12864_sendbyte(0xfc);
      return LCD12864_receivebyte();
}