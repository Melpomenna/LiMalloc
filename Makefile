.PHONY: build configure tests benchmarks

OS = $(shell uname -s)
ifeq ($(OS),Linux)
	PRESET=debug-Linux
else ifeq ($(OS),Darwin)
	PRESET=debug-MacOS
endif

CONFIG=debug
ENABLE_TESTS=TRUE
ENABLE_BENCHMARKS=TRUE

all: configure

configure:
ifeq ($(OS),Linux)
	sh ./configuration/Linux/configuration.sh
else ifeq ($(OS),Darwin)
	sh ./configuration/MacOS/configuration.sh
endif
	cmake --preset=$(PRESET)

rebuild: clean configure build

build:
	cmake --build . --preset=$(PRESET)

install:
	cmake --install . --preset=$(PRESET)

uninstall:
	cmake --install . --preset=$(PRESET) --uninstall

style:
	clang-format -i $$(find include -type f -name "*.h")
	clang-format -i $$(find src -type f -name "*.c")	
	clang-format -i $$(find tests -type f -name "*.cpp")
	clang-format -i $$(find benchmarks -type f -name "*.cpp")

tests:
ifeq ($(OS),Linux)
	ctest --preset=$(PRESET)
else
	./build/$(CONFIG)/WorkFolder/Tests
endif

benchmarks:
ifeq ($(OS),Linux)
	./build/${CONFIG}/WorkFolder/Benchmarks
else ifeq ($(OS),Darwin)
	xcodebuild -project ./build/${CONFIG}/Memory.xcodeproj -scheme run_benchmarks
endif

leaks:
ifeq ($(OS),Linux)
	cmake --leak-check --preset=$(PRESET)
endif

clean:
	rm -rf build