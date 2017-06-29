#include "leds.h"
#include "stdio.h"

static int help(int argc, char * argv[])
{
	printf("do command <%s>\n", argv[0]);
	printf("help message: \n");
	printf("leds <num> - display num by leds\n");

	return 0;
}

void parse_run_command(int argc, char * argv[])
{
	if (strcmp(argv[0], "help") == 0)
	{
		help(argc, argv);
		return;
	}

	if (strcmp(argv[0], "leds") == 0)
	{
		do_leds(argc, argv);
		return;
	}
}

