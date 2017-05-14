/************************************************* 
Author: candy_pz
Email: candy_pz@outlook.com
FileName: SocketClient.h
Date: 2016-8-31
Description: 客户端socket
**************************************************/

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include "SocketBase.h"

class CSocketClient :public CSocketBase{
public:
    CSocketClient();
    virtual ~CSocketClient();

    bool connectServer(const char *serverIp, unsigned short port);
    void sendMessage(const char *data, int count);
    void closeSocket();

    std::function<void(const char *data, int count)> onRecv; //接收回调
    std::function<void()> onDisconnect; //断开回调
private:
    bool initClient();
    void recvMessage();

    CSocket m_socketClient;
};

#endif