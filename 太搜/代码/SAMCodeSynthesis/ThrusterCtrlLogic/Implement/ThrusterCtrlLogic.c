#include "ThrusterCtrlLogic.h"

void ThrusterCtrlLogicFun(void *p)
{
    ThrusterCtrlLogic *pIp = (ThrusterCtrlLogic*)p;

    unint32 i;

    for (i = 0; i < 12; i++)
    {
        pIp->wPulse[i] = 0;         /* 控制量清零 */
    }

    if ( pIp->Yp[0] != 0)           /* 伪速率状态量 */
    {
        /* 软件喷气变量 */
        pIp->wPulse[0] = 1;
        pIp->wPulse[1] = 1;
    }

    if ( pIp->Yn[0] != 0)           /* 伪速率状态量 */
    {
        /* 软件喷气变量 */
        pIp->wPulse[2] = 1;
        pIp->wPulse[3] = 1;
    }

    if ( pIp->Yp[1] != 0)           /* 伪速率状态量 */
    {
        /* 软件喷气变量 */
        pIp->wPulse[4] = 1;
        pIp->wPulse[5] = 1;
    }

    if ( pIp->Yn[1] != 0)           /* 伪速率状态量 */
    {
        /* 软件喷气变量 */
        pIp->wPulse[6] = 1;
        pIp->wPulse[7] = 1;
    }

    if ( pIp->Yp[2] != 0)           /* 伪速率状态量 */
    {
        /* 软件喷气变量 */
        pIp->wPulse[8] = 1;
        pIp->wPulse[9] = 1;
    }

    if ( pIp->Yn[2] != 0)           /* 伪速率状态量 */
    {
        /* 软件喷气变量 */
        pIp->wPulse[10] = 1;
        pIp->wPulse[11] = 1;
    }

    return;
}
