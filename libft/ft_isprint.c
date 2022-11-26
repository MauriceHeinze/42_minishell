/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:03:52 by mheinze           #+#    #+#             */
/*   Updated: 2022/04/18 11:26:12 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int arg)
{
	if ((arg >= 32) && (arg <= 126))
		return (1);
	else
		return (0);
}