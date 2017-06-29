
objs := start.o system_clock.o main.o

system_clock.bin : $(objs)
	arm-linux-gnueabihf-ld -Tsystem_clock.lds -o system_clock.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S system_clock.elf $@
	arm-linux-gnueabihf-objdump -D -m arm  system_clock.elf > system_clock.dis

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -marm -c -O2 -o $@ $<

%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -marm -c -O2 -o $@ $<

clean:
	rm -f  *.dis *.bin *.elf *.o
	
	

