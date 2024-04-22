/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:17:25 by bohlee            #+#    #+#             */
/*   Updated: 2023/08/17 17:23:49 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_malloc_map(t_instruction **instruction)
{
	size_t	row;
	size_t	remove;

	row = 0;
	remove = 0;
	(*instruction)->map = (t_coordinate **)malloc(
			sizeof(t_coordinate *) * (*instruction)->row);
	if ((*instruction)->map == 0)
		return (1);
	while (row < (*instruction)->row)
	{
		(*instruction)->map[row] = (t_coordinate *)malloc(
				sizeof(t_coordinate) * (*instruction)->column);
		if ((*instruction)->map[row] == 0)
		{
			while (remove < row)
				free((*instruction)->map[remove++]);
			free((*instruction)->map);
			(*instruction)->map = 0;
			return (1);
		}
		row++;
	}
	return (0);
}

static int	ft_input_map(char *line, size_t row, t_instruction **instruction)
{
	size_t	index;
	size_t	column;
	int		sign;

	index = 0;
	column = 0;
	while (line[index] && column < (*instruction)->column)
	{
		sign = 1;
		while ((9 <= line[index] && line[index] <= 13) || line[index] == 32)
			index++;
		if (line[index] == '\n')
			break ;
		while ((line[index] == '-' || line[index] == '+'))
		{
			if (line[index++] == '-')
				sign *= -1;
		}
		if (ft_input_coordinate(&((*instruction)->map[row][column++]), line,
			&index, sign))
			return (1);
	}
	return (0);
}

static int	ft_fill_map(int fd, t_instruction **instruction)
{
	char	*line;
	size_t	row;

	line = get_next_line(fd);
	row = 0;
	while (line && row < (*instruction)->row)
	{
		if (ft_input_map(line, row, instruction))
		{
			free(line);
			return (1);
		}
		row++;
		free(line);
		line = get_next_line(fd);
	}
	if (row != (*instruction)->row)
		return (1);
	return (0);
}

int	ft_make_map(char *file, t_instruction **instruction)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("CAUSE : Can't open file.\n");
		return (1);
	}
	if (ft_malloc_map(instruction))
	{
		ft_printf("CAUSE : map malloc fail.\n");
		close(fd);
		return (1);
	}
	if (ft_fill_map(fd, instruction))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
