/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:00:10 by ralf              #+#    #+#             */
/*   Updated: 2022/12/18 12:27:49 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	cd_switch(char *dir)
{
	char	**first_arg;
	int		chdir_return;

	first_arg = NULL;
	chdir_return = 0;
	first_arg = ft_split(dir, ' ');
	chdir_return = chdir(*first_arg);
	if (first_arg != NULL)
		free_double_ptr(first_arg);
	if (chdir_return == -1)
		builtin_error(INVALID_PATH, NULL);
	return (chdir_return);
}

static int	cd_home(t_var *envp)
{
	if (chdir(get_env(envp, "HOME")) == -1)
	{
		builtin_error(CHDIR_ERROR, NULL);
		return (-1);
	}
	else
		return (0);
}

static int	cd_oldir(t_var *envp, int fd)
{
	if (chdir(get_env(envp, "OLDPWD")) == -1)
	{
		builtin_error(OLDPWD_ERROR, NULL);
		return (-1);
	}
	else
	{
		pwd(fd);
		return (0);
	}
}

int	cd(t_var *envp, char *dir, int fd)
{
	char	cwd[PATH_MAX];
	int		chdir_return;

	chdir_return = 0;
	if (getcwd(cwd, PATH_MAX) == NULL)
		builtin_error(GETCWD_ERROR, NULL);
	if (dir == NULL || dir[-1] == '\0')
		chdir_return = cd_home(envp);
	else if (ft_strcmp(dir, "-") == 0)
		chdir_return = cd_oldir(envp, fd);
	else
		chdir_return = cd_switch(dir);
	if (chdir_return == 0)
	{
		if (add_env(envp, ft_strdup("OLDPWD"), ft_strdup(cwd)) == NULL)
			builtin_error(ADD_ENV_ERROR, NULL);
		if (getcwd(cwd, PATH_MAX) == NULL)
			builtin_error(GETCWD_ERROR, NULL);
		if (add_env(envp, ft_strdup("PWD"), ft_strdup(cwd)) == NULL)
			builtin_error(ADD_ENV_ERROR, NULL);
	}
	return (chdir_return);
}
