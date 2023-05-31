/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:33:08 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/16 18:44:36 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
get the next line from the file
append to data->str
continue until gnl NULL return
*/
void	read_from_file(t_data *data, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			if (data->str[0] == '\0' || int_strlen(data->str) == 0)
			{
				free(data->str);
				exit(1);
			}
			break ;
		}
		data->str = strjoin_free(&data->str, &line);
		if (data->str == NULL)
		{
			free(data->str);
			exit(1);
		}
		if (line != NULL)
			free(line);
	}
	close(fd);
}

/*
open file to get fd
calloc data->str to free later in read_from_file()
*/
int	get_fd_str_calloc(t_data *data)
{
	int		fd;

	fd = open(data->argv[1], O_RDONLY);
	if (fd < 0)
		read_str_error(data, 0);
	data->str = malloc_and_bzero(sizeof(char *) + 1, 1);
	if (data->str == NULL)
		clean_memory(data, 0);
	return (fd);
}

/*
call reading to fill data->str
checking for extra empty lines
making map and mapdup for later
*/
void	fill_map(t_data *data)
{
	int	i;

	i = 0;
	read_from_file(data, get_fd_str_calloc(data));
	if (data->str == NULL || data->str[0] == '\0')
		read_str_error(data, 0);
	while (data->str[i] != '\0')
	{
		if (data->str[0] == '\n')
			read_str_error(data, 1);
		if (i >= 1)
			if (data->str[i] == '\n' && data->str[i - 1] == '\n')
				read_str_error(data, 1);
		i++;
	}
	data->map = ft_split(data->str, '\n');
	data->mapdup = ft_split(data->str, '\n');
	free(data->str);
	if (data->map == NULL || data->mapdup == NULL)
		clean_memory(data, 0);
}

/*
25 lines max each function :(
*/
void	fillstruct_assign_func(t_data *data, int flag)
{
	char	*sl;

	sl = "so_long";
	if (flag == 1)
	{
		fill_map(data);
		data->p_x = 0;
		data->e_x = 0;
		data->n_moves = 0;
	}
	if (flag == 2)
	{
		if (data->c_count == 0)
			print_map_error(data);
		data->c_total = data->c_count;
		if (data->e_x == 0 || data->p_x == 0)
			print_map_error(data);
		data->mlx = mlx_init(data->map_w * TS, data->map_h * TS, sl, false);
		if (!data->mlx)
			clean_memory(data, 0);
	}
}

/*
start the making progress
check for non approved characters
*/
void	fillstruct(t_data *data)
{
	int	y;
	int	x;
	int	temp_w;

	fillstruct_assign_func(data, 1);
	y = 0;
	x = 0;
	while (data->map[y][x] != '\0')
		x++;
	temp_w = x;
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			map_insides_check(data, x, y);
			x++;
		}
		data->map_w = x;
		if (data->map_w != temp_w)
			print_map_error(data);
		y++;
	}
	data->map_h = y;
	fillstruct_assign_func(data, 2);
}
