Sketch Map Editor

--------------------------------------------------------------------------------

Sketch is a simple, lightweight 2D tile map editor, written with C++, SDL and
lua. The core is written in C++ with graphics and input handled by SDL. Lua
scripts are used by the editor to process the map in various ways such as
custom saving and loading formats, random terrain generation or extended
functionality.

The source and documentation for this project can be found at

https://github.com/Ratstail91/Sketch

Reading the included lua scripts may help you to understand better than this
file.

--------------------------------------------------------------------------------

Controls

Mouse:
	Left click to set a tile
	Right click and drag to move around the map
	Scroll wheel up increases brush size
	Scroll wheel down decreases brush size

Keyboard:
	Tab key to switch to "tile select" mode
		NOTE: Escape while in tileselect mode will set the selected tile back
		to 0 (invisible, or null)
	Shift + Tab will toggle the visibility of the terminal window
	The terminal can be used to run lua scripts

Terminal:
	Some useful lua functions can be found in startup.lua, brush.lua and
	save_format.lua

Built in lua features:
	map --the map library
	tileset --the tileset library
	terminal --the terminal library
	brush --the currently active brush script, see brush section below
	
	map.load(x, y, l) --does NOT load anything, just  generates the memory for the map
	map.unload() --clears the map
	map.isloaded() --is the map loaded
	map.getxcount() --number tiles on the x axis
	map.getycount() --number tiles on the y axis
	map.getlcount() --number tiles on the l axis
	map.gettile(x,y,l) --gets the tile at x, y, l
	map.settile(x,y,l,v) --sets the tile at x, y, l to v
	map.fill(v) --fills the lowest layer with tile value v
	map.filllayer(l, v) --fills layer l with tile value v
	
	tileset.load(fname, w, h) --loads a tileset, w & h are the w & h of each tile
	tileset.unload() --clears the tileset
	tileset.isloaded() --is the tileset loaded
	tileset.getfname() --gets the filename of the tileset
	tileset.getxcount() --gets the number of tiles on the x axis
	tileset.getycount() --gets the number of tiles on the y axis
	tileset.getwidth() --gets the width of the tiles
	tileset.getheight() --gets the height of the tiles
	tileset.getcount() --gets the total number of tiles on the tileset
	
	debugtable(t) --outputs every element of t to the console, good for learning
		about the libraries above
	
	consoleprint() --standard lua print function
	terminalprint( )--same as terminal.print()
	
	save() --same as standard_save(), saves a map using the standard format
	load() --same as standard_load(), loads a map using the standard format
	
	setlayer(l) --set the current layer
	settile(t) --set the current tile
	setsize(s) --set the current size
	setbrush(b) --set the current brush

--------------------------------------------------------------------------------

Brushes

The heart of this program are the brush scripts. Currently, there are 4:

pencil:
	set a single tile

square:
	set all tiles within a square

circle:
	set all tiles within a circle

floodfill:
	sets all tiles matching the selected tile, touching the selected tile

To select a brush, type setbrush([brushname]) into the terminal.

--------------------------------------------------------------------------------

Known Bugs/Issues

I've had issues implementing the directory system at this late stage, so if the
map sucks the tileset directory into the save file, contact me.

To set the currently selected tile to 0 (deselect) you must open the tile select
screen, and press escape or space.

The current font file is missing some punctuation characters, including quote
marks.

--------------------------------------------------------------------------------

Information

You can contact me at:

ratstail91@yahoo.com.au
http://kr-studios.tumblr.com/
http://www.facebook.com/krgamestudios


--------------------------------------------------------------------------------

Copyright

