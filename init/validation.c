/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:20:56 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/01/22 20:45:43 by zaalrafa         ###   ########.fr       */
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

int	validate_map(char *file, int *width, int *height)
{
	int		fd;
	char	*line;
	char	**arr;
	int		row_width;
	int		first_width;

	first_width = -1;
	*width = 0;
	*height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
	{
		map_error(fd, NULL, "ERROR: map is empty.");
		return (-1);
	}
	while (line)
	{
		arr = ft_split(line, ' ');
		row_width = 0;
		while (arr[row_width])
			row_width++;
		if (first_width == -1)
			first_width = row_width;
		else if (row_width != first_width)
		{
			free_split(arr);
			free(line);
			close(fd);
			ft_printf("ERROR: map is not rectangular.\n");
			return (0);
		}
		(*height)++;
		free_split(arr);
		free(line);
		line = get_next_line(fd);
	}
	*width = first_width;
	close(fd);
	return (1);
}

int	validate(int argc, char *file, int *width, int *height)
{
	int	valid;

	if (argc != 2)
	{
		ft_printf("ERROR: ./fdf FILE\n");
		return (0);
	}
	if (validate_file_type(file))
		return (0);
	valid = validate_map(file, width, height);
	if (!valid)
	{
		ft_printf("ERROR: map invalid.\n");
		return (0);
	}
	else if (valid == -1)
		return (0);
	return (1);
}
