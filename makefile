CXXFLAGS = $(FLAGS) $(WARNINGS)

WARNINGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wconversion -Wzero-as-null-pointer-constant -Wuseless-cast
FLAGS = -std=c++17 -g -Wall

CPPFILES = Scanner.cpp Parser.cpp DatalogProgram.cpp Relation.cpp DatalogDatabase.cpp DatalogInterpreter.cpp DependencyGraphBuilder.cpp Graph.cpp RuleEvaluator.cpp
PROJECT = project5


main: main.cpp $(CPPFILES)

test: test.cpp $(CPPFILES)

passoff: main.cpp $(CPPFILES)
	g++ $(FLAGS) -o $(PROJECT) main.cpp $(CPPFILES)

errorless:
	g++ $(FLAGS) -o main main.cpp $(CPPFILES)

clean:
	rm -f main
	rm -f test
	rm -f $(PROJECT)
