#include "NoctrlJudge.h"

void NoctrlJudgeFun(void *p)
{
    NoctrlJudge *pIp = (NoctrlJudge*)p;

    float32 fabsmax ;

    /* 姿态角速度有一个大于2度/秒 */
    fabsmax = TripleFabsMaxF( pIp->rate[0], pIp->rate[1], pIp->rate[2]) ;

    if (fabsmax > pIp->maxRate)
    {
        pIp->countAV++;

        if (pIp->countAV > 300)
        {
        	pIp->Wav = TRUE ;

    	}
    }
	else if(pIp->countAV > 0)
	{
		pIp->countAV--;
	}
	else
	{
        /* 特殊设计 */
	}
    return;
}
