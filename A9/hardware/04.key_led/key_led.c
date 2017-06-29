
#define GPM4CON     (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT     (*(volatile unsigned int *)0x110002E4)

#define GPX3CON     (*(volatile unsigned int *)0x11000C60)
#define GPX3DAT     (*(volatile unsigned int *)0x11000C64)

int main(void)
{
    int val;
    int i;
    
    /*
     * 配置GPM4_0,GPM4_1,GPM4_2,GPM4_3为输出引脚
     * 对应LED1/2/3/4
     */
    GPM4CON = 0x1111;

    /* 设置K1、K2、K3、K4对应的GPIO(GPX3_2、GPX3_3、GPX3_4、GPX3_5)为输入 */
    GPX3CON &= ~((0xf << 8) | (0xf << 12) | (0xf << 16) | (0xf << 20));
        
    while (1)
    {
        val = GPX3DAT;           /* 读出按键引脚状态 */
        
        for (i = 2; i <= 5; i++)
        {
            if (val & (1<<i)) /* 某个按键是松开状态 : 高电平 */
            {
                /* 熄灭对应LED : GPIO输出高电平 */
                GPM4DAT |= (1 << (i - 2));
            }   
            else
            {
                /* 否则点亮对应LED : GPIO输出低电平 */
                GPM4DAT &= ~(1 << (i - 2));
            }
        }
     }

    return 0;
}
