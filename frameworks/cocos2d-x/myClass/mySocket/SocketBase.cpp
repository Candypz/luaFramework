#include "SocketBase.h"

CSocketBase::CSocketBase() {
    m_initSuccess = false;
#if (MY_PLATFORM_WIN32 == MY_PLATFORM_WIN32)  
    WORD wVersionRequested;
    wVersionRequested = MAKEWORD(2, 0);
    WSADATA wsaData;
    int nRet = WSAStartup(wVersionRequested, &wsaData);
    if (nRet != 0) {
        fprintf(stderr, "Initilize Error!\n");
        return;
    }
    m_initSuccess = true;
#endif  
}

CSocketBase::~CSocketBase() {
#if (MY_PLATFORM_WIN32 == MY_PLATFORM_WIN32)  
    if (m_initSuccess) {
        WSACleanup();
    }
#endif  
}

void CSocketBase::closeConnect(CSocket socket) {
#if (MY_PLATFORM_WIN32 == MY_PLATFORM_WIN32)
	closesocket(socket);
#else
	close(socket);
#endif
}

bool CSocketBase::error(CSocket socket) {
#if (MY_PLATFORM_WIN32 == MY_PLATFORM_WIN32)  
    return socket == SOCKET_ERROR;
#else
    return socket < 0;
#endif  
}