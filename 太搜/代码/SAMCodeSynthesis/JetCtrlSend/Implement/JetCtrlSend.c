#include "JetCtrlSend.h"

void JetCtrlSendFun(void *p)
{
    JetCtrlSend *pIp = (JetCtrlSend*)p;

#ifdef __GCC_COMPILED__

    unint08 sendBuf[10];
    unint08 wPulse = 0;

    if ( (pIp->pulse[0] == 1) || (pIp->pulse[1] == 1) )
    {
        wPulse = wPulse | 0x04 ;    /* 软件喷气变量 */
    }

    if ( (pIp->pulse[2] == 1) || (pIp->pulse[3] == 1) )
    {
        wPulse = wPulse | 0x08 ;    /* 软件喷气变量 */
    }

    if ( (pIp->pulse[4] == 1) || (pIp->pulse[5] == 1) )
    {
        wPulse = wPulse | 0x10 ;    /* 软件喷气变量 */
    }

    if ( (pIp->pulse[6] == 1) || (pIp->pulse[7] == 1) )
    {
        wPulse = wPulse | 0x20 ;    /* 软件喷气变量 */
    }

    if ( (pIp->pulse[8] == 1) || (pIp->pulse[9] == 1) )
    {
        wPulse = wPulse | 0x40 ;    /* 软件喷气变量 */
    }

    if ( (pIp->pulse[10] == 1) || (pIp->pulse[11] == 1) )
    {
        wPulse = wPulse | 0x80 ;    /* 软件喷气变量 */
    }

    sendBuf[0] = 0xEB;
    sendBuf[1] = 0x93;
    sendBuf[2] = wPulse;

    UartSend(pIp->uartno, &sendBuf[0], 3);

#else
	/* 快仿环境下 */

#endif

    return;
}