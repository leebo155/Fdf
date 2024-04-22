/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coordinates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:15:04 by bohlee            #+#    #+#             */
/*   Updated: 2023/08/18 16:07:03 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_check_color(char *line, size_t *start)
{
	size_t	index;

	index = 0;
	while (line[(*start) + index])
	{
		if ((9 <= line[(*start) + index] && line[(*start) + index] <= 13)
			|| line[(*start) + index] == 32 || index > 8)
			break ;
		if (index == 0 && line[(*start) + index] != '0')
			return (1);
		else if (index == 1 && line[(*start) + index] != 'x')
			return (1);
		else if ((1 < index && index < 8)
			&& ((ft_isdigit(line[(*start) + index]) == 0
					&& (65 > ft_toupper(line[(*start) + index])
						|| ft_toupper(line[(*start) + index]) > 70))))
			return (1);
		index++;
	}
	if (index < 4 || index > 8)
		return (1);
	*start += index;
	return (0);
}

static int	ft_fill_color(char *line, size_t *index, t_coordinate *coordinate)
{
	int		hex;
	int		color;

	color = 0;
	while ((9 <= line[(*index)] && line[(*index)] <= 13)
		|| line[(*index)] == 32)
		(*index)++;
	(*index) += 2;
	while (line[(*index)])
	{
		if ((9 <= line[(*index)] && line[(*index)] <= 13)
			|| line[(*index)] == 32)
			break ;
		hex = 0;
		while (ft_toupper(line[(*index)]) != "0123456789ABCDEF"[hex]
			&& hex < 16)
			hex++;
		color = color * 16 + hex;
		(*index)++;
	}
	(*coordinate).color = color;
	return (0);
}

static int	ft_check_comma_and_whitespace(char *line, size_t *start)
{
	while ((9 <= line[(*start)] && line[(*start)] <= 13)
		|| line[(*start)] == 32)
		(*start)++;
	if (line[(*start)] == ',')
	{
		(*start)++;
		while ((9 <= line[(*start)] && line[(*start)] <= 13)
			|| line[(*start)] == 32)
			(*start)++;
		if (ft_check_color(line, start))
			return (1);
	}
	else if (line[(*start)] == '-' || line[(*start)] == '+'
		|| line[(*start)] == 0 || line[(*start)] == '\n'
		|| ft_isdigit(line[(*start)]))
		return (0);
	else
		return (1);
	return (0);
}

int	ft_check_vaild_and_count(char *line, size_t *count)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		while ((9 <= line[index] && line[index] <= 13) || line[index] == 32)
			index++;
		while (line[index] == '-' || line[index] == '+')
			index++;
		if (ft_isdigit(line[index]))
			(*count)++;
		while (ft_isdigit(line[index]))
			index++;
		if (ft_check_comma_and_whitespace(line, &index))
		{
			ft_printf("CAUSE : Column %d\n", index + 1);
			return (1);
		}
		if (line[index] == '\n' || line[index] == 0)
			return (0);
	}
	return (0);
}

int	ft_input_coordinate(t_coordinate *coordinate,
		char *line, size_t *index, int sign)
{
	if (line[(*index)] == 0 || line[(*index)] == '\n')
		return (0);
	if (ft_atoss(coordinate, line, index, sign))
		return (1);
	while ((9 <= line[(*index)] && line[(*index)] <= 13)
		|| line[(*index)] == 32)
		(*index)++;
	if (line[(*index)] == ',')
	{
		(*index)++;
		while ((9 <= line[(*index)] && line[(*index)] <= 13)
			|| line[(*index)] == 32)
			(*index)++;
		if (ft_fill_color(line, index, coordinate))
			return (1);
	}
	else
		(*coordinate).color = 16777215;
	return (0);
}
