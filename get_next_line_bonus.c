/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:10:35 by adelaloy          #+#    #+#             */
/*   Updated: 2023/11/06 17:27:10 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *left)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(left, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			free(left);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		left = ft_strjoin(left, buff);
	}
	free(buff);
	return (left);
}

char	*extract_line(char *left)
{
	char	*tmp;
	int		j;

	j = 0;
	if (!left[j])
		return (NULL);
	while (left[j] != '\n' && left[j])
		j++;
	tmp = ft_substr(left, 0, ++j);
	return (tmp);
}

char	*make_new_left(char *left)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	tmp = NULL;
	while (left[j] != '\n' && left[j])
	{
		j++;
	}
	len = ft_strlen(left);
	if (left[j] == '\n')
	{
		j++;
		tmp = ft_substr(left, j, len);
	}
	free(left);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*left[MAX_OPEN];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left[fd] = read_line(fd, left[fd]);
	if (!left[fd])
	{
		return (NULL);
	}
	line = extract_line(left[fd]);
	left[fd] = make_new_left(left[fd]);
	return (line);
}

/*
# include <fcntl.h>
# include <stdio.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test1.txt", O_RDONLY);
	fd3 = open("test2.txt", O_RDONLY);
	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd1);
		printf("fd1: line %d: %s", i, line);
		free(line);
		printf("\n");
		line = get_next_line(fd2);
		printf("fd2: line %d: %s", i, line);
		free(line);
		printf("\n");
		line = get_next_line(fd3);
		printf("fd3: line %d: %s", i, line);
		free(line);
		printf("\n");
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
//gcc -Wall -Wextra -Werror *bonus.c
*/

