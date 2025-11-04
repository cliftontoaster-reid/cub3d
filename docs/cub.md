# .cub files

.cub files are configuration files used in the Cub3D project to define the textures and the map layout for a 3D game environment.

## File Structure

A .cub file typically consists of two main sections:

- **Options Section**: This section contains texture paths and color definitions. Each option is defined on a separate line. The options include:
  - `NO <path>`: Path to the texture for the north wall.
  - `SO <path>`: Path to the texture for the south wall.
  - `WE <path>`: Path to the texture for the west wall.
  - `EA <path>`: Path to the texture for the east wall.
  - `F <R,G,B>`: Floor color in RGB format.
  - `C <R,G,B>`: Ceiling color in RGB format.

- **Map Section**: This section defines the layout of the map using a grid of characters. The characters represent different elements in the game:
  - `1`: Wall
  - `0`: Empty space
  - `N`, `S`, `E`, `W`: Player's starting position and orientation (North, South, East, West)

## Example .cub File

```cub
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Parsing .cub Files

The parsing of the .cub file will go as follows:

- Find the last empty line in the file to separate options from the map.
- Split the file into two parts: options and map.
- For every line in options:
  - Trim whitespace and split the line by spaces.
  - Split with the first space character.
  - Validate and store the option based on its identifier (NO, SO, WE, EA, F, C).
- For the map use the `map_from_str` function inside `map/table.h` to parse and validate the map layout.

Ensure that the .cub file adheres to the specified format for successful parsing and game initialization.
