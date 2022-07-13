#ifndef NETWORKING_H
#define NETWORKING_H

#include "Core.h"

#ifdef UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif // UNIX

#ifdef WINDOWS
#include <stdlib.h>
#include <WS2tcpip.h>
#include <Windows.h>
#endif // WINDOWS

#endif // NETWORKING_H