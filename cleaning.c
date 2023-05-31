/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaning.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:29:57 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/15 22:30:43 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
freeing the individual pointers
then the main pointer char **map
*/
void	free_maps(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i] != NULL)
	{
		free(data->map[i]);
		i++;
	}
	if (data->map != NULL)
		free(data->map);
	i = 0;
	while (data->mapdup[i] != NULL)
	{
		free(data->mapdup[i]);
		i++;
	}
	if (data->mapdup != NULL)
		free(data->mapdup);
}

/*
flag should be 2 if init has already happenend
after mlx_init(), always close window and terminate
*/
void	clean_memory(t_data *data, int flag)
{
	free_maps(data);
	if (flag == 2)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	exit(1);
}
