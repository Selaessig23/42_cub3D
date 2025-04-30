# 42_cub3D
RayCaster with miniLibX - Wolfenstein Light
Please execute with ./cub3d [infile.cub]
(one argument serving as input file for game config required)

## General infile rules
- file requires extension .cub
- identifiers for textures: NO, SO, EA, WE.
- textures have to use .png-file format
- identifier for floor color: F.
- identifier for ceiling color: C.
- all identifiers have to be followed by a space
- color value has to consist of RGB-values (3) in range [0,255], seperated by comma
- except in the map-content spaces are ignored, tabs are considered, hence can cause error messages
- duplicates of identifiers are not accepted
- map content always has to be last part.

## Map rules
- map has to be surrounded by walls (1), not floors (0). If there is a space in the outer edge, it will be seen as a cave and checked if these cave is surrounded by walls as well. 
- if there is a hole of spaces within the map, these spaces will be interpreted as walls. 
- there must be one player within the map (no duplicates accepted), defined by one of the direction identifiers (N, S, E, W).
- if there is an empty line in map content this will cause an error

## known bugs
- if user tries to load a texture with .png extension that is not a valid png-file -- valgrind issues and undefined behaviour
- several valgrind issued caused by minilibx-library
