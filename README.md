# 42_cub3D
RayCaster with miniLibX - Wolfenstein Light
Please execute with ./cub3d [infile.cub]
(one argument serving as input file for game config required)

## General infile rules
> file requires extension .cub
> identifiers for textures: NO, SO, EA, WE.
> textures have to use .png-file format
> identifier for floor color: F.
> identifier for ceiling color: C.
> color value has to consist of RGB-values (3) in range [0,255]. 
> duplicates are not accepted
> map content always has to be last part.

## Map rules
> map has to be surrounded by walls (1), not floors (0). If there is a space in the outer edge, it will be seen as a cave and checked if these cave is surrounded by walls as well. 
> if there is a hole of spaces within the map, these spaces will be interpreted as walls. 
> there must be one player within the map (no dupolicates accepted), defined by one of the direction identifiers (N, S, E, W).

## Indivdual definitions (all of these are more or less easy to adapt):
> fixed defintion for color defintion (RGB, seperated by ',', spaces ignored) | if identifier for color was found, digits are read from this line, they can be seperated by anything alse than digit (current)
> space holes in map, how to handle (error, space = wall = current setup, space == floor)
> map enclosure, what about the edges (marked with *): have to be wall (current) | irrlevant for map-check
    1111111111111
    10000000*1*11
    111110111 111
    111110111 111
> what about content that comes after map (wrong chars, spaces, newlines, ...): error in case of wrong chars or simply ignored (current)


## to check:
> what about very big maps?

## known bugs
> if user tries to load a texture with .png extension that is not a valid png-file -> valgrind issues and undefined behaviour
