 g++ -Wall -g -std=c++11 digraph.cpp -c
 g++ -Wall -g -std=c++11 uf.cpp -c
 g++ -Wall -g -std=c++11 p2.cpp -c
 g++ -Wall -g -std=c++11 -o p2 p2.o uf.o digraph.o 
 ./p2 clustering_big.txt 
