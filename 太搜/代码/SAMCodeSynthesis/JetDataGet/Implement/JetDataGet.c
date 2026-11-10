#include "JetDataGet.h"

void JetDataGetFun(void *p)
{
    JetDataGet *pIp = (JetDataGet*)p;
	unint32 i;

	if(UI32_BIT_GET(ADDR_READ(pIp->stateAddr), pIp->bitA) == 0x1)
	{
		for (i = 0; i < 12; i++)
		{
			pIp->stateFlag[i] = 1;
		}
	}
	else
	{
		for (i = 0; i < 12; i++)
		{
			pIp->stateFlag[i] = 0;
		}
	}

    return;
}
