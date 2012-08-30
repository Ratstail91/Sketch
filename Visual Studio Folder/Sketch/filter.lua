--draw crazy stuff
--might need a rand() function, and a 

for i = 1, map.getxcount() do
	for j = 1, map.getycount() do
		local t = j * map.getxcount() + i
		map.settile(i,j,1,t%5*36+14)
	end
end