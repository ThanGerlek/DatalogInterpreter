WARNINGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wconversion -Wzero-as-null-pointer-constant -Wuseless-cast

CXXFLAGS = $(WARNINGS) -std=c++17 -g -DDEBUG

main: main.cpp Scanner.cpp Parser.cpp DatalogProgram.cpp

test: test.cpp Scanner.cpp Parser.cpp DatalogProgram.cpp

clean:
	rm -f main
	rm -f test
