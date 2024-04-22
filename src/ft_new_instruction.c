/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:56:10 by bohlee            #+#    #+#             */
/*   Updated: 2023/08/18 13:00:04 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_new_instruction(t_instruction **buffer)
{
	*buffer = (t_instruction *)malloc(sizeof(t_instruction));
	if (*buffer == 0)
		return (1);
	(*buffer)->row = 0;
	(*buffer)->column = 0;
	(*buffer)->hight = 50;
	(*buffer)->width = 87;
	(*buffer)->window_width = 0;
	(*buffer)->window_hight = 0;
	(*buffer)->start = 0;
	(*buffer)->map = 0;
	return (0);
}
