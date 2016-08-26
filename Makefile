ant: main.o ant.o
	g++ -std=c++11 -g -Wall main.o ant.o -o ant

main.o: main.cpp 
	g++ -std=c++11 -g -Wall -c main.cpp

ant.o: ant.cpp ant.h 
	g++ -std=c++11 -g -Wall -c ant.cpp


clean:
	rm *.o ant
	echo clean done
