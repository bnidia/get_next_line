/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:45:12 by bnidia            #+#    #+#             */
/*   Updated: 2022/01/15 22:49:59 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * get_next_line(int fd)
 * reads file and returns a string separated \n
 * if nothing else to read or error returns NULL
 * BUFFER_SIZE=xx will be used as the rb_array size for the read calls
*/

char	*get_next_line(int fd)
{
	static t_file	*file = NULL;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (file == NULL || check_file(fd, &file) == NULL)
		init_file(fd, &file);
	if (file == NULL)
		return (NULL);
	file->str_size = 0;
	return (make_string(&file));
}
