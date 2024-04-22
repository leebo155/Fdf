/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:40:29 by bohlee            #+#    #+#             */
/*   Updated: 2024/04/22 11:56:03 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_free_instruction(t_instruction **instruction)
{
	size_t	row_index;

	row_index = 0;
	if ((*instruction)->map)
	{
		while (row_index < (*instruction)->row)
			free((*instruction)->map[row_index++]);
		free((*instruction)->map);
	}
	free(*instruction);
}

static void	ft_print_error(t_instruction **instruction, char *str)
{
	if (*instruction)
		ft_free_instruction(instruction);
	ft_printf("ERROR : %s\n", str);
	exit(1);
}

static int	ft_start_mlx(t_instruction **instruction)
{
	t_mlx_vars	vars;

	if (ft_make_new_mlx_window(instruction))
		return (1);
	vars.mlx_ptr = mlx_init();
	if (vars.mlx_ptr == 0)
		return (1);
	vars.mlx_window = mlx_new_window(vars.mlx_ptr, (*instruction)->window_width,
			(*instruction)->window_hight, "fdf");
	if (vars.mlx_window == 0)
		return (1);
	if (ft_draw_map(instruction, &(vars.painting), &(vars.mlx_ptr)))
		return (1);
	ft_free_instruction(instruction);
	ft_regist_hooks(&vars);
	mlx_put_image_to_window(vars.mlx_ptr, vars.mlx_window,
		vars.painting.img, 0, 0);
	mlx_loop(vars.mlx_ptr);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_instruction	*instruction;

	instruction = 0;
	if (argc - 1 != 1)
		ft_print_error(&instruction, "there can only be one argument.");
	if (ft_new_instruction(&instruction))
		ft_print_error(&instruction, "instruction malloc fail.");
	if (ft_check_input_file(argv[1], &instruction))
		ft_print_error(&instruction, "detected problems with checking file.");
	if (ft_make_map(argv[1], &instruction))
		ft_print_error(&instruction, "detected problems with making map.");
	if (ft_start_mlx(&instruction))
		ft_print_error(&instruction, "detected problems with display window.");
	return (0);
}
