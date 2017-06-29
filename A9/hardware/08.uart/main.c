
void uart_init(void);
char getc(void);
void putc(char c);
void puts(char *s);

int main(void)
{
	char c;
	
	uart_init();
	puts("Test UART: add one and output\n\r");
	
	while (1)
	{
		c = getc();
		putc(c+1);
	}
	return 0;
}

