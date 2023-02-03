/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:54:54 by mhaksal           #+#    #+#             */
/*   Updated: 2023/02/03 17:07:50 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	checker(char *path)
{
	t_v		j_len;
	char	**map;

	map = map_control(path, &j_len, -1, 0);
	top_bottom_check(map, -1, (int)j_len.x, (int)j_len.y);
	right_left_check(map, -1, (int)j_len.x, (int)j_len.y);
	character_check(map, -1, (int)j_len.x);
	map_free(map, (int)j_len.x);
	return (j_len.y);
}

void	start_game(char *av)
{
	t_mlx		mlx;
	t_img		img;
	t_game		game;
	t_player	player;

	game.max_len = checker(av);
	mlx.mlx = mlx_init();
	process_args(&game, av, &player, &mlx);
	mlx.window = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	img.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.nd);
	mlx.image = &img;
	mlx.game = &game;
	mlx.player = &player;
	mlx_hook(mlx.window, 2, 1L << 0, keyhandler, &mlx);
	mlx_hook(mlx.window, 17, 0, close_exit, &mlx);
	mlx_hook(mlx.window, 6, 0L, &mouse_move, &mlx);
	mlx_loop_hook(mlx.mlx, draw_map, &mlx);
	mlx_loop(mlx.mlx);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		start_game(av[1]);
	else
		error("Error: 2 arguments required for the game!\n");
	return (0);
}
