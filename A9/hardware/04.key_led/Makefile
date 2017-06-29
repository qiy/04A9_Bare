objs := start.o key_led.o

key_led.bin : $(objs)
	arm-linux-gnueabihf-ld -Tkey_led.lds -o key_led.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S key_led.elf $@
	arm-linux-gnueabihf-objdump -D -m arm  key_led.elf > key_led.dis

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -marm -c -O2 -o $@ $<

%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f  *.dis *.bin *.elf *.o
	