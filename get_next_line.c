/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:33:22 by adelaloy          #+#    #+#             */
/*   Updated: 2023/11/06 17:26:56 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*left;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left = read_line(fd, left);
	if (!left)
	{
		return (NULL);
	}
	line = extract_line(left);
	left = make_new_left(left);
	return (line);
}

/*
# include <fcntl.h>
# include <stdio.h>
int	main(void)
{
	static int	fd;

	char path[] = "test.txt";
	fd = open(path, O_RDONLY);
	printf("1= %s", get_next_line(fd));
	printf("2= %s", get_next_line(fd));
	printf("3= %s", get_next_line(fd));
	printf("4= %s", get_next_line(fd));
	printf("5= %s", get_next_line(fd));
	printf("6= %s", get_next_line(fd));
	close(fd);
	// while(1); //valgrind ./a.out   leaks a.out    
	//gcc -W -W -W -fsanitize=address *.c
	// gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
	// gcc -Wall -Werror -Wextra get_next_line.h get_next_line.c get_next_line_utils.c
    // leaks -atExit -- ./a.out test.txt
}*/