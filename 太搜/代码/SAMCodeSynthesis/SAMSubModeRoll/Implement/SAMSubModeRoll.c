#include "SAMSubModeRoll.h"

void SAMSubModeRollFun(void *p)
{
    SAMSubModeRoll *pIp = (SAMSubModeRoll*)p;

    pIp->m_workMode = *pIp->m_curMode;  /* 当前模式赋值 */

    pIp->m_countMode ++;

    if (*pIp->flgSP == TRUE)                    /* 若SP=1 */
    {
        if (*pIp->royaw > 1.0f)
        {
            pIp->m_countPublic++ ;              /* 方式计数器计数 */

            if (pIp->m_countPublic > 12)        /* 方式计数器13=2.08s > 2.048s */
            {
                pIp->m_workMode = SAM_CRUISE;
                pIp->m_countMode = 0 ;          /* 控制周期计数器 */
                pIp->m_countPublic = 0 ;        /* 方式计数器清零 */
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
        pIp->m_countPublic = 0 ;                /* 方式计数器清零 */
    }

    if (pIp->m_countMode > 6250)                /* 若800s太阳仍不出现,置ωx=0度/秒,ωy=-0.5度/秒,重新俯仰搜索 */
    {
        pIp->m_workMode = SAM_PITCH;
        pIp->m_countMode = 0;                   /* 控制周期计数器 */
        pIp->m_countPublic = 0;                 /* 方式计数器清零 */
    }

    return;
}
