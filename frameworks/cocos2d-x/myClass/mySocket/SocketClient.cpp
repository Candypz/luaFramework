#include "SocketClient.h"

CSocketClient::CSocketClient():
onRecv(nullptr),
m_socketClient(0){

}

CSocketClient::~CSocketClient() {
    if (m_socketClient) {
        m_mutex.lock();
        closeConnect(m_socketClient);
        m_mutex.unlock();
    }
}

bool CSocketClient::initClient() {
    if (m_socketClient) {
        m_mutex.lock();
        closeConnect(m_socketClient);
        m_mutex.unlock();
    }
    m_socketClient = socket(AF_INET, SOCK_STREAM, 0);

    if (error(m_socketClient)) {
        printf("init socketClient error");
        m_socketClient = 0;
        return false;
    }

    return true;
}

bool CSocketClient::connectServer(const char *serverIp, unsigned short port) {
    if (!initClient()) {
        return false;
    }

    struct sockaddr_in _serverAddr;
    memset(&_serverAddr, 0, sizeof(struct sockaddr_in));

    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(port);
    _serverAddr.sin_addr.s_addr = inet_addr(serverIp);

    int _ret = 0;
    _ret = connect(m_socketClient, (struct sockaddr*)&_serverAddr, sizeof(struct sockaddr));
    if (_ret < 0) {
        closeConnect(m_socketClient);
        m_socketClient = 0;
        printf("connectServer error");
        return false;
    }

    std::thread _recvThread(&CSocketClient::recvMessage, this);
    _recvThread.detach();

    return true;
}

void CSocketClient::recvMessage() {
    char _recvBuf[65535] = { 0 };
    int _ret = 0;
    while (true) {
        _ret = recv(m_socketClient, _recvBuf, sizeof(_recvBuf), 0);
        if (_ret < 0) {
            printf("recv error");
            break;
        }
        if (_ret > 0 && onRecv != nullptr) {
            onRecv(_recvBuf, _ret);
        }
    }
    m_mutex.lock();
    closeConnect(m_socketClient);
    if (onDisconnect != nullptr) {
        onDisconnect();
    }
    m_socketClient = 0;
    m_mutex.unlock();
}

void CSocketClient::sendMessage(const char *data, int count) {
    if (m_socketClient != 0) {
        int _ret = send(m_socketClient, data, count, 0);
        if (_ret < 0) {
            printf("sendMessage error");
        }
    }
}

void CSocketClient::closeSocket() {
    if (m_socketClient != 0) {
        m_mutex.lock();
        closeConnect(m_socketClient);
        m_mutex.lock();
    }
}