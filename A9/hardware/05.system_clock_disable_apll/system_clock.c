// CMU_CPU
#define CLK_SRC_CPU			(*(volatile unsigned int *)0x10044200)
#define CLK_DIV_CPU0			(*(volatile unsigned int *)0x10044500)
#define CLK_DIV_CPU1			(*(volatile unsigned int *)0x10044504)
// CMU_DMC
#define CLK_SRC_DMC			(*(volatile unsigned int *)0x10040200)
#define CLK_DIV_DMC0		(*(volatile unsigned int *)0x10040500)
#define CLK_DIV_DMC1		(*(volatile unsigned int *)0x10040504)
// CMU_TOP
#define CLK_SRC_TOP0			(*(volatile unsigned int *)0x1003C210)
#define CLK_SRC_TOP1			(*(volatile unsigned int *)0x1003C214)
#define CLK_DIV_TOP			(*(volatile unsigned int *)0x1003C510)
// CMU_LEFTBUS
#define CLK_SRC_LEFTBUS		(*(volatile unsigned int *)0x10034200)
#define CLK_DIV_LEFTBUS		(*(volatile unsigned int *)0x10034500)
// CMU_RIGHTBUS
#define CLK_SRC_RIGHTBUS	(*(volatile unsigned int *)0x10038200)
#define CLK_DIV_RIGHTBUS	(*(volatile unsigned int *)0x10038500)
// locktime
#define APLL_LOCK			(*(volatile unsigned int *)0x10044000)
#define MPLL_LOCK			(*(volatile unsigned int *)0x10044008)
#define EPLL_LOCK			(*(volatile unsigned int *)0x1003C010)
#define VPLL_LOCK			(*(volatile unsigned int *)0x1003C020)
// APLL
#define APLL_CON1			(*(volatile unsigned int *)0x10044104)
#define APLL_CON0			(*(volatile unsigned int *)0x10044100)
// MPLL
#define MPLL_CON0			(*(volatile unsigned int *)0x10040108)
#define MPLL_CON1			(*(volatile unsigned int *)0x1004010c)
// EPLL
#define EPLL_CON2			(*(volatile unsigned int *)0x1003C118)
#define EPLL_CON1			(*(volatile unsigned int *)0x1003C114)
#define EPLL_CON0			(*(volatile unsigned int *)0x1003C110)
// VPLL
#define VPLL_CON0			(*(volatile unsigned int *)0x1003C120)
#define VPLL_CON1			(*(volatile unsigned int *)0x1003C124)
#define VPLL_CON2			(*(volatile unsigned int *)0x1003C128)


/*
 * 函数名:
 *  system_clock_init
 *  功能: 初始化4412的系统时钟
 */
void system_clock_init(void)
{
	/* IROM或BL1设置了APLL,
	 * 本程序设置不启动APLL,
	 * 而是使在晶振时钟, 以体验一下LED闪灯变慢
	 */
	CLK_SRC_CPU = 0x0;
}

