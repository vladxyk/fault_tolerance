all: client server 

client: client.o liblab.so mainlab.so
	g++ -o client client.o -L. -llab -Wl,-rpath,.

server: server.o liblab.so mainlab.so
	g++ -pthread -o server server.o -L. -llab -Wl,-rpath,.

server.o: server.cpp
	g++ -c server.cpp 

client.o: client.cpp
	g++ -c client.cpp

liblab.so: lib.o
	g++ -shared -o liblab.so lib.o

lib.o: lib.cpp
	g++ -c -fPIC lib.cpp main.cpp

mainlab.so: main.o
	g++ -shared -o mainlab.so main.o

main.o: main.cpp
	g++ -c -fPIC main.cpp
	
clean:
	rm -f *.o *.so 

clear:
	rm -f *.o *.so server client