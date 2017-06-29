objs := start.o leds.o

leds.bin : $(objs)
	arm-linux-gnueabihf-ld -Tleds.lds -N -o leds.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S leds.elf $@
	arm-linux-gnueabihf-objdump -D -m arm  leds.elf > leds.dis

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -marm -c -O2 -o $@ $<

%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f  *.dis *.bin *.elf *.o
	
