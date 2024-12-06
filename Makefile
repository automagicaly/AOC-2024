CC=clang-18
LIB_PATH=./lua/install/lib

lua_make:
	cd lua && $(MAKE) all test local
	touch lua_make

clean:
	rm lua_make elua
	cd lua && $(MAKE) clean

elua: lua_make main.c dyn_string.c
	$(CC) -lm -o $@ main.c $(LIB_PATH)/liblua.a dyn_string.c

day1: elua day1.lua
	./elua day1.lua

day1p2: elua day1p2.lua
	./elua day1p2.lua

day2: elua day2.lua
	./elua day2.lua

day2p2: elua day2p2.lua
	./elua day2p2.lua

day3: elua day3.lua
	./elua day3.lua

day3p2: elua day3p2.lua
	./elua day3p2.lua
