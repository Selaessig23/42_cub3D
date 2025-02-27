#include "cub3d.h"

// void start_window()
// {
// }


int	main(int argc, char *argv[])
{
	int				fd;
	t_gamedata		*config;

	fd = 0;
	config = NULL;
	//config->map = create_empty_map();
	

	if (argc == 2)
	{
		if (!ft_extension_check(argv[1]))
			fd = ft_access_check(argv[1]);
		// dprintf(1, "correct no of arguments and correct extension "
		// 	"for gaming fun, fd: %i\n", fd);
		config = ft_initiate_data(fd);
		config->cub3d_data.mlx = mlx_init(640, 480, "Markus' and Pavlos' cub3D", true);
		sleep(2);
		// printf("test x\n");
		close (fd);
		ft_testprint(config);
		ft_free_config(config);
		mlx_loop(config->cub3d_data.mlx);
		mlx_close_window(config->cub3d_data.mlx);
		mlx_terminate(config->cub3d_data.mlx);
	}
	else
		ft_error_handling(0, NULL, NULL);
	return (0);
}
