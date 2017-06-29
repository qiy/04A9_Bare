
objs := start.o system_clock.o uart.o uart.o main.o

uart.bin : $(objs)
	arm-linux-gnueabihf-ld -Tuart.lds -o uart.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S uart.elf $@
	arm-linux-gnueabihf-objdump -D -m arm  uart.elf > uart.dis

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -marm -fno-builtin -c -O2 -o $@ $<

%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f  *.dis *.bin *.elf *.o
	
	

