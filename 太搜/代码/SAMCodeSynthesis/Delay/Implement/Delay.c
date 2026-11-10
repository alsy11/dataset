#include "Delay.h"

void DelayFun(void *p)
{
    Delay *pIp = (Delay*)p;
    unint16 uidt ;

    for (uidt = 0; uidt < pIp->delaytime; uidt++)
    {
        ;
    }

    return;
}
