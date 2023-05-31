/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfinding.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:35:26 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/15 15:12:09 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_dup_around(t_data *data, int y, int x)
{
	if (!(data->mapdup[y - 1][x] == 'P' || data->mapdup[y - 1][x] == '1'))
		data->mapdup[y - 1][x] = 'P';
	if (!(data->mapdup[y + 1][x] == 'P' || data->mapdup[y + 1][x] == '1'))
		data->mapdup[y + 1][x] = 'P';
	if (!(data->mapdup[y][x - 1] == 'P' || data->mapdup[y][x - 1] == '1'))
		data->mapdup[y][x - 1] = 'P';
	if (!(data->mapdup[y][x + 1] == 'P' || data->mapdup[y][x + 1] == '1'))
		data->mapdup[y][x + 1] = 'P';
}

int	leftovers_in_mapdup(t_data *data)
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
			if (data->mapdup[y][x] == 'C' || data->mapdup[y][x] == 'E')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

//using data->mapdup
//loop through the entire map from x,y : 1,1 to len -1, len -1
//loop (width*height) - (2*width) times
//fill up the entire data->mapdub with P on all adjacent open tiles
//loop one final time to check if there are any E or C left
// pretty_print_map_dup(data); with two newlines after to seperate
int	path_possible(t_data *data)
{
	int	y;
	int	x;
	int	total;

	y = 1;
	x = 1;
	total = (data->map_h - 2) * (data->map_w - 2);
	while (total >= 0)
	{
		y = 1;
		while (y < data->map_h - 1)
		{
			x = 1;
			while (x < data->map_w - 1)
			{
				if (data->mapdup[y][x] == 'P')
					fill_dup_around(data, y, x);
				x++;
			}
			y++;
		}
		total--;
	}
	return (leftovers_in_mapdup(data));
}
