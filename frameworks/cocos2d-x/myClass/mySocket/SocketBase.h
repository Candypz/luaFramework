/************************************************* 
Author: candy_pz
Email: candy_pz@outlook.com
FileName: SocketBase.h
Date: 2016-8-31
Description: 
**************************************************/

#ifndef SOCKETBASE_H_
#define SOCKETBASE_H_

#include <thread>
#include <mutex>

#define  MY_PLATFORM_WIN32 MY_PLATFORM_WIN32
#define  MY_PLATFORM MY_PLATFORM

#if (MY_PLATFORM == MY_PLATFORM_WIN32)  
#include <WinSock2.h>  
#pragma comment(lib, "WS2_32.lib")  
#define CSocket SOCKET 
#else
#include <arpa/inet.h>     
#include <netdb.h>   
#include <netinet/in.h>   
#include <sys/types.h>   
#include <sys/socket.h>     
#include <unistd.h>  
#include <stdio.h>         
#include <stdlib.h>   
#include <string.h>   
#define CSocket int  
#endif   

class CSocketBase {
public:
    CSocketBase();
    virtual ~CSocketBase();
protected:
    void closeConnect(CSocket socket);
    bool error(CSocket socket);
    std::mutex m_mutex;
private:
    bool m_initSuccess;
};

#endif