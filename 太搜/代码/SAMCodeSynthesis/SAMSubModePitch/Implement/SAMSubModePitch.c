#include "SAMSubModePitch.h"

void SAMSubModePitchFun(void *p)
{
    SAMSubModePitch *pIp = (SAMSubModePitch*)p;

    pIp->m_workMode = *pIp->m_curMode;  /* 当前模式赋值 */

    pIp->m_countMode ++;

    if (*pIp->flgSP == TRUE)                    /* 若SP标志为见太阳 */
    {
        if (Fabsx(*pIp->piyaw) > 1.0f)          /* 太敏俯仰测量角 > 1度 */
        {
            pIp->m_countPublic++;               /* 方式计数器 */

            if (pIp->m_countPublic > 12)        /* 持续12TS,则太阳搜索完成,转巡航 */
            {
                /* 转入SAM巡航方式 */
                pIp->m_workMode = SAM_CRUISE;   /* 置巡航方式字 */
                pIp->m_countMode = 0;           /* 清控制周期计数 */
                pIp->m_countPublic = 0;         /* 方式计数器 */
            }
            else
            {
                /* 清控制量 */
                pIp->outUp[0] = 0.0f ;
                pIp->outUp[1] = 0.0f ;
                pIp->outUp[2] = 0.0f ;
            }
        }
    }
    else
    {
       pIp->m_countPublic = 0;                  /* 方式计数器 */
    }

    if (pIp->m_countMode > 5625)                /* 若720秒太阳仍不出现,置ωx=0.5度/秒,ωy=0度/秒,转滚动搜索 */
    {
       pIp->m_workMode = SAM_ROLL;              /* 转入SAM滚动搜索方式 */
       pIp->m_countMode = 0;                    /* 控制周期计数器 */
       pIp->m_countPublic = 0;                  /* 方式计数器 */
    }

    return;
}
