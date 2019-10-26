tsat:
	g++ utils/utils.cpp utils/config.cpp tsat.cpp -I -O2 -std=c++11
debug:
	g++ -DDEBUG utils/utils.cpp utils/config.cpp tsat.cpp -I -O2 -std=c++11
