#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
		exit(0);
	else
		printf("parent\n");
	return (0);
}
