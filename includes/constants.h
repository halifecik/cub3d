/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:23:42 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/27 20:39:49 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/* Screen dimensions */
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 920

/* Game constants */
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* Sensitivity Constant */
# define MOUSE_SENSITIVITY 0.0005

/* Map characters */
# define WALL '1'
# define EMPTY '0'
# define DOOR 'D'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

/* Texture indices */
# define NORTH_TEX 0
# define SOUTH_TEX 1
# define EAST_TEX 2
# define WEST_TEX 3
# define DOOR_TEX 4

/* Key codes */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_L 108
# define KEY_TAB 65289
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_E 101

/* Pixel Colors */
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define GRAY_PIXEL 0X444444
# define LIGHT_GRAY_PIXEL 0xCCCCCC
# define FANDANGO_PIXEL 0xB53389
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

/* Door constants */
# define DOOR_ANIMATION_SPEED 0.02
# define DOOR_INTERACTION_RANGE 2.0
# define CAP_DOOR 0.7
# define DOOR_CLOSED 0.0
# define DOOR_OPEN 1.0
# define DOOR_FRAMES 8
# define DOOR_TEX_BASE 4

/* Text Colors */
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

#endif
