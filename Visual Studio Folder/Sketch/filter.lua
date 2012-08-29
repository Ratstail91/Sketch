--draw crazy stuff

for i = 1, map.getxcount() do
	for j = 1, map.getycount() do
		local t = j * map.getxcount() + i
		if t % 6 == 0 then
			map.settile(i,j,1,50)
		end
	end
end