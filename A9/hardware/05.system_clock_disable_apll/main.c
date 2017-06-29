#define GPM4CON		(*(volatile unsigned int *)0x110002E0)
#define GPM4DAT		(*(volatile unsigned int *)0x110002E4)

/* 延时操作函数 */
void delay()
{
	volatile int i = 0x10000;
	while (i--);
}

int main(void)
{
	int i = 0;

	/* 配置GPM4_0,GPM4_1,GPM4_2,GPM4_3为输出引脚 */
	GPM4CON = 0x1111;

	/* GPM4_0,GPM4_1,GPM4_2,GPM4_3输出低电平，完成计数 */
	while (1)
	{		
		GPM4DAT = i;
		i++;
		if (i == 16)
			i = 0;
		delay();
	}

	return 0;
}

