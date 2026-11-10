#include "GetUartData.h"

void GetUartDataFun(void *p)
{
    GetUartData *pIp = (GetUartData*)p;

#ifdef __GCC_COMPILED__

	unint32 fifoCnt;
	unint32 i;
	unint32 numerror;

    unint08 obdhSendData[2];
	unint08 obdhRecvData[4];

	/* 发送取数指令 */
    obdhSendData[0] = 0xEB;
    obdhSendData[1] = 0x94;

    UartSend(pIp->uartno, &obdhSendData[0], 2);

	SYS_Delay(1000);

	/* 收数据 */
	pIp->bSucc = 0;

	UartRecv(pIp->uartno, pIp->data, &pIp->len, &numerror);

	if (pIp->data[0] == 0xE1)
	{
		pIp->bSucc = 0x1;
	}

#else
	/* 快仿环境下 */

#endif

    return;
}
