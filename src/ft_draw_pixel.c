/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:37:44 by bohlee            #+#    #+#             */
/*   Updated: 2023/08/17 17:11:28 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_draw_row(t_instruction **instruction, t_coordinate **map,
		size_t row, t_mlx_data *painting)
{
	t_spot	start;
	t_spot	end;
	size_t	column;

	column = 0;
	while (column + 1 < (*instruction)->column)
	{
		start.x = (row + column + 1) * (*instruction)->width;
		start.y = (*instruction)->start + (-(map[row][column].hight
					+ column - row - 1) * (*instruction)->hight);
		start.color = map[row][column].color;
		end.x = start.x + (*instruction)->width;
		end.y = (*instruction)->start + (-(map[row][column + 1].hight
					+ (column + 1) - row - 1) * (*instruction)->hight);
		end.color = map[row][column + 1].color;
		ft_draw_line(start, end, painting);
		column++;
	}
}

static void	ft_draw_column(t_instruction **instruction, t_coordinate **map,
		size_t column, t_mlx_data *painting)
{
	t_spot	start;
	t_spot	end;
	size_t	row;

	row = 0;
	while (row + 1 < (*instruction)->row)
	{
		start.x = (row + column + 1) * (*instruction)->width;
		start.y = (*instruction)->start + (-(map[row][column].hight
					+ column - row - 1) * (*instruction)->hight);
		start.color = map[row][column].color;
		end.x = start.x + (*instruction)->width;
		end.y = (*instruction)->start + (-(map[row + 1][column].hight
					+ column - (row + 1) - 1) * (*instruction)->hight);
		end.color = map[row + 1][column].color;
		ft_draw_line(start, end, painting);
		row++;
	}
}

int	ft_get_rgb(int start_color, int end_color,
		size_t total_width, size_t width_index)
{
	int	return_value;

	return_value = start_color + (((end_color - start_color) * (int)width_index)
			/ (int)total_width);
	return (return_value);
}

int	ft_draw_map(t_instruction **instruction, t_mlx_data *painting,
		void **mlx_ptr)
{
	size_t	row_i;
	size_t	column_i;

	row_i = 0;
	column_i = 0;
	(*painting).img = mlx_new_image(*mlx_ptr, (*instruction)->window_width,
			(*instruction)->window_hight);
	if ((*painting).img == 0)
		return (1);
	(*painting).addr = mlx_get_data_addr((*painting).img, &((*painting).bpp),
			&((*painting).line_length), &((*painting).endian));
	if ((*painting).addr == 0)
		return (1);
	while (row_i < (*instruction)->row)
		ft_draw_row(instruction, (*instruction)->map, row_i++, painting);
	while (column_i < (*instruction)->column)
		ft_draw_column(instruction, (*instruction)->map, column_i++, painting);
	return (0);
}
