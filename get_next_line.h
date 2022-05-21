/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:30:04 by bnidia            #+#    #+#             */
/*   Updated: 2022/01/19 21:31:29 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct file
{
	int			fd;
	char		rb_ar[BUFFER_SIZE];
	char		*str;
	ssize_t		rb_size;
	size_t		rb_pos;
	size_t		str_capacity;
	size_t		str_len;
	struct file	*next;
}	t_file;

char	*get_next_line(int fd);
t_file	*init_file(int fd, t_file **file);
t_file	*check_file(int fd, t_file **file);
void	make_string(t_file *file);
void	ft_realloc(t_file *file);
char	*delete_file(t_file **file);

#endif