/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:03:40 by bohlee            #+#    #+#             */
/*   Updated: 2023/08/18 16:39:17 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_check_extension(char *file)
{
	size_t	length;

	length = ft_strlen(file);
	if (length-- < 4)
		return (1);
	if (file[length - 3] != '.'
		|| file[length - 2] != 'f'
		|| file[length - 1] != 'd'
		|| file[length] != 'f')
		return (1);
	return (0);
}

static int	ft_check_first(char **line, t_instruction **instruction)
{
	size_t	column;

	if (*line == 0)
	{
		ft_printf("CAUSE : Can't read file.\n");
		return (1);
	}
	column = 0;
	if (ft_check_vaild_and_count(*line, &column))
	{
		ft_printf("CAUSE : Line %d\n", (*instruction)->row + 1);
		free(*line);
		return (1);
	}
	(*instruction)->column = column;
	(*instruction)->row++;
	return (0);
}

static int	ft_check_other_lines(char *line, t_instruction **instruction)
{
	size_t	column;

	if (line == 0)
		return (0);
	column = 0;
	if (ft_check_vaild_and_count(line, &column))
	{
		ft_printf("CAUSE : Line %d\n", (*instruction)->row + 1);
		return (1);
	}
	if ((*instruction)->column != column)
	{
		ft_printf("CAUSE : Find differented line %d\n",
			(*instruction)->row + 1);
		return (1);
	}
	(*instruction)->row++;
	return (0);
}

static int	ft_check_inside(int fd, t_instruction **instruction)
{
	char	*line;

	line = get_next_line(fd);
	if (ft_check_first(&line, instruction))
		return (1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (ft_check_other_lines(line, instruction))
		{
			free(line);
			return (1);
		}
	}
	return (0);
}

int	ft_check_input_file(char *file, t_instruction **instruction)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("CAUSE : Can't open %s\n", file);
		return (1);
	}
	if (ft_check_extension(file))
	{
		ft_printf("CAUSE : Invalid extension.\n");
		close(fd);
		return (1);
	}
	if (ft_check_inside(fd, instruction))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
