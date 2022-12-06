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

char	*str_remove(char const *orig, unsigned int start, size_t len)
{
	unsigned int	i;
	int				orig_i;
	int				new_part_i;
	char			*copy;

	if (start > 0)
		start--;
	i = 0;
	orig_i = 0;
	new_part_i = 0;
	copy = malloc(sizeof(char) * (ft_strlen(orig) + 1));
	if (!copy || !orig)
		return (NULL);
	while (orig[orig_i] != '\0' && (i < start))
		copy[i++] = orig[orig_i++];
	while (orig[orig_i] != '\0' && ((orig_i - start) < len))
		orig_i++;
	while (orig[orig_i] != '\0')
		copy[i++] = orig[orig_i++];
	copy[i] = '\0';
	return (copy);
}