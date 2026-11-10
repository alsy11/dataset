#include "LimitCtrlAngleInput.h"

void LimitCtrlAngleInputFun(void *p)
{
    LimitCtrlAngleInput *pIp = (LimitCtrlAngleInput*)p;

    pIp->Up[0] = pIp->angle[0] ;        /* 角度减偏置量，偏置量为0  */
    pIp->Up[1] = pIp->angle[1] ;        /* 角度减偏置量，偏置量为0  */
    pIp->Up[2] = 0.0f ;                 /* Z轴角度清零 */

    pIp->Up[0] = LimitFloat(pIp->Up[0], pIp->max) ;   /* 角度限幅8° */
    pIp->Up[1] = LimitFloat(pIp->Up[1], pIp->max) ;

    return;
}
