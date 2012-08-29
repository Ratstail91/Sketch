brush = {} --the brush table
brush.layer = 1
brush.tile = 1

--create a new brush profile
function brush.newbrush()
	local b = {}
	function b.mousemotion		(button, x, y, xrel, yrel)	end
	function b.mousebuttondown	(button, x, y)				end
	function b.mousebuttonup	(button, x, y)				end
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

-------------------------
--the standard brushes
-------------------------


-------------------------
--pencil
-------------------------

brush.pencil = brush.newbrush()

function brush.pencil.mousemotion(button, x, y, xrel, yrel)
	if button == 1 then --left click
		brush.pencil.script(x, y)
	end
end

function brush.pencil.mousebuttondown(button, x, y)
	if button == 1 then --left click
		brush.pencil.script(x, y)
	end
end

function brush.pencil.script(x, y)
	--ensure the user clicked within the map.
	if (x <= 0 or y <= 0 or x > map.getxcount() * tileset.getwidth() or y > map.getycount() * tileset.getheight()) then return end
	local t = map.gettile( math.ceil(x/tileset.getwidth()), math.ceil(y/tileset.getheight()), 1)
	map.settile( math.ceil(x/tileset.getwidth()), math.ceil(y/tileset.getheight()), brush.layer, brush.tile)
end


-------------------------
--square
--circle
--floodfill
-------------------------


-------------------------
--the current brush
-------------------------


brush.active = brush.pencil


