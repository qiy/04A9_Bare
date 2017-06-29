#include "uart.h"

void putchar(char c)
{
	if(c == '\r')
	{
		putc('\n');
	}

	if(c == '\n')
	{
		putc('\r');
	}

	putc(c);
}

int getchar(void)
{
	int c;

	c = (int)getc();

	if (c == '\r')
		return '\n';

	return c;
}

void puts(const char * s)
{
	while(*s)
		putchar(*s++);
}

char * gets(char * s)
{
	char * p = s;

	while ((*p = getchar()) != '\n')
	{
		if (*p != '\b')
		{
			putchar(*p++);
		}
		else	
		if (p > s)
		{
			puts ("\b \b");
			p--;
		}			
	}
	
	*p = '\0';
	putchar('\n');

	return s;
}

void putchar_hex(char c)
{
	char * hex = "0123456789ABCDEF";

	putc(hex[(c>>4) & 0x0F]);
	putc(hex[(c>>0) & 0x0F]);
}

void putint_hex(int a)
{
	putchar_hex( (a>>24) & 0xFF );
	putchar_hex( (a>>16) & 0xFF );
	putchar_hex( (a>>8) & 0xFF );
	putchar_hex( (a>>0) & 0xFF );
}

char * itoa(int a, char * buf)
{
	int num = a;
	int i = 0;
	int len = 0;

	do
	{
		buf[i++] = num % 10 + '0';
		num /= 10;
	}while (num);
	buf[i] = '\0';

	len = i;
	for (i = 0; i < len/2; i++)
	{
		char tmp;
		tmp = buf[i];
		buf[i] = buf[len-i-1];
		buf[len-i-1] = tmp;
	}
	
	return buf;
}

typedef int * va_list;
#define va_start(ap, A)		(ap = (int *)&(A) + 1)
#define va_arg(ap, T)		(*(T *)ap++)
#define va_end(ap)		((void)0)

int printf(const char * format, ...)
{
	char c;	
	va_list ap;
		
	va_start(ap, format);
	
	while ((c = *format++) != '\0')
	{
		switch (c)
		{
			case '%':
				c = *format++;
				
				switch (c)
				{
					char ch;
					char * p;
					int a;
					char buf[100];
									
					case 'c':
						ch = va_arg(ap, int);
						putchar(ch);
						break;
					case 's':
						p = va_arg(ap, char *);
						puts(p);
						break;					
					case 'x':
						a = va_arg(ap, int);
						putint_hex(a);
						break;		
					case 'd':
						a = va_arg(ap, int);
						itoa(a, buf);
						puts(buf);
						break;	
					
					default:
						break;
				}				
				break;		
		
			default:
				putchar(c);
				break;
		}
	}
	
	return 0;	
}

int strcmp(const char * s1, const char * s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return 0;	
		s1++;
		s2++;				
	}

	return *s1 - *s2;
}

