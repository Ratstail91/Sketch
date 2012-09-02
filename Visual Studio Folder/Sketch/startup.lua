--configure the outputs
consoleprint = print
terminalprint = terminal.print
print = terminal.print --shortcut

consoleprint("--Running startup script...")


--load the standard scripts
--dofile("config.lua") --not used
dofile("brush.lua")
dofile("save_format.lua")


--useful functions
function map.fill(v)
	map.filllayer(1, v)
end

function map.filllayer(l, v)
	if l < 1 or l > map.getlcount()	then
		print("Layer to fill out of range")
		return
	end
	
	for i = 1, map.getxcount() do
		for j = 1, map.getycount() do
			map.settile(i,j,l,v)
		end
	end
end

function debugtable(t)
	for k, v in pairs(t) do
		consoleprint(k,v)
	end
end


--default config
--tileset.load("terrain.bmp", 32, 32)
--map.load(40,40,3)
--map.fill(14)

load("bksave.txt")

consoleprint("--Finished")
