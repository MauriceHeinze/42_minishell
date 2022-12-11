/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:50:03 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 17:14:36 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../inc/minishell.h"

static void	chdir_sub(t_var *envp, char *dir, char *cwd)
{
	char	**first_arg;
	
	first_arg = NULL;
	if (dir == NULL || *dir == '\0')
	{
		if (chdir (get_env(envp, "HOME")) == -1)
			builtin_error(CHDIR_ERROR, NULL);
	}
	else
	{
		first_arg = ft_split(dir, ' ');
		if (chdir (*first_arg) == -1)
			special_error(INVALID_PATH);
		if (first_arg != NULL)
		{
			free_double_ptr(first_arg);
			free(first_arg);
		}
	}
}

int	cd(t_var *envp, char *dir, int fd)
{
	char	cwd[PATH_MAX];

	
	if (getcwd(cwd, PATH_MAX) == NULL)
		builtin_error(GETCWD_ERROR, NULL);
	if (ft_strcmp(dir, "-") == 0)
	{
		if (chdir (get_env(envp, "OLDPWD")) == -1)
			special_error(OLDPWD_ERROR);
		pwd(fd);
	}
	else
		chdir_sub(envp, dir, cwd);
	if (add_env(envp, ft_strdup("OLDPWD"), ft_strdup(cwd)) == NULL)
		builtin_error(ADD_ENV_ERROR, NULL);
	if (getcwd(cwd, PATH_MAX) == NULL)
		builtin_error(GETCWD_ERROR, NULL);
	if (add_env(envp, ft_strdup("PWD"), ft_strdup(cwd)) == NULL)
		builtin_error(ADD_ENV_ERROR, NULL);
	return (EXIT_SUCCESS);
}

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
		write(fd, "declare -x ", 11);
		write(fd, temp->name, ft_strlen(temp->name));
		if (temp->content != NULL)
		{
			write(fd, "=\"", 2);
			write(fd, temp->content, ft_strlen(temp->content));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
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
		builtin_error(EXPORT_ERROR, NULL);
		return (EXIT_FAILURE);
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
