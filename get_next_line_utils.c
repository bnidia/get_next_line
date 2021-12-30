/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:27:18 by bnidia            #+#    #+#             */
/*   Updated: 2021/12/29 21:37:14 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * init_file(t_file **file, int fd)
 * creating a struct file, were we store data about read file
 * and used buffer. It is circled struct.
 */
static void	init_file(t_file **file, int fd)
{
	(*file) = (t_file *)malloc(sizeof(t_file));
	if (!(*file))
		return ;
	(*file)->fd = fd;
	(*file)->next = *file;
	(*file)->str = (char *)malloc(4096);
	if (!((*file)->str))
		return ;
	(*file)->str_capacity = 4096;
}

/*
 * check_if_the_file_was_opened(fd, t_file)
 * check for the opened file, create file if it wasn't opened
 * delete file slots marked fd = -1
 */
static void	check_if_the_file_was_opened(int fd, t_file **file)
{
	t_file	*initial_position;
	t_file	*prev_file;
	t_file	*new_file;

	initial_position = *file;
	prev_file = *file;
	*file = (*file)->next;
	while (*file != initial_position)
	{
		if ((*file)->fd == -1)
		{
			prev_file->next = (*file)->next;
			*file = (*file)->next;
			free(*file);
		}
		if ((*file)->fd == fd)
			return ;
		prev_file = *file;
		*file = (*file)-> next;
	}
	init_file(&new_file, fd);
	new_file->next = (*file)->next;
	(*file)->next = new_file;
	*file = new_file;
}

static void	make_string(t_file *file)
{
	file -> str_size = 0;
	while (file->read_size >= 0)
	{
		if (file -> read_size == 0)
		{
			file -> buffer_position = 0;
			file->read_size = read(file->fd, file->read_buffer, BUFFER_SIZE);
			if (file -> read_size <= 0)
				return ;
			if (file -> read_size < BUFFER_SIZE)
				file -> fd = -1;
		}
		file->str[file->str_size] = file->read_buffer[file->buffer_position];
		if (file -> read_buffer[file -> buffer_position] == '\n')
		{
			file -> buffer_position++;
			file -> str[++file -> str_size] = '\0';
			file -> read_size--;
			return ;
		}
		file -> buffer_position++;
		file -> str_size++;
		if (file -> str_size + 2 == file -> str_capacity)
			ft_realloc(file);
		file -> read_size--;
	}
}

static void	ft_realloc(t_file *file)
{
	char	*return_string;
	size_t	i;

	i = 0;
	if (file->str_size <= 33554432)
		file->str_size *= 2;
	else
		file->str_size += 33554432;
	return_string = (char *)malloc(file -> str_size);
	while (file->str[i])
	{
		return_string[i] = file->str[i];
		i++;
	}
	file->str = return_string;
}
