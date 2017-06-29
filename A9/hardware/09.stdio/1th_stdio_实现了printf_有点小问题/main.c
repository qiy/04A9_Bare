#include "leds.h"
#include "stdio.h"

int main(void)
{
	leds_init();
	leds_test(5);

	putchar('o');
	putchar('k');
	putchar('\n');
	puts("fuck!");
	putchar('\n');
	printf("leds test ok!\n");
	printf("%d leds is on, %d leds is off!\n", 2, 2);

	while(1);

	return 0;
}

