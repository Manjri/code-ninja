OS := $(shell uname)
ifeq ($(OS), Linux)
    VCPKG_TRIPLET := x64-linux
else ifeq ($(OS), Darwin)
    VCPKG_TRIPLET := x64-osx
endif

CXXFLAGS := --std=c++17 -Wall -Werror
VCPKG_INCLUDES := -I ./vcpkg/installed/$(VCPKG_TRIPLET)/include
VCPKG_LIBPATHS := -L ./vcpkg/installed/$(VCPKG_TRIPLET)/lib

all: server client json_test

%.o: %.cc
	echo "Compiling $< ..."
	g++ -c $(CXXFLAGS) $(VCPKG_INCLUDES) $<

server: server.o
	echo "Linking $@ ..."
	g++ $^ -o $@ $(VCPKG_LIBPATHS) -ljsoncpp

client: client.o
	echo "Linking $@ ..."
	g++ $^ -o $@ $(VCPKG_LIBPATHS) -ljsoncpp

json_test: json_test.o
	echo "Linking $@ ..."
	g++ $^ -o $@ $(VCPKG_LIBPATHS) -ljsoncpp