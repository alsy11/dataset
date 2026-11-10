#include "SendUartData.h"

void SendUartDataFun(void *p)
{
    SendUartData *pIp = (SendUartData*)p;

#ifdef __GCC_COMPILED__

    UartSend(pIp->uartno, pIp->buf, pIp->sendsize);

#else
	/* 快仿环境下 */

#endif

    return;
}
