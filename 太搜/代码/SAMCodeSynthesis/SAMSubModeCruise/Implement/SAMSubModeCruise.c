#include "SAMSubModeCruise.h"

void SAMSubModeCruiseFun(void *p)
{
    SAMSubModeCruise *pIp = (SAMSubModeCruise*)p;

    if (*pIp->m_countMode == 4000)
    {
        pIp->CWsp = TRUE;
    }
    return;
}
