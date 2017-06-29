.text
.global _start
_start:
	LDR SP, =0x02027800		/* 设置堆栈，注意：这个地址范围只能在Iram中(见iROM手册P14：0x02027800 = 0x02020000(iRAM基地址) + 5K + 8K + 16K + 1K) */
	BL system_clock_init
	BL uart_init
	BL mem_ctrl_asm_init
	BL reload_core_sd_boot
	LDR SP, =0x42e00000
	bl clear_bss
	BL main					/* 调用C程序中的main函数 */
MAIN_LOOP:
	B MAIN_LOOP