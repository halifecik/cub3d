/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:23:42 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 18:42:41 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* Pixel Colors */
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
