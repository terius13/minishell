/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/19 16:08:16 by asyed            ###   ########.fr       */
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

t_ms_state	*init_status()

{
	t_ms_state	*status;

	status = (t_ms_state *)malloc(sizeof(t_ms_state));
	if (status == NULL)
	{
		perror ("status");
		return (NULL);
	}
	status->exit_status = 0;
	return (status);
}

t_env	**init_status_and_envdup(t_ms_state **status, char **env)

{
	t_env	**env_dup;

	*status = init_status();
	if (status == NULL)
		return (NULL);
	env_dup = init_env_copy(env);
	if (env_dup == NULL)
	{
		perror("init_env_copy");
		free(*status);
		*status = NULL;
		return(NULL);
	}
	return (env_dup);
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
	//if (signal_handlers_setup() != 0)
	//	return (1);
	env_dup = init_status_and_envdup(&status, env);
	if (status == NULL || env_dup == NULL)
		return (1);
	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*cmds = NULL;
	while (1)
	{
		line = readline(C "shell@st42:$ " RST);
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO); // Handle Ctrl + D
			rl_clear_history();
			break ; // exit if EOF or error, can be Ctrl + D
		}
		if (line && *line)
		{
			add_history(line);
			if (lexer_and_parse(cmds, line, env_dup))
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
					status->exit_status = execute_builtins(cmds, current->cmd_arr, env_dup, status);
				current = current->next;
			}
			free_cmds(cmds);
		}
	}
	return (status->exit_status);
}
