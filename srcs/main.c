/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:09 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/13 11:38:34 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "main.h"

// void start_window()
// {
// }

void render(void *param);

void load_wall_textures(t_gamedata *config);

#define WIDTH 800
#define HEIGHT 600

// Helper function to create a square with a specific color and alpha
mlx_image_t *create_square(mlx_t *mlx, uint32_t size, t_color color)
{
	mlx_image_t *img = mlx_new_image(mlx, size, size);
	if (!img)
		return NULL;

	// Fill the image with the specified color
	for (uint32_t y = 0; y < size; y++)
	{
		for (uint32_t x = 0; x < size; x++)
		{
			putPixel(color, img, x, y );
		}
	}
	return img;
}

// Function to create a checkerboard pattern with transparency
mlx_image_t *create_transparent_pattern(mlx_t *mlx, uint32_t size, uint32_t color)
{
	mlx_image_t *img = mlx_new_image(mlx, size, size);
	if (!img)
		return NULL;

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
	return img;
}
//test function to copy a vertical line from the east texture in the middle of the screen
void copy_texture(mlx_image_t *img, mlx_image_t *texture, uint32_t x, uint32_t y)
{
	 for (uint32_t i = 0; i < texture->height; i++)
	 {

			t_color color = {0xFFAAAA11};


			putPixel(color, img, x, y + i);
		//uint32_t color = texture->pixels[i * texture->width + texture->width / 2];
	 }
}

void fill_lower_half(mlx_image_t *img, t_color color)
{
	for (uint32_t y = img->height / 2; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			putPixel(color, img, x, y);
		}
	}
}

void fill_upper_half(mlx_image_t *img, t_color color)
{
	for (uint32_t y = 0; y < img->height / 2; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			putPixel(color, img, x, y);
		}
	}
}

void copy_texture_line(mlx_image_t *render_img, mlx_image_t *texture, int screen_x,
	int draw_start, int draw_end, float wall_x)
{
	int tex_x = (int)(wall_x * texture->width);

	if (tex_x < 0) tex_x = 0;
	if (tex_x >= texture->width) tex_x = texture->width - 1;

	int line_height = draw_end - draw_start;

	for (int screen_y = draw_start; screen_y < draw_end; screen_y++)
	{
	float step = (float)texture->height / line_height;
	int tex_y = (int)((screen_y - draw_start) * step);

	if (tex_y < 0) tex_y = 0;
	if (tex_y >= texture->height) tex_y = texture->height - 1;

	uint8_t *pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];

	t_color color;
	color.red = pixel[0];
	color.green = pixel[1];
	color.blue = pixel[2];
	color.alpha = pixel[3];

	putPixel(color, render_img, screen_x, screen_y);
	}
}

void cast_ray_and_draw_wall(char **map, t_vector2 player_pos, t_vector2 player_dir, mlx_image_t *img, t_gamedata *config)
{


	for (int x = 0; x < img->width; x++)
	{
		// Calculate the ray direction relative to the player's view
		float camera_x = 2.0f * x / (float)img->width - 1.0f; // x-coordinate in camera space
		t_vector2 ray_dir;
		ray_dir.x = player_dir.x + player_dir.y * camera_x * 0.66f; // Field of view adjustment
		ray_dir.y = player_dir.y - player_dir.x * camera_x * 0.66f; // Field of view adjustment

		// Initialize DDA algorithm variables
		int map_x = (int)player_pos.x;
		int map_y = (int)player_pos.y;

		// Calculate step and initial side_dist
		t_vector2 side_dist; // Length of ray from current position to next x or y-side
		t_vector2 delta_dist; // Length of ray from one x or y-side to next x or y-side

		// Calculate delta_dist based on ray direction
		delta_dist.x = (ray_dir.x == 0) ? 1e30 : fabs(1.0f / ray_dir.x);
		delta_dist.y = (ray_dir.y == 0) ? 1e30 : fabs(1.0f / ray_dir.y);

		// Determine step direction and initial side_dist
		int step_x, step_y;
		if (ray_dir.x < 0)
		{
			step_x = -1;
			side_dist.x = (player_pos.x - map_x) * delta_dist.x;
		}
		else
		{
			step_x = 1;
			side_dist.x = (map_x + 1.0f - player_pos.x) * delta_dist.x;
		}

		if (ray_dir.y < 0)
		{
			step_y = -1;
			side_dist.y = (player_pos.y - map_y) * delta_dist.y;
		}
		else
		{
			step_y = 1;
			side_dist.y = (map_y + 1.0f - player_pos.y) * delta_dist.y;
		}

		// Perform DDA
		t_direction side;
		int hit = 0;
		float perp_wall_dist;

		while (!hit)
		{
			// Jump to next map square
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map_x += step_x;

				// Determine which side was hit
				if (step_x > 0)
					side = DIR_WEST;  // Hit the west face (coming from east)
				else
					side = DIR_EAST;  // Hit the east face (coming from west)
			}
			else
			{
				side_dist.y += delta_dist.y;
				map_y += step_y;

				// Determine which side was hit
				if (step_y > 0)
					side = DIR_NORTH;  // Hit the north face (coming from south)
				else
					side = DIR_SOUTH;  // Hit the south face (coming from north)
			}

            // Check if ray has hit a wall
            if (map[map_y][map_x] == '1' || map[map_y][map_x] == ' ')
                hit = 1;
        }

		if (side == DIR_EAST || side == DIR_WEST)
			perp_wall_dist = (map_x - player_pos.x + (1 - step_x) / 2) / ray_dir.x;
		else
			perp_wall_dist = (map_y - player_pos.y + (1 - step_y) / 2) / ray_dir.y;


		int line_height = (int)(img->height / perp_wall_dist);

		int draw_start = img->height / 2 - line_height / 2;
		if (draw_start < 0)
			draw_start = 0;

		int draw_end = img->height / 2 + line_height / 2;
		if (draw_end >= img->height)
			draw_end = img->height - 1;

		float wall_x;
		if (side == DIR_EAST || side == DIR_WEST)
			wall_x = player_pos.y + perp_wall_dist * ray_dir.y;
		else
			wall_x = player_pos.x + perp_wall_dist * ray_dir.x;
		wall_x -= floor(wall_x);


// Choose texture based on hit direction
	mlx_image_t *texture;
	if (side == DIR_NORTH)
		texture = config->cub3d_data.north;
	else if (side == DIR_SOUTH)
		texture = config->cub3d_data.south;
	else if (side == DIR_EAST)
		texture = config->cub3d_data.east;
	else
		texture = config->cub3d_data.west;

	// Copy texture line to render surface
	copy_texture_line(img, texture, x, draw_start, draw_end, wall_x);
	}
}


void resize(int width, int height, void *param)
{
	t_gamedata *config = (t_gamedata *)param;
	mlx_resize_image(config->cub3d_data.img, width, height);
}
void key_handler(mlx_key_data_t keydata, void *param)
{
	t_gamedata *config = (t_gamedata *)param;

	// Close window on ESC
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(config->cub3d_data.mlx);

	// Define movement speed
	float move_speed = 0.5;  // Smaller value for more precise movement
	float rotation_speed = 0.15;  // Smaller value for more precise rotation

	// Handle player movement with arrow keys
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W  ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		// Calculate new position
		t_vector2 move_vec = normalizevector(config->player.dir);
		move_vec = multiplyvector(move_vec, move_speed);
		t_vector2 new_pos = addvectors(config->player.pos, move_vec);

		// Check collision for X and Y separately to allow sliding along walls
		t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};

        // Check if we can move in X direction
        if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
        config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
            config->player.pos.x = new_pos.x;

        // Check if we can move in Y direction
        if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
        config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
            config->player.pos.y = new_pos.y;
    }

	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		// Calculate new position (move backward)
		t_vector2 move_vec = normalizevector(config->player.dir);
		move_vec = multiplyvector(move_vec, -move_speed); // Negative for backward
		t_vector2 new_pos = addvectors(config->player.pos, move_vec);

		// Check collision for X and Y separately to allow sliding along walls
		t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};

        // Check if we can move in X direction
        if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
        config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
            config->player.pos.x = new_pos.x;

        // Check if we can move in Y direction
        if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
        config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
            config->player.pos.y = new_pos.y;
    }

	// Add strafe movement with A and D keys
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		// Calculate perpendicular vector for strafing left
		t_vector2 strafe_dir = {-config->player.dir.y, config->player.dir.x};
		strafe_dir = normalizevector(strafe_dir);
		strafe_dir = multiplyvector(strafe_dir, move_speed);
		t_vector2 new_pos = addvectors(config->player.pos, strafe_dir);

		// Check collision for X and Y separately
		t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};

        if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
        config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
            config->player.pos.x = new_pos.x;

        if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
        config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
            config->player.pos.y = new_pos.y;
    }

	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		// Calculate perpendicular vector for strafing right
		t_vector2 strafe_dir = {config->player.dir.y, -config->player.dir.x};
		strafe_dir = normalizevector(strafe_dir);
		strafe_dir = multiplyvector(strafe_dir, move_speed);
		t_vector2 new_pos = addvectors(config->player.pos, strafe_dir);

		// Check collision for X and Y separately
		t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};

        if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
        config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
            config->player.pos.x = new_pos.x;

        if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
        config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
            config->player.pos.y = new_pos.y;
    }

	// Handle rotation with arrow keys
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_Q )&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		// Rotate left (positive angle)
		config->player.dir = normalizevector(rotatevector(config->player.dir, rotation_speed));
	}

	if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_E ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		// Rotate right (negative angle)
		config->player.dir = normalizevector(rotatevector(config->player.dir, -rotation_speed));
	}
	if ((keydata.key == MLX_KEY_TAB) && (keydata.action == MLX_PRESS))
	{
		config->show_minimap = !config->show_minimap;
		printf("show minimap: %i\n", config->show_minimap);
	}
}

void draw_minimap(t_gamedata *config)
{
	// Skip if minimap is disabled
	if (!config->show_minimap)
		return;

	// Clear minimap surface
	for (int y = 0; y < config->cub3d_data.minimap_surface->height; y++)
		for (int x = 0; x < config->cub3d_data.minimap_surface->width; x++)
			putPixel((t_color){0x00000000}, config->cub3d_data.minimap_surface, x, y);

	// Define minimap size and position (in a corner)
	int minimap_size = 150; // Size in pixels
	int cell_size = 10;     // Size of each map cell in pixels
	int map_x_len = ft_strlen(config->map[0]);
	int map_y_len = ft_arrlen(config->map);

	// Colors
	t_color wall_color = {0xFFAAAAFF};   // Walls
	t_color floor_color = {0x66FF00AA};  // Floor (semi-transparent)
	t_color player_color = {0xFF0000FF}; // Player
	t_color bg_color = {0x33333388};     // Background

	// Draw background
	for (int y = 0; y < minimap_size; y++)
		for (int x = 0; x < minimap_size; x++)
			putPixel(bg_color, config->cub3d_data.minimap_surface, x, y);

	// Draw the map cells
	for (int y = 0; y < map_y_len; y++) {
		for (int x = 0; x < map_x_len; x++) {
			// Calculate screen coordinates
			int screen_x = x * cell_size;
			int screen_y = y * cell_size;

			// Skip if out of minimap bounds
			if (screen_x >= minimap_size || screen_y >= minimap_size)
				continue;

            // Draw cell
            t_color cell_color = (config->map[y][x] == '1' || config->map[y][x] == ' ' ) ? wall_color : floor_color;

			// Fill cell
			for (int cy = 0; cy < cell_size && screen_y + cy < minimap_size; cy++) {
				for (int cx = 0; cx < cell_size && screen_x + cx < minimap_size; cx++) {
					putPixel(cell_color, config->cub3d_data.minimap_surface, screen_x + cx, screen_y + cy);
				}
			}
		}
	}

	// Draw the player
	int player_x = (int)(config->player.pos.x * cell_size);
	int player_y = (int)(config->player.pos.y * cell_size);

	// Draw player dot
	for (int y = -2; y <= 2; y++) {
		for (int x = -2; x <= 2; x++) {
			if (x*x + y*y <= 4) // Circle with radius 2
				putPixel(player_color, config->cub3d_data.minimap_surface, player_x + x, player_y + y);
		}
	}

	// Draw direction line
	t_vector2 dir_end = addvectors(
		(t_vector2){player_x, player_y},
		multiplyvector(normalizevector(config->player.dir), 5)
	);

	// Implement simple line drawing if drawLine function isn't available
	// Or uncomment your drawLine function if it exists
	putPixel(player_color, config->cub3d_data.minimap_surface, player_x, player_y);
	putPixel(player_color, config->cub3d_data.minimap_surface, dir_end.x, dir_end.y);
}

void clear_minimap(mlx_image_t *minimap_surface)
{
	for (int y = 0; y < minimap_surface->height; y++)
		for (int x = 0; x < minimap_surface->width; x++)
			putPixel((t_color){0x00000000}, minimap_surface, x, y);
}

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
		ft_testprint(config);
		if (!(config->cub3d_data.mlx = mlx_init(640, 480, "Markus' and Pavlos' cub3D", true)))
			ft_error_handling(20, NULL, config);

		config->cub3d_data.img = mlx_new_image(config->cub3d_data.mlx, 640, 480);
		config->cub3d_data.minimap_surface = mlx_new_image(config->cub3d_data.mlx, 640, 480);
		//render(config);
		//
		load_wall_textures(config);

		//copy_texture(config->cub3d_data.img,east_img, 100, 100);
		int img_instance = mlx_image_to_window(config->cub3d_data.mlx, config->cub3d_data.img, 0, 0);
		mlx_set_instance_depth(&config->cub3d_data.img->instances[img_instance], 0);

		int minimap_instance = mlx_image_to_window(config->cub3d_data.mlx, config->cub3d_data.minimap_surface, 0, 0);
		mlx_set_instance_depth(&config->cub3d_data.minimap_surface->instances[minimap_instance], 1);


		char **map = config->map;
		int map_x = ft_strlen(map[0]);
		int map_y = ft_arrlen(map);
		printf("map: %c\n", map[0][0]);
		printf("map_x: %i\n", map_x);
		printf("map_y: %i\n", map_y);
		printf("textures: %s %s %s %s\n", config->t_north, config->t_south, config->t_east, config->t_west);

		mlx_resize_hook(config->cub3d_data.mlx, resize, config);
		mlx_key_hook(config->cub3d_data.mlx, key_handler, config);
		mlx_loop_hook(config->cub3d_data.mlx, render, config);
		mlx_loop(config->cub3d_data.mlx);

		close(fd);
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.img);
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.minimap_surface);
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.east);
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.west);
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.north);
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.south);
		mlx_close_window(config->cub3d_data.mlx);
		mlx_terminate(config->cub3d_data.mlx);
		ft_free_config(config);
	}
	else
		ft_error_handling(0, NULL, NULL);
	return (0);
}

void render(void *param)
{
	t_gamedata * config = (t_gamedata *)param;
	fill_lower_half(config->cub3d_data.img, *config->floor);
	fill_upper_half(config->cub3d_data.img, *config->ceiling);
	cast_ray_and_draw_wall(config->map, config->player.pos, config->player.dir, config->cub3d_data.img, config);
	if(config->show_minimap)
		draw_minimap(config);
	else
		clear_minimap(config->cub3d_data.minimap_surface);


}

void load_wall_textures(t_gamedata * config)
{
	mlx_texture_t *e_t = mlx_load_png(config->t_east);
	mlx_image_t *easttxt = mlx_texture_to_image(config->cub3d_data.mlx, e_t);
	mlx_delete_texture(e_t);

	mlx_texture_t *w_t = mlx_load_png(config->t_west);
	mlx_image_t *westtxt = mlx_texture_to_image(config->cub3d_data.mlx, w_t);
	mlx_delete_texture(w_t);

	mlx_texture_t *n_t = mlx_load_png(config->t_north);
	mlx_image_t *northtxt = mlx_texture_to_image(config->cub3d_data.mlx, n_t);
	mlx_delete_texture(n_t);

	mlx_texture_t *s_t = mlx_load_png(config->t_south);
	mlx_image_t *southtxt = mlx_texture_to_image(config->cub3d_data.mlx, s_t);
	mlx_delete_texture(s_t);

	config->cub3d_data.east = easttxt;
	config->cub3d_data.west = westtxt;
	config->cub3d_data.north = northtxt;
	config->cub3d_data.south = southtxt;
}
