CC=clang-18
LIB_PATH=./lua/install/lib

lua_make:
	cd lua && $(MAKE) all test local
	touch lua_make

clean:
	rm lua_make elua
	cd lua && $(MAKE) clean

elua: lua_make main.c
	$(CC) -lm -o $@ main.c $(LIB_PATH)/liblua.a

day1: elua day1.lua
	./elua day1.lua
