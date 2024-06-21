src = main.cpp \
	cc20_file.cpp \
	FileReader.cpp \
	cpp-mmf/memory_mapped_file.cpp \
	City.cpp
includes = -I./. \
	-I./cpp-mmf

all:
	clang++ $(includes) $(src) $(defs) -O3 -lpthread -o obr -std=c++17
debug:
	clang++ $(includes) $(src) $(defs) -O0 -lpthread -g -o obr -std=c++17
clean:
	rm -f obr
