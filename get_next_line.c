/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:45:12 by bnidia            #+#    #+#             */
/*   Updated: 2021/12/30 09:14:48 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * get_next_line(int fd)
 * reads file and returns a string separated \n
 * if nothing else to read or error returns NULL
 * BUFFER_SIZE=xx will be used as the read_buffer size for the read calls
*/

char	*get_next_line(int fd)
{
	static t_file	*file = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (file == NULL)
		init_file(&file, fd);
	if (file->fd != fd)
		check_if_the_file_was_opened(fd, &file);
	make_string(file);
	return (file -> str);
}
