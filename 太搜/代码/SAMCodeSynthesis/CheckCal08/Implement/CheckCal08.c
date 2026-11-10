#include "CheckCal08.h"

void CheckCal08Fun(void *p)
{
    CheckCal08 *pIp = (CheckCal08*)p;

    unint32 i;

    pIp->chksum = 0;

    for (i = 0; i < pIp->len; i++)
    {
        pIp->chksum = pIp->chksum + pIp->pkv[i];
    }
    return;
}
