/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:50:03 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/19 15:11:22 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*export_content(char *export)
{
	int		lc;
	char	*content;

	lc = 0;
	if (export[lc] == '\0' && export[lc] == ' ' && export[lc] == ';')
		return (NULL);
	while (export[lc] != '\0' && export[lc] != ' ' && export[lc] != ';')
		lc++;
	content = malloc(sizeof(char) * (lc + 1));
	ft_strlcpy(content, export, lc + 1);
	content[lc] = '\0';
	return (content);
}

int	export_print(t_var *envp, int fd)
{
	t_var	*temp;

	temp = envp;
	while (temp != NULL)
	{
		if (strcmp("?", temp->name))
		{
			write(fd, "declare -x ", 11);
			write(fd, temp->name, ft_strlen(temp->name));
			if (temp->content != NULL)
			{
				write(fd, "=\"", 2);
				write(fd, temp->content, ft_strlen(temp->content));
				write(fd, "\"", 1);
			}
			write(fd, "\n", 1);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

static void	first_arg_builtin_error(char *str)
{
	char	**args;

	args = ft_split(str, ' ');
	if (args[0] != NULL)
		builtin_error(EXPORT_ERROR, args[0]);
	free_double_ptr(args);
}

int	export_name(char *export, t_var *envp)
{
	int		length_name;
	char	*name;
	char	*content;

	content = NULL;
	if (!((*export >= 'A' && *export <= 'Z')
			|| (*export >= 'a' && *export <= 'z')))
	{
		first_arg_builtin_error(export);
		return (-1);
	}
	else
	{
		length_name = 0;
		while (export[length_name] != '\0' && export[length_name] != '='
			&& export[length_name] != ' ' && export[length_name] != ';')
			length_name++;
		name = malloc(sizeof(char) * (length_name + 1));
		ft_strlcpy(name, export, length_name + 1);
		name[length_name] = '\0';
		if (export[length_name] == '=')
			content = export_content(&(export[length_name + 1]));
		add_env(envp, name, content);
	}
	return (EXIT_SUCCESS);
}
