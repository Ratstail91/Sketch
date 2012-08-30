brush = {} --the brush table
brush.layer = 1
brush.tile = 1
brush.size = 1

--create a new brush profile
function brush.newbrush()
	local b = {}
	function b.mousemotion		(button, mouse_x, mouse_y, mouse_xrel, mouse_yrel) end
	function b.mousebuttondown	(button, mouse_x, mouse_y) end
	function b.mousebuttonup	(button, mouse_x, mouse_y) end
	return b
end

function brush.setlayer(l)
	if l > map.getlcount() or l < 1 then
		print("Layer out of range")
	else
		brush.layer = l
		print("Layer: ", brush.layer)
	end
end

function brush.settile(t)
	if t > tileset.getcount() or t < 0 then
		print("Tile out of range")
	else
		brush.tile = t
		print("Tile: ", brush.tile)
	end
end

function brush.setsize(s)
	if s > 8 or t < 1 then
		print("Size out of range")
	else
		brush.size = s
		print("Size: ", brush.size)
	end
end

-------------------------
--the standard brushes
-------------------------


-------------------------
--pencil
-------------------------

brush.pencil = brush.newbrush()

function brush.pencil.mousemotion(button, mouse_x, mouse_y, mouse_xrel, mouse_yrel)
	if button == 1 then --left click
		brush.pencil.script(
			math.ceil(mouse_x/tileset.getwidth()),
			math.ceil(mouse_y/tileset.getheight())
			)
	end
end

function brush.pencil.mousebuttondown(button, mouse_x, mouse_y)
	if button == 1 then --left click
		brush.pencil.script(
			math.ceil(mouse_x/tileset.getwidth()),
			math.ceil(mouse_y/tileset.getheight())
			)
	end
end

function brush.pencil.script(tile_x, tile_y)
	--ensure the user clicked within the map.
	if (tile_x < 1 or
		tile_y < 1 or
		tile_x > map.getxcount() or
		tile_y > map.getycount()
		) then return end
	
	map.settile( tile_x, tile_y, brush.layer, brush.tile)
end


-------------------------
--square
-------------------------

--


-------------------------
--circle
-------------------------

--


-------------------------
--floodfill
-------------------------

brush.floodfill = brush.newbrush()

function brush.floodfill.mousebuttondown(button, mouse_x, mouse_y)
	--upper part
	local tile_x = math.ceil(mouse_x/tileset.getwidth())
	local tile_y = math.ceil(mouse_y/tileset.getheight())
	
	--can access the tiles in the call to map.gettile below
	if (tile_x < 1 or
		tile_y < 1 or
		tile_x > map.getxcount() or
		tile_y > map.getycount()
		) then return end
	
	
	if button == 1 then --left click
		--make sure each parameter is ok
		brush.floodfill.script(
			map.gettile(tile_x, tile_y, brush.layer),
			brush.tile,
			tile_x,
			tile_y,
			brush.layer
			)
	end
end

function brush.floodfill.script(oldtile, newtile, tile_x, tile_y, tile_l)
	--ensure the user clicked within the map
	if (oldtile < 0 or oldtile > tileset.getcount() or
		newtile < 0 or newtile > tileset.getcount() or
		tile_x < 1 or tile_x > map.getxcount() or
		tile_y < 1 or tile_y > map.getycount() or
		tile_l < 1 or tile_l > map.getlcount()
		) then return end
	
--	print(oldtile, newtile, tile_x, tile_y, tile_l)
	
	--set
	map.settile(tile_x, tile_y, tile_l, newtile)
	
	--recursive calls
	--if next tile being checked is within range, and equal to "oldtile"
	if tile_x > 1 and map.gettile(tile_x-1, tile_y, tile_l) == oldtile then
		brush.floodfill.script(oldtile, newtile, tile_x-1, tile_y, tile_l)
	end
	if tile_x < map.getxcount() and map.gettile(tile_x+1, tile_y, tile_l) == oldtile then
		brush.floodfill.script(oldtile, newtile, tile_x+1, tile_y, tile_l)
	end
	if tile_y > 1 and map.gettile(tile_x, tile_y-1, tile_l) == oldtile then
		brush.floodfill.script(oldtile, newtile, tile_x, tile_y-1, tile_l)
	end
	if tile_y < map.getycount() and map.gettile(tile_x, tile_y+1, tile_l) == oldtile then
		brush.floodfill.script(oldtile, newtile, tile_x, tile_y+1, tile_l)
	end
end


-------------------------
--the current brush
-------------------------

brush.active = brush.pencil


