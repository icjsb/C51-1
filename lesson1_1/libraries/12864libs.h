#include<REG52.H>
#define uchar unsigned char
#define uint unsigned int

/*���Ŷ���*/

sbit CS=P2^7;                //RS
sbit SID=P2^6;               //RW
sbit SCK=P2^5;               //EN

/*��������*/
void  LCD12864_clear_DDRAM();                //����
void  LCD12864_sendbyte(uchar);              //�����ֽ�,�Ӹߵ���
void  LCD12864_write_cmd(uchar);             //дָ��,RS=L,RW=L
void  LCD12864_write_data(uchar);            //д����,RS=H,RW=L
void  LCD12864_pos(uchar,uchar);             //�ַ�λ��,�������ַ�16*16����Ϊ��λ
void  LCD12864_init();                       //��ʼ��,���ò���(��Щ�ͺŵ�12864��������)
void  LCD12864_check_busy();                 //�ж�12864�Ƿ���æ,һ��Ҫ��,������ܵ������ݶ�ʧ
void  LCD12864_SET_CGRAM(uchar,uchar*);      //д��CGRAM
void  LCD12864_display_CGRAM(uchar);         //��ʾCGRAM
void  LCD12864_showstring(uchar*,uint,uint); //���ܰ�vscode������ʾ�ĺ�����ռλ������ʵ��λ�����������ľ���ռ2���ֽڵ�
void  LCD12864_display_image(uchar*);        //GDRAM��ͼģʽ
void  LCD12864_clear_GDRAM();                //���GDRAM
uchar LCD12864_receivebyte();                //��ȡ�ֽ�,�Ӹߵ���
uchar LCD12864_read_data();                  //������,RS=H,RW=H
uchar LCD12864_read_status();                //��״̬,RS=L,RW=H

/*��������*/
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
      LCD12864_write_cmd(0x34);             //����ָ�
      LCD12864_write_cmd(0x02);             //��13��,��������CGRAM��ַ
      LCD12864_write_cmd(0x30);             //�ص�����ָ�
      firstadd=(0x40|num<<4);
      for(i=0;i<16;i++)
      {
          LCD12864_write_cmd(firstadd+i);   //����������
          LCD12864_write_data(p[i*2]);
          LCD12864_write_data(p[i*2+1]);
      }
}
void  LCD12864_display_CGRAM(uchar num)
{
      LCD12864_write_data(0x00);            //CGRAM�������ݵ���
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
      LCD12864_write_cmd(0x34);              //����ָ�,��ͼģʽ��
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
      LCD12864_write_cmd(0x34);              //����ָ�,��ͼģʽ��
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