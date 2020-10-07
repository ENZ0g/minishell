#include "minishell.h"

int     main(int argc, char **argv, char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	return (0);
}