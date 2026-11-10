#include "TMProcess.h"
#include "CheckCal16.h"
#include "SendUartData.h"

void TMProcessFun(void *p)
{
    TMProcess *pIp = (TMProcess*)p;

    unint16 chksum;
    unint32 i;
    unint08 pkv[32];    /* 遥测数据 */

    chksum = 0;

    for(i = 0; i < 32; i++)
    {
        pkv[i] = 0;
    }

    /* 打包包头 */
    pkv[0] = 0xD0;
    pkv[1] = 0xC1;

    /* 计算校验和 */
    chksum = 0;
    for (i = 0; i < 30u; i++)
    {
        chksum = chksum + pkv[i];
    }

    /* 校验和打包 */
    pkv[30] = (chksum >> 8u) & 0xFFu;
    pkv[31] = (chksum >> 0u) & 0xFFu;

    /* 遥测数据发送 */
    for (i = 0; i < 32; i++)
    {
        ADDR_WRITE(0x88D8, pkv[i]);
    }

    return;
}
