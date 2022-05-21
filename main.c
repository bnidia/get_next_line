/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:13:42 by bnidia            #+#    #+#             */
/*   Updated: 2021/12/23 14:16:06 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd1 = open("../test1.txt", O_RDONLY);
	int		fd2 = open("../test2.txt", O_RDONLY);
	int		fd3 = open("../test3.txt", O_RDONLY);
	int		i = 1;

	while (i++ <= 2)
	{
		char *s1 = get_next_line(fd1);
		printf("%s", s1);
		free(s1);
		char *s2 = get_next_line(fd2);
		printf("%s", s2);
		free(s2);
		char *s3 = get_next_line(fd3);
		printf("%s", s3);
		free(s3);
	}
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
	if (fd3 > 0)
		close(fd3);
	return (0);
}
