--the standard save file format

function standard_save(fname)
	local hFile = io.open(fname, "w") --lua handles errors here
	
	hFile:write("sketch format 001\n")
	hFile:write(tileset.getfname(), "\n")
	
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
	if hFile:read() ~= "sketch format 001" then
		consoleprint("Load Error: incorrect file format")
		terminal.print("Load Error: Check console")
		hFile:close()
		return
	end
	
	tileset.load(hFile:read(), 32, 32)
	
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

