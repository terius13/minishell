/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/20 20:25:32 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	signal_handlers_setup()

{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask)
	
	sa_int.sa_handler = sigint_handler;
}
*/

void	sigignore_handler()
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler()

{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	signal_handlers_setup(void)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_quit;	
	
	sa_ignore.sa_handler = sigignore_handler;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	if (sigaction(SIGINT, &sa_ignore, NULL) == -1)
	{
		perror("SIGINT");
		return (1);
	}
	sa_quit.sa_handler = sigquit_handler;
	sigemptyset(&sa_ignore.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("SIGQUIT");
		return (1);
	}
	return (0);
}
int	main(int ac, char **av, char **env)
{
	char		*line;
	t_cmd		**cmds;
	t_env		**env_dup;
	t_cmd		*current;
	t_ms_state	*status;

	(void)ac;
	(void)av;
	if (signal_handlers_setup() != 0)
		return (1);
	status = init_status();
	env_dup = init_envdup(status, env);
	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*cmds = NULL;
	while (1)
	{
		line = readline(C "shell@st42:$ " RST);
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO); // Handle Ctrl + D
			rl_clear_history();
			free_all_and_exit(cmds, env_dup, status);
			exit(EXIT_SUCCESS); // EOF, Ctrl + D
		}
		if (line && *line)
		{
			add_history(line);
			if (lexer_and_parse(cmds, line, env_dup, status))
			{
				free_cmds(cmds);
				free(line); //prob dont need to free, only in exit
				continue;
			}
			free(line);
			current = *cmds;
			while(current)
			{
				if (current->builtin)
					execute_builtins(cmds, current->cmd_arr, env_dup, status);
				current = current->next;
			}
			free_cmds(cmds);
		}
	}
	return (status->exit_status);
}
