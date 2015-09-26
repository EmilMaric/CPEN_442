CC := g++ -O3

all: tetragram_builder playfair_solver

playfair_solver: playfair_solver.cpp
	${CC} $< -o $@

tetragram_builder: tetragram_builder.cpp
	${CC} $< -o $@

clean:
	rm tetragram_builder tetragram_list.txt
