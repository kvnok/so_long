/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pngs_images_instances.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:35:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/16 17:22:05 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//try to load all the png files and store the 'textures'
void	load_pngs(t_data *data)
{
	data->t_b = mlx_load_png("./pngs/floor.png");
	if (!data->t_b)
		clean_memory(data, 2);
	data->t_c = mlx_load_png("./pngs/collectable.png");
	if (!data->t_c)
		clean_memory(data, 2);
	data->t_e = mlx_load_png("./pngs/exit.png");
	if (!data->t_e)
		clean_memory(data, 2);
	data->t_p = mlx_load_png("./pngs/player.png");
	if (!data->t_p)
		clean_memory(data, 2);
	data->t_w = mlx_load_png("./pngs/wall.png");
	if (!data->t_w)
		clean_memory(data, 2);
}

//make images from textures
void	convert_textures(t_data *data)
{
	data->i_b = mlx_texture_to_image(data->mlx, data->t_b);
	if (!data->i_b)
		clean_memory(data, 2);
	data->i_c = mlx_texture_to_image(data->mlx, data->t_c);
	if (!data->i_c)
		clean_memory(data, 2);
	data->i_e = mlx_texture_to_image(data->mlx, data->t_e);
	if (!data->i_e)
		clean_memory(data, 2);
	data->i_p = mlx_texture_to_image(data->mlx, data->t_p);
	if (!data->i_p)
		clean_memory(data, 2);
	data->i_w = mlx_texture_to_image(data->mlx, data->t_w);
	if (!data->i_w)
		clean_memory(data, 2);
}

//creating new instances
void	helper_image_creator(t_data *data, int y, int x)
{
	if ((mlx_image_to_window(data->mlx, data->i_b, x * TS, y * TS)) < 0)
		clean_memory(data, 2);
	if (data->map[y][x] == '1')
		if ((mlx_image_to_window(data->mlx, data->i_w, x * TS, y * TS)) < 0)
			clean_memory(data, 2);
	if (data->map[y][x] == 'C')
		if ((mlx_image_to_window(data->mlx, data->i_c, x * TS, y * TS)) < 0)
			clean_memory(data, 2);
	if (data->map[y][x] == 'E')
		if ((mlx_image_to_window(data->mlx, data->i_e, x * TS, y * TS)) < 0)
			clean_memory(data, 2);
}

//looping through map
void	create_map_images(t_data *data)
{
	int	x;
	int	y;
	int	p_y;
	int	p_x;

	y = 0;
	p_y = data->p_y;
	p_x = data->p_x;
	while (y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			helper_image_creator(data, y, x);
			x++;
		}
		y++;
	}
	if ((mlx_image_to_window(data->mlx, data->i_p, p_x * TS, p_y * TS)) < 0)
		clean_memory(data, 2);
}
