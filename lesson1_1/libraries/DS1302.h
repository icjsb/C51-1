#include<REG52.H>
#include<INTRINS.H>
#include"DS1302name.h"
#define uchar unsigned char
#define uint unsigned int

/*���Ŷ���*/
sbit CE = P1^0;
sbit SK = P1^1;
sbit IO = P1^2;

/*��������*/
void  DS1302_init();
void  DS1302_Write_Data(uchar,uchar);            //д����
uchar DS1302_Read_Data (uchar);                  //������
uchar DS1302_convert_Data(uchar,uchar);
/*��������*/
void  DS1302_init()
{      
      DS1302_Write_Data(SecondWrite,0x80);     //����ʱ����ͣλ
}
void  DS1302_Write_Data(uchar address,uchar Data)
{
      uchar i;
      //��ʼ��ƽ
      CE=0;
      SK=0;
      _nop_();
      //��ʼ���� 
      CE=1;
      //�����ַ
      for(i=0;i<8;i++)
      {
          SK=0;
          _nop_();            //�Ӹߵ���1us
          IO=address&0x01;    //׼�����ݲ�����
          _nop_();            //����������ʱ1us
          SK=1;              //ʱ���ź�������
          _nop_();            //�ӵ͵���1us
          address>>=1;
      }
      //��������
      for(i=0;i<8;i++)
      {
          SK=0;
          _nop_();            //�Ӹߵ���1us
          IO=Data&0x01;       //׼�����ݲ�����
          _nop_();            //����������ʱ1us
          SK=1;              //ʱ���ź�������
          _nop_();            //�ӵ͵���1us
          Data>>=1;
      }
      CE=0;
      _nop_();
}
uchar DS1302_Read_Data (uchar address)
{
      uchar i,result=0;
      //��ʼ��ƽ
      CE=0;
      SK=0;
      _nop_();
      //��ʼ���� 
      CE=1;
      //�����ַ
      for(i=0;i<8;i++)
      {
          SK=0;
          _nop_();            //�Ӹߵ���1us
          IO=address&0x01;    //׼�����ݲ�����
          _nop_();            //����������ʱ1us
          SK=1;              //ʱ���ź�������
          _nop_();            //�ӵ͵���1us
          address>>=1;
      }
      IO=1;                   //�ͷ�����
      for(i=0;i<8;i++)
      {
          result>>=1;
          SK=1;
          _nop_();
          SK=0;
          _nop_();
          if(IO)
          result|=0x80;
      }
      return result;
}  
uchar DS1302_convert_Data(uchar address,uchar Data)
{
      if(address==HourRead&&Data>>7)//bit7Ϊ1,12Сʱ�� 
      {
          return ((Data>>4)%2)*10+Data%16;
      }
      else
      {
          return Data/16*10+Data%16;
      }
}

