all: NaiveAllocator

NaiveAllocator:
	mkdir -p build && cd build; \
	cmake ..; \
	make

test: NaiveAllocator
	./build/tests/NaiveAllocator_tests

clean:
	rm -rf ./build

compile_commands:
	mkdir -p build && cd build; \
	cmake -H. -BDebug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES ..;
	cp ./build/Debug/compile_commands.json ./tests

.PHONY: all NaiveAllocator test clean
