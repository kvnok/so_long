/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_print_etc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 18:49:00 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/15 22:46:46 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
printing map to debug
*/
void	printmap(t_data *data)
{
	int	i;

	i = 0;
	if (write(1, "map : \n", 7) == -1)
		clean_memory(data, 0);
	while (data->map[i] != NULL)
	{
		if (write(1, data->map[i], okstrlen(data->map[i])) == -1)
			clean_memory(data, 0);
		if (write(1, "\n", 1))
			clean_memory(data, 0);
		i++;
	}
}

/*
printing the dub of map to debug
also with spaces so can see better how the mapdup gets filled up
*/
void	pretty_print_map_dup(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data->mapdup[y] != NULL)
	{
		x = 0;
		while (data->mapdup[y][x] != '\0')
		{
			if (write(1, &data->mapdup[y][x], 1) == -1)
				clean_memory(data, 2);
			if (write(1, " ", 1) == -1)
				clean_memory(data, 2);
			x++;
		}
		if (write(1, "\n", 1) == -1)
			clean_memory(data, 2);
		y++;
	}
}

/*
called if someone goes wrong during reading the map file
*/
void	read_str_error(t_data *data, int flag)
{
	if (flag == 1)
		free(data->str);
	if (write(1, "Error\n", 6) == -1)
		exit(1);
	if (write(1, "Can't create that into a map!\n", 30) == -1)
		exit(1);
	exit(1);
}

/*
called if file doesnt end with .ber
*/
void	print_incorrect_format(void)
{
	if (write(1, "Error\n", 6) == -1)
		exit(1);
	if (write(1, "Incorrect Map Format\n", 21) == -1)
		exit(1);
	exit(1);
}

/*
called if the map character are incorrect
*/
void	print_map_error(t_data *data)
{
	if (write(1, "Error\n", 6) == -1)
		clean_memory(data, 0);
	if (write(1, "Map misconfiguration!\n", 22) == -1)
		clean_memory(data, 0);
	clean_memory(data, 0);
}
