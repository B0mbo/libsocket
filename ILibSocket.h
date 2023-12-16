//Socket library interface

#pragma once

#include <cstdint>

extern "C++" {

namespace libsocket {

class ILibSocket {
public:
    //send TCP data
    virtual int SendTCPData(const uint8_t * const in_pData, uint32_t in_nDataLen) = 0;
    //send UDP data
    virtual int SendUDPData(const uint8_t * const in_pData, uint32_t in_nDataLen) = 0;

    //send TCP data
    virtual int SendTCPRequest(const uint8_t * const in_pData, uint32_t in_nDataLen, uint8_t* &out_pData, int32_t& out_nDataLen) = 0;
    //send UDP data
    virtual int SendUDPRequest(const uint8_t * const in_pData, uint32_t in_nDataLen, uint8_t* &out_pData, int32_t& out_nDataLen) = 0;

    //get UDP answer
    virtual int GetUDPData(const uint8_t *out_pData, std::string in_strAddr) = 0;
};

}; //libsocket namespace
}
