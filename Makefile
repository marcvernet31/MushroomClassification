all: fulldistance calculate

fulldistance: fulldistance.cc
	g++ -std=c++11 -Wall -O2 fulldistance.cc -o fulldist.x

calculate: fulldist.x dist-matrix.csv mushrooms.csv filenames.txt
	./fulldist.x < filenames.txt

clean:
	rm *.x
