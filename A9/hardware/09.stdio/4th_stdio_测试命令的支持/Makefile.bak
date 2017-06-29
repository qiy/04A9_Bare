reload.bin:start.S system_clock.c uart.c mem_init_tiny4412.S reload.c leds.c stdio.c command.c main.c
	arm-linux-gcc -nostdlib -c -o start.o start.S
	arm-linux-gcc -nostdlib -c -o system_clock.o system_clock.c
	arm-linux-gcc -nostdlib -fno-builtin -c -o uart.o uart.c
	arm-linux-gcc -nostdlib -c -o mem_init_tiny4412.o mem_init_tiny4412.S
	arm-linux-gcc -nostdlib -c -o reload.o reload.c
	arm-linux-gcc -nostdlib -fno-builtin -c -o leds.o leds.c
	arm-linux-gcc -nostdlib -fno-builtin -c -o stdio.o stdio.c
	arm-linux-gcc -nostdlib -fno-builtin -c -o command.o command.c
	arm-linux-gcc -nostdlib -fno-builtin -c -o main.o main.c
	arm-linux-ld -Tboot.lds start.o system_clock.o uart.o mem_init_tiny4412.o reload.o leds.o stdio.o command.o main.o -o reload_elf
	arm-linux-objcopy -O binary -S reload_elf reload.bin
	
clean:
	rm -rf reload_elf ddr3.bin *.o

