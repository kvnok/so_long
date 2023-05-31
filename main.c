/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:33:45 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/15 22:39:29 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
once everything is loaded in
functions only get called when a new keypress is registered
*/
int	main(int argc, char **argv)
{
	t_data	data;

	data.argc = argc;
	data.argv = argv;
	cmdline_input_errorcheck(argc, argv);
	fillstruct(&data);
	last_error_checks(&data);
	load_pngs(&data);
	convert_textures(&data);
	create_map_images(&data);
	mlx_key_hook(data.mlx, &key_activation, &data);
	mlx_loop(data.mlx);
	clean_memory(&data, 2);
	return (0);
}
