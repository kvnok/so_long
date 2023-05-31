/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_wasd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:34:08 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/16 17:20:20 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
latest total moves in terminal
*/
void	display_moves(t_data *data, int n)
{
	char	c;

	if (n > 9)
		display_moves(data, n / 10);
	c = (n % 10) + '0';
	if (write(1, &c, 1) == -1)
		clean_memory(data, 2);
}

/*
UP
*/
void	move_w(t_data *data)
{
	int	pos[2];
	int	temp;

	pos[0] = data->i_p->instances[0].y / TS;
	pos[1] = data->i_p->instances[0].x / TS;
	if (data->map[pos[0] - 1][pos[1]] != '1')
	{
		data->i_p->instances[0].y -= TS;
		pos[0] = data->i_p->instances[0].y / TS;
		data->n_moves++;
		temp = data->n_moves;
		display_moves(data, temp);
		if (write(1, "\n", 1) == -1)
			clean_memory(data, 2);
		if (data->map[pos[0]][pos[1]] == 'C')
			handle_collectables(data);
		if (data->map[pos[0]][pos[1]] == 'E')
			handle_exit(data);
	}
}

/*
LEFT
*/
void	move_a(t_data *data)
{
	int	pos[2];
	int	temp;

	pos[0] = data->i_p->instances[0].y / TS;
	pos[1] = data->i_p->instances[0].x / TS;
	if (data->map[pos[0]][pos[1] - 1] != '1')
	{
		data->i_p->instances[0].x -= TS;
		pos[1] = data->i_p->instances[0].x / TS;
		data->n_moves++;
		temp = data->n_moves;
		display_moves(data, temp);
		if (write(1, "\n", 1) == -1)
			clean_memory(data, 2);
		if (data->map[pos[0]][pos[1]] == 'C')
			handle_collectables(data);
		if (data->map[pos[0]][pos[1]] == 'E')
			handle_exit(data);
	}
}

/*
DOWN
*/
void	move_s(t_data *data)
{
	int	pos[2];
	int	temp;

	pos[0] = data->i_p->instances[0].y / TS;
	pos[1] = data->i_p->instances[0].x / TS;
	if (data->map[pos[0] + 1][pos[1]] != '1')
	{
		data->i_p->instances[0].y += TS;
		pos[0] = data->i_p->instances[0].y / TS;
		data->n_moves++;
		temp = data->n_moves;
		display_moves(data, temp);
		if (write(1, "\n", 1) == -1)
			clean_memory(data, 2);
		if (data->map[pos[0]][pos[1]] == 'C')
			handle_collectables(data);
		if (data->map[pos[0]][pos[1]] == 'E')
			handle_exit(data);
	}
}

/*
RIGHT
*/
void	move_d(t_data *data)
{
	int	pos[2];
	int	temp;

	pos[0] = data->i_p->instances[0].y / TS;
	pos[1] = data->i_p->instances[0].x / TS;
	if (data->map[pos[0]][pos[1] + 1] != '1')
	{
		data->i_p->instances[0].x += TS;
		pos[1] = data->i_p->instances[0].x / TS;
		data->n_moves++;
		temp = data->n_moves;
		display_moves(data, temp);
		if (write(1, "\n", 1) == -1)
			clean_memory(data, 2);
		if (data->map[pos[0]][pos[1]] == 'C')
			handle_collectables(data);
		if (data->map[pos[0]][pos[1]] == 'E')
			handle_exit(data);
	}
}
