/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:30:22 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/15 22:41:41 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
strlen with int return type
also has a NULL check to return 0
*/
int	okstrlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (i);
	while (s[i])
	{
		i++;
	}
	return (i);
}

/*
argc check
len check
ends with .ber check
*/
void	cmdline_input_errorcheck(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		if (write(1, "Error\n", 6) == -1)
			exit(1);
		if (write(1, "Please provide just one map file\n", 33) == -1)
			exit(1);
		exit(1);
	}
	len = int_strlen(argv[1]);
	if (len <= 4)
		print_incorrect_format();
	if (!(argv[1][len - 1] == 'r' && argv[1][len - 2] == 'e'
		&& argv[1][len - 3] == 'b' && argv[1][len - 4] == '.'))
	{
		print_incorrect_format();
	}
}

/*
any hole in the top, bottom, left or right wall?
*/
int	check_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (x < data->map_w)
	{
		if (data->map[0][x] != '1')
			return (1);
		if (data->map[data->map_h - 1][x] != '1')
			return (1);
		x++;
	}
	while (y < data->map_h)
	{
		if (data->map[y][0] != '1')
			return (1);
		if (data->map[y][data->map_w - 1] != '1')
			return (1);
		y++;
	}
	return (0);
}

/*
any non approved characters?
*/
void	map_insides_check(t_data *data, int x, int y)
{
	if (!(data->map[y][x] == '1' || data->map[y][x] == '0'
	|| data->map[y][x] == 'P' || data->map[y][x] == 'E'
	|| data->map[y][x] == 'C'))
	{
		print_map_error(data);
	}
	if (data->map[y][x] == 'C')
		data->c_count++;
	if (data->map[y][x] == 'P')
	{
		if (data->p_x != 0)
			print_map_error(data);
		data->p_x = x;
		data->p_y = y;
	}
	if (data->map[y][x] == 'E')
	{
		if (data->e_x != 0)
			print_map_error(data);
		data->e_x = x;
		data->e_y = y;
	}
}

/*
called after fillstruct() function for last map checks
*/
void	last_error_checks(t_data *data)
{
	if (check_walls(data) == 1)
	{
		if (write(1, "Error\n", 6) == -1)
			clean_memory(data, 2);
		if (write(1, "WALLS INCORRECT!\n", 17) == -1)
			clean_memory(data, 2);
		clean_memory(data, 2);
	}
	if (path_possible(data) == 1)
	{
		if (write(1, "Error\n", 6) == -1)
			clean_memory(data, 2);
		if (write(1, "NO PATH POSSIBLE!\n", 18) == -1)
			clean_memory(data, 2);
		clean_memory(data, 2);
	}
}
