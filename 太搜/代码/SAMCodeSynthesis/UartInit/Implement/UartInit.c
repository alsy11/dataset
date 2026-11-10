#include "UartInit.h"

void UartInitFun(void *p)
{
    UartInit *pIp = (UartInit*)p;
#ifdef __GCC_COMPILED__
	Drv_Uart_Init(pIp->uartno, pIp->baud, pIp->even, pIp->stop);
#else
	/* 快仿环境下 */
#endif
	return;
}
