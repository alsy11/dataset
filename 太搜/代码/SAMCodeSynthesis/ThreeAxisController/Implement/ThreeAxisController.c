#include "ThreeAxisController.h"

void ThreeAxisControllerFun(void *p)
{
    ThreeAxisController *pIp = (ThreeAxisController*)p;

    /* 角度限幅 */
    pIp->mController[0].Up = pIp->pAngle[0] ;           /* 角度减偏置量，偏置量为0  */
    pIp->mController[1].Up = pIp->pAngle[1] ;           /* 角度减偏置量，偏置量为0  */
    pIp->mController[2].Up = 0.0f ;                     /* Z轴角度清零 */

    pIp->mController[0].Up = LimitFloat(pIp->mController[0].Up, 8.0f) ;   /* 角度限幅8° */
    pIp->mController[1].Up = LimitFloat(pIp->mController[1].Up, 8.0f) ;

    /* 角速度限幅 */
    pIp->mController[0].Ud = pIp->pRate[0] - pIp->destRate[0] ;     /* 角速度减偏置量 */
    pIp->mController[1].Ud = pIp->pRate[1] - pIp->destRate[1] ;     /* 角速度减偏置量 */
    pIp->mController[2].Ud = pIp->pRate[2] ;                        /* Z轴角速度无偏置 */

    pIp->mController[0].Ud = LimitFloat(pIp->mController[0].Ud, 1.2f) ;   /* 角速度限幅1.2° */
    pIp->mController[1].Ud = LimitFloat(pIp->mController[1].Ud, 1.2f) ;
    pIp->mController[2].Ud = LimitFloat(pIp->mController[2].Ud, 1.2f) ;

    /* 三轴控制器计算 */
    pIp->mController[0].fy = pIp->mController[0].Up * pIp->CTRL_PARAM_SAM[0].Kp + pIp->mController[0].Ud * pIp->CTRL_PARAM_SAM[0].Kd;
    pIp->mController[1].fy = pIp->mController[1].Up * pIp->CTRL_PARAM_SAM[1].Kp + pIp->mController[1].Ud * pIp->CTRL_PARAM_SAM[1].Kd;
    pIp->mController[2].fy = pIp->mController[2].Ud * pIp->CTRL_PARAM_SAM[2].Kd;

    /* 控制器输出限幅,伪速率调制器输入,即控制器输出 */
    pIp->u[0] = LimitFloat(pIp->mController[0].fy, 1.3f); /* 伪速率状态量 */
    pIp->u[1] = LimitFloat(pIp->mController[1].fy, 1.3f); /* 伪速率状态量 */
    pIp->u[2] = LimitFloat(pIp->mController[2].fy, 1.3f); /* 伪速率状态量 */

    return;
}
