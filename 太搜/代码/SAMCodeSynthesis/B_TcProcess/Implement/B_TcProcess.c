#include "B_TcProcess.h"

void B_TcProcessFun(void *p)
{
	B_TcProcess *pIp = (B_TcProcess*)p;

	unint08 chksum;
	unint08 i;

	chksum = 0;

	if ((pIp->tcaData[0] == 0xE1) && (pIp->tcaData[1] == 0x00))					/* 包头正确 */
	{
		for (i = 0; i < 3; i++)
		{
			chksum = chksum + pIp->tcaData[i];
		}

		if(pIp->tcaData[3] == chksum)
		{
			/* 校验和正确 */
			if(pIp->tcaData[2] == 0)
			{
				*pIp->workMode = SAM_DAMP;
			}
			else if(pIp->tcaData[2] == 1)
			{
				*pIp->workMode = SAM_CRUISE;
			}
			else
			{
				*pIp->workMode = NOCTRL;
			}
		}
	}
	return;
}
