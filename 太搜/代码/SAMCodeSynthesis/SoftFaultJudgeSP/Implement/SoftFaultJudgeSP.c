#include "SoftFaultJudgeSP.h"

void SoftFaultJudgeSPFun(void *p)
{
    SoftFaultJudgeSP *pIp = (SoftFaultJudgeSP*)p;

    //if (pIp->flgSp == 0)     							/* SP = 0 太阳不可见*/
    //{
    //	pIp->countSPLost++ ;							/* 太阳不可见计数器加1 */
    //	pIp->countSPSeen = 0 ;							/* 太阳临时不可见计数器清零  */
    //}
    //else
    //{
    //	if (pIp->countSPLost != 0)    					/* 太阳一次不可见 */
    //	{
    //		pIp->countSPSeen++ ;						/* 太阳临时不可见计数器自加 */
    //	}

    //	if (pIp->countSPSeen > 2)  					/* 太阳连续两次不可见 */
    //	{
    //		pIp->countSPLost = 0 ;						/* 太阳不可见计数器清零 */
    //		pIp->countSPSeen = 0 ;						/* 太阳临时不可见计数器清零  */
    //	}
    //}

    ///* 太阳丢失持续33750周期 */
    //if (pIp->countSPLost > pIp->lostThr)
    //{
    //	pIp->Wsp = TRUE ;
    //	pIp->countSPLost = 0 ;
    //	pIp->countSPset = 0 ;							/* 清切换太敏计数器 */
    //}

    return;
}
