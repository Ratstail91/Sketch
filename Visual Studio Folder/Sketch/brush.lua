brush = nil --the brush table
local brushdata = {} --the "global" brush data
brushdata.layer = 1
brushdata.tile = 1
brushdata.size = 1

--create a new brush profile
function newbrush()
	local b = {}
	
	function b.isbrush() return true end
	
	function b.mousemotion		(button, mouse_x, mouse_y, mouse_xrel, mouse_yrel) end
	function b.mousebuttondown	(button, mouse_x, mouse_y) end
	function b.mousebuttonup	(button, mouse_x, mouse_y) end
	
	return b
end

function setlayer(l)
	if l > map.getlcount() or l < 1 then
		print("Layer out of range")
	else
		brushdata.layer = l
		print("Layer: ", brushdata.layer)
	end
end

function settile(t)
	if t > tileset.getcount() or t < 0 then
		print("Tile out of range")
	else
		brushdata.tile = t
		print("Tile: ", brushdata.tile)
	end
end

function setsize(s)
	if s > 8 or s < 1 then
		print("Size out of range")
	else
		brushdata.size = s
		print("Size: ", brushdata.size)
	end
end

function setbrush(b)
	if b.isbrush() ~= true then
		print("Invalid brush")
	else
		brush = b
	end
end


--accessors, for more advanced stuff?
function getlayer() return brushdata.layer end
function gettile() return brushdata.tile end
function getsize() return brushdata.size end
function getbrush() return brush end


-------------------------
--the standard brushes
-------------------------


-------------------------
--pencil
-------------------------

pencil = newbrush()

function pencil.mousemotion(button, mouse_x, mouse_y, mouse_xrel, mouse_yrel)
	if button == 1 then --left click
		pencil.script(
			math.ceil(mouse_x/tileset.getwidth()),
			math.ceil(mouse_y/tileset.getheight())
			)
	end
end

function pencil.mousebuttondown(button, mouse_x, mouse_y)
	if button == 1 then --left click
		pencil.script(
			math.ceil(mouse_x/tileset.getwidth()),
			math.ceil(mouse_y/tileset.getheight())
			)
	end
end

function pencil.script(tile_x, tile_y)
	--ensure the user clicked within the map.
	if (tile_x < 1 or
		tile_y < 1 or
		tile_x > map.getxcount() or
		tile_y > map.getycount()
		) then return end
	
	map.settile(tile_x, tile_y, brushdata.layer, brushdata.tile)
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

floodfill = newbrush()

function floodfill.mousebuttondown(button, mouse_x, mouse_y)
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
		floodfill.script(
			map.gettile(tile_x, tile_y, brushdata.layer),
			brushdata.tile,
			tile_x,
			tile_y,
			brushdata.layer
			)
	end
end

function floodfill.script(oldtile, newtile, tile_x, tile_y, tile_l)
	--ensure the user clicked within the map
	if (oldtile == newtile or
		oldtile < 0 or oldtile > tileset.getcount() or
		newtile < 0 or newtile > tileset.getcount() or
		tile_x < 1 or tile_x > map.getxcount() or
		tile_y < 1 or tile_y > map.getycount() or
		tile_l < 1 or tile_l > map.getlcount()
		) then return end
	
	--set this tile
	map.settile(tile_x, tile_y, tile_l, newtile)
	
	--recursive calls
	--if next tile being checked is within range, and equal to "oldtile"
	if tile_x > 1 and map.gettile(tile_x-1, tile_y, tile_l) == oldtile then
		floodfill.script(oldtile, newtile, tile_x-1, tile_y, tile_l)
	end
	if tile_x < map.getxcount() and map.gettile(tile_x+1, tile_y, tile_l) == oldtile then
		floodfill.script(oldtile, newtile, tile_x+1, tile_y, tile_l)
	end
	if tile_y > 1 and map.gettile(tile_x, tile_y-1, tile_l) == oldtile then
		floodfill.script(oldtile, newtile, tile_x, tile_y-1, tile_l)
	end
	if tile_y < map.getycount() and map.gettile(tile_x, tile_y+1, tile_l) == oldtile then
		floodfill.script(oldtile, newtile, tile_x, tile_y+1, tile_l)
	end
end


-------------------------
--the current brush
-------------------------

setbrush(pencil)


