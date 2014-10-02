//========================================================================
// Copyright (c) 2014 Yannick Pflanzer
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#if !defined(MHTTP_CONNECTION_H) && defined(USE_NETWORKING)
#define MHTTP_CONNECTION_H

#include <TCPInterface.h>
#include <HTTPConnection.h>
#include <MEngine.h>

class MHTTPConnection
{
    RakNet::TCPInterface m_tcp;
    RakNet::HTTPConnection m_connection;

    bool m_init;
    MString m_host;

    const char* connectionLoop();

public:
    MHTTPConnection(const char* host, int port);

    const char* sendPostRequest(const char* path, const char* data);
    const char* sendGetRequest(const char* path);
};

#endif