/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:23:42 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 18:17:18 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// ===== Screen Dimensions ====
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 920

// ====== Game Constants ======
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MOUSE_SENSITIVITY 0.0005

// ===== Map Characters =======
# define WALL '1'
# define DOOR 'D'
# define EAST 'E'
# define WEST 'W'
# define NORTH 'N'
# define SOUTH 'S'
# define EMPTY '0'
# define SPRITE 'X'

// ===== Texture Indices ======
# define EAST_TEX 2
# define WEST_TEX 3
# define DOOR_TEX 4
# define NORTH_TEX 0
# define SOUTH_TEX 1
# define COIN_TEX_BASE 8

// ======== Key Codes =========
# define KEY_A 97
# define KEY_D 100
# define KEY_E 101
# define KEY_L 108
# define KEY_S 115
# define KEY_W 119
# define KEY_ESC 65307
# define KEY_TAB 65289
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// ====== Pixel Colors ========
# define RED_PIXEL 0xFF0000
# define BLUE_PIXEL 0x0000FF
# define GRAY_PIXEL 0X444444
# define BLACK_PIXEL 0x000000
# define GREEN_PIXEL 0x00FF00
# define WHITE_PIXEL 0xFFFFFF
# define PURPLE_PIXEL 0x500CA2
# define LIGHT_GRAY_PIXEL 0xCCCCCC

// ======= Error Codes ========
# define ERROR -1
# define SUCCESS 0
# define MAP_ERROR -4
# define MLX_ERROR -5
# define FILE_ERROR -3
# define MALLOC_ERROR -2

// = Mathematical Constants ===
# define PI 3.14159265359

// ===== Door Constants =======
# define DOOR_OPEN 1.0
# define DOOR_FRAMES 4
# define DOOR_CLOSED 0.0
# define DOOR_TEX_BASE 4
# define DOOR_ANIMATION_SPEED 0.05
# define DOOR_INTERACTION_RANGE 2.0

// ===== Sprite Constants =====
# define COIN_FRAMES 2
# define COIN_FLOAT_HEIGHT 15.0
# define COIN_FLOAT_SPEED 0.08
# define COIN_COLLECT_RANGE 1.0
# define COIN_ANIMATION_SPEED 0.05

// ====== Text Colors =========
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define MAGENTA "\033[0;35m"

#endif
