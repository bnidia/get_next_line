/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:30:04 by bnidia            #+#    #+#             */
/*   Updated: 2021/12/29 21:27:41 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3//16384
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct file
{
	int			fd;
	char		read_buffer[BUFFER_SIZE];
	ssize_t		read_size;
	size_t		buffer_position;
	char		*str;
	size_t		str_capacity;
	size_t		str_size;
	struct file	*next;
}	t_file;

char	*get_next_line(int fd);
void	init_file(int fd, t_file **file);
int		check_if_the_file_was_opened(int fd, t_file **file);
char	*make_string(t_file *file);
int		ft_realloc(t_file *file);
void	delete_file(t_file *file);

#endif