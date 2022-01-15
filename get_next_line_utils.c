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
 * Traditional line length research, limited to print-based text, gave a
 * variety of results, but generally for printed text it is widely accepted
 * that line length fall between 45 and 75 characters per line (cpl),
 * though the ideal is 66 cpl (including letters and spaces)
 */
void	init_file(int fd, t_file **file)
{
	(*file) = (t_file *)malloc(sizeof(t_file));
	if (!(*file))
		return ;
	(*file)->str = (char *)malloc(4096);
	if (!((*file)->str))
	{
		free(*file);
		*file = NULL;
		return ;
	}
	(*file)->fd = fd;
	(*file)->read_size = 0;
	(*file)->next = *file;
	(*file)->str_capacity = 4096;
}

/*
 * check_if_the_file_was_opened(fd, t_file)
 * check for the opened file, create file if it wasn't opened
 * delete file slots marked fd = -1
 */
int	check_if_the_file_was_opened(int fd, t_file **file)
{
	t_file	*initial_position;
	t_file	*new_file;

	initial_position = *file;
	*file = (*file)->next;
	while (*file != initial_position)
	{
		if ((*file)->fd == fd)
			return (0);
		*file = (*file)->next;
	}
	init_file(fd, &new_file);
	if (new_file == NULL)
		return (-1);
	new_file->next = (*file)->next;
	(*file)->next = new_file;
	*file = new_file;
	return (0);
}

char	*make_string(t_file *file)
{
	char	*str;

	file->str_size = 0;
	while (file->read_size >= 0)
	{
		if (file->read_size == 0)
		{
			file->buffer_position = 0;
			file->read_size = read(file->fd, file->read_buffer, BUFFER_SIZE);
			if (file->read_size <= 0) {
				str = file->str;
				delete_file(file);
				return (str);
			}
		}
		file->str[file->str_size++] = file->read_buffer[file->buffer_position++];
		if (file->read_buffer[file->buffer_position-1] == '\n')
		{
			file->str[file->str_size] = '\0';
			return (file->str);
		}
		if (file->str_size + 2 == file->str_capacity)
			if (ft_realloc(file) == -1)
				return (file->str);
	}
	return (file->str);
}

int	ft_realloc(t_file *file)
{
	char	*return_string;
	size_t	i;

	i = 0;
	if (file->str_size <= 33554432)
		file->str_size *= 2;
	else
		file->str_size += 33554432;
	return_string = (char *)malloc(file->str_size);
	if (return_string == NULL)
		return (-1);
	while (file->str[i])
	{
		return_string[i] = file->str[i];
		i++;
	}
	free(file->str);
	file->str = return_string;
	return (0);
}

void	delete_file(t_file *file)
{
	t_file	*del_file;
	t_file	*prev_file;

	del_file = file;
	file = file->next;
	while(file != file->next)
	{
		prev_file = file;
		file = file->next;
	}
	file = prev_file;
	file->next = del_file->next;
	free(del_file->str);
	free(del_file);
}