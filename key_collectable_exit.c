/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_collectable_exit.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:34:57 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/16 16:55:53 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
move collectable in negative y
above screen
*/
void	handle_collectables(t_data *data)
{
	int	p_pos[2];
	int	c_pos[2];
	int	i;

	p_pos[0] = data->i_p->instances[0].y / TS;
	p_pos[1] = data->i_p->instances[0].x / TS;
	data->map[p_pos[0]][p_pos[1]] = '0';
	data->c_count--;
	i = 0;
	while (i < data->c_total)
	{
		c_pos[0] = data->i_c->instances[i].y / TS;
		c_pos[1] = data->i_c->instances[i].x / TS;
		if (p_pos[0] == c_pos[0] && p_pos[1] == c_pos[1])
		{
			data->i_c->instances[i].y = -TS * (i + 1);
			data->i_c->instances[i].x = -TS * (i + 1);
			return ;
		}
		i++;
	}
}

/*
all collectables gotten
*/
void	handle_exit(t_data *data)
{
	int	pos[2];

	pos[0] = data->i_p->instances[0].y / TS;
	pos[1] = data->i_p->instances[0].x / TS;
	if (data->c_count <= 0)
		clean_memory(data, 2);
}

/*
listening for key input
*/
void	key_activation(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			clean_memory(data, 2);
		if (keydata.key == MLX_KEY_W)
			move_w(data);
		if (keydata.key == MLX_KEY_A)
			move_a(data);
		if (keydata.key == MLX_KEY_S)
			move_s(data);
		if (keydata.key == MLX_KEY_D)
			move_d(data);
	}
}
