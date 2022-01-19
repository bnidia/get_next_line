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
 * check_file(fd, t_file)
 * check for presence of opened file in t_file ring structure
 * if t_file not found return NULL
 */
t_file	*check_file(int fd, t_file **file)
{
	t_file	*initial_position;

	if ((*file)->fd == fd)
		return (*file);
	initial_position = *file;
	*file = (*file)->next;
	while (*file != initial_position)
	{
		if ((*file)->fd == fd)
			return (*file);
		*file = (*file)->next;
	}
	return (NULL);
}

/*
 * init_file(t_file **file, int fd)
 * creating a struct file, were we store data about read file
 * and used buffer. It is circled struct.
 * Traditional line length research, limited to print-based text, gave a
 * variety of results, but generally for printed text it is widely accepted
 * that line length fall between 45 and 75 characters per line (cpl),
 * though the ideal is 66 cpl (including letters and spaces)
 */
t_file	*init_file(int fd, t_file **file)
{
	(*file) = (t_file *)malloc(sizeof(t_file));
	if ((*file) == NULL)
		return (NULL);
	(*file)->fd = fd;
	(*file)->rb_size = 0;
	(*file)->next = *file;
	return (*file);
}

char	*make_string(t_file **file)
{
	char	*str;

	while (42)
	{
		if ((*file)->rb_size == 0)
		{
			(*file)->rb_size = read((*file)->fd, (*file)->rb_array,
								 BUFFER_SIZE);
			if ((*file)->rb_size == 0 && (*file)->str_size > 0)
			{
				str[(*file)->str_size] = '\0';
				return (str);
			}
			if ((*file)->rb_size <= 0)
				return (delete_file(file, str));
			(*file)->rb_pos = 0;
		}
		if ((*file)->str_size == 0 || (*file)->str_size + 8 >=
											  (*file)->str_capacity)
		{
			str = ft_realloc(*file, &str);
			if (str == NULL)
				return (NULL);
		}
		str[(*file)->str_size++] = (*file)->rb_array[
				(*file)->rb_pos++];
		(*file)->rb_size--;
		if ((*file)->rb_array[(*file)->rb_pos - 1] == '\n')
		{
			str[(*file)->str_size] = '\0';
			return (str);
		}
	}
}

char	*ft_realloc(t_file *file, char **str)
{
	char	*return_string;
	size_t	i;

	i = -1;
	if (file->str_size == 0)
		file->str_capacity = 128;
	else if (file->str_capacity <= 33554432)
		file->str_capacity *= 2;
	else
		file->str_capacity += 33554432;
	return_string = (char *)malloc(file->str_capacity);
	if (return_string == NULL)
		return (delete_file(&file, NULL));
	if (file->str_size == 0)
		return (return_string);
	while (i++ < file->str_size)
		return_string[i] = *(*str + i);
	free(*str);
	return (return_string);
}

char	*delete_file(t_file **file, char *str)
{
	t_file	*del_file;
	t_file	*prev_file;

	if ((*file)->str_size > 0)
		free(str);
	del_file = *file;
	prev_file = *file;
	*file = (*file)->next;
	while(del_file != (*file)->next)
	{
		prev_file = *file;
		*file = (*file)->next;
	}
	*file = prev_file;
	(*file)->next = del_file->next;
	free(del_file);
	del_file = NULL;
	if (prev_file == *file) {
		*file = NULL;
		file = NULL;
	}
	return (NULL);
}