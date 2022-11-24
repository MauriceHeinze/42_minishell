/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_itoa.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mheinze <mheinze@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/04/06 19:11:49 by mheinze		   #+#	#+#			 */
/*   Updated: 2022/04/22 10:42:09 by mheinze		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	absolute_value(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

int	get_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		++len;
	while (nbr != 0)
	{
		++len;
		nbr = nbr / 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*result;
	int		len;

	len = get_len(nbr);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nbr < 0)
		result[0] = '-';
	else if (nbr == 0)
		result[0] = '0';
	while (nbr != 0)
	{
		--len;
		result[len] = absolute_value(nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (result);
}
