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
	struct sockaddr_in addr;
	struct in_addr in;
	struct hostent *hp;

	if(strAddr.empty())
	    return NO_ADDRSET;

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
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
	
	close(sock);

	return 0;
}

int LibSocket::SendTCPData(const uint8_t * const in_pData, uint32_t in_nDataLen)
{ 
	int sock;
	struct sockaddr_in addr;
	struct in_addr in;
	struct hostent *hp;

	if(strAddr.empty())
	    return NO_ADDRSET;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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
	
	close(sock);

	return 0;
}

int LibSocket::SendUDPRequest(const uint8_t * const in_pData, uint32_t in_nDataLen, const uint8_t * out_pData, uint32_t out_nDataLen)
{ return 0; }

int LibSocket::SendTCPRequest(const uint8_t * const in_pData, uint32_t in_nDataLen, const uint8_t * out_pData, uint32_t out_nDataLen)
{ return 0; }

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
	
	close(sock);

	return 0;

}

void LibSocket::GetData(int& sock)
{
}

void LibSocket::SetAddr(std::string in_strAddr, uint16_t in_nPort)
{
    strAddr = in_strAddr;
    nPort = in_nPort;
}

}; //libsocket namespace
