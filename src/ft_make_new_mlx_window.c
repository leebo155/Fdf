/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_new_mlx_window.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:36:27 by bohlee            #+#    #+#             */
/*   Updated: 2023/08/19 16:35:45 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	ft_get_window_width(t_instruction **instruction)
{
	size_t	return_value;

	return_value = ((*instruction)->row + (*instruction)->column)
		* (*instruction)->width;
	if (return_value == 0)
		return_value = (*instruction)->width * 2;
	return (return_value);
}

static size_t	ft_get_window_hight(t_instruction **instruction)
{
	size_t	row_i;
	size_t	col_i;
	ssize_t	high;
	ssize_t	low;

	low = 0;
	row_i = 0;
	while (row_i < (*instruction)->row)
	{
		col_i = 0;
		while (col_i < (*instruction)->column)
		{
			high = ((*instruction)->map[row_i][col_i].hight - row_i + col_i)
				* (*instruction)->hight;
			if ((*instruction)->start < high)
				(*instruction)->start = high;
			if (low > high)
				low = high;
			col_i++;
		}
		row_i++;
	}
	if ((*instruction)->start - low == 0)
		return ((*instruction)->hight * 2);
	return ((*instruction)->start - low + ((*instruction)->hight * 2));
}

int	ft_make_new_mlx_window(t_instruction **instruction)
{
	size_t	ratio;

	ratio = 0;
	(*instruction)->window_width = ft_get_window_width(instruction);
	(*instruction)->window_hight = ft_get_window_hight(instruction);
	if ((*instruction)->window_width > 2088)
		ratio = (*instruction)->window_width / 2088 + 1;
	if ((*instruction)->window_hight > 1200)
	{
		if (ratio < (*instruction)->window_hight / 1200 + 1)
			ratio = (*instruction)->window_hight / 1200 + 1;
	}
	if (ratio)
	{
		if (ratio > 50)
		{
			ft_printf("CAUSE : Can't display all of map. MAX scale 1:50.\n");
			return (1);
		}
		(*instruction)->width /= ratio;
		(*instruction)->hight /= ratio;
		(*instruction)->start = 0;
		ft_make_new_mlx_window(instruction);
	}
	return (0);
}
