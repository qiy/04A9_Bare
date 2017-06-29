
#define SDMMC_ReadBlocks(uStartBlk, uNumOfBlks, uDstAddr)	\
	(((void(*)(unsigned int, unsigned int, unsigned int *))(*((unsigned int *)0x02020030)))(uStartBlk, uNumOfBlks, uDstAddr))
#define CORE_START_BLK		49				// 我们是把代码下载到这里的
#define CORE_BLKCNT			200				// 100K
#define CORE_DST_ADDR		0x43e00000		// 0x40000000 + 0x3e00000

void clear_bss(void)
{
	extern int __bss_start, __bss_end;
	int *p = &__bss_start;

	for (; p < &__bss_end; p++)
		*p = 0;
}

void reload_core_sd_boot(void)
{
	SDMMC_ReadBlocks(CORE_START_BLK, CORE_BLKCNT, (unsigned int *)CORE_DST_ADDR);
}

