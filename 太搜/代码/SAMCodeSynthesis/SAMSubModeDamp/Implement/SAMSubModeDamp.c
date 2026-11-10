#include "SAMSubModeDamp.h"

/* SAM速率阻尼方式 */
void SAMSubModeDampFun(void *p)
{
    SAMSubModeDamp *pIp = (SAMSubModeDamp*)p;

    float32 fabsmax;                                /* 临时：绝对值最大 */

    pIp->m_workMode = *pIp->m_curMode;  /* 当前模式赋值 */
    pIp->m_countMode ++;

    fabsmax = TripleFabsMaxF( pIp->pRate[0], pIp->pRate[1], pIp->pRate[2] ) ;/* 求三轴姿态角速度最大值 */

    if ( fabsmax < 0.15f )                          /* 三轴姿态角速度均小于0.15度/秒 */
    {
        pIp->m_countPublic++ ;                      /* 方式计数器 */
    }

    /* 若700Ts角速度都小于0.07度/s 或 速率阻尼持续时间大于128秒时,置俯仰角速度偏置为-0.5度/s, 转入俯仰搜索 */
    if (( pIp->m_countPublic > pIp->time_D2P ) || ( pIp->m_countMode > pIp->time_D2P_overtime ))
    {
        pIp->m_workMode = SAM_PITCH;

        pIp->m_countMode = 0 ;                      /* 清控制周期计数器 */
        pIp->m_countPublic = 0 ;                    /* 方式计数器 */
    }

    return;
}
