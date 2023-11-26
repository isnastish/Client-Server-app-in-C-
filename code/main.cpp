#include <winsock.h>

int main(int args_count, char** argv)
{
	WinSock win_sock;
	for (int address_index = 1; address_index < args_count; ++address_index)
	{
		win_sock.displayAddrInfo(argv[address_index]);
	}

	return 0;
}