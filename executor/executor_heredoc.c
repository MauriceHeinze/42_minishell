/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:02:52 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 14:05:29 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	check_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '1')
		return (1);
	return (0);
}

static void	sub_write_loop(int file, t_var *envp, char **split, int *i)
{
	int		var_length;
	char	*var;

	while (split[*i] != NULL)
	{
		var_length = 0;
		while (check_char(split[*i][var_length]))
			var_length++;
		var = malloc(sizeof(char) * (var_length + 1));
		ft_strlcpy(var, split[*i], var_length + 1);
		var[var_length] = '\0';
		if (get_env(envp, var))
			write(file, get_env(envp, var), ft_strlen(get_env(envp, var)));
		while (split[*i][var_length] != '\0')
			write(file, &(split[*i][var_length++]), 1);
		free(var);
		*i = *i + 1;
	}
}

static void	sub_write(int file, char *buffer, t_var *envp, char **split)
{
	int		i;
	int		var_length;
	char	*var;

	i = 0;
	if (*buffer != '$')
	{
		write(file, split[i], ft_strlen(split[i]));
		i++;
	}
	while (split[i] != NULL)
	{
		var_length = 0;
		while (check_char(split[i][var_length]))
			var_length++;
		var = malloc(sizeof(char) * (var_length + 1));
		ft_strlcpy(var, split[i], var_length + 1);
		var[var_length] = '\0';
		if (get_env(envp, var))
			write(file, get_env(envp, var), ft_strlen(get_env(envp, var)));
		while (split[i][var_length] != '\0')
			write(file, &(split[i][var_length++]), 1);
		free(var);
		i++;
	}
}

static void	heredoc(t_executor	*executor, t_var *envp)
{
	int		file;
	char	*buffer;
	char	*ret;
	char	**split;

	if (executor == NULL)
		return ;
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return ;
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
			exec_error(HEREDOC_BUFFER_ERROR, NULL);
		if (!ft_strncmp(executor->limiter, buffer,
				ft_strlen(executor->limiter)))
			break ;
		split = ft_split(buffer, '$');
		sub_write(file, buffer, envp, split);
		write(file, "\n", 1);
		free_double_ptr(split, 1);
		free(buffer);
	}
	close(file);
}

void	heredoc_handler(t_executor *executor, t_node *node_tmp, t_var *envp)
{
	t_fd	*fd_temp;

	if (executor == NULL || node_tmp == NULL)
		return ;
	fd_temp = node_tmp->fd;
	while (fd_temp != NULL)
	{
		if (fd_temp->mode == MODE_HEREDOC)
		{
			executor->limiter = fd_temp->meta;
			heredoc(executor, envp);
			executor->heredoc = open(".heredoc_tmp", O_RDONLY);
			if (executor->heredoc < 0)
			{
				unlink(".heredoc_tmp");
				exec_error(PERMISSION_ERROR, ".heredoc_tmp");
			}
		}
		fd_temp = fd_temp->next;
	}
}
