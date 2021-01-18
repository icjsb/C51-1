#include"12864libs.h"

uchar str1[17]="年轻人不讲武德啊";

void main()
{
   uint i=0;
   LCD12864_init();
   LCD12864_pos(1,0);
   while(str1[i]!='\0')
   {
       LCD12864_write_data(str1[i]);
       i++;
   }
   while(1);
}
/*总结下来有三个错误点
  1. 判忙函数写错了
  2. 读取状态和数据的函数写成死循环
  3. 写指令函数没有将CS置高电平,若不用判忙函数又会少一个字节
*/