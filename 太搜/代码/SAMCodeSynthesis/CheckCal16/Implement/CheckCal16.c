#include "CheckCal16.h"

void CheckCal16Fun(void *p)
{
    CheckCal16 *pIp = (CheckCal16*)p;

    unint32 i;

    pIp->chksum = 0;

    for (i = 0; i < pIp->len; i++)
    {
        pIp->chksum = pIp->chksum + pIp->pkv[i];
    }
    return;
}
