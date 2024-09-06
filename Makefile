all: sample1 em

sample1: sample1.cc
	g++ -std=c++14 -o $@ sample1.cc -lbenchmark

em: em.cc
	g++ -std=c++14 -o $@ em.cc -lbenchmark
