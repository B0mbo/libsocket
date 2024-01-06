#
#
#

CC=clang++
DBG=

main: lib
	$(CC) $(DBG) -o main main.cpp *.o -L./ -lsocket
	rm *.o
lib:
	$(CC) $(DBG) -c -o libsocket.o LibSocket.cpp
	ar rvs libsocket.a *.o
clean:
	rm main *.a *.o
