/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:10:54 by ting              #+#    #+#             */
/*   Updated: 2024/06/28 17:22:38 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_reset_cancel;

int	illegal_builtins(t_cmd *current)
{
	if (current->builtin && (!ft_strcmp(current->cmd_arr[0], "cd")
			|| !ft_strcmp(current->cmd_arr[0], "export")
			|| !ft_strcmp(current->cmd_arr[0], "unset")
			|| !ft_strcmp(current->cmd_arr[0], "exit")))
	{
		return (1);
	}
	return (0);
}

void	free_n_exit_child(t_pipeline *pipeline)
{
	int	stat;
	int	num_cmds;

	num_cmds = cmds_len((*pipeline->cmds));
	stat = pipeline->status->exit_status;
	free_all_and_exit(pipeline->cmds, pipeline->env, pipeline->status);
	free_pipe_ends(pipeline->pipe_ends, num_cmds);
	free(pipeline);
	exit(stat);
}

void	execute_cmd(t_cmd *cmd, t_env **env, t_ms_state *status)
{
	char	*cmd_path;

	cmd_path = find_path(cmd->cmd_arr[0], env);
	if (cmd_path)
	{
		execve(cmd_path, cmd->cmd_arr, env_in_arr(env));
		free(cmd_path);
	}
	else
	{
		printf("%s: command not found\n", cmd->cmd_arr[0]);
		status->exit_status = 127;
	}
}

char	*trim_whitespace(char *str)
{
	char	*end;

	// Trim leading space
	while (*str == ' ' || *str == '\n' || *str == '\r')
		str++;

	if (*str == 0)
		return (str);

	// Trim trailing space
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\n' || *end == '\r'))
		end--;

	// Write new null terminator
	*(end + 1) = '\0';
	return (str);
}

char *env_var_heredoc(char *line, t_env **env, t_ms_state *stat)
{
    char *result;
    char *end;
    char *var_name;
    char *var_value;
    char *normal_char;
    char *temp_result;
	int		free_flag;

    result = ft_strdup("");
	free_flag = 0;
    while (*line)
    {
        if (*line == '$' && (ft_isalnum(*(line + 1)) || *(line + 1) == '?'))
        {
            end = line + 1;
			if (*end == '?')
                end++;
            else
                while (ft_isalnum(*end) || *end == '_')
                    end++;
            var_name = ft_substr(line + 1, 0, end - line - 1);
			printf("Variable name: %s\n", var_name); 
			var_value = get_env_value(var_name, &free_flag, env, stat);
            printf("Variable value: %s\n", var_value);  
            if (var_value)
                temp_result = ft_strjoin(result, var_value);
            else
                temp_result = ft_strdup(result);
            free(result);  // Free previous result
            result = temp_result;
            line = end;  // Move line pointer past the variable name
			if (free_flag)
				free(var_value);
        }
        else
        {
            normal_char = ft_substr(line, 0, 1);
            temp_result = ft_strjoin(result, normal_char);
            free(result);  // Free previous result
            free(normal_char);  // Free normal_char after use
            result = temp_result;
            line++;  // Move to the next character in the input line
        }
    }
    return (result);
}


void	here_doc(t_cmd *current, t_env **env, t_ms_state *stat)
{
	char	*line;
	int		fd;
	char	*file;
	char	*trimmed_line;

	if (!current->hdoc_delimeter)
		return;
	file = "./heredoc.tmp";
	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);

	while (1)
	{
		if (g_reset_cancel)
		{
			g_reset_cancel = 0;
			continue;
		}
		write(1, "> ", 2);
		if (g_reset_cancel)
		{
			printf("test1\n");
			break;
		}
		line = get_next_line(0);
		if (g_reset_cancel)
		{
			free (line);
			break;
		}
		if (!line)
		{
			printf("shell@st42:$ warning: here-document delimited by end-of-file (wanted `%s')\n", current->hdoc_delimeter);
			break;
		}
		trimmed_line = trim_whitespace(env_var_heredoc(line, env, stat));
		if (ft_strcmp(trimmed_line, current->hdoc_delimeter) == 0)
		{
			free(line);
			free(trimmed_line);
			trimmed_line = NULL;
			break;
		}
		ft_putendl_fd(trimmed_line, fd);
		free(trimmed_line);
		free(line);
	}
	close(fd);
	if (!current->infile)
		current->infile = ft_calloc(2, sizeof(char *));
	add_to_arr(&(current->infile), file);
}

void	do_single_cmd(t_cmd **cmds, t_env **env, t_ms_state *status)
{
	int	pid;
	int	stat;
	int	exit_status;

	if (illegal_builtins((*cmds)))
		return (execute_builtins(cmds, (*cmds)->cmd_arr, env, status));
	here_doc((*cmds), env, status);
	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
	{
		do_redirection((*cmds), status);
		if ((*cmds)->builtin)
			execute_builtins(cmds, (*cmds)->cmd_arr, env, status);
		else if ((*cmds)->cmd_arr[0])
			execute_cmd((*cmds), env, status);
		stat = status->exit_status;
		free_all_and_exit(cmds, env, status);
		exit(stat);
	}
	wait(&exit_status);
	if (WIFEXITED(exit_status))
		status->exit_status = WEXITSTATUS(exit_status);
}

void	execute_child_process(t_pipeline *pipeline, t_cmd *current, int i)
{
	init_dup(pipeline->num_cmds, i, pipeline->pipe_ends);
	do_redirection(current, pipeline->status);
	if (illegal_builtins(current))
		free_n_exit_child(pipeline);
	if (current->builtin)
		execute_builtins(&current, current->cmd_arr, pipeline->env,
			pipeline->status);
	else if (current->cmd_arr[0])
		execute_cmd(current, pipeline->env, pipeline->status);
	free_n_exit_child(pipeline);
}
