/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:27:52 by bohlee            #+#    #+#             */
/*   Updated: 2023/04/10 17:09:52 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
size_t	ft_isnewline(char *str, int flag);
char	*ft_makebuffer(char **buffer);
void	*ft_makefree(char **str);
char	*ft_strlinedup(char *buffer, ssize_t length, ssize_t *index, int *flag);
char	*ft_strfreecat(char **dst, char *buf, ssize_t length, ssize_t *index);

#endif
