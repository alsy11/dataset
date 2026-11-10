#include "LimitCtrlRateInput.h"

void LimitCtrlRateInputFun(void *p)
{
    LimitCtrlRateInput *pIp = (LimitCtrlRateInput*)p;

    pIp->Ud[0] = pIp->rate[0] - pIp->biasX ;    /* 角速度减偏置量 */
    pIp->Ud[1] = pIp->rate[1] - pIp->biasY ;    /* 角速度减偏置量 */
    pIp->Ud[2] = pIp->rate[2] ;                 /* Z轴角速度无偏置 */

    pIp->Ud[0] = LimitFloat(pIp->Ud[0], pIp->max) ;   /* 角速度限幅1.2° */
    pIp->Ud[1] = LimitFloat(pIp->Ud[1], pIp->max) ;
    pIp->Ud[2] = LimitFloat(pIp->Ud[2], pIp->max) ;

    return;
}
