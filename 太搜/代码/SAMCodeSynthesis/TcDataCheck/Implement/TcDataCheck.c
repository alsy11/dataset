#include "TcDataCheck.h"

void TcDataCheckFun(void *p)
{
    TcDataCheck *pIp = (TcDataCheck*)p;

    unint32 i;
    unint32 chksum = 0;

    pIp->ret = 0;

    if ((pIp->data[0] == 0xE1) && (pIp->data[1] == 0x00))	/* 包头正确 */
    {
        for (i = 0; i < 3; i++)
        {
            chksum = chksum + pIp->data[i];
        }

        if(pIp->data[3] == chksum)
        {
            pIp->ret = 1;
        }
    }

    return;
}
