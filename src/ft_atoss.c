/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:50:10 by bohlee            #+#    #+#             */
/*   Updated: 2023/08/16 17:11:28 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoss(t_coordinate *coordinate, char *number, size_t *index, int sign)
{
	ssize_t	hight;
	ssize_t	old_hight;
	int		dex;

	hight = 0;
	old_hight = 0;
	while (ft_isdigit(number[(*index)]))
	{
		dex = 0;
		while (number[(*index)] != "0123456789"[dex] && dex < 10)
			dex++;
		hight = (hight * 10) + (dex * sign);
		if (sign == -1 && hight > old_hight)
			return (1);
		else if (sign == 1 && hight < old_hight)
			return (1);
		old_hight = hight;
		(*index)++;
	}
	(*coordinate).hight = hight;
	return (0);
}
