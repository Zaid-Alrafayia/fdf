/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:20:56 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/20 17:29:28 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../fdf.h"
#include <stddef.h>
#include <stdlib.h>

static int	map_error(int fd, char *line, char *msg)
{
	if (msg)
		ft_printf("%s\n", msg);
	if (line)
		free(line);
	close(fd);
	return (0);
}

int	validate_file_type(char *file)
{
	char	*index;

	index = ft_strchr(file, '.');
	if (ft_strncmp(index, ".fdf", 4) != 0)
	{
		ft_printf("ERROR: file type incompatiable!");
		return (1);
	}
	return (0);
}

int	validate_map(char *file)
{
	int		fd;
	size_t	size;
	size_t	len;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
	{
		map_error(fd, NULL, "ERROR: map is empty.");
		return (-1);
	}
	len = ft_strlen(line);
	size = 0;
	while (line && len == ft_strlen(line))
	{
		size += len;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return ((int)size);
}

int	validate(int argc, char *file)
{
	int	malloc_size;

	if (argc != 2)
	{
		ft_printf("ERROR: ./fdf FILE\n");
		return (0);
	}
	if (validate_file_type(file))
		return (0);
	malloc_size = validate_map(file);
	if (!malloc_size)
	{
		ft_printf("ERROR: map invalid.");
		return (0);
	}
	else if (malloc_size == -1)
		return (0);
	return (1);
}
