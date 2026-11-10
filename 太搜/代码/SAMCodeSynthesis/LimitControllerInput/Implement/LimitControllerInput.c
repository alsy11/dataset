#include "LimitControllerInput.h"

void LimitControllerInputFun(void *p)
{
    LimitControllerInput *pIp = (LimitControllerInput*)p;

    /* 角度限幅 */
    pIp->Up[0] = pIp->angle[0] ;        /* 角度减偏置量，偏置量为0  */
    pIp->Up[1] = pIp->angle[1] ;        /* 角度减偏置量，偏置量为0  */
    pIp->Up[2] = 0.0f ;                 /* Z轴角度清零 */

    pIp->Up[0] = LimitFloat(pIp->Up[0], pIp->angLimit) ;  /* 角度限幅 */
    pIp->Up[1] = LimitFloat(pIp->Up[1], pIp->angLimit) ;

    /* 角速度限幅 */
    pIp->Ud[0] = pIp->rate[0] - pIp->bias[0] ;  /* 角速度减偏置量 */
    pIp->Ud[1] = pIp->rate[1] - pIp->bias[1] ;  /* 角速度减偏置量 */
    pIp->Ud[2] = pIp->rate[2] ;                 /* Z轴角速度无偏置 */

    pIp->Ud[0] = LimitFloat(pIp->Ud[0], pIp->veloLimit) ; /* 角速度限幅 */
    pIp->Ud[1] = LimitFloat(pIp->Ud[1], pIp->veloLimit) ;
    pIp->Ud[2] = LimitFloat(pIp->Ud[2], pIp->veloLimit) ;

    return;
}
