#include "DSSDataGet.h"

DEBUGXXX debugDss;

void DSSDataGetFun(void *p)
{
	DSSDataGet *pIp = (DSSDataGet*)p;

#ifdef __GCC_COMPILED__

	unint32 len;
	unint32 numerror;
	unint32 bSucc = 0;
	unint08 dssSendData[2];
	unint08 dssRecvData[11];
	unint32 sum = 0, i;
	USED_WORD tmpw;

	/* 发送太阳取数指令 */
    dssSendData[0] = 0xEB;
    dssSendData[1] = 0x92;

    UartSend(pIp->uartno, &dssSendData[0], 2);

	SYS_Delay(1000);

	len = 11;
	bSucc = UartRecv(pIp->uartno, &dssRecvData[0], &len, &numerror);

	debugDss.ErrCode = bSucc;

	if (bSucc != 0)
    {
        debugDss.ErrCnt ++ ;
    }
    else
    {
        for (i = 0; i < 10; i++)
        {
            sum += dssRecvData[i];
        }

        if ((sum & 0xFF) != dssRecvData[10])
        {
            debugDss.ErrCode = 0xCC;
            debugDss.ErrCnt ++ ;
        }
    }

	// tmpw.Byte.High_h = dssRecvData[0];	/* 大小端 */
	// tmpw.Byte.High_l = dssRecvData[1];
	// tmpw.Byte.Low_h  = dssRecvData[2];
	// tmpw.Byte.Low_l  = dssRecvData[3];
	tmpw.Byte.Low_l  = dssRecvData[0];
	tmpw.Byte.Low_h  = dssRecvData[1];
	tmpw.Byte.High_l = dssRecvData[2];
	tmpw.Byte.High_h = dssRecvData[3];
	pIp->royaw = tmpw.Float;

	// tmpw.Byte.High_h = dssRecvData[4];	/* 大小端 */
	// tmpw.Byte.High_l = dssRecvData[5];
	// tmpw.Byte.Low_h  = dssRecvData[6];
	// tmpw.Byte.Low_l  = dssRecvData[7];
	tmpw.Byte.Low_l  = dssRecvData[4];
	tmpw.Byte.Low_h  = dssRecvData[5];
	tmpw.Byte.High_l = dssRecvData[6];
	tmpw.Byte.High_h = dssRecvData[7];
	pIp->piyaw = tmpw.Float;

	if ((dssRecvData[8] == 0x1) || (dssRecvData[9] == 0x1))
	{
		pIp->flgSP = 0x1;
	}
	else
	{
		pIp->flgSP = 0x0;
	}

#else
	/* 快仿环境下 */

#endif

	return;
}
