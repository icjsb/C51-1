#include"libraries\DS1302.h"
#include"libraries\12864libs.h"
#include"libraries\string.h"
#include"libraries\delay.h"
uchar str[21],str1[21];
uchar temp;
void main()
{
     LCD12864_init();
     //设置XX年,XX月,XX日,XX时,XX分,XX秒,星期X,12/24
     DS1302_init();
     //设置2021年
     DS1302_Write_Data(YearWrite,0x21);
     //设置1月份
     DS1302_Write_Data(MonthWrite,0x01);
     //设置21号
     DS1302_Write_Data(DateWrite,0x21);
     //设置星期三
     DS1302_Write_Data(DayWrite,0x03);
     //设置10时,12小时制
     DS1302_Write_Data(HourWrite,0x90);
     //设置27分
     DS1302_Write_Data(MinuteWrite,0x50);
     //设置31秒
     DS1302_Write_Data(SecondWrite,0x31);
     
     while(1)
     {    
          //LCD12864_clear_DDRAM();刷新屏幕
          //合成"20XX年"字符串
          String_numtostring(2000+DS1302_convert_Data(YearRead,DS1302_Read_Data(YearRead)),str);
          String_mergestring(str,"年",String_strlen(str),String_strlen("年"),str);
          LCD12864_showstring(str,0,0);
          //合成"01月"字符串
          String_numtostring(DS1302_convert_Data(MonthRead,DS1302_Read_Data(MonthRead)),str);
          String_mergestring(str,"月",String_strlen(str),String_strlen("月"),str);
          LCD12864_showstring(str,0,4);
          //合成"20日"字符串
          String_numtostring(DS1302_convert_Data(DateRead,DS1302_Read_Data(DateRead)),str);
          String_mergestring(str,"日",String_strlen(str),String_strlen("日"),str);
          LCD12864_showstring(str,0,6);

          temp=DS1302_Read_Data(HourRead);
          if(temp>>7)
          {
               if((temp>>5)%2)LCD12864_showstring("PM",1,0);
               else LCD12864_showstring("AM",1,0);
          }
          
          temp=DS1302_Read_Data(DayRead);
          switch (temp)
          {
          case 1:LCD12864_showstring("星期一",1,3);
                 break;
          case 2:LCD12864_showstring("星期二",1,3);
                 break;
          case 3:LCD12864_showstring("星期三",1,3);
                 break;
          case 4:LCD12864_showstring("星期四",1,3);
                 break;
          case 5:LCD12864_showstring("星期五",1,3);
                 break;
          case 6:LCD12864_showstring("星期六",1,3);
                 break; 
          case 7:LCD12864_showstring("星期日",1,3);
                 break;     
          }

          String_numtostring(DS1302_convert_Data(HourRead,DS1302_Read_Data(HourRead)),str);
          String_mergestring(str,":",String_strlen(str),String_strlen(":"),str);
          String_numtostring(DS1302_convert_Data(MinuteRead,DS1302_Read_Data(MinuteRead)),str1);
          String_mergestring(str,str1,String_strlen(str),String_strlen(str1),str);
          LCD12864_showstring(str,2,3);

          temp=DS1302_Read_Data(SecondRead);
          String_numtostring(DS1302_convert_Data(SecondRead,temp),str);
          LCD12864_showstring(str,3,7);
          delay1ms(1000);
          while(temp==DS1302_Read_Data(SecondRead));
     }
     
}