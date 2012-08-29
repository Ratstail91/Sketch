--bkprint = print
print = terminal.print --shortcut

print("--Running startup script...")


--dofile("config.lua") --not used


--useful functions
function map.fill(v)
	for i = 1, map.getxcount() do
		for j = 1, map.getycount() do
			map.settile(i,j,1,v)
		end
	end
end


function debugtable(t)
	for k, v in pairs(t) do
		print(k,v)
	end
	print("")
end


--default config
tileset.load("terrain.bmp", 32, 32)
map.load(40,40,3)
map.fill(1)


--load the standard brushes
dofile("brush.lua")


print("--Finished")
