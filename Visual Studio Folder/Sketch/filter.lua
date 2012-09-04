--draw crazy stuff
--might need a rand() function, and a 

print("Loading filters...")

--resize the map to (x,y,l), truncating the data
function resize(newx, newy, newl)
	if newl == nil then newl = map.getlcount() end --optional parameter
	
	local tempmap = {}
	local oldx = map.getxcount()
	local oldy = map.getycount()
	local oldl = map.getlcount()
	
	for i = 1, newx do
		tempmap[i] = {}
		for j = 1, newy do
			tempmap[i][j] = {}
			for k = 1, newl do
				tempmap[i][j][k] = 0
				
				if i <= oldx and j <= oldy and k <= oldl then
					tempmap[i][j][k] = map.gettile(i, j, k)
				end
			end
		end
	end
	
	map.unload()
	map.load(newx, newy, newl)
	
	for i = 1, map.getxcount() do
		for j = 1, map.getycount() do
			for k = 1, map.getlcount() do
				map.settile(i,j,k,tempmap[i][j][k])
			end
		end
	end
	
	--compensate for this possible glitch
	if getlayer() > map.getlcount() then
		setlayer(map.getlcount())
	end
end

--curry the above script
function pushlayers(lcount)
	resize(map.getxcount(), map.getycount(), map.getlcount()+lcount)
	print("Layers: ", map.getlcount())
end

function poplayers(lcount)
	if lcount >= map.getlcount() then
		consoleprint("Error: Cannot pop that many layers")
		terminalprint("Filter Error: Check console")
		return
	end
	
	resize(map.getxcount(), map.getycount(), map.getlcount()-lcount)
	print("Layers: ", map.getlcount())
end
