/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:06:20 by rpohl             #+#    #+#             */
/*   Updated: 2022/04/25 18:15:58 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	chr;

	i = 0;
	chr = c;
	while (*(s + i) != 0)
		i++;
	if (chr == 0)
	{
		return ((char *)(s + i));
	}
	else
	{
		while (*(s + i) != chr)
		{
			i--;
			if (i <= 0 && *s != chr)
			{
				return ((void *)0);
			}
		}
	}
	return ((char *)(s + i));
}
