#include "cub3d.h"

void start_window()
{
}

int	main(int ac, char *av[])
{
	int				fd;
	t_gamedata		*config;
	t_cub3d			cub3d_data;

	fd = 0;
	config = NULL;
	cub3d_data.mlx = mlx_init(640, 480, "Markus' and Pavlos' cub3D", true);
	sleep(2);
	mlx_close_window(cub3d_data.mlx);
	mlx_terminate(cub3d_data.mlx);
	if (ac == 2)
	{
		if (!ft_extension_check(av[1]))
			fd = ft_access_check(av[1]);
		dprintf(1, "correct no of arguments and correct extension "
			"for gaming fun, fd: %i\n", fd);
		config = ft_initiate_data(fd);
		// printf("test x\n");
		close (fd);
		ft_testprint(config);
		ft_free_config(config);
		return (0);
	}
	ft_error_handling(0, NULL, NULL);
}
