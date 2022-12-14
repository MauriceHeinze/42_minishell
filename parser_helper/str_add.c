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

char	*str_add(char *orig, char *new_part, int pos)
{
	int		i;
	int		orig_i;
	int		new_part_i;
	int		max_len;
	char	*copy;

	if (!new_part && orig)
		return (orig);
	pos--;
	i = 0;
	orig_i = 0;
	new_part_i = 0;
	max_len = ft_strlen(orig) + ft_strlen(new_part) + 1;
	copy = malloc(sizeof(char) * max_len);
	if (!copy || !orig)
		return (NULL);
	while (orig[orig_i] != '\0' && (i < max_len && i < pos))
		copy[i++] = orig[orig_i++];
	while (new_part[new_part_i] != '\0')
		copy[i++] = new_part[new_part_i++];
	while (orig[orig_i] != '\0')
		copy[i++] = orig[orig_i++];
	copy[i] = '\0';
	return (copy);
}
