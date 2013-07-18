print("Running startup script...")

--create the program's tables
mouse = {}
sketch = {}
brush = {}

--create the mouse button callbacks
mouse.Motion = function(x, y, xrel, yrel)
	--
end

mouse.ButtonDown = function(x, y)
	--
end

mouse.ButtonUp = function(x, y)
	--
end

--create the default save & load functions
sketch.Save = function(fname)
	--
end

sketch.Load = function(fname)
	--
end

print("Finished startup script")
