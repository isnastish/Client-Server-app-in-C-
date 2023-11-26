#ifndef WINSOCK_H

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <optional>

// NOTE: Don't differentiate between client and a server? Support config?

class Client 
{
	// TODO: Not Implemented
};

class Server
{
	// TODO: Not Implemented!
};

class WinSock
{
	void init();
public:
	WinSock();
	~WinSock();

	void displayVersion() const;
	void displayAddrInfo(const char *ip_address) const;
private:
	WSADATA m_wsa_data;
};

#endif // WINSOCK_H