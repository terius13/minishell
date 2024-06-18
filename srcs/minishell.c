/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:58:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/18 10:26:02 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*


int	signal_handlers_setup()

{
	struct sigaction	sa_int;

	sa_int.sa_handler = sigint_handler;


}

*/
/*
int	main(int ac, char **av, char **env)
{
	char		*line;
	t_cmd		**cmds;
	t_env		**env_dup;
	t_cmd		*current;
	t_ms_state	*update;

	(void)ac;
	(void)av;

	// signal_handlers_setup();
	update = (t_ms_state *)malloc(sizeof(t_ms_state));
	if (update == NULL)
	{
		perror ("init_env_copy");
		return (1);
	}
	update->exit_status = 0;
	env_dup = init_env_copy(env);
	if (env_dup == NULL)
	{
		perror ("init_env_copy");
		free(update);
		return (1);
	}
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
			if (lexer_and_parse(cmds, line, env_dup, update))
			{
				free_cmds(cmds);
				free(line); //prob dont need to free, only in exit
				continue;
			}
			free(line);
			current = *cmds;
			while(current)
			{
				do_redirection(current, update);
				if (current->builtin)
				{
					perror("Entering builtin");
					execute_builtins(cmds, current->cmd_arr, env_dup, update);
				}
				current = current->next;
			}
			free_cmds(cmds);
		}
	}
}
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char *find_command_path(char *command, char **env) {
    char *path_env = NULL;
    char *paths = NULL;
    char **dirs = NULL;
    char *command_path = NULL;
    int i = 0;

    while (env[i]) {
        if (strncmp(env[i], "PATH=", 5) == 0) {
            path_env = env[i] + 5; // Skip "PATH="
            break;
        }
        i++;
    }

    if (!path_env) {
        return NULL; // PATH not found
    }

    paths = strdup(path_env);
    dirs = ft_split(paths, ':'); // Assuming you have a split function like ft_split

    i = 0;
    while (dirs[i]) {
        command_path = malloc(strlen(dirs[i]) + strlen(command) + 2);
        if (!command_path) {
            perror("malloc");
            return NULL;
        }
        strcpy(command_path, dirs[i]);
        strcat(command_path, "/");
        strcat(command_path, command);

        if (access(command_path, X_OK) == 0) {
            free(paths);
            // Free other allocations if necessary
            return command_path;
        }

        free(command_path);
        i++;
    }

    free(paths);
    // Free other allocations if necessary
    return NULL;
}


int main(int ac, char **av, char **env) {
    char *line;
    t_cmd **cmds;
    t_env **env_dup;
    t_cmd *current;
    t_ms_state *update;
    pid_t pid;
    int status;

    (void)ac;
    (void)av;

    update = (t_ms_state *)malloc(sizeof(t_ms_state));
    if (update == NULL) {
        perror("init_env_copy");
        return 1;
    }
    update->exit_status = 0;
    env_dup = init_env_copy(env);
    if (env_dup == NULL) {
        perror("init_env_copy");
        free(update);
        return 1;
    }
    cmds = (t_cmd **)malloc(sizeof(t_cmd *));
    *cmds = NULL;

    while (1) {
        line = readline("shell@st42:$ ");
        if (line == NULL) {
            ft_putendl_fd("exit", STDOUT_FILENO);
            rl_clear_history();
            break;
        }
        if (line && *line) {
            add_history(line);
            if (lexer_and_parse(cmds, line, env_dup, update)) {
                free_cmds(cmds);
                free(line);
                continue;
            }
            free(line);
            current = *cmds;
            while (current) {
                pid = fork();
                if (pid == 0) {
                    if (do_redirection(current, update)) {
                        exit(update->exit_status);
                    }
                    if (current->builtin) {
                        execute_builtins(cmds, current->cmd_arr, env_dup, update);
                        exit(update->exit_status);
                    } else {
                        char *cmd_path = find_command_path(current->cmd_arr[0], env);
                        if (cmd_path) {
                            execve(cmd_path, current->cmd_arr, env);
                            perror("execve");
                            free(cmd_path);
                        } else {
                            fprintf(stderr, "Command not found: %s\n", current->cmd_arr[0]);
                        }
                        exit(1);
                    }
                } else if (pid < 0) {
                    perror("fork");
                    return 1;
                } else {
                    waitpid(pid, &status, 0);
                    if (WIFEXITED(status)) {
                        update->exit_status = WEXITSTATUS(status);
						if (current->builtin) {
                        execute_builtins(cmds, current->cmd_arr, env_dup, update);
						//exit only works in parent process
						}
                    }
                }
                current = current->next;
            }
            free_cmds(cmds);
        }
    }

    // Cleanup code...

    return 0;
}


