--[[
 * File Name: save_format.lua
 * Author: Kayne Ruse
 * Date: 5/9/2012
 * Copyright: (c) Kayne Ruse 2012
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * Description:
 *     ...
--]]

--Do not edit this file unless you know what you are doing!!

--the standard save file format

function standard_save(fname)
	local hFile, errmsg = io.open(dir["map"] .. fname, "w") --lua handles errors here
	
	if (hFile == nil) then
		print("Save Error: " .. errmsg)
		return
	end
	
	hFile:write("sketch format 004\n") --this format version
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
	local hFile, errmsg = io.open(dir["map"] .. fname, "r") --lua handles errors here
	
	if (hFile == nil) then
		print("Load Error: " .. errmsg)
		return
	end
	
	if hFile:read() ~= "sketch format 004" then --this format version
		consoleprint("Load Error: incorrect file format")
		terminalprint("Load Error: Check console")
		hFile:close()
		return
	end
	
	fname = hFile:read()
	
	local x = hFile:read("*n")
	local y = hFile:read("*n")
	local l = hFile:read("*n")
	local w = hFile:read("*n")
	local h = hFile:read("*n")
	
	map.load(x,y,l) --load here is a misnomer, this only generates the array in memory
	tileset.load(dir["tileset"] .. fname,w,h)
	
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

