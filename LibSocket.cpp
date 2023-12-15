//Implementation of the socket library

#include<iostream>
#include<cstring>
#include<netdb.h>
#include<memory>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include "LibSocket.h"

namespace libsocket {

enum SOCKET_ERRORS {NO_SOCKET=1, NO_HOSTENT, NO_CONNECT, NO_ADDRSET};

LibSocket::LibSocket(const std::string& in_strAddr, uint16_t in_nPort)
{
    SetAddr(in_strAddr, in_nPort);
}

int LibSocket::SendUDPData(const uint8_t * const in_pData, uint32_t in_nDataLen)
{
	int sock;

	if(SendData(sock, SOCK_DGRAM, in_pData, in_nDataLen) == 0)
	{}
	
	close(sock);

	return 0;
}

int LibSocket::SendTCPData(const uint8_t * const in_pData, uint32_t in_nDataLen)
{ 
	int sock;

	if(SendData(sock, SOCK_STREAM, in_pData, in_nDataLen) == 0)
	{}

        close(sock);

	return 0;
}

int LibSocket::SendUDPRequest(const uint8_t * const in_pData, uint32_t in_nDataLen, uint8_t* &out_pData, int32_t& out_nDataLen)
{
	int sock, nRet, nOffset = 0;

	if((nRet = SendData(sock, SOCK_DGRAM, in_pData, in_nDataLen)) != 0) { // 0 если всё OK
	    std::cerr << "LibSocket: error, nRet=" << nRet << std::endl;
	    close(sock);
	    return nRet;
	}
//	do {
	    nRet = GetData(sock, out_pData + nOffset, out_nDataLen);
//	    nOffset += nRet;
//	    std::cerr << "nOffset=" << nOffset << std::endl;
//	} while(nRet > 0);

	close(sock);

	return nRet;
}

int LibSocket::SendTCPRequest(const uint8_t * const in_pData, uint32_t in_nDataLen, uint8_t* &out_pData, int32_t& out_nDataLen)
{
	int sock, nRet, nOffset = 0;

	if((nRet = SendData(sock, SOCK_STREAM, in_pData, in_nDataLen)) != 0) {
		close(sock);
		return nRet;
	}
	do {
	    nRet = GetData(sock, out_pData + nOffset, out_nDataLen);
	    nOffset += nRet;
	} while(nRet > 0);

	close(sock);

	return nRet;
}

int LibSocket::GetUDPData(const uint8_t * in_pData, std::string in_strAddr)
{ return 0; }

int LibSocket::SendData(int& sock, int type, const uint8_t * const in_pData, uint32_t in_nDataLen)
{
	struct sockaddr_in addr;
	struct in_addr in;
	struct hostent *hp;

	if(strAddr.empty())
	    return NO_ADDRSET;

	if((sock = socket(AF_INET, type, 0)) == -1)
		return NO_SOCKET;

	hp = gethostbyname(strAddr.c_str()); //get hostent struct

	if(hp == NULL)
	{
		close(sock);
		return NO_HOSTENT;
	}
	bzero(&addr, sizeof(addr));
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length); //copy address
	addr.sin_family = hp->h_addrtype;
	addr.sin_port = htons(nPort);

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		close(sock);
		return NO_CONNECT;
	}
	
	send(sock, in_pData, in_nDataLen, 0);
	
	return 0;

}

int LibSocket::GetData(int& sock, uint8_t* out_pData, int32_t& out_nDataLen)
{
	int nRet;
	uint8_t *pBuff = new uint8_t[1024*1024];
	nRet = recv(sock, pBuff, 1024*1024, 0);
	if(nRet > 0) {
	    memcpy(out_pData, pBuff, nRet);
	    out_nDataLen = nRet;
	} else {
	    out_nDataLen = 0;
	}
	delete [] pBuff;
	return nRet;
}

void LibSocket::SetAddr(std::string in_strAddr, uint16_t in_nPort)
{
    strAddr = in_strAddr;
    nPort = in_nPort;
}

}; //libsocket namespace
