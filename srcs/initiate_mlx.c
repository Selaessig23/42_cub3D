
#include "cub3d.h"

/**
 * DESCRPIPTION:
 * file that organises the setup of mlx-lib-functions
 * 1) create window
 * 2) create images
 * 3) load textures
 * 4) define depth (z-index)
 * 
 */

/**
 * @brief function that organises the mlx-image-to-window-setup
 * while considering the image numbers to define the layers depth later on
 * 
 * mlx_image_to_window by now seems to always return 0, so it does not seem to be
 * necessary to catch the value for using it in ft_init_mlx 
 * (for -> mlx_set_instance_depth). 
 * In the past the number of instance was returned 
 * (when calling mlx_image_to_window for same image for several times).
 * 
 */
static void	ft_place_image(t_gamedata *config, 
	int *img_instance, int *minimap_instance)
{
	int	img;
	int	minimap;

	img = mlx_image_to_window(config->cub3d_data.mlx, 
			config->cub3d_data.img, 0, 0);
	if (img < 0)
	{
		ft_cleanup(config, true);
		ft_error_handling(22, NULL, config);
	}
	minimap = mlx_image_to_window(config->cub3d_data.mlx, 
			config->cub3d_data.minimap_surface, 0, 0);
	if (minimap < 0)
	{
		ft_cleanup(config, true);
		ft_error_handling(22, NULL, config);
	}
	*img_instance = img;
	*minimap_instance = minimap;
}

/**
 * @brief function to create a mlx_image out of a path
 * to png-texture
 */
static mlx_image_t	*load_single_wall_texture(t_gamedata *config, char *path)
{
	mlx_texture_t	*t;
	mlx_image_t		*ttxt;

	t = mlx_load_png(path);
	if (!t)
	{
		ft_cleanup(config, true);
		ft_error_handling(23, NULL, config);
	}
	ttxt = mlx_texture_to_image(config->cub3d_data.mlx, t);
	if (!ttxt)
	{
		ft_cleanup(config, true);
		ft_error_handling(24, NULL, config);
	}
	mlx_delete_texture(t);
	return (ttxt);
}

/**
 * @brief function to assign the textures to cub3D (mlx-)images
 */
static void	load_wall_textures(t_gamedata *config)
{
	config->cub3d_data.east = 
		load_single_wall_texture(config, config->t_east);
	config->cub3d_data.west = 
		load_single_wall_texture(config, config->t_west);
	config->cub3d_data.north = 
		load_single_wall_texture(config, config->t_north);
	config->cub3d_data.south = 
		load_single_wall_texture(config, config->t_south);
}

/**
 * @brief function to initiate the two layers cub3D-image and
 * minimap-image
 */
static void	ft_init_imgs(t_gamedata *config)
{
	config->cub3d_data.img = 
		mlx_new_image(config->cub3d_data.mlx, 640, 480);
	if (!config->cub3d_data.img)
	{
		ft_cleanup(config, true);
		ft_error_handling(21, NULL, config);
	}
	config->cub3d_data.minimap_surface = 
		mlx_new_image(config->cub3d_data.mlx, 640, 480);
	if (!config->cub3d_data.minimap_surface)
	{
		ft_cleanup(config, true);
		ft_error_handling(21, NULL, config);
	}
}

/**
 * @brief function that organises the image creation and connection to mlx-window
 * of the two layers (cub3d and minimap) and than defines the depth of each layer
 * (z-index), higher values appear above lower ones (minimap appears above cub3d)
 * 
 * function mlx_set_instance seems to work with mlx_image_t->instances[0]
 * as each required image (cub3d & minimap) was only created once
 */
void	ft_init_mlx(t_gamedata *config)
{
	int	img_instance;
	int	minimap_instance;

	img_instance = 0;
	minimap_instance = 0;
	config->cub3d_data.mlx = mlx_init(640, 480, "cub3Deluxe", true);
	if (!config->cub3d_data.mlx)
		ft_error_handling(20, NULL, config);
	ft_init_imgs(config);
	load_wall_textures(config);
	ft_place_image(config, &img_instance, &minimap_instance);
	mlx_set_instance_depth
		(&config->cub3d_data.img->instances[img_instance], 0);
	mlx_set_instance_depth
		(&config->cub3d_data.minimap_surface->instances[minimap_instance], 1);
}
