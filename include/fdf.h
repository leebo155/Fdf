/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:50:35 by bohlee            #+#    #+#             */
/*   Updated: 2024/04/22 11:54:17 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>

typedef struct s_coordinate
{
	ssize_t			hight;
	unsigned int	color;
}					t_coordinate;

typedef struct s_instruction
{
	size_t				row;
	size_t				column;
	size_t				hight;
	size_t				width;
	size_t				window_width;
	size_t				window_hight;
	ssize_t				start;
	struct s_coordinate	**map;
}				t_instruction;

typedef struct s_mlx_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_mlx_data;

typedef struct s_spot
{
	size_t	x;
	size_t	y;
	int		color;
}				t_spot;

typedef struct s_mlx_vars
{
	void			*mlx_ptr;
	void			*mlx_window;
	t_mlx_data		painting;
}				t_mlx_vars;

int		ft_new_instruction(t_instruction **buffer);
int		ft_atoss(t_coordinate *coordinate, char *number, size_t *index,
			int sign);
int		ft_check_input_file(char *file, t_instruction **instruction);
int		ft_check_vaild_and_count(char *line, size_t *count);
int		ft_input_coordinate(t_coordinate *coordinate, char *line, size_t *index,
			int sign);
int		ft_make_map(char *file, t_instruction **instruction);
int		ft_make_new_mlx_window(t_instruction **instruction);
int		ft_draw_map(t_instruction **instruction, t_mlx_data *painting,
			void **mlx_ptr);
void	ft_draw_line(t_spot start, t_spot end, t_mlx_data *painintg);
int		ft_get_rgb(int start_color, int end_color, size_t total_width,
			size_t width_index);
void	ft_regist_hooks(t_mlx_vars *vars);

#endif
