#
#
#

CC=clang++

main: lib
	$(CC) -fPIC -L./ -lsocket -o main main.cpp *.o
lib:
	$(CC) -fPIC -c -o libsocket.o LibSocket.cpp
	ar rvs libsocket.a *.o
clean:
	rm main *.a *.o