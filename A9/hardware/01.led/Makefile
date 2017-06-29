led.bin : led.S
	arm-linux-gnueabihf-gcc -c -o led.o led.S
	arm-linux-gnueabihf-ld -Tled.lds -N led.o -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S led.elf led.bin
	arm-linux-gnueabihf-objdump -D -m arm  led.elf > led.dis
clean:
	rm -f *.dis *.bin *.elf *.o

	

