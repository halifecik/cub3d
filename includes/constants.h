#ifndef CONSTANTS_H
# define CONSTANTS_H

/* Screen dimensions */
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768

/* Game constants */
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* Map characters */
# define WALL '1'
# define EMPTY '0'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

/* Texture indices */
# define NORTH_TEX 0
# define SOUTH_TEX 1
# define EAST_TEX 2
# define WEST_TEX 3

/* Key codes (may vary by system) */
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

/* Colors */
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000

/* Error codes */
# define SUCCESS 0
# define ERROR -1
# define MALLOC_ERROR -2
# define FILE_ERROR -3
# define MAP_ERROR -4
# define MLX_ERROR -5

/* Mathematical constants */
# define PI 3.14159265359

#endif
