#include<cstdint>
#include<cstring>
#include<iostream>

#include"LibSocket.h"

#define DATA_SIZE 1024

int main()
{
	uint8_t *pszData, *pData;
	uint32_t nLen;
	int32_t nDataSize;
	char message[] = "Hello, World!\n";
	std::string strAddr = "localhost";
	libsocket::LibSocket *lib = new libsocket::LibSocket(strAddr, 7777);

	nLen = strlen(message);
	pszData = new uint8_t[DATA_SIZE];
	memset(pszData, 0, DATA_SIZE);
	memcpy(pszData, message, nLen);

	lib->SendUDPRequest(pszData, strlen((char *)pszData), pData, nDataSize);

	delete [] pszData;
	delete lib;
	
	return 0;
}
