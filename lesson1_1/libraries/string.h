#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif
/*函数声明*/
void  String_numtostring(uint,uchar*);
void  String_mergestring(uchar*,uchar*,uchar,uchar,uchar*);      //合并字符串
void  String_strcpy(uchar*,uchar*,uint);                         //拷贝字符串
uchar String_strlen(uchar*);                                     //计算字符串长度

/*函数定义*/
void  String_numtostring(uint num,uchar *p)
{
     uint i,temp,count;
     if(num<10){i=1;p[0]='0';}
     else i=0;
     temp=0;
     count=num==0?1:0;
     while(num)
     {
         temp=temp*10+num%10;
         num/=10;
         count++;
     }
     for(;count--;i++)
     {
         p[i]=temp%10+'0';
         temp/=10;
     }
     p[i]='\0';
}
void  String_mergestring(uchar*a,uchar*b,uchar len1,uchar len2,uchar*c)
{
      uchar temp[21],i;
      for(i=0;i<len1;i++)
      {
          temp[i]=a[i];
      }
      for(;i<len1+len2;i++)
      {
          temp[i]=b[i-len1];
      }
      for(i=0;i<len1+len2;i++)
      {
          c[i]=temp[i];
      }
      c[i]='\0';
}
void  String_strcpy(uchar*a,uchar*b,uint len)
{
      uchar i;
      for(i=0;i<len;i++)
      {
          a[i]=b[i];
      }
}
uchar String_strlen(uchar*a)
{
       uchar i=0;
       while(a[i]!='\0')
       i++;
       return i;
}