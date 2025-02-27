#include "../../include/cub3d.h"

int setInitialPosition(t_gamedata *config);
int setInitialDirection(t_gamedata *config);
int initPlayer(t_gamedata *config);

void putPixel(t_color color, mlx_texture_t *surface, int x, int y);

void fillCeiling(t_gamedata *config);
void fillFloor(t_gamedata *config);

mlx_texture_t* selectTexturebyDirection(t_gamedata *config);
int calculateTexelX();
int calculateTexelY();
t_color getTexelColor(mlx_texture_t *texture, int x, int y);


