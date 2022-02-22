function OnCollision()
	file = io.open("lua_out.txt", "a+")

	io.output(file)

	io.write("[LUA] Collision Detected\n")

	io.close(file)
end