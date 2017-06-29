// GPIO
#define GPA0CON             (*(volatile unsigned int *)0x11400000)
#define GPA1CON             (*(volatile unsigned int *)0x11400020)
// system clock
#define CLK_SRC_PERIL0      (*(volatile unsigned int *)0x1003C250)
#define CLK_DIV_PERIL0      (*(volatile unsigned int *)0x1003C550)
// UART
#define UFCON0              (*(volatile unsigned int *)0x13800008)
#define ULCON0              (*(volatile unsigned int *)0x13800000)
#define UCON0               (*(volatile unsigned int *)0x13800004)
#define UBRDIV0             (*(volatile unsigned int *)0x13800028)
#define UFRACVAL0           (*(volatile unsigned int *)0x1380002c)
#define UTXH0               (*(volatile unsigned int *)0x13800020)
#define URXH0				(*(volatile unsigned int *)0x13800024)

#define UTRSTAT0            (*(volatile unsigned int *)0x13800010)


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

void puts(char *s)
{
    while (*s)
    {
        putc(*s);
        s++;
    }
}

void uart_init(void)
{
    /* 1.设置相应的GPIO用于串口功能 */
    GPA0CON = 0x22222222;
    GPA1CON = 0x222222;

    /* 2.设置UART时钟源SCLK_UART */
    /* 2.1 CLK_SRC_DMC  : bit[12]即MUX_MPLL_SEL=1, SCLKMPLLL使用MPLL的输出
     * 2.2 CLK_SRC_TOP1 : bit[12]即MUX_MPLL_USER_SEL_T=1, MUXMPLL使用SCLKMPLLL
     * 2.3 CLK_SRC_PERIL0 : bit[3:0]即UART0_SEL=6, MOUTUART0使用SCLKMPLL_USER_T
     * 所以, MOUTUART0即等于MPLL的输出, 800MHz
     */
    /*
     *   PWM_SEL = 0;
     *   UART5_SEL = 0;
     *   UART4_SEL = 6;      // 串口时钟源选 SCLKMPLL_USER_T
     *   UART3_SEL = 6;
     *   UART2_SEL = 6;
     *   UART1_SEL = 6;
     *   UART0_SEL = 6;
     */
    CLK_SRC_PERIL0 = ((0 << 24) | (0 << 20) | (6 << 16) | (6 << 12) | (6<< 8) | (6 << 4)    | (6));

    /*
     × 分频系数 = 7+1 = 8
     * 2.4 CLK_DIV_PERIL0 : bit[3:0]即UART0_RATIO=7,所以SCLK_UART0=MOUTUART0/(7+1)=100MHz
     */
    CLK_DIV_PERIL0 = ((7 << 20) | (7 << 16) | (7 << 12) | (7 << 8) | (7 << 4) | (7));

    /* 3.设置串口0相关 */
    /* 设置FIFO中断触发阈值
     * 使能FIFO
     */
    UFCON0 = 0x111;
    
    /* 设置数据格式: 8n1, 即8个数据位,没有较验位,1个停止位 */
    ULCON0 = 0x3;
    
    /* 工作于中断/查询模式
     * 另一种是DMA模式,本章不使用
     */
    UCON0  = 0x5;
    
    /* SCLK_UART0=100MHz, 波特率设置为115200
     * 寄存器的值如下计算:
     *    DIV_VAL   = 100,000,000 / (115200 * 16)   - 1 = 53.25
     *    UBRDIVn0  = 整数部分 = 53
     *    UFRACVAL0 = 小数部分 x 16 = 0.25 * 16 = 4
     */
    UBRDIV0 = 53;
    UFRACVAL0 = 4;
}
