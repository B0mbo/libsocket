//Header of socket library

#pragma once

#include "ILibSocket.h"

extern "C++" {

namespace libsocket {

class LibSocket : public ILibSocket
{
    std::string strAddr;// remote host address
    uint16_t nPort;	// remote port
    
public:
    LibSocket() {};
    LibSocket(const std::string& in_strAddr, uint16_t in_nPort);
    ~LibSocket() {};

    //send TCP data
    int SendTCPData(const uint8_t * const in_pData, uint32_t in_nDataLen);
    //send UDP data
    int SendUDPData(const uint8_t * const in_pData, uint32_t in_nDataLen);

    //send TCP request and get answer
    int SendTCPRequest(const uint8_t * const in_pData, uint32_t in_nDataLen, uint8_t* &out_pData, int32_t& out_nDataLen);
    //send UDP request and get ansger
    int SendUDPRequest(const uint8_t * const in_pData, uint32_t in_nDataLen, uint8_t* &out_pData, int32_t& out_nDataLen);

    //get UDP data
    int GetUDPData(const uint8_t *in_pData, std::string strAddr);
    
    int SendData(int& sock, int type, const uint8_t * const in_pData, uint32_t in_nDataLen);
    int GetData(int& sock, uint8_t* out_pData, int32_t& out_nDataLen);
    void SetAddr(std::string in_strAddr, uint16_t in_nPort);

};

}; //libsocket namespace

}
