// GPIO
#define GPA0CON				(*(volatile unsigned int *)0x11400000)
#define GPA1CON				(*(volatile unsigned int *)0x11400020)
// system clock
#define CLK_SRC_PERIL0		(*(volatile unsigned int *)0x1003C250)
#define CLK_DIV_PERIL0		(*(volatile unsigned int *)0x1003C550)
// UART
#define ULCON0				(*(volatile unsigned int *)0x13800000)
#define UCON0				(*(volatile unsigned int *)0x13800004)
#define UBRDIV0				(*(volatile unsigned int *)0x13800028)
#define UFRACVAL0			(*(volatile unsigned int *)0x1380002c)
#define UTXH0				(*(volatile unsigned int *)0x13800020)
#define URXH0				(*(volatile unsigned int *)0x13800024)
#define UTRSTAT0				(*(volatile unsigned int *)0x13800010)

void uart_init(void)
{
	/* 1.设置相应的GPIO用于串口功能 */
	GPA0CON = 0x22222222;
	GPA1CON = 0x222222;

	/* 2.设置SCLK_UART */
	/*
		PWM_SEL = 0;
		UART5_SEL = 0;
		UART4_SEL = 6;		// 串口时钟源选 SCLKMPLL_USER_T
		UART3_SEL = 6;
		UART2_SEL = 6;
		UART1_SEL = 6;
		UART0_SEL = 6;
	*/
	CLK_SRC_PERIL0 = ((0 << 24) | (0 << 20) | (6 << 16) | (6 << 12) | (6<< 8) | (6 << 4)	| (6));
	/*
		分频系数 = 7+1 = 8
	*/
	CLK_DIV_PERIL0 = ((7 << 20) | (7 << 16) | (7 << 12) | (7 << 8) | (7 << 4) | (7));

	/* 3.设置串口0相关 */
	/* bit[1:0]:0x3 = 8位数据位
	 * 其他位默认,即1位停止位，无校验，正常模式
	 */
	ULCON0 = 0x3;

	/*
	 * Receive Mode [1:0]:1 = 接收采用查询或者中断模式
	 * Transmit Mode[3:2]:1 = 发送采用查询或者中断模式
	 * bit[6]:1 = 产生错误中断
	 * bit[10]:0 = 时钟源为PCLK
	 */
	UCON0 = (1<<6)|(1<<2)|(1<<0);

	/* 设置波特率 */
	UBRDIV0 = 0x35;
	UFRACVAL0 = 0x4;
}

char getc(void)
{
	char c;
	/* 查询状态寄存器，直到有有效数据 */
	while (!(UTRSTAT0 & (1<<0)));
	
	c = URXH0; /* 读取接收寄存器的值 */
		
	return c;
}

void putc(char c)
{
	/* 查询状态寄存器，直到发送缓存为空 */
	while (!(UTRSTAT0 & (1<<2)));
	
	UTXH0 = c; /* 写入发送寄存器 */
	
	return;
}

