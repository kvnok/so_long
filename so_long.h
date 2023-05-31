/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 17:29:42 by kkroon        #+#    #+#                 */
/*   Updated: 2023/04/16 17:05:39 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdarg.h>
# include "./MLX42/include/MLX42/MLX42.h"

//TS : TILE SIZE
# define TS 64
# define BUFFER_SIZE 100

typedef struct s_data
{
	int				argc;
	char			**argv;
	mlx_t			*mlx;
	mlx_texture_t	*t_b;
	mlx_texture_t	*t_c;
	mlx_texture_t	*t_e;
	mlx_texture_t	*t_p;
	mlx_texture_t	*t_w;
	mlx_image_t		*i_b;
	mlx_image_t		*i_c;
	mlx_image_t		*i_e;
	mlx_image_t		*i_p;
	mlx_image_t		*i_w;
	char			**map;
	char			**mapdup;
	char			*str;
	int				map_w;
	int				map_h;
	int				p_x;
	int				p_y;
	int				e_x;
	int				e_y;
	int				c_count;
	int				c_total;
	int				n_moves;
}	t_data;

//get_next_line.c
char	*strjoin_free(char **s1, char **s2);
char	*save(char **line, char **afternewline);
char	*reading(int fd, char *buffer, char **line, char **afternewline);
char	*get_next_line(int fd);

//get_next_line_utils.c
int		int_strlen(char *s);
void	*malloc_and_bzero(int count, int size);
char	*cut_free(char **s, int start, int len, char **extra);
int		find_newline(char *s);
char	*cleanup(char **line, char **afternewline);

//ft_split.c
char	**ft_split(char const *s, char c);

//make_map.c
void	read_from_file(t_data *data, int fd);
int		get_fd_str_calloc(t_data *data);
void	fill_map(t_data *data);
void	fillstruct_assign_func(t_data *data, int flag);
void	fillstruct(t_data *data);

//error_checks.c
int		okstrlen(char *s);
void	cmdline_input_errorcheck(int argc, char **argv);
int		check_walls(t_data *data);
void	map_insides_check(t_data *data, int x, int y);
void	last_error_checks(t_data *data);

//pngs_images_instances.c
void	load_pngs(t_data *data);
void	convert_textures(t_data *data);
void	helper_image_creator(t_data *data, int y, int x);
void	create_map_images(t_data *data);

//key_collectable_exit.c
void	handle_collectables(t_data *data);
void	handle_exit(t_data *data);
void	key_activation(mlx_key_data_t keydata, void *param);

//move_wasd.c
void	display_moves(t_data *data, int n);
void	move_w(t_data *data);
void	move_a(t_data *data);
void	move_s(t_data *data);
void	move_d(t_data *data);

//cleaning.c
void	free_maps(t_data *data);
void	clean_memory(t_data *data, int flag);

//pathfinding.c
void	fill_dup_around(t_data *data, int y, int x);
int		leftovers_in_mapdup(t_data *data);
int		path_possible(t_data *data);

//error_print_etc.c
void	printmap(t_data *data);
void	pretty_print_map_dup(t_data *data);
void	read_str_error(t_data *data, int flag);
void	print_incorrect_format(void);
void	print_map_error(t_data *data);
#endif
