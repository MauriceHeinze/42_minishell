/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_cmd_path.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mheinze <mheinze@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/04 21:08:49 by mheinze		   #+#	#+#			 */
/*   Updated: 2022/11/22 16:15:23 by mheinze		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_var	*setup_var_node(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);

	var->name = "";
	var->content = "";
	var->not_splitted = "";
	var->next = NULL;
	return (var);
}

t_var	*store_env(char *env[])
{
	t_var	*var;
	t_var	*head;
	int		last_pos;
	int		i;
	int		k;

	var = setup_var_node();
	head = var;
	last_pos = 0;
	i = 0;
	while (env[i])
	{
		k = 0;
		while (env[i][k] != '\0')
			k++;
		var->not_splitted = ft_substr(env[i], 0, k);
		k = 0;
		while (env[i][k] != '\0' && env[i][k] != '=')
			k++;
		last_pos = k;
		var->name = ft_substr(env[i], 0, k);
		if (env[i][k] == '=')
			k++;
		last_pos = k;
		while (env[i][k] != '\0')
			k++;
		var->content = ft_substr(env[i], last_pos, k);
		if (env[i + 1] != NULL)
		{
			var->next = setup_var_node();
			var = var->next;
		}
		i++;
	}
	return (head);
}

// TODO: Add check for double
t_var	*add_env(t_var *env, char *name, char* content)
{
	t_var   *head;
	char   *tmp;
	int	 exists;

	head = env;
	exists = 0;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			exists = 1;
			break;
		}
		if (env->next)
			env = env->next;
		else
			break;
	}
	if (exists)
	{
		free(env->name);
		env->name = name;
		free(env->not_splitted);
		free(env->content);
		env->content = content;
		tmp = ft_strjoin(name, "=");
		env->not_splitted = ft_strjoin(tmp, env->content);
		free(tmp);
	}
	else
	{
		env->next = setup_var_node();
		env = env->next;
		env->name = name;
		env->content = content;
		tmp = ft_strjoin(name, "=");
		env->not_splitted = ft_strjoin(tmp, env->content);
		free(tmp);
	}
	return (head);
}

void	remove_env(t_var *env, char *name)
{
	t_var *head;
	t_var *tmp;

	head = env;

	// check first element
	if (ft_strcmp(env->name, name) == 0) // found it!
	{
		head = env->next;
		free(env->name);
		free(env->content);
		free(env->not_splitted);
		free(env);
		program->envp = head;
	}
	// check next elements
	while (env)
	{
		if (!env->next)
			break;
		if (ft_strcmp(env->next->name, name) == 0) // found it!
		{
			tmp = env->next;
			// remove next node
			// set pointer to next node
			env->next = tmp->next;
			free(tmp->name);
			free(tmp->content);
			free(tmp->not_splitted);
			free(tmp);
		}
		env = env->next;
	}
	program->envp = head;
}

char	*get_env(t_var *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

void	free_env(void)
{
	t_var *envp;
	t_var *tmp_envp;

	int i = 0;

	envp = program->envp;
	while (envp != NULL)
	{
		tmp_envp = envp;
		envp = envp->next;
		free(tmp_envp->name);
		// printf("\nFails at:\n name: %s\ncontent: %s\n", tmp_envp->next->name, tmp_envp->next->content);
		free(tmp_envp->content);
		free(tmp_envp->not_splitted);
		free(tmp_envp);
	}
}