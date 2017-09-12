atmSim.exe	:	atmSim.o
	g++ atmSim.o -std=c++11 -o atmSim.exe

atmSim.o	:	atmSim.cpp atmSim.h
	g++ -std=c++11 -c atmSim.cpp

clean:
	del *.o
	del *.exe

