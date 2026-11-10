#include "GyroStateGet.h"

DEBUGXXX debugGyro;

void GyroStateGetFun(void *p)
{
    GyroStateGet *pIp = (GyroStateGet*)p;

#ifdef __GCC_COMPILED__

    unint32 i;
    unint32 fifoCnt;
    unint32 bSucc;
    unint08 gyroRecvData[48];
    unint08 gyroSendData[2];
    unint16 uidt ;
    unint32 len;
    unint32 numerror;
    unint32 sum = 0;
    USED_WORD tmpw;

    /* 发送陀螺取数指令 */
    gyroSendData[0] = 0xEB;
    gyroSendData[1] = 0x91;

    UartSend(pIp->uartno, &gyroSendData[0], 2);

    SYS_Delay(5000);

    /* 收数据 */
    bSucc = 0;
    len = 48;

    bSucc = UartRecv(pIp->uartno, &gyroRecvData[0], &len, &numerror);

    debugGyro.ErrCode = bSucc;

    if (bSucc != 0)
    {
        debugGyro.ErrCnt ++ ;
    }
    else
    {
        for (i = 0; i < 47; i++)
        {
            sum += gyroRecvData[i];
        }

        if ((sum & 0xFF) != gyroRecvData[47])
        {
            debugGyro.ErrCode = 0xCC;
            debugGyro.ErrCnt ++ ;
        }
    }

    /* 陀螺数据通讯处理 */
    for (i = 0; i < pIp->NumGyro; i++)
    {
        /* 陀螺脉冲计数1-9 */
        // tmpw.Byte.High_h = gyroRecvData[2+4*i];  /* 大小端 */
        // tmpw.Byte.High_l = gyroRecvData[3+4*i];
        // tmpw.Byte.Low_h  = gyroRecvData[4+4*i];
        // tmpw.Byte.Low_l  = gyroRecvData[5+4*i];
        tmpw.Byte.Low_l  = gyroRecvData[2+4*i];
        tmpw.Byte.Low_h  = gyroRecvData[3+4*i];
        tmpw.Byte.High_l = gyroRecvData[4+4*i];
        tmpw.Byte.High_h = gyroRecvData[5+4*i];
        pIp->wa[i] = tmpw.Float;
        // pIp->wa[i] = DIVIATION_TO_FLOAT_FOG((gyroRecvData[2 + i * 2] << 8) | (gyroRecvData[2 + i * 2 + 1]));

        /* 陀螺加电状态1-9 */
        pIp->stateFlag[i] = gyroRecvData[38 + i];
    }

#else
	/* 快仿环境下 */

#endif

    return;
}
