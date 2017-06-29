#define GPM4CON		(*(volatile unsigned int *)0x110002E0)
#define GPM4DAT		(*(volatile unsigned int *)0x110002E4)

void leds_init(void)
{
	/* ÅäÖÃGPM4_0,GPM4_1,GPM4_2,GPM4_3ÎªÊä³öÒı½Å */
	GPM4CON = 0x1111;
}

void leds_test(int num)
{
	GPM4DAT = 0;
	GPM4DAT = num;
}

