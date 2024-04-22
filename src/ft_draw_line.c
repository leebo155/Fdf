/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:45:26 by bohlee            #+#    #+#             */
/*   Updated: 2023/08/19 17:16:29 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_put_pixel(t_mlx_data *painting, int x, int y, int color)
{
	char	*coordinate;

	coordinate = painting->addr
		+ (y * painting->line_length + x * (painting->bpp / 8));
	(*(unsigned int *)coordinate) = color;
}

static int	ft_get_y(size_t start_y, size_t end_y, size_t total_width,
		size_t width_index)
{
	int	return_value;

	if (width_index == 0)
		return (start_y);
	else if (width_index == total_width)
		return (end_y);
	return_value = end_y - start_y;
	return_value *= width_index;
	return_value /= (int)total_width;
	return_value += start_y;
	return (return_value);
}

static int	ft_get_color(unsigned int start_color, unsigned int end_color,
		size_t total_width, size_t width_index)
{
	int	return_value;

	if (width_index == 0)
		return (start_color);
	else if (width_index == total_width)
		return (end_color);
	return_value = ft_get_rgb((start_color & (0xFF << 16)) >> 16,
			(end_color & (0xFF << 16)) >> 16, total_width, width_index);
	return_value = return_value << 8;
	return_value += ft_get_rgb((start_color & (0xFF << 8)) >> 8,
			(end_color & (0xFF << 8)) >> 8, total_width, width_index);
	return_value = return_value << 8;
	return_value += ft_get_rgb(start_color & 0xFF,
			end_color & 0xFF, total_width, width_index);
	return (return_value);
}

static void	ft_fill_empty_line(t_spot end, t_spot start, t_mlx_data *painting)
{
	int		pixel_index;
	int		x;
	int		color;	
	int		move;

	pixel_index = 0;
	x = start.x;
	color = start.color;
	move = 1;
	if ((int)(end.y - start.y) < 0)
		move = -1;
	while (start.y + (pixel_index * move) != end.y)
	{
		ft_put_pixel(painting, x, start.y + (pixel_index * move), color);
		if ((int)(end.y - start.y) / 2 == (pixel_index * move) / 2)
		{
			x = end.x;
			color = end.color;
		}
		pixel_index++;
	}
}

void	ft_draw_line(t_spot start, t_spot end, t_mlx_data *painting)
{
	size_t	pixel_index;
	t_spot	select_pixel;
	t_spot	old_pixel;

	pixel_index = 0;
	old_pixel = start;
	while (start.x + pixel_index <= end.x)
	{
		select_pixel.x = start.x + pixel_index;
		select_pixel.y = ft_get_y(start.y, end.y, end.x - start.x, pixel_index);
		select_pixel.color = ft_get_color(start.color, end.color,
				end.x - start.x, pixel_index);
		if (-1 > (int)(select_pixel.y - old_pixel.y)
				|| (int)(select_pixel.y - old_pixel.y) > 1)
			ft_fill_empty_line(select_pixel, old_pixel, painting);
		ft_put_pixel(painting, select_pixel.x, select_pixel.y,
			select_pixel.color);
		old_pixel = select_pixel;
		pixel_index++;
	}
}
