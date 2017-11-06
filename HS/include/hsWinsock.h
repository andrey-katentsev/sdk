//
// File: hsWinsock.h
// Description: Windows Sockets utilities.
// Created: 4/7/2012
// Author: Andrey A. Katentsev
//
// Copyright (c) 2012, Hyperlink Software.
//

#pragma once
#include <string>
#include <winsock2.h>

std::string hsGetPeerIPv4(SOCKET peer);