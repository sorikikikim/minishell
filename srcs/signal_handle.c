#include "../includes/minishell.h"
#include <signal.h>

static void	handle_signal2(int signo, int pid)
{
	if (signo == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \b\b", STDOUT);
		}
		else
			ft_putstr_fd("Quit: 3\n", STDOUT);
	}
}

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \n", STDOUT);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", STDOUT);
	}
	else
		handle_signal2(signo, pid);
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
