/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:55:28 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 16:25:57 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../inc/minishell.h"

int	pwd(int fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		builtin_error(GETCWD_ERROR, NULL);
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

static char	*echo_pre(char *str, int *n)
{
	int		num_n;

	*n = 0;
	num_n = 0;
	while ((ft_strncmp(&(str[num_n]), "-", 1) == 0))
	{
		num_n += 1;
		if ((ft_strncmp(&(str[num_n]), "n", 1) != 0))
			break ;
		while ((ft_strncmp(&(str[num_n]), "n", 1) == 0))
			num_n += 1;
		if (str[num_n] != '\0' && (ft_strncmp(&(str[num_n]), " ;", 2) != 0))
			break ;
		else
		{
			str += 2;
			str += num_n;
			num_n = 0;
			*n = 1;
		}
	}
	return (str);
}

static int	echo_move(char **str, int *isq, int *idq)
{
	if (**str == '\"' && !(*isq))
	{
		if (*idq)
			*idq = 0;
		else if (!(*idq))
			*idq = 1;
		*str = *str + 1;
		return (1);
	}
	else if (!(*idq) && **str == '\'')
	{
		if (*isq)
			*isq = 0;
		else if (!(*isq))
			*isq = 1;
		*str = *str + 1;
		return (1);
	}
	return (0);
}

int	echo_lat(char *str, int fd)
{
	int		isq;
	int		idq;
	int		n;

	n = 0;
	str = echo_pre(str, &n);
	isq = 0;
	idq = 0;
	while (*str != '\0')
	{
		if (*str == '\"' || *str == '\'')
		{
			if (echo_move(&str, &isq, &idq))
				continue ;
		}
		else if (*str == ';' && !isq && !idq)
			str++;
		else
			write(fd, str++, 1);
	}
	if (!n)
		write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}
