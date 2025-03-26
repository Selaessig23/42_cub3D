/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:59:13 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/26 14:30:06 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*create_square(mlx_t *mlx, uint32_t size, t_color color)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	// Fill the image with the specified color
	for (uint32_t y = 0; y < size; y++)
	{
		for (uint32_t x = 0; x < size; x++)
		{
			putPixel(color, img, x, y );
		}
	}
	return (img);
}

mlx_image_t	*create_transparent_pattern(mlx_t *mlx, uint32_t size, uint32_t color)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	// Create a checkerboard pattern with some pixels fully transparent
	for (uint32_t y = 0; y < size; y++)
	{
		for (uint32_t x = 0; x < size; x++)
		{
			// Make a checkerboard pattern by making some pixels transparent
			if ((x / 10 + y / 10) % 2 == 0)
				mlx_put_pixel(img, x, y, color);
			else
				mlx_put_pixel(img, x, y, 0x00000000); // Fully transparent
		}
	}
	return (img);
}

void	copy_texture(mlx_image_t *img, mlx_image_t *texture, uint32_t x, uint32_t y)
{
	 for (uint32_t i = 0; i < texture->height; i++)
	 {

			t_color color = {0xFFAAAA11};


			putPixel(color, img, x, y + i);
		//uint32_t color = texture->pixels[i * texture->width + texture->width / 2];
	 }
}

/**
 * @brief function to define floor-color for each pixel of 
 * lower half
 * 
 * TODO: use while instead of for
 */
void	fill_lower_half(mlx_image_t *img, t_color color)
{
	for (uint32_t y = img->height / 2; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			putPixel(color, img, x, y);
		}
	}
}

/**
 * @brief function to define ceiling-color for each pixel of 
 * upper half
 * 
 * TODO: use while instead of for
 */

void	fill_upper_half(mlx_image_t *img, t_color color)
{
	for (uint32_t y = 0; y < img->height / 2; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			putPixel(color, img, x, y);
		}
	}
}
t_color pixel_to_color(uint8_t* pixel)
{
	t_color color;

		color.red = pixel[0];
		color.green = pixel[1];
		color.blue = pixel[2];
		color.alpha = pixel[3];

		return color;
}
void copy_texture_line(mlx_image_t *render_img, mlx_image_t *texture,
					   int screen_x, int draw_start, int draw_end, float wall_x)
{
	int		tex_x;
	int		tex_y;
	uint8_t	*pixel;
	float	step;

	tex_x = (int)(wall_x * texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	for (int screen_y = draw_start; screen_y < draw_end; screen_y++)
	{
		step = (float)texture->height / (draw_end - draw_start);
		tex_y = (int)((screen_y - draw_start) * step);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		putPixel(pixel_to_color(pixel), render_img, screen_x, screen_y);
	}
}




t_hit_info init_hit_info(void)
{
	t_hit_info hit_info;

	hit_info.hit = 0;
	hit_info.perp_wall_dist = 0;
	return hit_info;
}

static void init_ray(t_ray *ray, t_player player, float camera_x)
{
    ray->dir.x = player.dir.x + player.dir.y * camera_x * 0.66f; // Field of view adjustment
    ray->dir.y = player.dir.y - player.dir.x * camera_x * 0.66f; // Field of view adjustment
    ray->map_x = (int)player.pos.x;
    ray->map_y = (int)player.pos.y;
    ray->delta_dist.x = (ray->dir.x == 0) ? 1e30 : fabs(1.0f / ray->dir.x);
    ray->delta_dist.y = (ray->dir.y == 0) ? 1e30 : fabs(1.0f / ray->dir.y);
    if (ray->dir.x < 0) {
        ray->step_x = -1;
        ray->side_dist.x = (player.pos.x - ray->map_x) * ray->delta_dist.x;
    } else {
        ray->step_x = 1;
        ray->side_dist.x = (ray->map_x + 1.0f - player.pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0) {
        ray->step_y = -1;
        ray->side_dist.y = (player.pos.y - ray->map_y) * ray->delta_dist.y;
    } else {
        ray->step_y = 1;
        ray->side_dist.y = (ray->map_y + 1.0f - player.pos.y) * ray->delta_dist.y;
    }
}

static void perform_dda(char **map, t_ray *ray, t_hit_info *hit_info)
{
    hit_info->hit = 0;

    while (!hit_info->hit) {
        if (ray->side_dist.x < ray->side_dist.y) {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map_x += ray->step_x;
            if (ray->step_x > 0)
                hit_info->side = DIR_WEST; // Hit the west face (coming from east)
            else
                hit_info->side = DIR_EAST; // Hit the east face (coming from west)
        } else {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map_y += ray->step_y;
            if (ray->step_y > 0)
                hit_info->side = DIR_NORTH; // Hit the north face (coming from south)
            else
                hit_info->side = DIR_SOUTH; // Hit the south face (coming from north)
        }
        if (map[ray->map_y][ray->map_x] == '1' || map[ray->map_y][ray->map_x] == ' ')
            hit_info->hit = 1;
    }
}

static void calculate_wall_properties(t_ray *ray, t_hit_info *hit_info, t_vector2 player_pos)
{
    if (hit_info->side == DIR_EAST || hit_info->side == DIR_WEST)
        hit_info->perp_wall_dist = (ray->map_x - player_pos.x + (1 - ray->step_x) / 2) / ray->dir.x;
    else
        hit_info->perp_wall_dist = (ray->map_y - player_pos.y + (1 - ray->step_y) / 2) / ray->dir.y;
    if (hit_info->side == DIR_EAST || hit_info->side == DIR_WEST)
        ray->wall_x = player_pos.y + hit_info->perp_wall_dist * ray->dir.y;
    else
        ray->wall_x = player_pos.x + hit_info->perp_wall_dist * ray->dir.x;

    ray->wall_x -= floor(ray->wall_x);
}

static void calculate_render_line(t_render_line *line, mlx_image_t *img, float perp_wall_dist, int screen_x)
{
    line->height = (int)(img->height / perp_wall_dist);
    line->screen_x = screen_x;
    line->draw_start = img->height / 2 - line->height / 2;
    if (line->draw_start < 0)
        line->draw_start = 0;
    line->draw_end = img->height / 2 + line->height / 2;
    if (line->draw_end >= img->height)
        line->draw_end = img->height - 1;
}

/**
 * @brief 
 */
void	cast_ray_and_draw_wall(char **map, mlx_image_t *img, t_gamedata *config)
{
	t_ray			ray;
	t_hit_info		hit_info;
	t_render_line	line;
	int				x;
	float			camera_x;

	x = 0;
	while (x < img->width)
	{
		camera_x = 2.0f * x / (float)img->width - 1.0f;
		init_ray(&ray, config->player, camera_x);
		hit_info = init_hit_info();
		perform_dda(map, &ray, &hit_info);
		calculate_wall_properties(&ray, &hit_info, config->player.pos);
		calculate_render_line(&line, img, hit_info.perp_wall_dist, x);
		pick_and_place(hit_info.side, config, img, x, line.draw_start, 
			line.draw_end, ray.wall_x);
		x++;
	}
}

void pick_and_place(t_direction side, t_gamedata * config, mlx_image_t * img, int x, int draw_start, int draw_end, float wall_x)
{
	mlx_image_t	*texture;

	if (side == DIR_NORTH)
		texture = config->cub3d_data.north;
	else if (side == DIR_SOUTH)
		texture = config->cub3d_data.south;
	else if (side == DIR_EAST)
		texture = config->cub3d_data.east;
	else
		texture = config->cub3d_data.west;
	copy_texture_line(img, texture, x, draw_start, draw_end, wall_x);
}


/**
 * @brief function to assign values to the minimap struct
 */
void	fill_minimap_data(t_minimap_data *minimap_data, t_gamedata *config)
{
	minimap_data->cell_size = 10;
	minimap_data->map_y_len = ft_arrlen(config->map);
	minimap_data->map_x_len = ft_strlen(config->map[0]);
	if (minimap_data->map_x_len > minimap_data->map_y_len)
		minimap_data->minimap_size = 
			minimap_data->map_x_len * minimap_data->cell_size;
	else
		minimap_data->minimap_size = 
			minimap_data->map_y_len * minimap_data->cell_size;
	minimap_data->wall_color = (t_color){0xFFAAAAFF};
	minimap_data->floor_color = (t_color){0x66FF00AA};
	minimap_data->player_color = (t_color){0xFF0000FF};
	minimap_data->bg_color = (t_color){0x33333388};
}

/**
 *  Draw a single cell of the minimap grid
 * 
 * TODO: decrease number of parameter to 4
 */ 
void	draw_minimap_cell(t_gamedata *config, t_minimap_data minimap_data,
	int map_x, int map_y, int screen_x, int screen_y)
{
	t_color	cell_color;
	int		cx;
	int		cy;

	if (screen_x >= minimap_data.minimap_size 
		|| screen_y >= minimap_data.minimap_size)
		return ;
	if (config->map[map_y][map_x] == '1' || config->map[map_y][map_x] == ' ')
		cell_color = minimap_data.wall_color;
	else
		cell_color = minimap_data.floor_color;
	cy = 0;
	while (cy < minimap_data.cell_size && screen_y 
		+ cy < minimap_data.minimap_size)
	{
		cx = 0;
		while (cx < minimap_data.cell_size && screen_x 
			+ cx < minimap_data.minimap_size)
		{
			putPixel(cell_color, config->cub3d_data.minimap_surface, 
				screen_x + cx, screen_y + cy);
			cx++;
		}
		cy++;
	}
}

// Draw the entire minimap grid by iterating through the map
void	draw_minimap_grid(t_gamedata *config, t_minimap_data minimap_data)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	i = 0;
	while (i < minimap_data.map_y_len)
	{
		j = 0;
		while (j < minimap_data.map_x_len)
		{
			screen_x = j * minimap_data.cell_size;
			screen_y = i * minimap_data.cell_size;
			draw_minimap_cell(config, minimap_data, j, i, screen_x, screen_y);
			j++;
		}
		i++;
	}
}

// 5. Main minimap function that orchestrates the drawing
void	draw_minimap(t_gamedata *config)
{
	t_minimap_data	minimap_data;

	fill_minimap_data(&minimap_data, config);
	if (!config->show_minimap)
		return;
	// Clear the minimap surface
	clear_minimap_surface(config, minimap_data);
	// Draw the map grid (walls and floor)
	draw_minimap_grid(config, minimap_data);
	// Draw the player position
	draw_player_position(config, minimap_data);
	// Draw the player direction
	draw_player_direction(config, minimap_data);
}

int	main(int argc, char *argv[])
{
	int				fd;
	t_gamedata		*config;
	int				map_x;
	int				map_y;
	char			**map;
	// int				img_instance;
	// int				minimap_instance;

	fd = 0;
	config = NULL;
	if (argc == 2)
	{
		if (!ft_extension_check(argv[1]))
			fd = ft_access_check(argv[1]);
		config = ft_initiate_data(fd);

        //without this we can floating point problems - i think it is the equivalent of using a bigger collision box
        config->player.pos.x += 0.1;
        config->player.pos.y += 0.1;


		// if (!config->player.pos.x)
		// 	config->player.pos.x = 9;
		// if (!config->player.pos.y)
		// 	config->player.pos.y = 5;
		// if (!config->player.dir.x)
		// 	config->player.dir.x = -1;
		// if (!config->player.dir.y)
		// 	config->player.dir.y = 0;
		// if (!config->player.fov)
		// 	config->player.fov = 90;

		//just for testing reasons
		ft_testprint(config);

		//initiate mlx-data with game-config-data (validated)
		ft_init_mlx(config);
		// if (!(config->cub3d_data.mlx = mlx_init(640, 480, "cub3Deluxe", true)))
		// 	ft_error_handling(20, NULL, config);
		// config->cub3d_data.img = mlx_new_image(config->cub3d_data.mlx, 640, 480);
		// if (!config->cub3d_data.img)
		// 	ft_error_handling(21, NULL, config);
		// config->cub3d_data.minimap_surface = mlx_new_image(config->cub3d_data.mlx, 640, 480);
		// if (!config->cub3d_data.minimap_surface)	
		// 	ft_error_handling(21, NULL, config);
		// load_wall_textures(config);
		// img_instance = mlx_image_to_window(config->cub3d_data.mlx, config->cub3d_data.img, 0, 0);
		// if (img_instance < 0)
		// 	ft_error_handling(22, NULL, config);
		// //set the depth of each image (z-index), higher values appear above lower ones
		// mlx_set_instance_depth(&config->cub3d_data.img->instances[img_instance], 0);
		// minimap_instance = mlx_image_to_window(config->cub3d_data.mlx, config->cub3d_data.minimap_surface, 0, 0);
		// if (minimap_instance < 0)
		// 	ft_error_handling(22, NULL, config);
		// //depth of minimap is higher than cub3D-image
		// mlx_set_instance_depth(&config->cub3d_data.minimap_surface->instances[minimap_instance], 1);

		
		//set size of map -> maybe move to parsing part, if required,
		//seems to not have any specific use
		// map = config->map;
		// map_x = ft_strlen(map[0]);
		// map_y = ft_arrlen(map);

		//adapt image size in case of window resizing
		mlx_resize_hook(config->cub3d_data.mlx, resize, config);
		//handling of keyboard use
		mlx_key_hook(config->cub3d_data.mlx, key_handler, config);
		//raycasting-part
		mlx_loop_hook(config->cub3d_data.mlx, render, config);
		//game loop
		mlx_loop(config->cub3d_data.mlx);

		//cleaning up
		close(fd);
		delete_images(config);
		mlx_close_window(config->cub3d_data.mlx);
		mlx_terminate(config->cub3d_data.mlx);
		ft_free_config(config);
	}
	else
		ft_error_handling(0, NULL, NULL);
	return (0);
}

/**
 * @brief function to delete the images that have been created for
 * game execution
 */
void	delete_images(t_gamedata *config)
{
	mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.img);
	mlx_delete_image(config->cub3d_data.mlx,
					 config->cub3d_data.minimap_surface);
	mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.east);
	mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.west);
	mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.north);
	mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.south);
}

/**
 * @brief function to assign the textures to cub3D (mlx-)images
 */
void	load_wall_textures(t_gamedata * config)
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
 * @brief function to create a mlx_image out of a path
 * to png-texture
 */
mlx_image_t	*load_single_wall_texture(t_gamedata *config, char *path)
{
	mlx_texture_t	*t;
	mlx_image_t		*ttxt;

	t = mlx_load_png(path);
	if (!t)
		ft_error_handling(23, NULL, config);
	ttxt = mlx_texture_to_image(config->cub3d_data.mlx, t);
	if (!ttxt)
		ft_error_handling(24, NULL, config);
	mlx_delete_texture(t);
	return (ttxt);
}
