
#define GPM4CON		(*(volatile unsigned int *)0x110002E0)
#define GPM4DAT		(*(volatile unsigned int *)0x110002E4)


int main(void)
{
	unsigned long tmp = 0;

	/*
	 * set GPM4_0 as output
	 */
	tmp = GPM4CON;
	tmp &= ~0xf;
	tmp |= 1;
	GPM4CON = tmp;
	
	/* GPM4_0 output low */
	GPM4DAT &= ~1;

	return 0;
}
