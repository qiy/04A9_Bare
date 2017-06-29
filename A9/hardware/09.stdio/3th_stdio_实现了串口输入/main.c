#include "leds.h"
#include "stdio.h"

#define	CFG_PROMPT		"100ask # "	/* Monitor Command Prompt	*/
#define	CFG_CBSIZE		256		/* Console I/O Buffer Size	*/

static char *argv[10];

static int readline (const char *const prompt)
{
	char console_buffer[CFG_CBSIZE];		/* console I/O buffer	*/
	char *buf = console_buffer;
	int argc = 0;
	int state = 0;

	printf("%s",prompt);
	gets(console_buffer);

	while(*buf)
	{
		if (*buf != ' ' && state == 0)
		{
			argv[argc++] = buf;
			state = 1;
		}
		
		if (*buf == ' ' && state == 1)
		{
			*buf = '\0';
			state = 0;
		}
		
		buf++;	
	}
	
	return argc;
}

int main(void)
{
	int argc = 0;

	leds_init();
	leds_test(5);

	printf("\n**********************************************************\n");
	printf("\nDesigned by 100ask in ShenZhen\n");
	printf("    http://www.100ask.net/\n");
	printf("    http://100ask.taobao.com/\n");
	printf("\n**********************************************************\n");

	while(1)
	{
		argc = readline (CFG_PROMPT);
	}

	return 0;
}

