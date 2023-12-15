#
#
#

CC=clang++

main: lib
	$(CC) -g -o main main.cpp *.o -L./ -lsocket
lib:
	$(CC) -g -c -o libsocket.o LibSocket.cpp
	ar rvs libsocket.a *.o
clean:
	rm main *.a *.o