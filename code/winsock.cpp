#include "winsock.h"

WinSock::WinSock()
{
	init();
}

WinSock::~WinSock()
{
	WSACleanup();
}

void WinSock::init() 
{
	int major = 2, minor = 2;
	if (int err = WSAStartup(MAKEWORD(major, minor), &m_wsa_data))
	{
		switch (err) 
		{
		case WSASYSNOTREADY:
		{
			std::fprintf(stderr, "error: failed to initialize windows sockets library. The underlying network subsystem is not ready for network communication.");
		}break;
		case WSAVERNOTSUPPORTED:
		{
			std::fprintf(stderr, "error: failed to initialize windows sockets library."
				"The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation.");
		}break;
		case WSAEINPROGRESS:
		{
			std::fprintf(stderr, "error: failed to initialize windows sockets library. A blocking Windows Sockets 1.1 operation is in progress.");
		}break;
		case WSAEPROCLIM:
		{
			std::fprintf(stderr, "error: failed to initialize windows sockets library. A limit on the number of tasks supported by the Windows Sockets implementation has been reached.");
		}break;
		case WSAEFAULT:
		{
			std::fprintf(stderr, "error: failed to initialize windows sockets library. 	The lpWSAData parameter is not a valid pointer.");
		}break;
		}

		exit(1);
	}

	if (LOBYTE(m_wsa_data.wVersion) < 2 ||
		HIBYTE(m_wsa_data.wVersion) < 2)
	{
		std::fprintf(stderr, "error: Current version: [%i.%i] is not supported.", major, minor);
		exit(2);
	}
}

void WinSock::displayVersion() const 
{
	std::ostringstream oss;

	int major_version = static_cast<int>(LOBYTE(m_wsa_data.wVersion));
	int minor_version = static_cast<int>(HIBYTE(m_wsa_data.wVersion));
	oss << "Version: " << std::setw(5) << major_version << "." << minor_version << "\n";
	
	std::cout << oss.str();
}

void WinSock::displayAddrInfo(const char* address) const
{
	ADDRINFO* p_addr_info;
	ADDRINFO hint_addr_info = {};
	hint_addr_info.ai_family = AF_UNSPEC; // either IPv4 or IPv6. For the former use AF_INET, for later AF_INET6
	hint_addr_info.ai_socktype = SOCK_STREAM; // SOCK_DGRAM, SOCK_RAW
	hint_addr_info.ai_protocol = IPPROTO_TCP; // IPPROTO_UDP, IPPROTO_RM

	int err = getaddrinfo(address, 0, &hint_addr_info, &p_addr_info);
	if (err)
	{
		std::fprintf(stderr, "error: failed to retrieve information for address: %s, with error: %i.\n", address, err);
		return;
	}

	std::cout << std::left << std::setw(25) << "Input address: " << address << "\n\n";
	for (auto* cur_addr_info = p_addr_info; cur_addr_info != 0; cur_addr_info = cur_addr_info->ai_next)
	{
		void* p_address = nullptr;
		std::ostringstream oss;

		oss << std::left;
		{
			oss << std::setw(25) << "\tIP address version: ";
			if (cur_addr_info->ai_family == AF_INET)
			{
				SOCKADDR_IN* p_sock_addr_ipv4 = reinterpret_cast<SOCKADDR_IN*>(cur_addr_info->ai_addr);
				p_address = &p_sock_addr_ipv4->sin_addr;
				oss << "IPv4\n";
			}
			else // AF_INET6
			{
				SOCKADDR_IN6* p_sock_addr_ipv6 = reinterpret_cast<SOCKADDR_IN6*>(cur_addr_info->ai_addr);
				p_address = &p_sock_addr_ipv6->sin6_addr;
				oss << "IPv6\n";
			}
		}

		{
			oss << std::setw(25) << "\tSocket type: ";
			if (cur_addr_info->ai_socktype == SOCK_STREAM)
			{
				oss << "SOCK_STREAM\n";
			}
			else if (cur_addr_info->ai_socktype == SOCK_DGRAM)
			{
				oss << "SOCK_DGRAM\n";
			}
			else if (cur_addr_info->ai_socktype == SOCK_RAW)
			{
				oss << "SOCK_RAW\n";
			}
		}

		{
			oss << std::setw(25) << "\tProtocol: ";
			if (cur_addr_info->ai_protocol == IPPROTO_TCP)
			{
				oss << "TCP\n";
			}
			else if (cur_addr_info->ai_protocol == IPPROTO_UDP)
			{
				oss << "UDP\n";
			}
		}

		// convert IPv4 or IPv6 from binary to a string in Internet standard format.
		char buf[1024] = {};
		if (!inet_ntop(cur_addr_info->ai_family, p_address, buf, sizeof(buf)))
		{
			std::fprintf(stderr, "error: inet_ntop failed!\n");
			continue;
		}

		oss << std::setw(25) << "\tIP Address: " << buf << "\n";
		std::cout << oss.str() << "\n\n";
	}
	freeaddrinfo(p_addr_info);
}