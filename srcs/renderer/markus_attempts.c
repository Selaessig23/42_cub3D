#include "cub3d.h"

/**
 * @brief function to organise the rendering according to HEIGHT & WIDTH, 
 * touching all points on the x & y coordinates
 * 
 * @param fract A pointer to the t_fractol structure containing
 * the mlx / image / hook data. 
 */
 void	rendering(t_gamedata *config)
 {
     int	x;
     int	y;
 
     y = 0;
     x = 0;
     while (y < HEIGHT)
     {
        while (++x < WIDTH)
        {
            handle_pixel(x, y, config);
            x += 1;
        }
        y += 1;
     }
     mlx_put_image_to_window(fract->mlx,
        fract->mlx_win,
        fract->img.img,
        0, 0);
 }

