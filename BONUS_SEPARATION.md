# Bonus Separation Documentation

## Overview
This document describes the separation of mandatory and bonus functionality in the cub3D project according to 42 norm requirements.

## Binaries
- **cub3d**: Mandatory version with basic raycasting only
- **cub3d_bonus**: Bonus version with all features (minimap, doors, sprites, mouse control)

## Build System
```bash
make        # Builds mandatory version (cub3d)
make bonus  # Builds bonus version (cub3d_bonus)
make clean  # Cleans object files
make fclean # Cleans binaries and object files
make re     # Rebuilds everything
```

## Header Files
### Mandatory
- `cub3d_mandatory.h`: Function declarations for mandatory features
- `structs_mandatory.h`: Data structures for mandatory features

### Bonus
- `cub3d_bonus.h`: Function declarations including bonus features
- `structs_bonus.h`: Extended data structures with bonus fields

## Source File Organization

### Files with Separate Versions
The following files have separate `_bonus.c` versions because they contain functionality that differs between mandatory and bonus:

1. **Main Entry Points**
   - `main.c` / `main_bonus.c`

2. **Game Logic**
   - `game/loop.c` / `game/loop_bonus.c`
   - `game/actions.c` / `game/actions_bonus.c`
   - `game/movement.c` / `game/movement_bonus.c`
   - `game/rotation.c` / `game/rotation_bonus.c`
   - `game/mouse_bonus.c` (bonus only)

3. **Initialization**
   - `init/graphics.c` / `init/graphics_bonus.c`
   - `init/map.c` / `init/map_bonus.c`

4. **Parsing**
   - `parse/parse_map.c` / `parse/parse_map_bonus.c`

5. **Raycasting**
   - `raycast/raycast.c` / `raycast/raycast_bonus.c`
   - `raycast/render.c` / `raycast/render_bonus.c`
   - `raycast/texture.c` / `raycast/texture_bonus.c`

6. **Cleanup**
   - `utils/cleanup/clean_data.c` / `utils/cleanup/clean_data_bonus.c`
   - `utils/cleanup/clean_graphics.c` / `utils/cleanup/clean_graphics_bonus.c`
   - `utils/cleanup/clean_map.c` / `utils/cleanup/clean_map_bonus.c`

### Bonus-Only Features
Located in `src/bonus/` directory:

1. **Minimap**
   - `bonus/minimap/draw_minimap_bonus.c`
   - `bonus/minimap/draw_full_map_bonus.c`
   - `bonus/minimap/minimap_tools_bonus.c`

2. **Doors**
   - `bonus/door/door_action_bonus.c`
   - `bonus/door/door_manager_bonus.c`
   - `bonus/door/door_utils_bonus.c`

3. **Sprites**
   - `bonus/sprite/initialize_bonus.c`
   - `bonus/sprite/update_bonus.c`
   - `bonus/sprite/sort_bonus.c`
   - `bonus/sprite/render_bonus.c`
   - `bonus/sprite/interface_bonus.c`
   - `bonus/sprite/texture_bonus.c`
   - `bonus/sprite/calculate_bonus.c`

### Shared Files
The following files are used by both mandatory and bonus versions without modification:
- `init/player.c`
- `init/direction.c`
- `init/raycast.c`
- `init/config.c`
- `parse/check_map.c`
- `raycast/calculate.c`
- `utils/render.c`
- `utils/map.c`
- `utils/utilities.c`
- `utils/cleanup/clean_config.c`

## Norm Compliance
✓ No conditional compilation (#ifdef) in source files
✓ Separate _bonus.c files for bonus functionality
✓ Clear separation between mandatory and bonus headers
✓ Two distinct binaries with independent build processes
✓ All bonus files properly named with _bonus suffix

## Key Differences

### Mandatory Version (cub3d)
- Basic raycasting engine
- Wall collision detection
- Player movement (WASD + arrows)
- Texture rendering (4 textures: N, S, E, W)
- Minimal graphics initialization

### Bonus Version (cub3d_bonus)
- All mandatory features
- Interactive minimap (Tab to toggle full/mini)
- Animated doors (E to interact)
- Collectible sprites (coins with animation)
- Mouse control for camera rotation
- Extended texture support (12 textures)
- Door animation system
- Sprite rendering and sorting

## Testing
Both binaries should build independently:
```bash
make        # Should build cub3d successfully
make bonus  # Should build cub3d_bonus successfully
```

Both should run with a valid .cub map file:
```bash
./cub3d maps/map.cub
./cub3d_bonus maps/map.cub
```
