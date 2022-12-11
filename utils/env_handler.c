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

t_var	*setup_var_node(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = NULL;
	var->content = NULL;
	var->not_splitted = NULL;
	var->next = NULL;
	return (var);
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
	t_var	*envp;
	t_var	*tmp_envp;

	envp = g_program->envp;
	while (envp != NULL)
	{
		tmp_envp = envp;
		envp = envp->next;
		free(tmp_envp->name);
		free(tmp_envp->content);
		free(tmp_envp->not_splitted);
		free(tmp_envp);
	}
}
