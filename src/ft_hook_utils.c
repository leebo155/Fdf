/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:12:26 by bohlee            #+#    #+#             */
/*   Updated: 2024/04/22 11:57:59 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_hook_key_press(int keycode, t_mlx_vars *vars)
{
	(void)vars;
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_window);
		mlx_destroy_image(vars->mlx_ptr, vars->painting.img);
		exit(0);
	}
	return (0);
}

static int	ft_hook_close_window(int keycode, t_mlx_vars *vars)
{
	(void)keycode;
	(void)vars;
	exit(0);
	return (0);
}

void	ft_regist_hooks(t_mlx_vars *vars)
{
	mlx_hook(vars->mlx_window, 2, 1L, ft_hook_key_press, vars);
	mlx_hook(vars->mlx_window, 17, 0L, ft_hook_close_window, vars);
}
