# SDL2-RPG
######Author: *waddleDee (Daniel Hicks)*
######Languages: *C++*
######APIs: *SDL 2.0*
##Introduction
####Purpose
A little SDL2 program I've been developing from scratch as a supplement to my C++ dive, and to learn basic game development mechanics.
####POU
A foundation for loading a player and external level assets (sprite maps, tilesets, walls, NPC interactions, etc).

##Creating a level
Maps and tilesets are instantiated in the main function, outside of the game loop.
```
Tileset instanceName("/path/to/tileset.png", numOfXTilesInSheet, numOfTilesYInSheetY);
Map instanceName("/path/to/map/folder");
```
The default tile size will be calculated by dividing the png's height and width, by the amount of tiles specified in constructor function for each axis.
####Drawing Tiles
Inside of the map folder you have specified, you should create two files:
```
header.map
tiles.map
```
`header.map` declares the map's total width and height, and should only contain two integers in decimal. The first being the number of tiles wide the level will be, and the second being the number of tiles high.

`tiles.map` actually contains the visual representation of your tiles, using a `Uint16` in hexadecimal to indicate the specific tile you want to use.

**Example:**
````
0x2DAC 0x0000 0x14FF 0x0000
0x0000 0x2DAC 0x14FF 0x0000
0x0000 0x0000 0x2DAC 0x0000
````
**A note on formatting:** The intention of this `tiles.map` file is to visuallize your map numerically. The way I have formatted my tiles is by mimicking a table, with each column of tiles on the same line, and each row of tiles represented on a new line. This isn't necessary, but it will probably save you a crapton of time when you're mapping out your tiles :P

I'm going to use the value `F` to demonstrate what each byte represents.

`0x000F` is the base value for the tile's X co-ordinate.<br />
`0x00F0` is the modifier for the base value of X.<br />
`0x0F00` is the base value for the tile's Y co-ordinate.<br />
`0xF0F0` is the modifier for the base value of Y.

The first two bytes are multiplied together in order to give you a tile's X co-ordinate, and the last two are for the Y co-ordinate. You could think of each value as `0xYYXX`.

The reason I implemented this was because it gave a good visualization of what each tile was, and gives a maximum range of 226 values (15*15 + 1 for zero) in each axis, allowing for a maximum tileset consisting of 51 076 unique tiles.

To draw your level, simply call `yourMapInstance.draw(yourTilesetInstance)` from inside your game loop :)
