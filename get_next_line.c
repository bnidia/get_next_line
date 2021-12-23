/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:45:12 by bnidia            #+#    #+#             */
/*   Updated: 2021/12/23 14:12:55 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	read_buffer[BUFFER_SIZE];
	ssize_t	n;
	char	line[100];

	if (ft_clipboard != NULL)
	{
		ft_clipboard(fd, line);
		return (line);
	}
	n = read(fd, read_buffer, sizeof read_buffer);
	return (line);
}

int	ft_clipboard(int fd)
{
	char	**clipboard;

}

