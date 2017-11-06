//
// File: hsWinsock.cpp
// Description: Windows Sockets utilities.
// Created: 4/7/2012
// Author: Andrey A. Katentsev
//
// Copyright (c) 2012, Hyperlink Software.
//

#include "hsWinsock.h"

std::string hsGetPeerIPv4(SOCKET peer)
{
	std::string szPeerIP;
	SOCKADDR_IN service = {0};
 size_t nSize = sizeof(service);

	szPeerIP.clear();
 if(0 == getpeername(peer, reinterpret_cast<SOCKADDR*>(&service), reinterpret_cast<int*>(&nSize))) // 0 == SUCCESS : SOCKET_ERROR
	{
		szPeerIP.reserve(16);
		szPeerIP = inet_ntoa(service.sin_addr);
	}

 return szPeerIP;
}