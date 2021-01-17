#include"DHT11.h"

void main()
{
    COM_init();
    DHT11_init();
    if(!flag)
    {
        byte1=DHT11_readbyte();
        byte2=DHT11_readbyte();
        byte3=DHT11_readbyte();
        byte4=DHT11_readbyte();
        byte5=DHT11_readbyte();
        COM_send("初始化成功！\n");
        DHT11_check();
        if(flag)
        {
            COM_send("校验成功！\n");
            COM_send("当前温度是:");
            COM_send(DHT11_string(byte3));
            COM_send(".");
            COM_send(DHT11_string(byte4));
            COM_send("℃ ");
            COM_send("当前湿度是:");
            COM_send(DHT11_string(byte1));
            COM_send(".");
            COM_send(DHT11_string(byte2));
            COM_send("%\n");
        }
        else
        {
            COM_send("校验失败！\n");
        }  
    }
    DHT11_delay1s();
}