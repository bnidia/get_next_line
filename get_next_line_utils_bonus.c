/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:27:18 by bnidia            #+#    #+#             */
/*   Updated: 2022/01/19 19:58:35 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
 * Line length research says that line length fall between 45 and
 * 75 characters per line, medium is 66 chars (letters and spaces)
 */
t_file	*init_file(int fd, t_file **file)
{
	t_file	*new_file;

	new_file = (t_file *)malloc(sizeof(t_file));
	if (new_file == NULL)
		return (NULL);
	new_file->fd = fd;
	new_file->rb_size = 0;
	new_file->next = new_file;
	if (*file == NULL)
		return (new_file);
	new_file->next = (*file)->next;
	(*file)->next = new_file;
	*file = new_file;
	return (*file);
}

void	make_string(t_file *file)
{
	while (42)
	{
		if (file->rb_size == 0)
		{
			file->rb_size = read(file->fd, file->rb_ar, BUFFER_SIZE);
			if (file->rb_size <= 0)
				return ;
			file->rb_pos = 0;
		}
		if (file->s_size == 0 || file->s_size + 8 >= file->s_capacity)
			ft_realloc(file);
		if (file->str == NULL)
			return ;
		file->str[file->s_size++] = file->rb_ar[file->rb_pos++];
		file->rb_size--;
		if (file->rb_ar[file->rb_pos - 1] == '\n')
		{
			file->str[file->s_size] = '\0';
			return ;
		}
	}
}

void	ft_realloc(t_file *file)
{
	char	*return_string;
	size_t	i;

	i = 0;
	if (file->s_size == 0)
		file->s_capacity = 128;
	else if (file->s_capacity <= 33554432)
		file->s_capacity *= 2;
	else
		file->s_capacity += 33554432;
	return_string = (char *)malloc(file->s_capacity);
	while (i < file->s_size && return_string != NULL)
	{
		return_string[i] = file->str[i];
		i++;
	}
	free(file->str);
	file->str = return_string;
}

char	*delete_file(t_file **file)
{
	t_file	*del_file;

	if (*file == (*file)->next)
	{
		free(*file);
		*file = NULL;
		return (NULL);
	}
	del_file = *file;
	*file = (*file)->next;
	while (del_file != (*file)->next)
		*file = (*file)->next;
	(*file)->next = del_file->next;
	free(del_file);
	del_file = NULL;
	return (NULL);
}
