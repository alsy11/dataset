#include "CheckCal.h"

void CheckCalFun(void *p)
{
    CheckCal *pIp = (CheckCal*)p;

    unint32 i;
    
    pIp->chksum = 0;

    for (i = 0; i < pIp->len; i++)
    {
        pIp->chksum = pIp->chksum + pIp->pkv[i];
    }
    return;
}
