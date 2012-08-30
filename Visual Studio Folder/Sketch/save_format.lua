--the standard save file format

function standard_save(fname)
	local hFile = io.open(fname, "w") --lua handles errors here
	
	hFile:write("sketch format 002\n")
	hFile:write(tileset.getfname(), "\n")
	
	hFile:write(map.getxcount(), " ", map.getycount(), " ", map.getlcount(), " ", tileset.getwidth(), " ", tileset.getheight(), "\n")
	
	--note the y outside x format here, giving a more readable output
	for j = 1, map.getycount() do
		for i = 1, map.getxcount() do
			for k = 1, map.getlcount() do
				hFile:write(map.gettile(i,j,k), " ")
			end
			hFile:write("\t")
		end
		hFile:write("\n")
	end
	
	hFile:close()
	
	print("Save complete")
end

function standard_load(fname)
	local hFile = io.open(fname, "r") --lua handles errors here
	
	--error checking
	if hFile:read() ~= "sketch format 002" then
		consoleprint("Load Error: incorrect file format")
		terminal.print("Load Error: Check console")
		hFile:close()
		return
	end
	
	fname = hFile:read()
	
	local x = hFile:read("*n")
	local y = hFile:read("*n")
	local l = hFile:read("*n")
	local w = hFile:read("*n")
	local h = hFile:read("*n")
	
	map.load(x,y,l)
	tileset.load(fname,w,h)
	
	--note the y outside x format here, giving a more readable output
	for j = 1, map.getycount() do
		for i = 1, map.getxcount() do
			for k = 1, map.getlcount() do
				local v = hFile:read("*n")
				map.settile(i,j,k,v)
			end
		end
	end
	
	hFile:close()
	
	print("Load complete")
end


save = standard_save
load = standard_load

