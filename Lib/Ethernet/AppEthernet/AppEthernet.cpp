#include "AppEthernet.h"

int32_t AppEthernetInit(void)
{
	MX_ETH_Init();
	if (MX_LWIP_Init()) {
		return -1;
	}

	return 0;
}
