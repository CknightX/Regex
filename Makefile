




main : re.o state_list.o dfa.o nfa.o parser.o main.cpp
	g++ -std=c++11 -o  main re.o state_list.o dfa.o nfa.o parser.o main.cpp -g
re.o : re.cpp
	g++ -std=c++11 -c re.cpp
state_list.o : state_list.cpp
	g++ -std=c++11 -c state_list.cpp
dfa.o : dfa.cpp
	g++ -std=c++11 -c dfa.cpp
nfa.o : nfa.cpp
	g++ -std=c++11 -c nfa.cpp

parser.o : parser.cpp
	g++ -std=c++11 -c parser.cpp

clean :
	rm *.o